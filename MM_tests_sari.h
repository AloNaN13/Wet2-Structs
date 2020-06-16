//
// Created by User on 6/15/2020.
//

#ifndef WET2_DATASTRUCTS_MM_TESTS_H
#define WET2_DATASTRUCTS_MM_TESTS_H

#include "MusicManager.h"



void MM_test();
void MM_test1();
void MM_test2();



void MM_test(){
    MM_test1();
    MM_test2();
    return;
}

void MM_test2(){
    MusicManager manger;
    assert(MM_SUCCESS == manger.MMAddArtist( 123));
    assert(MM_SUCCESS == manger.MMAddArtist(456));
    assert(MM_SUCCESS == manger.MMAddSong( 123 ,7));
    assert(MM_SUCCESS == manger.MMAddSong(123, 4));
    assert(MM_FAILURE == manger.MMAddSong (789, 10 ));// Failure - Artist does not exist
    assert(MM_FAILURE == manger.MMRemoveArtist( 123)); // Failure - Artist has songs
    assert(MM_INVALID_INPUT == manger.MMRemoveArtist( 0)); // Invalid Input
    assert(MM_SUCCESS == manger.MMRemoveArtist( 456));
    assert(MM_SUCCESS == manger.MMAddArtist( 456));
    assert(MM_SUCCESS == manger.MMAddSong( 456, 1));
    assert(MM_SUCCESS == manger.MMAddToSongCount( 123, 4, 5));
    int bestSong = -1;
    assert(MM_SUCCESS == manger.MMGetArtistBestSong( 123,&bestSong)); // Song 4 has 5 streams
    assert(bestSong == 4);
    int bestArtist = -1;
    assert(MM_SUCCESS == manger.MMGetRecommendedSongInPlace( 3,&bestArtist,&bestSong)); // The songs are ranked (123,4) > (123,7) > (456,1)
    assert(bestArtist == 456);
    assert(bestSong == 1);
}
void MM_test1(){
    MusicManager manger;
    /*for(int i=1;i<1000;i++){
        assert(MM_SUCCESS == manger.AddArtist(i));
        for(int j=0;j<i;j++){
            assert(MM_FAILURE == manger.AddArtist(i));
        }
    }*/
    assert(MM_SUCCESS == manger.MMAddArtist( 1 ));
    assert(MM_SUCCESS == manger.MMAddArtist( 100));
    assert(MM_SUCCESS == manger.MMAddArtist( 2));
    assert(MM_SUCCESS == manger.MMAddArtist( 99));
    assert(MM_SUCCESS == manger.MMAddArtist( 3));
    assert(MM_SUCCESS == manger.MMAddArtist( 98));
    assert(MM_SUCCESS == manger.MMAddArtist( 4));
    assert(MM_SUCCESS == manger.MMAddArtist( 97));
    assert(MM_SUCCESS == manger.MMAddArtist( 5));
    assert(MM_SUCCESS == manger.MMAddArtist( 6));
    assert(MM_SUCCESS == manger.MMAddArtist( 96));
    assert(MM_SUCCESS == manger.MMAddArtist( 95));
    assert(MM_SUCCESS == manger.MMAddArtist( 7));
    assert(MM_SUCCESS == manger.MMAddArtist( 94));
    assert(MM_SUCCESS == manger.MMAddArtist( 8));
    assert(MM_SUCCESS == manger.MMAddArtist( 93));
    assert(MM_SUCCESS == manger.MMAddArtist( 9));
    assert(MM_SUCCESS == manger.MMAddArtist( 92));
    assert(MM_SUCCESS == manger.MMAddArtist( 91));
    assert(MM_SUCCESS == manger.MMAddArtist( 10));
    assert(MM_FAILURE == manger.MMAddArtist( 1));
    assert(MM_FAILURE == manger.MMAddArtist( 100));
    assert(MM_FAILURE == manger.MMAddArtist( 2));
    assert(MM_FAILURE == manger.MMAddArtist( 99));
    assert(MM_FAILURE == manger.MMAddArtist( 3));
    assert(MM_FAILURE == manger.MMAddArtist( 98));
    assert(MM_FAILURE == manger.MMAddArtist( 4));
    assert(MM_FAILURE == manger.MMAddArtist( 97));
    assert(MM_FAILURE == manger.MMAddArtist( 5));
    assert(MM_FAILURE == manger.MMAddArtist( 6));
    assert(MM_FAILURE == manger.MMAddArtist( 96));
    assert(MM_FAILURE == manger.MMAddArtist( 95));
    assert(MM_FAILURE == manger.MMAddArtist( 7));
    assert(MM_FAILURE == manger.MMAddArtist( 94));
    assert(MM_FAILURE == manger.MMAddArtist( 8));
    assert(MM_FAILURE == manger.MMAddArtist( 93));
    assert(MM_FAILURE == manger.MMAddArtist( 9));
    assert(MM_FAILURE == manger.MMAddArtist( 92));
    assert(MM_FAILURE == manger.MMAddArtist( 91));
    assert(MM_FAILURE == manger.MMAddArtist( 10));


    assert(MM_SUCCESS == manger.MMRemoveArtist(96));
    assert(MM_SUCCESS == manger.MMRemoveArtist( 95));
    assert(MM_SUCCESS == manger.MMRemoveArtist( 7));
    assert(MM_SUCCESS == manger.MMRemoveArtist( 94));
    assert(MM_SUCCESS == manger.MMRemoveArtist( 8));
    assert(MM_SUCCESS == manger.MMRemoveArtist( 93));
    assert(MM_SUCCESS == manger.MMRemoveArtist( 9));
    assert(MM_SUCCESS == manger.MMRemoveArtist( 92));
    assert(MM_SUCCESS == manger.MMRemoveArtist( 91));
    assert(MM_SUCCESS == manger.MMRemoveArtist( 10));
    assert(MM_FAILURE == manger.MMRemoveArtist( 96));
    assert(MM_FAILURE == manger.MMRemoveArtist( 95));
    assert(MM_FAILURE == manger.MMRemoveArtist( 7));
    assert(MM_FAILURE == manger.MMRemoveArtist( 94));
    assert(MM_FAILURE == manger.MMRemoveArtist( 8));
    assert(MM_FAILURE == manger.MMRemoveArtist( 93));
    assert(MM_FAILURE == manger.MMRemoveArtist( 9));
    assert(MM_FAILURE == manger.MMRemoveArtist( 92));
    assert(MM_FAILURE == manger.MMRemoveArtist( 91));
    assert(MM_FAILURE == manger.MMRemoveArtist( 10));
}




#endif //WET2_DATASTRUCTS_MM_TESTS_H
