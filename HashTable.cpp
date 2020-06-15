
#include "HashTable.h"

int HashTable::hashFunction(int key, int hash_for){
    if(hash_for == EXPAND){
        return (key % (this->table_size*2));
    }
    if(hash_for == SHRINK){
        return (key % (this->table_size/2));
    }
    if(hash_for == REGULAR){
        return (key % this->table_size);
    }

    // doesnt get here
    return 0;
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

HashResult HashTable::hashRemoveNode(int key){
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


HashResult HashTable::expandHash(){
    List* new_table = new List[table_size*2];
    for(int i=0; i<table_size; i++){
        ListNode* curr_node = this->table[i].getListFirstNode();
        for(; curr_node != nullptr; curr_node = curr_node->getNextNode()){
            ListNode node_to_insert(*curr_node);
            int hashed_key = hashFunction(node_to_insert.getArtistFromNode()->GetArtistID(), EXPAND);
            new_table[hashed_key].insertNodeToList(&node_to_insert);
        }
    }
    List* temp = this->table;
    this->table = new_table;
    this->table_size = table_size*2;
    delete[] table;

    HashResult HASH_SUCCESS;
}

HashResult HashTable::shrinkHash(){
    List* new_table = new List[table_size/2];
    for(int i=0; i<table_size; i++){
        ListNode* curr_node = this->table[i].getListFirstNode();
        for(; curr_node != nullptr; curr_node = curr_node->getNextNode()){
            ListNode node_to_insert(*curr_node);
            int hashed_key = hashFunction(node_to_insert.getArtistFromNode()->GetArtistID(), SHRINK);
            new_table[hashed_key].insertNodeToList(&node_to_insert);
        }
    }
    List* temp = this->table;
    this->table = new_table;
    this->table_size = table_size/2;
    delete[] table;

    HashResult HASH_SUCCESS;

}

