



#ifndef WET2_STRUCTS_HASHTABLE_H
#define WET2_STRUCTS_HASHTABLE_H



#include "List.h"

typedef enum hash_for_t{
    REGULAR,
    EXPAND,
    SHRINK
};

typedef enum HashResult_t{
    HASH_SUCCESS,
    HASH_ALLOCATION_ERROR,
    HASH_KEY_ALREADY_EXISTS,
    HASH_KEY_DOESNT_EXISTS
}HashResult;





// Check ENUM ERRORS IN FUNCTIONS
// Check expand and shrink - working properly? deleting the old table properly?



class HashTable{
private:
    List* table;
    int table_size;
public:
    explicit HashTable(int table_size): table_size(table_size), table(new List[table_size]) {}; // improve the new?
    ~HashTable() {delete[] table;};
    HashTable(const HashTable& hash) = delete; //implement?
    HashTable& operator=(const HashTable& hash) = delete; //implement?

    int hashFunction(int key, int hash_for);
    ListNode* hashFindNode(int key);
    HashResult hashInsertNode(ListNode* node_to_insert);
    HashResult hashDeleteNode(int key);

    HashTable* expandHash();
    HashTable* shrinkHash();

    // printHash?

};




int HashTable::hashFunction(int key, int hash_for){
    if(hash_for == EXPAND){
        return (key % (this.table_size*2));
    }
    if(hash_for == SHRINK){
        return (key % (this.table_size/2));
    }
    return (key % this.table_size);
}

ListNode* HashTable::hashFindNode(int key){
    int hashed_key = hashFunction(key, REGULAR);
    ListNode* curr_node = table[hashed_key].getListFirstNode();
    for(; curr_node != nullptr; curr_node = curr_node->getNextNode()){
        if(curr_node->getNodeKey() == key){
            return curr_node;
        }
    }
    return nullptr;

    //should return HashResult?

}

HashResult HashTable::hashInsertNode(ListNode* node_to_insert){
    int hashed_key = hashFunction(node_to_insert->getArtistFromNode()->GetArtistID(), REGULAR);
    table[hashed_key].insertNodeToList(node_to_insert);
    return HASH_SUCCESS;
}

HashResult HashTable::hashDeleteNode(int key){
    //get the hashed_key of the artist
    int hashed_key = hashFunction(key, REGULAR);
    ListNode* curr_node = table[hashed_key].getListFirstNode();
    for(; curr_node != nullptr; curr_node = curr_node->getNextNode()){
        if(curr_node->getNodeKey() == key){
            table[hashed_key].removeNodeFromList(curr_node);
        }
    }

    return HASH_SUCCESS;
}


HashTable* HashTable::expandHash(){
    List* new_table = new List[table_size*2];
    for(int i=0; i<table_size; i++){
        ListNode* curr_node = this->table[i].getListFirstNode();
        for(; curr_node != nullptr; curr_node = curr_node->getNextNode()){
            node_to_insert(*curr_node);
            int hashed_key = hashFunction(node_to_insert->getArtistFromNode()->GetArtistID(), EXPAND);
            new_table[hashed_key].insertNodeToList(&node_to_insert);
        }
    }
    List* temp = this->table;
    this->table = new_table;
    delete[] table;

    HashResult HASH_SUCCESS;
}

HashTable* HashTable::shrinkHash(){
    List* new_table = new List[table_size/2];
    for(int i=0; i<table_size; i++){
        ListNode* curr_node = this->table[i].getListFirstNode();
        for(; curr_node != nullptr; curr_node = curr_node->getNextNode()){
            node_to_insert(*curr_node);
            int hashed_key = hashFunction(node_to_insert->getArtistFromNode()->GetArtistID(), SHRINK);
            new_table[hashed_key].insertNodeToList(&node_to_insert);
        }
    }
    List* temp = this->table;
    this->table = new_table;
    delete[] table;

    HashResult HASH_SUCCESS;

}


#endif //WET2_STRUCTS_HASHTABLE_H
