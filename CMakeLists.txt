cmake_minimum_required(VERSION 3.15)
project(Wet2_Structs)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(
        Wet2_Structs
        #Artist.cpp
        #Artist.h
        AvlTree.h
        HashTable.cpp
        HashTable.h
        library2.cpp
        library2.h
        List.cpp
        List.h
        #main_tests.cpp
        main2.cpp
        MusicManager.cpp
        MusicManager.h
        )
