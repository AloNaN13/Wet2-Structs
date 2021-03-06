
#ifndef WET2_STRUCTS_LIST_H
#define WET2_STRUCTS_LIST_H

#include "Artist.h"

typedef enum ListResult_t{
    LIST_SUCCESS,
    //LIST_ALLOCATION_ERROR,
    //LIST_NODE_ALREADY_EXISTS,
    //LIST_NODE_DOESNT_EXISTS
}ListResult;

class ListNode{
private:
    const int key;
    Artist* artist;
    ListNode* prev_node;
    ListNode* next_node;
public:
    // the artist is created and deleted outside of the node
    explicit ListNode(Artist* artist): key(artist->GetArtistID()), artist(artist), prev_node(nullptr), next_node(nullptr) {};
    ~ListNode() = default;
    ListNode(const ListNode& node) = default;
    ListNode& operator=(const ListNode& node) = default;

    int getNodeKey() { return this->key;};
    Artist* getArtistFromNode() { return this->artist;};
    void setPrevNode(ListNode* new_prev) { this->prev_node=new_prev;};
    ListNode* getPrevNode() { return this->prev_node;};
    void setNextNode(ListNode* new_next) { this->next_node=new_next;};
    ListNode* getNextNode() { return this->next_node;};

};

class List{
private:
    // notice - implemented with the Node out of the List
    // no use of an iterator - could have
    int list_size;
    ListNode* first_node;
    ListNode* last_node;

    static void deleteAllListNodes(ListNode* node);

public:
    List(): list_size(0), first_node(nullptr), last_node(nullptr) {};
    ~List();
    List(const List& other_list) = default;
    List& operator=(const List& list) = default;

    ListNode* getListFirstNode() {return this->first_node;};
    ListNode* getListLastNode() {return this->last_node;};
    ListResult insertNodeToList(ListNode* node_to_insert);
    ListResult removeNodeFromList(ListNode* node_to_remove);

};

#endif //WET2_STRUCTS_LIST_H
