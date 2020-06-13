


/* OLD CODE FROM WET1



#include "List.h"


void StreamList::deleteAllStreamNodes(StreamListNode* node) {
    if(node){
        deleteAllStreamNodes((node->getNextNode()));
        delete(node);
    }
}

StreamList::~StreamList(){
    if(first_node){
        deleteAllStreamNodes(first_node);
    }
}


// inserts after the curr_node
StreamListResult StreamList::insertNode(StreamListNode* curr_node, AvlTree<AvlTree<int,int>*,int>& stream_artists, int num_of_streams) {

    // num_of_streams exists for sure - checked in thhe caller function

    StreamListNode* new_node = new StreamListNode(stream_artists,num_of_streams); // why new?

    if(curr_node->getNextNode() != nullptr){
        new_node->SetNextNode(curr_node->getNextNode());
        curr_node->getNextNode()->SetPrevNode(new_node);
    }
    new_node->SetPrevNode(curr_node);
    curr_node->SetNextNode(new_node);

    if(curr_node == last_node){
        last_node = curr_node->getNextNode();
    }

    return SL_SUCCESS;

}

StreamListResult StreamList::removeNode(StreamListNode* node) {

    // num_of_streams exists for sure - checked in thhe caller function

    if(node->getNextNode() == nullptr){
        last_node = node->getPrevNode();
    }
    else{
        node->getNextNode()->SetPrevNode(node->getPrevNode());
    }
    if(node != first_node){
        node->getPrevNode()->SetNextNode(node->getNextNode());
    }

    delete(node);
    return SL_SUCCESS;

}
