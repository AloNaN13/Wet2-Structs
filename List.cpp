



// implement changes






#include "List.h"


// return value? SUCCESS?
void List::deleteAllListNodes(ListNode* node) {
    if(node){
        List::deleteAllListNodes((node->getNextNode()));
        delete(node);
    }
}

List::~List(){
    if(first_node){
        List::deleteAllListNodes(first_node);
    }
}


// inserts after the curr_node
ListResult List::insertNodeToList(ListNode* node_to_insert){

    // check if node already exists?
    // remember to create node in the function before we insert it to the list!!!

    if(this->first_node == nullptr){
        first_node = node_to_insert;
        last_node = node_to_insert;
    }
    else{
        node_to_insert->setNextNode(first_node);
        first_node->setPrevNode(node_to_insert);
        first_node = node_to_insert;
    }

    list_size++;
    return LIST_SUCCESS;

}

ListResult List::removeNodeFromList(ListNode* node_to_remove){

    // check if node even exists - I checked in the caller function

    if(node_to_remove->getNextNode() == nullptr){
        last_node = node_to_remove->getPrevNode();
    }
    else{
        node_to_remove->getNextNode()->setPrevNode(node_to_remove->getPrevNode());
    }

    if(node_to_remove == first_node){
        first_node = node_to_remove->getNextNode();
    }
    else{
        node_to_remove->getPrevNode()->setNextNode(node_to_remove->getNextNode());
    }

    list_size--;
    delete(node_to_remove);
    return LIST_SUCCESS;

}
