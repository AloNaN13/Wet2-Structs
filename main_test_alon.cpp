

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
    std::cout << "Added first Artist " << std::endl;
    Manager.MMAddArtist(456);
    std::cout << "Added second Artist " << /*(MusicManager*)Manager. <<*/ std::endl;







    return 0;
}

