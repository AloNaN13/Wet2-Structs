
#ifndef WET1_STRUCTS_ARTIST_H
#define WET1_STRUCTS_ARTIST_H

#include "AvlTree.h"

typedef enum ArtistResult_t{
    ARTIST_KEY_ALREADY_EXISTS,
    ARTIST_SUCCESS,
    ARTIST_ALLOCATION_ERROR,
    ARTIST_KEY_DOESNT_EXISTS,
    ARTIST_FAILURE
}ArtistResult;

class  Pair{
private:
    int num_streams;
    int song_id;
public:
    Pair(int numStreams,int song_id):num_streams(numStreams),song_id(song_id){};
    ~Pair()= default;
    Pair(const Pair& pair)= default;
    int getNumStreams(){ return num_streams;};
    int getSongID(){ return song_id;};
    bool operator==(const Pair& pair)const {
        return pair.num_streams == num_streams && pair.song_id == song_id;
    }
    bool operator< (const Pair& pair1)const {
        if(num_streams<pair1.num_streams){
            return true;
        }
        return (num_streams==pair1.num_streams&&song_id>pair1.song_id);
    }
    bool operator>(const Pair& pair)const{
        if(num_streams>pair.num_streams){
            return true;
        }
        return (num_streams==pair.num_streams && song_id<pair.song_id);
    }
};

class Artist{
private:
    int artist_id;
    int total_num_of_songs;
    AvlTree<int, int> songs_tree;
    AvlTree<int,Pair> streams_tree;
public:
    explicit Artist(int id):artist_id(id),total_num_of_songs(0){};
    ~Artist()= default;
    Artist(const Artist &a)= default;

    Artist &operator=(const Artist &a) = default;
    ArtistResult addSong(int song_id);
    ArtistResult removeSong(int song_id, int* num_of_streams);
    ArtistResult addToSongCount(int song_id, int count, int* initial_streams);
    ArtistResult getArtistBestSong(int* song_id);

    int GetTotalNumOfSongs() { return this->total_num_of_songs; };
    int GetArtistID() { return this->artist_id; };

};

#endif //WET1_STRUCTS_ARTIST_H
