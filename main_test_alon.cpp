

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

int main(){




    //Sari's Test
    MM_test();





/*

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


*/

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






    return 0;
}

