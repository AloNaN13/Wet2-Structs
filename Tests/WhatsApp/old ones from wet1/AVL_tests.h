//
// Created by User on 4/29/2020.
//

#ifndef WET1_DATASTRUCTS_AVL_TESTS_H

#include <iostream>
#include "AvlTree.h"
#include <cassert>
#include <cmath>

void AVL_TESTS();
void AVL_Basics();


void AVL_test1();//basic insert remove
void AVL_test2(int size);//stress test - basic insert remove
void AVL_test3(int size);//stress test - advanced insert remove
void AVL_test4(int size);//depth test
void AVL_test5(int size);//random insertion./removal test & copy
void AVL_test6();// basic get test (randomized)

//void AVL_test7(int size);//iter running on static tree
//void AVL_test8(int size);//iterator stability
//void AVL_test9(int size);//iterator stress test
void AVL_TESTS(){
    AVL_Basics();
    //AVL_Iterator();
}

void AVL_Basics(){
    std::cout << "testing general tree insert/remove" << std::endl;
/*
    std::cout << "Starting test 1" << std::endl;
    AVL_test1();
    std::cout << "test 1 successful" << std::endl;

    std::cout << "Starting test 2" << std::endl;
    AVL_test2(10000);
    std::cout << "test 2 successful" << std::endl;

    std::cout << "Starting test 3" << std::endl;
    AVL_test3(10000);
    std::cout << "test 3 successful" << std::endl;

/*
    std::cout << "Starting test 4" << std::endl;
    AVL_test4(10000);
    std::cout << "test 4 successful" << std::endl;

    std::cout << "Starting test 5" << std::endl;
    AVL_test5(10000);
    std::cout << "test 5 successful" << std::endl;

    std::cout << "Starting test 6" << std::endl;
    AVL_test6();
    std::cout << "test 6 successful" << std::endl;

    std::cout << "::::::::::::::::::::::::::::::::" << std::endl;

    std::cout << "you've passed the general test!" << std::endl;
    std::cout << "::::::::::::::::::::::::::::::::" << std::endl;

*/
}




void AVL_test6() {
    AvlTree<int, int> tree;
    tree.insert(2, 1);
    *tree.getElementptr(1) = 5;
    assert(*tree.getElementptr(1) == 5);
    int *elem = tree.getElementptr(1);
    *elem = 10;
    assert(*tree.getElementptr(1) == 10);
}

void AVL_test5(int size){
    AvlTree<int,int> tree;
    int *array = new int[size];
    bool *occ = new bool[size];
    for(int i=0;i<size;i++) occ[i]=false;
    AvlTreeResult result;

   // for(int i=0;i<size*100;i++){
    for(int i=0;i<size;i++){
        printf("%d\n",i);
        int index = rand()%size;
        int elem = rand();
        if(rand()%2){
            //insert
            if(occ[index]){
                result=tree.insert(elem,index);
                assert(result==AVL_KEY_ALREADY_EXISTS);
            }
            else{
                result=tree.insert(elem,index);
                assert(result==AVL_SUCCESS);
                array[index]=elem;
                occ[index]=true;
            }
        }
        else{
            //remove
            if(occ[index]){
                result=tree.remove(index);
                assert(result==AVL_SUCCESS);
                occ[index]=false;
            }
            else{
                result=tree.remove(index);
                assert(result==AVL_KEY_DOESNT_EXISTS);
            }

        }
    }
    tree.printTree();

    delete[](array);
    delete[](occ);
}

void AVL_test4(int size){
    AvlTree<double,int> tree;
    //insert all
    for(int i=-size*5;i<size*5;i+=5){
        AvlTreeResult result=tree.insert(double(i)/13,i);
        assert(AVL_SUCCESS == result);
        assert(tree.insert(double(i),i)==AVL_KEY_ALREADY_EXISTS);
        assert(double(i)/13 == *(tree.getElementptr(i)));
    }
    unsigned int depth = tree.getHeight();
    std::cout << "for " << size << " we get a depth of " << depth <<" which is " <<(depth/(log(size)/log(2))) <<" times bigger than the log"<<std::endl;
    assert((depth/(log(size)/log(2)))<3);
}
/*
void AVL_test3(int size){
    AvlTree<int,double> tree;
    //insert all
    for(int i=-size*5;i<size*5;i+=5){
        assert(AVL_SUCCESS == tree.insert(i,double(i)/13));
        assert(tree.insert(i,double(i))==AVL_KEY_ALREADY_EXISTS);
        assert(double(i)/13 == *tree.getElementptr(i));
    }
    int* array = tree.inorderArrayTest(2*size);
    for(int i=-size*5;i<size*5;i+=5){
        assert(double(i)/13 == *tree.getElementptr(i));
        assert(i == array[(i+size*5)/5]);
    }
    delete[] array;

    //remove lower half
    for(int i=-size*5;i<0;i+=5){
        assert(tree.remove(i)==AVL_SUCCESS);
        assert(tree.remove(i)==AVL_KEY_DOESNT_EXISTS);
    }
    for(int i=-size*5;i<0;i+=5){
        try{
            *tree.getElementptr(i);
            assert(false);
        }
        catch(AVL<int,double>::AVLexception& excep){
            assert(excep.AVL_what()==AVL_KEY_DOES_NOT_EXIST);
        }
    }
    array = tree.inorderArrayTest(size);
    for(int i=0;i<size*5;i+=5){
        assert(double(i)/13 == tree.get(i));
        assert(i == array[i/5]);
    }
    delete[] array;

    //re-insert lower half
    for(int i=-size*5;i<0;i+=5){
        assert(AVL_SUCCESS == tree.insert(i,double(i)/13));
        assert(tree.insert(i,double(i))==AVL_KEY_ALREADY_EXISTS);
        assert(double(i)/13 == tree.get(i));
    }

    array = tree.inorderArrayTest(2*size);
    for(int i=-size*5;i<size*5;i+=5){
        assert(double(i)/13 == tree.get(i));
        assert(i == array[(i+size*5)/5]);
    }
    delete[] array;

    for(int i=-size*5;i<size*5;i+=5){
        assert(tree.insert(i,double(i))==AVL_KEY_ALREADY_EXISTS);
        assert(double(i)/13 == tree.get(i));
    }
    for(int i=-size*5;i<size*5;i+=5){
        //std::cout<<i<<std::endl;
        //tree.removeKey(i);
        assert(tree.insert(i,double(i))==AVL_KEY_ALREADY_EXISTS);
        assert(tree.remove(i)==AVL_SUCCESS);
        assert(tree.remove(i) == AVL_KEY_DOESNT_EXISTS);
    }

}*/
/*
void AVL_test2(int size){
    AVL<int,double> tree;
    for(int i=-size*5;i<size*5;i+=5){
        assert(AVL_SUCCESS == tree.insert(i,double(i)/13));
        assert(tree.insert(i,double(i))==AVL_KEY_ALREADY_EXISTS);
        assert(double(i)/13 == tree.get(i));
    }
    int* array = tree.inorderArrayTest(2*size);
    for(int i=-size*5;i<size*5;i+=5){
        assert(double(i)/13 == tree.get(i));
        //std::cout<<array[(i+size*5)/5]<<std::endl;
    }
    for(int i=-size*5;i<size*5;i+=5){
        assert(double(i)/13 == tree.get(i));
        assert(i == array[(i+size*5)/5]);
    }
    for(int i=-size*5;i<size*5;i+=5){
        assert(tree.removeKey(i)==AVL_SUCCESS);
        assert(tree.removeKey(i)==AVL_KEY_DOES_NOT_EXIST);
    }
    delete[] array;
}

*/
/*
void AVL_test1(){
    AvlTree<int,int> tree;
    try{
        tree.get(1);
    }
    catch(const AVL<int,int>::AVLexception& excep){
        if(excep.AVL_what()!=AVL_KEY_DOES_NOT_EXIST){
            assert(false);
        }
    }
    assert(AVL_SUCCESS==tree.insert(1,3));
    assert(1==tree.NodeHeight(1));

    assert(AVL_SUCCESS==tree.insert(2,15));
    assert(2==tree.NodeHeight(1));
    assert(1==tree.NodeHeight(2));

    assert(AVL_SUCCESS==tree.insert(4,2));
    assert(1==tree.NodeHeight(1));
    assert(1==tree.NodeHeight(4));
    assert(2==tree.NodeHeight(2));

    assert(AVL_KEY_ALREADY_EXISTS==tree.insert(4,1));
    assert(1==tree.NodeHeight(1));
    assert(1==tree.NodeHeight(4));
    assert(2==tree.NodeHeight(2));

    assert(AVL_SUCCESS==tree.insert(6,1));
    assert(2==tree.NodeHeight(4));
    assert(3==tree.NodeHeight(2));
    assert(1==tree.NodeHeight(1));
    assert(1==tree.NodeHeight(6));

    assert(AVL_SUCCESS==tree.removeKey(2));
    assert(2==tree.NodeHeight(4));
    assert(1==tree.NodeHeight(1));
    assert(1==tree.NodeHeight(6));
    assert(AVL_KEY_DOESNT_EXISTS==tree.removeKey(2));

    assert(AVL_SUCCESS==tree.insert(3,2));
    assert(3==tree.NodeHeight(4));
    assert(2==tree.NodeHeight(1));
    assert(1==tree.NodeHeight(6));
    assert(1==tree.NodeHeight(3));

    assert(AVL_SUCCESS==tree.insert(2,2));
    assert(3==tree.NodeHeight(4));
    assert(2==tree.NodeHeight(2));
    assert(1==tree.NodeHeight(1));
    assert(1==tree.NodeHeight(3));
    assert(1==tree.NodeHeight(6));

    assert(AVL_SUCCESS==tree.insert(5,2));
    assert(3==tree.NodeHeight(4));
    assert(2==tree.NodeHeight(2));
    assert(1==tree.NodeHeight(1));
    assert(1==tree.NodeHeight(3));
    assert(2==tree.NodeHeight(6));
    assert(1==tree.NodeHeight(5));

    assert(3==*tree.getElementptr(1));
    assert(2==*tree.getElementptr(2));
    assert(2==*tree.getElementptr(3));
    assert(2==*tree.getElementptr(4));
    assert(2==*tree.getElementptr(5));
    assert(1==*tree.getElementptr(6));


    assert(tree.remove(5)==AVL_SUCCESS);

    assert(tree.remove(6)==AVL_SUCCESS);
    try {
        tree.get(6);
        assert(false);
    }
    catch(AVL<int,int>::AVLexception& excep){
        assert(excep.AVL_what()==AVL_KEY_DOES_NOT_EXIST);
    }
    assert(tree.remove(6)==AVL_KEY_DOESNT_EXISTS);
    assert(3==tree.NodeHeight(2));
    assert(2==tree.NodeHeight(4));
    assert(1==tree.NodeHeight(3));
    assert(1==tree.NodeHeight(1));


    assert(tree.remove(2)==AVL_SUCCESS);
    assert(tree.remove(2)==AVL_KEY_DOESNT_EXISTS);
    assert(2==tree.NodeHeight(3));
    assert(1==tree.NodeHeight(4));
    assert(1==tree.NodeHeight(1));

    assert(tree.removE(3)==AVL_SUCCESS);
    assert(tree.remove(3)==AVL_KEY_DOESNT_EXISTS);
    assert(2==tree.NodeHeight(4));
    assert(1==tree.NodeHeight(1));



    assert(tree.remove(1)==AVL_SUCCESS);
    assert(tree.remove(1)==AVL_KEY_DOESNT_EXISTS);
    assert(1==tree.NodeHeight(4));

    assert(tree.remove(4)==AVL_SUCCESS);
    assert(tree.remove(4)==AVL_KEY_DOESNT_EXISTS);

*/

#define WET1_DATASTRUCTS_AVL_TESTS_H

#endif //WET1_DATASTRUCTS_AVL_TESTS_H
