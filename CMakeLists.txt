cmake_minimum_required(VERSION 3.15)
project(Wet2_Structs)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Wet2_Structs
        "Tests/WhatsApp/old ones from wet1/AVL_tests.h"
        "Tests/WhatsApp/old ones from wet1/AVLTreeTest (1) (1).cpp"
        "Tests/WhatsApp/old ones from wet1/MusicManger_sari_tests.h"
        Artist.cpp
        Artist.h
        AvlTree.h
        HashTable.cpp
        HashTable.h
        library2.cpp
        library2.h
        List.cpp
        List.h
        main2.cpp
        main_test.cpp
        MusicManager.cpp
        MusicManager.h)
