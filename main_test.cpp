

#include "AVLTree.h"
#include <vector>
#include <ostream>
#include <random>
#include <chrono>
#include <algorithm>


#define addNode insert
#define removeNode remove

#include "AvlTree.h"
#include "AVL_tests.h"
#include "MusicManger_sari_tests.h"
#include "MusicManager.h"
int main(){
   //MusicMangerTest();

  /* AvlTree<int,int> check;
   check.insert(1,1);
   check.remove(1);
   check.insert(2,2);*/
  MusicManager manager=*new MusicManager();
 // manager.MMAddArtist(1,2);
  manager.MMAddArtist(1,3);
  manager.MMAddArtist(2,2);
 // manager.MMAddArtist(3,2);
  //manager.MMAddToSongCount(2,1);
  //manager.MMAddToSongCount(3,0);
  //manager.MMAddToSongCount(1,1);
  manager.MMAddToSongCount(1,2);

  manager.MMRemoveArtist(2);
  //  manager.MMAddToSongCount(2,1);


  //manager.MMAddArtist(1,5);



  printf("hello\n");


    return 0;
}

