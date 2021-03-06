
#ifndef WET1_STRUCTS_MUSICMANAGER_H
#define WET1_STRUCTS_MUSICMANAGER_H

#include "HashTable.h"

// enums for exceptions
typedef enum MMStatusType_t{
    MM_ALLOCATION_ERROR,
    MM_INVALID_INPUT,
    MM_FAILURE,
    MM_SUCCESS
}MMStatusType;

class Trio{
private:
    int num_streams;
    int artist_id;
    int song_id;
public:
    Trio(int numStreams, int artist_id, int song_id):num_streams(numStreams),
                                                      artist_id(artist_id),song_id(song_id){};
    ~Trio()= default;
    Trio(const Trio& trio)= default;
    int getArtistID() { return artist_id;};
    int getSongID() { return song_id;};
    int getNumStreams() {return num_streams;};
    bool operator==(const Trio& trio)const{
        return (artist_id==trio.artist_id && song_id==trio.song_id
                    &&num_streams==trio.num_streams);
    }
    bool operator<(const Trio& trio)const {
        if(num_streams>trio.num_streams){
            return true;
        }
        if(num_streams<trio.num_streams){
            return false;
        }
        if(artist_id<trio.artist_id){
            return true;
        }
        if(artist_id>trio.artist_id){
            return false;
        }
        return (song_id<trio.song_id);
    }
    bool operator>(const Trio& trio) const {
        if(num_streams<trio.num_streams){
            return true;
        }
        if(num_streams>trio.num_streams){
            return  false;
        }
        if(artist_id>trio.artist_id){
            return true;
        }
        if(artist_id<trio.artist_id){
            return false;
        }
        return (song_id>trio.song_id);
    }
};

class MusicManager {
private:
    HashTable artists_in_system;
    int total_num_of_artists;
    int total_num_of_songs;
    AvlTree<Trio, Trio> songs_of_system;
public:
    MusicManager() : artists_in_system(1),total_num_of_artists(0), total_num_of_songs(0) {}; // add hashtable and avltree?
    ~MusicManager();
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
