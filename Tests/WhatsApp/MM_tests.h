//
// Created by User on 6/15/2020.
//

#ifndef WET2_DATASTRUCTS_MM_TESTS_H
#define WET2_DATASTRUCTS_MM_TESTS_H

#include "MM_tests.h"
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
    assert(MM_SUCCESS == manger.AddArtist( 123));
    assert(MM_SUCCESS == manger.AddArtist(456));
    assert(MM_SUCCESS == manger.AddSong( 123 ,7));
    assert(MM_SUCCESS == manger.AddSong(123, 4));
    assert(MM_FAILURE == manger.AddSong (789, 10 ));// Failure - Artist does not exist
    assert(MM_FAILURE == manger.RemoveArtist( 123)); // Failure - Artist has songs
    assert(MM_INVALID_INPUT == manger.RemoveArtist( 0)); // Invalid Input
    assert(MM_SUCCESS == manger.RemoveArtist( 456));
    assert(MM_SUCCESS == manger.AddArtist( 456));
    assert(MM_SUCCESS == manger.AddSong( 456, 1));
    assert(MM_SUCCESS == manger.AddToSongCount( 123, 4, 5));
    int bestSong = -1;
    assert(MM_SUCCESS == manger.GetArtistBestSong( 123,&bestSong)); // Song 4 has 5 streams
    assert(bestSong == 4);
    int bestArtist = -1;
    assert(MM_SUCCESS == manger.GetRecommendedSongInPlace( 3,&bestArtist,&bestSong)); // The songs are ranked (123,4) > (123,7) > (456,1)
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
    assert(MM_SUCCESS == manger.AddArtist( 1 ));
    assert(MM_SUCCESS == manger.AddArtist( 100));
    assert(MM_SUCCESS == manger.AddArtist( 2));
    assert(MM_SUCCESS == manger.AddArtist( 99));
    assert(MM_SUCCESS == manger.AddArtist( 3));
    assert(MM_SUCCESS == manger.AddArtist( 98));
    assert(MM_SUCCESS == manger.AddArtist( 4));
    assert(MM_SUCCESS == manger.AddArtist( 97));
    assert(MM_SUCCESS == manger.AddArtist( 5));
    assert(MM_SUCCESS == manger.AddArtist( 6));
    assert(MM_SUCCESS == manger.AddArtist( 96));
    assert(MM_SUCCESS == manger.AddArtist( 95));
    assert(MM_SUCCESS == manger.AddArtist( 7));
    assert(MM_SUCCESS == manger.AddArtist( 94));
    assert(MM_SUCCESS == manger.AddArtist( 8));
    assert(MM_SUCCESS == manger.AddArtist( 93));
    assert(MM_SUCCESS == manger.AddArtist( 9));
    assert(MM_SUCCESS == manger.AddArtist( 92));
    assert(MM_SUCCESS == manger.AddArtist( 91));
    assert(MM_SUCCESS == manger.AddArtist( 10));
    assert(MM_FAILURE == manger.AddArtist( 1));
    assert(MM_FAILURE == manger.AddArtist( 100));
    assert(MM_FAILURE == manger.AddArtist( 2));
    assert(MM_FAILURE == manger.AddArtist( 99));
    assert(MM_FAILURE == manger.AddArtist( 3));
    assert(MM_FAILURE == manger.AddArtist( 98));
    assert(MM_FAILURE == manger.AddArtist( 4));
    assert(MM_FAILURE == manger.AddArtist( 97));
    assert(MM_FAILURE == manger.AddArtist( 5));
    assert(MM_FAILURE == manger.AddArtist( 6));
    assert(MM_FAILURE == manger.AddArtist( 96));
    assert(MM_FAILURE == manger.AddArtist( 95));
    assert(MM_FAILURE == manger.AddArtist( 7));
    assert(MM_FAILURE == manger.AddArtist( 94));
    assert(MM_FAILURE == manger.AddArtist( 8));
    assert(MM_FAILURE == manger.AddArtist( 93));
    assert(MM_FAILURE == manger.AddArtist( 9));
    assert(MM_FAILURE == manger.AddArtist( 92));
    assert(MM_FAILURE == manger.AddArtist( 91));
    assert(MM_FAILURE == manger.AddArtist( 10));


    assert(MM_SUCCESS == manger.RemoveArtist(96));
    assert(MM_SUCCESS == manger.RemoveArtist( 95));
    assert(MM_SUCCESS == manger.RemoveArtist( 7));
    assert(MM_SUCCESS == manger.RemoveArtist( 94));
    assert(MM_SUCCESS == manger.RemoveArtist( 8));
    assert(MM_SUCCESS == manger.RemoveArtist( 93));
    assert(MM_SUCCESS == manger.RemoveArtist( 9));
    assert(MM_SUCCESS == manger.RemoveArtist( 92));
    assert(MM_SUCCESS == manger.RemoveArtist( 91));
    assert(MM_SUCCESS == manger.RemoveArtist( 10));
    assert(MM_FAILURE == manger.RemoveArtist( 96));
    assert(MM_FAILURE == manger.RemoveArtist( 95));
    assert(MM_FAILURE == manger.RemoveArtist( 7));
    assert(MM_FAILURE == manger.RemoveArtist( 94));
    assert(MM_FAILURE == manger.RemoveArtist( 8));
    assert(MM_FAILURE == manger.RemoveArtist( 93));
    assert(MM_FAILURE == manger.RemoveArtist( 9));
    assert(MM_FAILURE == manger.RemoveArtist( 92));
    assert(MM_FAILURE == manger.RemoveArtist( 91));
    assert(MM_FAILURE == manger.RemoveArtist( 10));
}




#endif //WET2_DATASTRUCTS_MM_TESTS_H
