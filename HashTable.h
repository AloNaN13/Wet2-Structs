



#ifndef WET2_STRUCTS_HASHTABLE_H
#define WET2_STRUCTS_HASHTABLE_H



#include "List.h"

enum{
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

    int getHashTableSize() { return this->table_size;};
    int hashFunction(int key, int hash_for);
    ListNode* hashFindNode(int key);
    HashResult hashInsertNode(ListNode* node_to_insert);
    HashResult hashRemoveNode(int key);

    HashResult expandHash();
    HashResult shrinkHash();

    // printHash?
    // FOR CHECK
    List& getIndexOfTable(){ return table[3];};


};







#endif //WET2_STRUCTS_HASHTABLE_H
