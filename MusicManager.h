#ifndef WET1_STRUCTS_MUSICMANAGER_H
#define WET1_STRUCTS_MUSICMANAGER_H

#include "AvlTree.h"
//#include "List.h"
#include "Artist.h"
#include "HashTable.h"


class  TreeSet{
private:
    int num_streams;
    int artist_id;
    int song_id;
public:
    TreeSet(int numStreams,int artist_id,int song_id):num_streams(numStreams),
                                                      artist_id(artist_id),song_id(song_id){};
    ~TreeSet()= default;
    TreeSet(const TreeSet& treeSet)= default;
    int getArtistID(){ return artist_id;};
    int getSongID(){ return song_id;};
    int getNumStreams{return num_Streams;};
    operator==(const TreeSet& treeSet){
        return ( this->artist_id==treeSet.artist_id&&
                 this->song_id==treeSet.song_id&&this->num_streams==treeSet.num_streams);
    }
    operator<(const TreeSet& treeSet){
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
};




// decided on enums for exceptions
typedef enum MMStatusType_t{
    MM_ALLOCATION_ERROR,
    MM_INVALID_INPUT,
    MM_FAILURE,
    MM_SUCCESS
}MMStatusType;


class MusicManager {
private:
    //Hash ARTIST


    int total_num_of_songs;
    AvlTree<TreeSet, TreeSet> songs_of_system;
    HashTable artists_in_system;


public:
    MusicManager() : total_num_of_songs(0) {};

    ~MusicManager() = default;

    MusicManager(const MusicManager &music_manager) = default;

    MusicManager &operator=(const MusicManager &music_manager) = default;

    MMStatusType MMAddArtist(int artistID);

    MMStatusType MMRemoveArtist(int artistID);

    MMStatusType MMAddSong(int artistID, int song_ID);

    MMStatusType MMRemoveSong(int artistID, int song_ID);

    MMStatusType MMAddToSongCount(int artistID, int song_ID, int count);

    MMStatusType MMGetArtistBestSong(int artistID, int *songID);

    MMStatusType MMGetRecommendedSongInPlace(int rank, int *artist_ID, int *song_ID);


}

MMStatusType MMStatusType MusicManager::MMAddToSongCount(int artistID, int song_ID, int count) {
    if(artistID<=0||song_ID<=0||count<=0){
        return MM_INVALID_INPUT;
    }
    Artist* wanted_artist=artists_in_system.hashFindNode(artistID);
    if(wanted_artist== nullptr){
        return MM_FAILURE;
    }
    int* pre_adding_streams;
    ArtistResult result=wanted_artist->addToSongCount(song_ID,count,pre_adding_streams);
    if(result==ARTIST_KEY_DOESNT_EXISTS){
        return MM_FAILURE;
    }
    TreeSet preeThreeSet(*pre_adding_streams,artistID,song_ID);
    songs_of_system.remove(preeThreeSet);
    TreeSet after_adding_count(*pre_adding_streams+count,artistID,song_ID);
    songs_of_system.insert(after_adding_count,after_adding_count);
    return MM_SUCCESS;
}


MMStatusType MMStatusType MusicManager::MMGetArtistBestSong(int artistID, int *songID) {
    if(artistID<=0||songID== nullptr){
        return MM_INVALID_INPUT;
    }
    Artist* wanted_artist=artists_in_system.hashFindNode(artistID);
    if(wanted_artist== nullptr){
        return MM_FAILURE;
    }
    if(wanted_artist->GetTotalNumOfSongs()==0){
        return MM_FAILURE;
    }
    wanted_artist->getArtistBestSong(songID);
}

MMStatusType MMStatusType MusicManager::MMGetRecommendedSongInPlace(int rank, int *artist_ID, int *song_ID) {
    if(rank<=0 ||artist_ID== nullptr ||song_ID== nullptr){
        return MM_INVALID_INPUT;
    }
    if(rank>total_num_of_songs){
        return MM_FAILURE;
    }
    ///need to use rank of tree
    TreeSet* wanted_rank=songs_of_system.getNodeInRank(rank);
    *artist_ID=wanted_rank->getArtistID();
    *song_ID=wanted_rank->getSongID();
    return MM_SUCCESS;
}

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

#endif //WET1_STRUCTS_MUSICMANAGER_H
