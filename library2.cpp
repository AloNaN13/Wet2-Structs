
#include "library2.h"
#include "MusicManager.h"

StatusType changeMMResultToStatusType(MMStatusType result){
    if(result==MM_SUCCESS){
        return SUCCESS;
    }
    if(result==MM_FAILURE){
        return FAILURE;
    }
    if(result==MM_ALLOCATION_ERROR){
        return  ALLOCATION_ERROR;
    }
    if(result==MM_INVALID_INPUT){
        return  INVALID_INPUT;
    }

    // does not reach here - only for the compiler's warning
    return SUCCESS;

}

void* Init(){
    MusicManager* DS = new MusicManager();
    return (void*)DS;
}

StatusType AddArtist(void* DS, int artistID){
    if(DS == nullptr){
        return INVALID_INPUT;
    }
    return changeMMResultToStatusType(((MusicManager*)DS)->MMAddArtist(artistID));
}

StatusType RemoveArtist(void* DS, int artistID) {
    if(DS == nullptr){
        return INVALID_INPUT;
    }
    return changeMMResultToStatusType(((MusicManager*)DS)->MMRemoveArtist(artistID));
}

StatusType AddSong(void *DS, int artistID, int songID){
    if(DS == nullptr){
        return INVALID_INPUT;
    }
    return changeMMResultToStatusType(((MusicManager*)DS)->MMAddSong(artistID, songID));
}

StatusType RemoveSong(void *DS, int artistID, int songID){
    if(DS == nullptr){
        return INVALID_INPUT;
    }
    return changeMMResultToStatusType(((MusicManager*)DS)->MMRemoveSong(artistID, songID));
}

StatusType AddToSongCount(void* DS, int artistID, int songID, int count){
    if(DS == nullptr){
        return INVALID_INPUT;
    }
    return changeMMResultToStatusType(((MusicManager*)DS)->MMAddToSongCount(artistID, songID, count));
}

StatusType GetArtistBestSong(void *DS, int artistID, int *songId){
    if(DS == nullptr){
        return INVALID_INPUT;
    }
    return changeMMResultToStatusType(((MusicManager*)DS)->MMGetArtistBestSong(artistID, songId));
}

StatusType GetRecommendedSongInPlace(void *DS, int rank, int *artistId, int *songId){
    if(DS == nullptr){
        return INVALID_INPUT;
    }
    return changeMMResultToStatusType(((MusicManager*)DS)->MMGetRecommendedSongInPlace(rank, artistId, songId));
}

void Quit(void**DS ){
    delete ((MusicManager*)(*DS));
    *DS= nullptr;
}
