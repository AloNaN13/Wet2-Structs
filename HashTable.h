
#ifndef WET2_STRUCTS_HASHTABLE_H
#define WET2_STRUCTS_HASHTABLE_H



#include "List.h"

typedef enum HashResult_t{
    HASH_SUCCESS,
    HASH_ALLOCATION_ERROR,
    HASH_KEY_ALREADY_EXISTS,
    HASH_KEY_DOESNT_EXISTS
}HashResult;





//Check ENUM ERRORS IN FUNCTIONS
// Do I need to create a real list for every index in the hash? or is pointer enough?
//implement dtor?




class HashTable{
private:
    List* table;
    int table_size;
public:
    /*explicit*/ HashTable(int table_size): table_size(table_size), table(new List[table_size]) {}; // improve the new?
    ~HashTable() {delete[] table;};
    HashTable(const HashTable& hash) = delete; //implement?
    HashTable& operator=(const HashTable& hash) = delete; //implement?

    int hashFunction(int key);
    HashResult hashInsertNode(ListNode* node_to_insert);
    HashResult hashDeleteNode(int key);

    HashTable* expandHash();
    HashTable* shrinkHash();

    // printHash?

};





int HashTable::hashFunction(int key){
    return (key % this.table_size);
}

HashResult HashTable::hashInsertNode(ListNode* node_to_insert){
    int hashed_key = hashFunction(node_to_insert->getArtistFromNode()->GetArtistID());
    table[hashed_key].insertNodeToList(node_to_insert);
    return HASH_SUCCESS;
}

HashResult HashTable::hashDeleteNode(int key){
    //get the hashed_key of the artist
    int hashed_key = hashFunction(key);
    ListNode* curr_node = table[hashed_key].getListFirstNode();
    for(; curr_node != nullptr; curr_node = curr_node->getNextNode()){
        if(curr_node->getNodeKey() == key){
            table[hashed_key].removeNodeFromList(curr_node);
        }
    }

    return HASH_SUCCESS;
}


HashTable* HashTable::expandHash(){
    HashTable();
}

HashTable* HashTable::shrinkHash(){
    ;
}








#endif //WET2_STRUCTS_HASHTABLE_H
