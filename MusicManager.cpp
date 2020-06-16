
#include "MusicManager.h"

MMStatusType MusicManager::MMAddArtist(int artistID){

    try {
        if (artistID <= 0) {
            return MM_INVALID_INPUT;
        }
        if (this->artists_in_system.hashFindNode(artistID)) {
            return MM_FAILURE;
        }


        if(this->total_num_of_artists == this->artists_in_system.getHashTableSize()){
            this->artists_in_system.expandHash();
            // check hashResult?
        }
        else if(this->total_num_of_artists == (this->artists_in_system.getHashTableSize()/4)
                && this->artists_in_system.getHashTableSize()>=4){
            this->artists_in_system.shrinkHash();
            // check hashResult?
        }


        Artist* artist_to_insert = new Artist(artistID);
        ListNode* node_to_insert = new ListNode(artist_to_insert);
        this->artists_in_system.hashInsertNode(node_to_insert);
        //check hashResult?

        // put in IF statement if we check the Result
        this->total_num_of_artists++;

        return MM_SUCCESS;

    }catch (...){
        return MM_ALLOCATION_ERROR;
    }

}



MMStatusType MusicManager::MMRemoveArtist(int artistID){

    try {
        if (artistID <= 0) {
            return MM_INVALID_INPUT;
        }
        if (!(this->artists_in_system.hashFindNode(artistID)) ||
            (this->artists_in_system.hashFindNode(artistID)->getArtistFromNode()->GetTotalNumOfSongs()>0)) {
            return MM_FAILURE;
        }


        if(this->total_num_of_artists == this->artists_in_system.getHashTableSize()){
            this->artists_in_system.expandHash();
            // check hashResult?
        }
        else if(this->total_num_of_artists == (this->artists_in_system.getHashTableSize()/4)){
            this->artists_in_system.shrinkHash();
            // check hashResult?
        }


        delete(this->artists_in_system.hashFindNode(artistID)->getArtistFromNode());
        this->artists_in_system.hashRemoveNode(artistID);
        //check hashResult?

        this->total_num_of_artists--;
        return MM_SUCCESS;

    }catch (...){
        return MM_ALLOCATION_ERROR;
    }

}

MMStatusType MusicManager::MMAddSong(int artistID, int songID){

    try {
        if (artistID <= 0 || songID <= 0) {
            return MM_INVALID_INPUT;
        }
        if (!(this->artists_in_system.hashFindNode(artistID))) {
            return MM_FAILURE;
        }

        // add song to artist
        Artist* artist = this->artists_in_system.hashFindNode(artistID)->getArtistFromNode();
        ArtistResult res = artist->addSong(songID);
        if(res == ARTIST_KEY_ALREADY_EXISTS){
            return MM_FAILURE;
        }

        // add song with 0 streams to songs_of_system
        // CHECK WITH AVITAL IF CORRECT
        TreeSet treeset_to_add(0, artistID, songID);

        AvlTreeResult res2 = this->songs_of_system.insert(treeset_to_add, treeset_to_add);
        if(res2 == AVL_KEY_ALREADY_EXISTS){
            return MM_FAILURE;
        }

        this->total_num_of_songs++;
        return MM_SUCCESS;

    }catch (...){
        return MM_ALLOCATION_ERROR;
    }

}

MMStatusType MusicManager::MMRemoveSong(int artistID, int songID){

    try {
        if (artistID <= 0 || songID <= 0) {
            return MM_INVALID_INPUT;
        }
        if (!(this->artists_in_system.hashFindNode(artistID))) {
            return MM_FAILURE;
        }

        // remove song from artist
        Artist* artist = this->artists_in_system.hashFindNode(artistID)->getArtistFromNode();
        int* num_of_streams;
        ArtistResult res = artist->removeSong(songID, num_of_streams);
        if(res == ARTIST_KEY_DOESNT_EXISTS){
            return MM_FAILURE;
        }

        // remove song with from songs_of_system
        // CHECK WITH AVITAL IF CORRECT
        TreeSet treeset_to_remove(*num_of_streams, artistID, songID);
        AvlTreeResult res2 = this->songs_of_system.remove(treeset_to_remove);
        if(res2 == AVL_KEY_DOESNT_EXISTS){
            return MM_FAILURE;
        }

        this->total_num_of_songs--;
        return MM_SUCCESS;

    }catch (...){
        return MM_ALLOCATION_ERROR;
    }

}

MMStatusType MusicManager::MMAddToSongCount(int artistID, int songID, int count) {
    if(artistID<=0||songID<=0||count<=0){
        return MM_INVALID_INPUT;
    }
    if(this->artists_in_system.hashFindNode(artistID) == nullptr){
        return MM_FAILURE;
    }
    Artist* wanted_artist=artists_in_system.hashFindNode(artistID)->getArtistFromNode();
    int pre_adding_streams = 0;
    ArtistResult result=wanted_artist->addToSongCount(songID,count,&pre_adding_streams);
    if(result==ARTIST_KEY_DOESNT_EXISTS){
        return MM_FAILURE;
    }
    TreeSet preeThreeSet(pre_adding_streams,artistID,songID);
    songs_of_system.remove(preeThreeSet);
    TreeSet after_adding_count(pre_adding_streams+count,artistID,songID);
    songs_of_system.insert(after_adding_count,after_adding_count);
    return MM_SUCCESS;
}


MMStatusType MusicManager::MMGetArtistBestSong(int artistID, int *songId) {
    if (artistID <= 0 || songId == nullptr) {
        return MM_INVALID_INPUT;
    }
    if (!(this->artists_in_system.hashFindNode(artistID)) ||
        (this->artists_in_system.hashFindNode(artistID)->getArtistFromNode()->GetTotalNumOfSongs()<=0)) {
        return MM_FAILURE;
    }
    this->artists_in_system.hashFindNode(artistID)->getArtistFromNode()->getArtistBestSong(songId);
    return MM_SUCCESS;
}

MMStatusType MusicManager::MMGetRecommendedSongInPlace(int rank, int *artistId, int *songId) {
    if(rank <=0 || artistId == nullptr || songId == nullptr){
        return MM_INVALID_INPUT;
    }
    if(rank > total_num_of_songs){
        return MM_FAILURE;
    }
    ///need to use rank of tree
    TreeSet* wanted_rank = songs_of_system.getNodeInRank(rank);
    *artistId = wanted_rank->getArtistID();
    *songId = wanted_rank->getSongID();
    return MM_SUCCESS;
}



/* OLD CODE FROM WET1



#include "MusicManager.h"


MMStatusType MusicManager:: MMAddArtist( int artistID, int numOfSongs){

    try {
        if (artistID <= 0 || numOfSongs <= 0) {
            return MM_INVALID_INPUT;
        }

        AvlTree<Artist, int> &tree = this->MMGetArtistsTree();

        if (tree.findKeyAlreadyExists(artistID)) {
            return MM_FAILURE;
        }

        Artist artist_to_add(artistID, numOfSongs);


        StreamList &list = this->MMGetListOfStreams();
        StreamListNode *zero_streams_node = list.GetListFirstNode();
        // all songs now point to the "0" streams node
        for (int i = 0; i < artist_to_add.GetTotalNumOfSongs(); i++) {
            artist_to_add.SetStreamsNumForSong(i, zero_streams_node);
        }

        // insert artist into songs
        tree.insert(artist_to_add, artistID);

        // insert pointer to the artist in "0" node AVLTree
        AvlTree<AvlTree<int, int> *, int> &node_tree = zero_streams_node->getNodeAvlTree();
        node_tree.insert((tree.getElementptr(artistID)->GetNumOfStreamsTree().getFirst()), artistID);

        this->totalNumOfSongs = this->totalNumOfSongs + numOfSongs;
        return MM_SUCCESS;
    }catch (...){
        return MM_ALLOCATION_ERROR;
    }

}

MMStatusType MusicManager::MMRemoveArtist(int artistID){

    try {

        if (artistID <= 0) {
            return MM_INVALID_INPUT;
        }

        AvlTree<Artist, int> &tree = this->MMGetArtistsTree();
        if (!(tree.findKeyAlreadyExists(artistID))) {
            return MM_FAILURE;
        }
        Artist *artist = tree.getElementptr(artistID);

        StreamListNode *num_node;
        AvlTree<int, int> *songs_to_null_tree = nullptr;
        for (int i = 0; i < artist->GetTotalNumOfSongs(); i++) {
            num_node = artist->GetSongNumOfStreamsNode(i);
            if (num_node == nullptr) {
                continue;
            }
            AvlTree<AvlTree<int, int> *, int> &num_node_tree = num_node->getNodeAvlTree();
            songs_to_null_tree = *(num_node_tree.getElementptr(artistID));
            int *curr_song = songs_to_null_tree->getFirst();
            while (curr_song != nullptr) {
                int *next_song = songs_to_null_tree->getNext();
                artist->SetStreamsNumForSong(*curr_song, nullptr);
                curr_song = next_song;
            }
            num_node_tree.remove(artistID);
            if (num_node->GetNodeNumOfStreams() != 0) {
                if (num_node_tree.getFirst() == nullptr) {
                    this->MMGetListOfStreams().removeNode(num_node);
                }
            }
        }
        int num_songs_of_artist = artist->GetTotalNumOfSongs();
        tree.remove(artistID);

        this->totalNumOfSongs = this->totalNumOfSongs - num_songs_of_artist;
        return MM_SUCCESS;
    }catch (...){
        return MM_ALLOCATION_ERROR;
    }

}

MMStatusType  MusicManager::MMAddToSongCount(int artistID, int songID){

    try {

        if (artistID <= 0 || songID < 0) {
            return MM_INVALID_INPUT;
        }

        AvlTree<Artist, int> &tree = this->MMGetArtistsTree();
        if (!(tree.findKeyAlreadyExists(artistID))) {
            return MM_FAILURE;
        }

        //get the tree, the artist and the list
        Artist *artist = tree.getElementptr(artistID);
        if (artist->GetTotalNumOfSongs() <= songID) {
            return MM_INVALID_INPUT;
        }

        //StreamList& list_of_streams = this->MMGetListOfStreams();
        AvlTree<int, int> *node_to_point_to = nullptr;
        StreamListNode *stream_list_node_to_point_to = nullptr;

        //change in the ArtistsTree
        AvlTree<AvlTree<int, int>, int> &num_of_streams_tree = artist->GetNumOfStreamsTree();
        StreamListNode *num_of_streams_list_node = artist->GetSongNumOfStreamsNode(songID);
        int songs_num_of_streams = num_of_streams_list_node->GetNodeNumOfStreams();
        // remove song node
        AvlTree<int, int> &num_of_streams_tree_node = *(num_of_streams_tree.getElementptr(songs_num_of_streams));
        num_of_streams_tree_node.remove(songID);

        bool should_remove_stream_node = false;
        if (num_of_streams_tree_node.getFirst() == nullptr) {
            should_remove_stream_node = true;
            num_of_streams_tree.remove(songs_num_of_streams);
        }
        // insert song to the next num_of_streams node
        if (num_of_streams_tree.findKeyAlreadyExists(songs_num_of_streams + 1)) {
            num_of_streams_tree.getElementptr(songs_num_of_streams + 1)->insert(songID, songID);
        } else {
            AvlTree<int, int> new_songs_tree = AvlTree<int, int>();
            new_songs_tree.insert(songID, songID);
            num_of_streams_tree.insert(new_songs_tree, songs_num_of_streams + 1);
            node_to_point_to = num_of_streams_tree.getElementptr(songs_num_of_streams + 1);
        }

        // change in the List
        StreamListNode *num_of_streams_list_next_node = num_of_streams_list_node->getNextNode();
        if (num_of_streams_list_next_node != nullptr && num_of_streams_list_next_node->GetNodeNumOfStreams()
                                                        == songs_num_of_streams + 1) {
            AvlTree<AvlTree<int, int> *, int> &num_of_streams_list_next_node_tree =
                    num_of_streams_list_next_node->getNodeAvlTree();
            num_of_streams_list_next_node_tree.insert(node_to_point_to, artistID);
            stream_list_node_to_point_to = num_of_streams_list_next_node;
        } else {
            AvlTree<AvlTree<int, int> *, int> &new_node_tree = *(new AvlTree<AvlTree<int, int> *, int>());
            new_node_tree.insert(node_to_point_to, artistID);
            list_of_streams.insertNode(num_of_streams_list_node, new_node_tree, songs_num_of_streams + 1);
            stream_list_node_to_point_to = num_of_streams_list_node->getNextNode();
        }

        // remove the artist's node from the original node's tree
        if (should_remove_stream_node) {
            AvlTree<AvlTree<int, int> *, int> &num_of_streams_list_node_tree = num_of_streams_list_node->getNodeAvlTree();
            num_of_streams_list_node_tree.remove(artistID);
            if (num_of_streams_list_node->GetNodeNumOfStreams() != 0) {
                if (num_of_streams_list_node_tree.getFirst() == nullptr) {
                    list_of_streams.removeNode(num_of_streams_list_node);
                }
            }
        }

        // change in the songs array
        artist->SetStreamsNumForSong(songID, stream_list_node_to_point_to);

        return MM_SUCCESS;
    }catch (...){
        return MM_ALLOCATION_ERROR;
    }

}

MMStatusType  MusicManager:: MMNumberOfStreams(int artistID, int songID, int* streams){

    try {


        if (artistID <= 0 || streams == nullptr || songID < 0) {
            return MM_INVALID_INPUT;
        }

        AvlTree<Artist, int> &tree = this->MMGetArtistsTree();
        if (!(tree.findKeyAlreadyExists(artistID))) {
            return MM_FAILURE;
        }

        Artist &artist = *(tree.getElementptr(artistID));
        if (artist.GetTotalNumOfSongs() <= songID) {
            return MM_INVALID_INPUT;
        }
        StreamListNode *num_node = artist.GetSongNumOfStreamsNode(songID);

        int num = num_node->GetNodeNumOfStreams();
        *streams = num;

        return MM_SUCCESS;
    }catch (...){
        return MM_ALLOCATION_ERROR;
    }

}

MMStatusType MusicManager:: MMgetRecommendedSongs( int numOfSongs, int* artists, int* songs){
    try {

        if (numOfSongs <= 0) {
            return MM_ALLOCATION_ERROR;
        }
        if (numOfSongs > totalNumOfSongs) {
            return MM_FAILURE;
        }
        StreamListNode *current_Node_of_hearings = list_of_streams.GetListLastNode();
        int count = 0;;
        //Artist* currentArtist;
        AvlTree<int, int> *songs_of_current_artist_with_num_streams;
        int *song;
        int current_ArtistId;
        while (count < numOfSongs) {
            //int numStreams=0;
            songs_of_current_artist_with_num_streams = *(((current_Node_of_hearings->getNodeAvlTree())).getFirst());

            while (count < numOfSongs && songs_of_current_artist_with_num_streams) {
                song = songs_of_current_artist_with_num_streams->getFirst();
                current_ArtistId = (current_Node_of_hearings->getNodeAvlTree()).getKey();
                while (song && count < numOfSongs) {
                    artists[count] = current_ArtistId;
                    songs[count] = songs_of_current_artist_with_num_streams->getKey();

                    count++;
                    song = songs_of_current_artist_with_num_streams->getNext();
                }

                AvlTree<int, int> **tmp = (current_Node_of_hearings->getNodeAvlTree()).getNext();
                if (tmp) {
                    songs_of_current_artist_with_num_streams = *tmp;
                } else {
                    songs_of_current_artist_with_num_streams = nullptr;
                }
                // songs_of_current_artist_with_num_streams=*((current_Node_of_hearings->getNodeAvlTree()).getNext());
            }
            current_Node_of_hearings = current_Node_of_hearings->getPrevNode();
        }
        return MM_SUCCESS;
    }catch (...){
        return MM_ALLOCATION_ERROR;
    }

}

*/