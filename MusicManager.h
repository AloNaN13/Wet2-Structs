#ifndef WET1_STRUCTS_MUSICMANAGER_H
#define WET1_STRUCTS_MUSICMANAGER_H

//#include "AvlTree.h"
//#include "List.h"
#include "Artist.h"
#include "HashTable.h"


// decided on enums for exceptions
typedef enum MMStatusType_t{
    MM_ALLOCATION_ERROR,
    MM_INVALID_INPUT,
    MM_FAILURE,
    MM_SUCCESS
}MMStatusType;


class TreeSet{
private:
    int num_streams;
    int artist_id;
    int song_id;
public:
    TreeSet(int numStreams, int artist_id, int song_id):num_streams(numStreams),
                                                      artist_id(artist_id),song_id(song_id){};
    ~TreeSet()= default;
    TreeSet(const TreeSet& treeSet)= default;
    int getArtistID() { return artist_id;};
    int getSongID() { return song_id;};
    int getNumStreams() {return num_streams;};
    bool operator==(const TreeSet& treeSet)const{
        return (artist_id==treeSet.artist_id && song_id==treeSet.song_id
                    &&num_streams==treeSet.num_streams);
        /*return ( this->artist_id == treeSet.getArtistID() &&
                 this->song_id == treeSet.getSongID() &&
                 this->num_streams == treeSet.getNumStreams());*/
    }
    bool operator<(const TreeSet& treeSet)const {
        if(num_streams<treeSet.num_streams){
            return true;
        }
        if(num_streams>treeSet.num_streams){
            return  false;
        }
        if(artist_id>treeSet.artist_id){
            return true;
        }
        if(artist_id<treeSet.artist_id){
            return false;
        }
        return (song_id>treeSet.song_id);
    }
    bool operator>(const TreeSet& treeSet) const {
        if(num_streams>treeSet.num_streams){
            return true;
        }
        if(num_streams<treeSet.num_streams){
            return  false;
        }
        if(artist_id<treeSet.artist_id){
            return true;
        }
        if(artist_id>treeSet.artist_id){
            return false;
        }
        return (song_id<treeSet.song_id);

    }
};


class MusicManager {
private:
    HashTable artists_in_system;
    int total_num_of_artists;
    int total_num_of_songs;
    AvlTree<TreeSet, TreeSet> songs_of_system;
public:
    MusicManager() : artists_in_system(1),total_num_of_artists(0), total_num_of_songs(0) {}; // add hashtable and avltree?
    ~MusicManager() = default;
    MusicManager(const MusicManager &music_manager) = default;
    MusicManager &operator=(const MusicManager &music_manager) = default;

    MMStatusType MMAddArtist(int artistID);
    MMStatusType MMRemoveArtist(int artistID);
    MMStatusType MMAddSong(int artistID, int songID);
    MMStatusType MMRemoveSong(int artistID, int songID);
    MMStatusType MMAddToSongCount(int artistID, int songID, int count);
    MMStatusType MMGetArtistBestSong(int artistID, int *songId);
    MMStatusType MMGetRecommendedSongInPlace(int rank, int *artistId, int *songId);

};




#endif //WET1_STRUCTS_MUSICMANAGER_H






// OLD MM CODE FROM WET1

/*
class MusicManager{
private:
    AvlTree<Artist,int> artists_tree;
    StreamList list_of_streams;
    int totalNumOfSongs;
public:
    MusicManager(): totalNumOfSongs(0){};
    ~MusicManager() = default;
    MusicManager(const MusicManager& music_manager) = default;
    MusicManager& operator=(const MusicManager& music_manager) = default;

    StreamList& MMGetListOfStreams() {return this->list_of_streams;};
    AvlTree<Artist,int>& MMGetArtistsTree() {return this->artists_tree;};
    MMStatusType MMAddArtist(int artistID, int numOfSongs);
    MMStatusType MMRemoveArtist(int artistID);
    MMStatusType MMAddToSongCount(int artistID, int songID);
    MMStatusType MMNumberOfStreams(int artistID, int songID, int* streams);
    MMStatusType MMgetRecommendedSongs( int numOfSongs, int* artists, int* songs);

};
*/


