
#ifndef WET1_DATASTRUCTS_MUSICMANGER_TESTS_H
#define WET1_DATASTRUCTS_MUSICMANGER_TESTS_H

#include "MusicManager.h"
#include <assert.h>
#include <iostream>

void MusicMangerTest();

void MusicManger_test1();// VERY basic operation
void MusicManger_test2();
void MusicManger_test3(int artistSize,int songSize);

void MusicMangerTest(){
    std::cout << "testing MusicManger" << std::endl;

    std::cout << "Starting test 1" << std::endl;
    MusicManger_test1();
    std::cout << "test 1 successful" << std::endl;

    std::cout << "Starting test 2" << std::endl;
    MusicManger_test2();
    std::cout << "test 2 successful" << std::endl;

    std::cout << "Starting test 3" << std::endl;
    MusicManger_test3(2,1);
    std::cout << "test 3 successful" << std::endl;

}
void MusicManger_test3(int artistSize,int songSize){
    srand(time(NULL));
    MusicManager manger;
    int* array = new int[artistSize*songSize];
    int* numOfSongs = new int[artistSize];
    bool* occ = new bool[artistSize];
    for(int i=0;i<artistSize;i++){
        for(int j=0;j<songSize;j++){
            array[i*songSize+j]=0;
        }
        occ[i] = false;
        numOfSongs[i] = 0;
    }
    //start:

    for(int count = 0;count<artistSize*songSize*1000;count++){
        int artist = rand()%artistSize;
        if(artist==0) artist = 1;
        int song = rand()%songSize;
        if(song==0) song = 1;//check what happens when 0 and aritstAdd
        int operation = rand()%100;
        if(operation<5) operation = 1;
        else if(operation<55) operation =0;
        else operation = 2;

        switch(operation){
            case 0://insert
                if(occ[artist]){
                    assert(manger.MMAddArtist(artist,song)==MM_FAILURE);
                }
                else{
                    assert(manger.MMAddArtist(artist,song)==MM_SUCCESS);
                    occ[artist]=true;
                    numOfSongs[artist]=song;
                }
            break;
            case 1://remove
                if(occ[artist]){
                    assert(manger.MMRemoveArtist(artist)==MM_SUCCESS);
                    occ[artist] = false;
                    numOfSongs[artist]=0;
                    for(int i=0;i<songSize;i++) array[artist*songSize+i] = 0;
                }
                else{
                    assert(manger.MMRemoveArtist(artist)==MM_FAILURE);
                }
            break;
            default://addcount
                if(occ[artist]){
                    if(song>numOfSongs[artist]-1){
                        assert(manger.MMAddToSongCount(artist,song)==MM_INVALID_INPUT);
                    }
                    else{
                        assert(manger.MMAddToSongCount(artist,song)==MM_SUCCESS);
                        array[artist*songSize+song]+=1;
                    }
                }
                else{
                    assert(manger.MMAddToSongCount(artist,song)==MM_FAILURE);
                }
            break;
        }
    }
    int * orderedArtists = new int[songSize*artistSize];
    int* orderedSongs = new int[songSize*artistSize];
    int totalSongs = 0;
    for(int i=0; i<artistSize;i++){
        if(occ[i]){
            totalSongs+=numOfSongs[i];
        }
    }
    //testing get reccomended
    assert(manger.MMgetRecommendedSongs(totalSongs+1,orderedArtists,orderedSongs)==MM_FAILURE);
    assert(manger.MMgetRecommendedSongs(totalSongs+2,orderedArtists,orderedSongs)==MM_FAILURE);
    assert(manger.MMgetRecommendedSongs(totalSongs+10,orderedArtists,orderedSongs)==MM_FAILURE);
    assert(manger.MMgetRecommendedSongs(totalSongs+50,orderedArtists,orderedSongs)==MM_FAILURE);
    assert(manger.MMgetRecommendedSongs(totalSongs+70,orderedArtists,orderedSongs)==MM_FAILURE);
    assert(manger.MMgetRecommendedSongs(0,orderedArtists,orderedSongs)==MM_INVALID_INPUT);

    assert(manger.MMgetRecommendedSongs(totalSongs,orderedArtists,orderedSongs)==MM_SUCCESS);
    int * orderedArtists_test = new int[songSize*artistSize];
    int* orderedSongs_test = new int[songSize*artistSize];
    for(int curr =0 ;curr<totalSongs;curr++){
        int max = -1;
        int currArtist = 0;
        int currSong = 0;
        for(int i = 0;i<artistSize;i++){
            if(occ[i]){
                for (int j = 0; j < numOfSongs[i]; j++) {
                    if (array[i * songSize + j] > max) {
                        bool newFind = true;
                        for (int m = 0; m < curr; m++) {
                            if (orderedArtists_test[m] == i && orderedSongs_test[m] == j) {
                                newFind = false;
                                break;
                            }
                        }
                        if (newFind) {
                            max = array[i * songSize + j];
                            currArtist = i;
                            currSong = j;
                        }
                    }
                }
            }
        }
        orderedArtists_test[curr] = currArtist;
        orderedSongs_test[curr] = currSong;
    }

    for(int i=0;i<totalSongs;i++){
        //std::cout<<"real artist "<<orderedArtists_test[i]<< " not so real "<<orderedArtists[i]<< std::endl;
        //std::cout<<"real song "<<orderedSongs_test[i]<< " not so real "<<orderedSongs[i]<< std::endl;

        assert(orderedArtists_test[i]==orderedArtists[i]);
        assert(orderedSongs_test[i]==orderedSongs[i]);
    }
    int streams=0;
    ///testiong numberOfStreams
    for(int i=-10;i<artistSize;i++){
        for(int j=-10;j<songSize;j++){
            if(i<=0 || j<0){
                assert(manger.MMNumberOfStreams(i,j,&streams)==MM_INVALID_INPUT);
            }
            else if(!occ[i]){
                assert(manger.MMNumberOfStreams(i,j,&streams)==MM_FAILURE);
            }
            else if(j>=numOfSongs[i]){
                assert(manger.MMNumberOfStreams(i,j,&streams)==MM_INVALID_INPUT);
            }
            else{
                assert(manger.MMNumberOfStreams(i,j,&streams)==MM_SUCCESS);
                assert(streams == array[i*songSize + j]);
            }
        }
    }
    delete[](orderedArtists_test);
    delete[](orderedSongs_test);
    delete[](orderedArtists);
    delete[](orderedSongs);
    delete[](array);
    delete[](numOfSongs);
    delete[](occ);
}
void MusicManger_test2(){
    MusicManager manger;
    int streams=0;
    //testing while empty
    assert(manger.MMNumberOfStreams(1,1,&streams)==MM_FAILURE);
    assert(manger.MMRemoveArtist(4)==MM_FAILURE);
    assert(manger.MMAddToSongCount(1,1)==MM_FAILURE);
    assert(manger.MMgetRecommendedSongs(1,nullptr,nullptr)==MM_FAILURE);
    //starting:
    assert(manger.MMAddArtist(5,7)==MM_SUCCESS);
    assert(manger.MMAddArtist(5,10)==MM_FAILURE);

}


void MusicManger_test1(){
    MusicManager manager;

    assert(manager.MMRemoveArtist(1)==MM_FAILURE);
    assert(manager.MMAddArtist(1,5)==MM_SUCCESS);
    assert(manager.MMAddArtist(1,3)==MM_FAILURE);
    assert(manager.MMAddArtist(1,7)==MM_FAILURE);
    assert(manager.MMAddToSongCount(1,6)==MM_INVALID_INPUT);
    assert(manager.MMAddToSongCount(1,4)==MM_SUCCESS);
    assert(manager.MMAddToSongCount(1,5)==MM_INVALID_INPUT);
    assert(manager.MMAddToSongCount(1,0)==MM_SUCCESS);
    int streams = 0;


    assert(manager.MMNumberOfStreams(1,0,&streams)==MM_SUCCESS);
    assert(streams == 1);

    assert(manager.MMNumberOfStreams(1,1,&streams)==MM_SUCCESS);
    assert(streams == 0);

    assert(manager.MMNumberOfStreams(1,2,&streams)==MM_SUCCESS);
    assert(streams == 0);

    assert(manager.MMNumberOfStreams(1,3,&streams)==MM_SUCCESS);
    assert(streams == 0);

    assert(manager.MMNumberOfStreams(1,4,&streams)==MM_SUCCESS);
    assert(streams == 1);

    assert(manager.MMNumberOfStreams(1,-1,&streams)==MM_INVALID_INPUT);
    assert(manager.MMNumberOfStreams(1,5,&streams)==MM_INVALID_INPUT);

    //std::cout << "GOT HERE 1" << std::endl;
    //assert(manager.MMRemoveArtist(1)==MM_SUCCESS);


    MMStatusType GetRecommendedSongs(int numOfSongs,int* artists,int* songs);
    int* artists = new int[5];
    int* songs = new int[5];
    assert(manager.MMgetRecommendedSongs(5,artists,songs)==MM_SUCCESS);
    assert(artists[0]==1);
    assert(artists[1]==1);
    assert(artists[2]==1);
    assert(artists[3]==1);
    assert(artists[4]==1);
    std::cout<< songs[0]<<std ::endl;

    assert(songs[0]==0);
    assert(songs[1]==4);
    assert(songs[2]==1);
    assert(songs[3]==2);
    assert(songs[4]==3);
    delete[](artists);
    delete[](songs);
}
#endif //WET1_DATASTRUCTS_MUSICMANGER_TESTS_H
