


/* OLD CODE FROM WET1



#ifndef WET1_STRUCTS_LIST_H
#define WET1_STRUCTS_LIST_H

#include "AvlTree.h"


typedef enum StreamListResult_t{
    SL_SUCCESS,
    //SL_ALLOCATION_ERROR,
    //SL_NODE_ALREADY_EXISTS,
    //SL_NODE_DOESNT_EXISTS
}StreamListResult;

class StreamListNode{
private:
    const int num_of_streams;
    AvlTree<AvlTree<int,int>*,int>& stream_artists;
    StreamListNode* prev_node;
    StreamListNode* next_node;
public:
    explicit StreamListNode(int num_of_streams): num_of_streams(num_of_streams),
            stream_artists(*(new AvlTree<AvlTree<int,int>*,int>())), prev_node(nullptr),
            next_node(nullptr) {};
    StreamListNode(AvlTree<AvlTree<int,int>*,int>& stream_artists, int num_of_streams):
            num_of_streams(num_of_streams), stream_artists(stream_artists),
            prev_node(nullptr), next_node(nullptr) {};
    ~StreamListNode() {delete(&stream_artists);};
    //StreamListNode(const StreamListNode& node) = delete;
    //StreamListNode& operator=(const StreamListNode& node) = delete;

    int GetNodeNumOfStreams() {return this->num_of_streams;};
    StreamListNode* getPrevNode() { return this->prev_node;};
    void SetPrevNode(StreamListNode* new_prev) { this->prev_node=new_prev;};
    StreamListNode* getNextNode() { return this->next_node;};
    void SetNextNode(StreamListNode* new_next) { this->next_node=new_next;};
    AvlTree<AvlTree<int,int>*,int>& getNodeAvlTree() {return this->stream_artists; };
    //ListNode& getNodeFromKey(const Key key);

};

class StreamList{
private:

    // notice - implemented with the Node out of the List

    StreamListNode* first_node;
    StreamListNode* last_node;
    // no use of an iterator - could have

public:
    StreamList(): first_node(new StreamListNode(0)), last_node(nullptr) {
        last_node = first_node;
    };
    ~StreamList();
    void deleteAllStreamNodes(StreamListNode* node);
    StreamList& operator=(const StreamList& list) = default;

    StreamListNode* GetListFirstNode() {return this->first_node;};
    StreamListNode* GetListLastNode() {return this->last_node;};

    //void SetListFirstNode(StreamListNode* node) {this->first_node = node;}; // void?
    //void SetListLastNode(StreamListNode* node) {this->last_node = node;}; // void?
    //AvlTree<AvlTree<int,int>*,int>& getAvlTreeFromNode(StreamListNode& node) {return node.getNodeAvlTree();};

    //StreamListNode* getNodePrev(StreamListNode* node) { return node->getPrevNode();};
    //StreamListNode* getNodeNext(StreamListNode* node) { return node->getNextNode();};

    StreamListResult insertNode(StreamListNode* curr_node, AvlTree<AvlTree<int,int>*,int>& stream_artists, int num_of_streams);
    StreamListResult removeNode(StreamListNode* node);

};


#endif //WET1_STRUCTS_LIST_H
