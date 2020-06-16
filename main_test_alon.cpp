

#include "AVLTree.h"
#include <vector>
#include <ostream>
#include <random>
#include <chrono>
#include <algorithm>


#define addNode insert
#define removeNode remove

#include "AvlTree.h"
#include "library2.h"
#include "MusicManager.h"

#include "MM_tests_sari.h"


//declarations
void general1();
void general2();
void Sari_test();
void official_test_alon();

int main(){
    general1();
    //general2();
    //Sari_test();
    //official_test_alon();

    return 0;
}


void general1(){

    int bestSong2 = 0;
    int bestSong3 = 0;
    int rank1artist = 0;
    int rank1song = 0;

    MusicManager Manager;
    Manager.MMAddArtist(1);
    Manager.MMAddArtist(2);
    Manager.MMAddArtist(3);
    Manager.MMAddArtist(4);
    Manager.MMAddArtist(5);
    Manager.MMAddSong(1,1);
    Manager.MMAddSong(1,2);
    Manager.MMAddSong(1,3);
    Manager.MMAddSong(2,1);
    Manager.MMAddSong(2,2);
    Manager.MMAddSong(2,3);
    Manager.MMGetArtistBestSong(2,&bestSong2);
    Manager.MMGetArtistBestSong(3,&bestSong3);
    Manager.MMAddSong(3,1);
    Manager.MMGetArtistBestSong(3,&bestSong3);
    Manager.MMRemoveArtist(3);
    std::cout << "GOT HERE " << std::endl;

    Manager.MMGetRecommendedSongInPlace(1,&rank1artist,&rank1song);
    std::cout << "GOT HERE 2 " << std::endl;



    /*Init
    AddArtist 1
    AddArtist 2
    AddArtist 3
    AddArtist 4
    AddArtist 5
    AddSong 1 1
    AddSong 1 2
    AddSong 1 3
    AddSong 2 1
    AddSong 2 2
    AddSong 2 3
    GetArtistBestSong 2
    GetArtistBestSong 3
    AddSong 3 1
    GetArtistBestSong 3
    RemoveArtist 3
    GetRecommendedSongInPlace 1
    //and more
    */
}


void general2(){
    int a = 1;
}


void Sari_test(){
    MM_test();
}



void official_test_alon(){
    int best_song = 0;
    int third_artist = 0;
    int third_song = 0;

    MusicManager Manager;
    //void* Manager = Init();
    std::cout << "INIT SUCCESS " << std::endl;
    Manager.MMAddArtist(123);
    std::cout << "Added Artist 123 " << std::endl;
    Manager.MMAddArtist(456);
    std::cout << "Added Artist 456 " << std::endl;
    Manager.MMAddSong(123,7);
    std::cout << "Added song 7 to Artist 123 " << std::endl;
    Manager.MMAddSong(123,4);
    std::cout << "Added song 4 to Artist 123 " << std::endl;
    Manager.MMRemoveArtist(456);
    std::cout << "Removed Artist 456 " << std::endl;
    Manager.MMAddArtist(456);
    std::cout << "Added Artist 456 again! " << std::endl;
    Manager.MMAddSong(456,1);
    std::cout << "Added song 1 to Artist 456 " << std::endl;

    Manager.MMAddToSongCount(123,4,5);
    std::cout << "Added 5 counts to Artist 123 song 4 " << std::endl;



    //List indexOfTable = Manager.getArtistsInSystem().getIndexOfTable();


    Manager.MMGetArtistBestSong(123, &best_song);
    std::cout << "Artist 123 best song is " << best_song << " (should be 4) " << std::endl;

    Manager.MMGetRecommendedSongInPlace(3,&third_artist,&third_song);
    std::cout << "3 rank is: Artist " << third_artist << " Song " << third_song << std::endl;




    /*
    Init
    AddArtist 123
    AddArtist 456
    AddSong 123 7
    AddSong 123 4
    AddSong 789 10 # Failure - Artist does not exist
    RemoveArtist 123 # Failure - Artist has songs
    RemoveArtist 0 # Invalid Input
    RemoveArtist 456
    AddArtist 456
    AddSong 456 1
    AddToSongCount 123 4 5
    GetArtistBestSong 123 # Song 4 has 5 streams
    GetRecommendedSongInPlace 3 # The songs are ranked (123,4) > (123,7) > (456,1)
    Quit
    */

}