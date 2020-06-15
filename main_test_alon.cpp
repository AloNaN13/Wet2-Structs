

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

int main(){

    MusicManager Manager;
    //void* Manager = Init();
    std::cout << "INIT SUCCESS " << std::endl;
    Manager.MMAddArtist(123);
    std::cout << "Added Artist 123 " << std::endl;
    Manager.MMAddArtist(456);
    std::cout << "Added Artist 456 " << std::endl;
    //Manager.MMRemoveArtist(456);
    //std::cout << "Removed Artist 456 " << std::endl;


    Manager.MMAddSong(123,7);
    std::cout << "Added song 7 to Artist 123 " << std::endl;
    Manager.MMAddSong(123,4);
    std::cout << "Added song 4 to Artist 123 " << std::endl;







    return 0;
}

