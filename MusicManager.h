


/* OLD CODE FROM WET1



#ifndef WET1_STRUCTS_MUSICMANAGER_H
#define WET1_STRUCTS_MUSICMANAGER_H

#include "AvlTree.h"
#include "List.h"
#include "Artist.h"

// decided on enums for exceptions
typedef enum MMStatusType_t{
    MM_ALLOCATION_ERROR,
    MM_INVALID_INPUT,
    MM_FAILURE,
    MM_SUCCESS
}MMStatusType;

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


#endif //WET1_STRUCTS_MUSICMANAGER_H
