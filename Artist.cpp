






#include "Artist.h"



ArtistResult Artist::addSong(int song_id) {
    AvlTreeResult result=songs_tree.insert(0,song_id);
    if(result == AVL_KEY_ALREADY_EXISTS){
        return ARTIST_KEY_ALREADY_EXISTS;
    }
    //it was successfull
    total_num_of_songs++;
    Pair new_pair(0,song_id);
    streams_tree.insert(song_id,new_pair);
    return ARTIST_SUCCESS;
}

ArtistResult Artist::removeSong(int song_id, int* num_of_streams) {
    *num_of_streams=*(songs_tree.getElementptr(song_id));
    int* current_streams_of_song=songs_tree.getElementptr(song_id);
    if(current_streams_of_song == nullptr){//there is no such song under the artist
        return ARTIST_KEY_DOESNT_EXISTS;
    }
    Pair pair_of_song(*current_streams_of_song,song_id);
    songs_tree.remove(song_id);
    streams_tree.remove(pair_of_song);
    total_num_of_songs--;
    return ARTIST_SUCCESS;
}

ArtistResult Artist::addToSongCount(int song_id, int count, int* initial_streams) {
    int* pre_count=songs_tree.getElementptr(song_id);
    int* if_song_exists = songs_tree.getElementptr(song_id);
    if(pre_count== nullptr || if_song_exists == nullptr){
        return ARTIST_KEY_DOESNT_EXISTS;
    }
    *initial_streams=*(songs_tree.getElementptr(song_id));

    int pre=*pre_count;

    Pair old_pair(pre,song_id);

    songs_tree.remove(song_id);
    streams_tree.remove(old_pair);


    Pair new_pair(pre+count,song_id);
    songs_tree.insert(pre+count,song_id);
    streams_tree.insert(song_id,new_pair);
}

ArtistResult Artist::getArtistBestSong(int *song_id) {
    if(total_num_of_songs==0){
        return ARTIST_FAILURE;
    }
    *song_id=*(streams_tree.getLast());
}

/*
Artist::Artist(int id, int num_of_songs) : full_songs_list((new StreamListNode*[num_of_songs])){
    artist_id = id;
    total_num_of_songs = num_of_songs;
    //create the songs tree - create an array, insert it, delete it
    int* songs_arr = new int[num_of_songs];
    for(int i = 0; i < num_of_songs; i++){
        songs_arr[i] = i;
    }
    AvlTree<int, int> tmp(songs_arr,songs_arr,num_of_songs);
    delete[] songs_arr;
    // create AvlTree for streams_tree - with first node "0" for all the songs
    num_of_streams_tree.insert(tmp,0);
}

Artist::~Artist() {
    delete[] full_songs_list;
}

Artist::Artist(const Artist& a) : artist_id(a.artist_id), total_num_of_songs(a.total_num_of_songs),
                                    num_of_streams_tree(a.num_of_streams_tree) {
    full_songs_list = new StreamListNode*[a.total_num_of_songs];
    for(int i = 0; i < a.total_num_of_songs; i++){
        full_songs_list[i] = a.full_songs_list[i];
    }
}

StreamListNode* Artist::GetSongNumOfStreamsNode(int song_id) {
    return this->full_songs_list[song_id];
}

void Artist::SetStreamsNumForSong(int song_id, StreamListNode* node){
    full_songs_list[song_id] = node;
}

*/