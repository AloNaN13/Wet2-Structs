
#include "MusicManager.h"

MusicManager::~MusicManager(){
    this->artists_in_system.deleteHashArtists();
}

MMStatusType MusicManager::MMAddArtist(int artistID){
    try {
        if (artistID <= 0) {
            return MM_INVALID_INPUT;
        }
        if (this->artists_in_system.hashFindNode(artistID)) {
            return MM_FAILURE;
        }

        Artist* artist_to_insert = new Artist(artistID);
        ListNode* node_to_insert = new ListNode(artist_to_insert);
        this->artists_in_system.hashInsertNode(node_to_insert);
        //check hashResult?

        this->total_num_of_artists++;

        //expand the hash table if needed
        if(this->total_num_of_artists == this->artists_in_system.getHashTableSize()){
            this->artists_in_system.expandHash();
            // check hashResult?
        }

        // put in IF statement if we check the Result
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

        delete(this->artists_in_system.hashFindNode(artistID)->getArtistFromNode());
        this->artists_in_system.hashRemoveNode(artistID);
        //check hashResult?

        this->total_num_of_artists--;

        //shrink the hash table if needed
        if(this->total_num_of_artists == (this->artists_in_system.getHashTableSize()/4)){
            this->artists_in_system.shrinkHash();
            // check hashResult?
        }

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
        int* num_of_streams = new int(0);
        ArtistResult res = artist->removeSong(songID, num_of_streams);
        if(res == ARTIST_KEY_DOESNT_EXISTS){
            return MM_FAILURE;
        }

        // remove song with from songs_of_system
        TreeSet treeset_to_remove(*num_of_streams, artistID, songID);
        AvlTreeResult res2 = this->songs_of_system.remove(treeset_to_remove);
        if(res2 == AVL_KEY_DOESNT_EXISTS){
            return MM_FAILURE;
        }

        delete num_of_streams;

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
