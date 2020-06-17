
#include "Artist.h"

ArtistResult Artist::addSong(int song_id) {
    AvlTreeResult result=songs_tree.insert(0,song_id);
    if(result == AVL_KEY_ALREADY_EXISTS){
        return ARTIST_KEY_ALREADY_EXISTS;
    }
    Pair new_pair(0,song_id);
    streams_tree.insert(song_id,new_pair);
    total_num_of_songs++;
    return ARTIST_SUCCESS;
}

ArtistResult Artist::removeSong(int song_id, int* num_of_streams) {
    *num_of_streams=*(songs_tree.getElementptr(song_id));
    int* current_streams_of_song=songs_tree.getElementptr(song_id);
    if(songs_tree.getElementptr(song_id) == nullptr){//there is no such song under the artist
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

    return ARTIST_SUCCESS;

}

ArtistResult Artist::getArtistBestSong(int *song_id) {
    if(total_num_of_songs==0){
        return ARTIST_FAILURE;
    }
    *song_id=*(streams_tree.getLast());
    return ARTIST_SUCCESS;
}
