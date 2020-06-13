






#ifndef WET1_STRUCTS_ARTIST_H
#define WET1_STRUCTS_ARTIST_H

#include "AvlTree.h"
#include "List.h"

class  Pair{
private:
    int num_streams;
    int song_id;
public:
    Pair(int numStreams,int song_id):num_streams(numStreams),song_id(song_id){};
    ~Pair()= default;
    Pair(const Pair& pair)= default;
    operator==(Pair& pair1){
        return (this->song_id==pair1.song_id&&this->num_streams==pair1.num_streams);
    }
    operator<(Pair& pair1){
        if(num_streams<pair1.num_streams){ return true;}
        return (num_streams==pair1.num_streams &&song_id>pair1.song_id);
    }
};

typedef enum ArtistResult_t{ARTIST_KEY_ALREADY_EXISTS,ARTIST_SUCCESS,ARTIST_ALLOCATION_ERROR
    ,ARTIST_KEY_DOESNT_EXISTS
}ArtistResult;
class Artist {
private:
    int artist_id;
    int total_num_of_songs;
    AvlTree<int, int> songs_tree;
    AvlTree<int,Pair> streams_tree;
public:
    Artist(int id):artist_id(id),total_num_of_songs(0){};
    ~Artist()= default;
    Artist(const Artist &a)= default;

    Artist &operator=(const Artist &a) = default;
    ArtistResult addSong(int song_id);
    ArtistResult removeSong(int song_id);
    ArtistResult addToSongCount(int song_id, int count);


    int GetTotalNumOfSongs() { return this->total_num_of_songs; };
    int GetArtistID() { return this->artist_id; };


}

/*

private:
    int artist_id;
    int total_num_of_songs;
    StreamListNode** full_songs_list;
    AvlTree<AvlTree<int,int>,int> num_of_streams_tree;
public:
    Artist(int id, int num_of_songs);
    ~Artist();
    Artist(const Artist& a);
    Artist& operator=(const Artist& a) = default;

    //getters-
    StreamListNode* GetSongNumOfStreamsNode(int song_id);
    int GetTotalNumOfSongs() {return this->total_num_of_songs;};
    AvlTree<AvlTree<int,int>,int>& GetNumOfStreamsTree() {return this->num_of_streams_tree;};
    //int GetArtistID() {return this->artist_id;};
    /*AvlTree<int,int>* getSongsWithNumOfStreams(const Key& key){
        return num_of_streams_tree.getElementptr(key);
    }


    //setters
    void SetStreamsNumForSong(int song_id, StreamListNode* wanted_node);


};
 */


#endif //WET1_STRUCTS_ARTIST_H
