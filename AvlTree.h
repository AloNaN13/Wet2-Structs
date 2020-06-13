





#ifndef MIVNE_AVLTREE_H
#define MIVNE_AVLTREE_H

//#define MAX(a, b) ((a > b) ? a : b)

#include <cmath>
#include <iostream>
#include <assert.h>

using namespace std;

typedef enum AvlTreeResult_t{AVL_KEY_ALREADY_EXISTS,AVL_SUCCESS,AVL_ALLOCATION_ERROR
,AVL_KEY_DOESNT_EXISTS
}AvlTreeResult;

template <class Element,class Key>
class AvlTree {
private:
    class Node{
    public:
        Element& data;
        const Key& key;
        Node* right_son;
        Node* left_son;
        Node* parent;
        int hl;
        int hr;
        int size_sub_tree;
        int size_left_sub_tree;
        int size_right_sub_tree;

        Node(const Element& data,const Key& key):data(*(new Element(data))),key(*(new Key(key))),right_son(nullptr)
                ,left_son(nullptr),parent(nullptr),hl(0),hr(0),size_sub_tree(1),
                size_left_sub_tree(0),size_right_sub_tree(0){};
        ~Node(){
            delete &data;
            delete &key;
        };
        Node& operator=(const Node&)= default;
        int getHeight(){
            if(hl>hr){
                return 1+hl;
        }
            return 1+hr;
        };
        int getSubTreeSize(){ return size_sub_tree;};
        int getBalanceFactor();

        Node* getParent(){ return parent;};
        Node& getNodeFromKey(const Key key);
        Node* FindNext();
    };

    Node* root;
    Node* iterator;
    Node* first;
    Node* last;
    int numOfNodes;
    void swapNodes(Node *node_to_del,Node* next_by_value);

    Node* removeBinarySearch(Node* node_to_del);
    void InsertNode(Node &newNode);
    void deleteAllNodes(Node* node);
    void BalanceInsert(Node& insertedNode);
    void BalanceRemove(Node* node);
    void rotateLeft(Node& node);
    void rotateRight(Node& node);
    void fixHeightAfterInsert(Node& inserted_node);
    void fixHeightAfterRemove(Node* parent_of_removed);
    void fixHeightAfterRotation(Node* rotated_node);
    Node* buildTreeFromArrays(Element* arrElement, Key* arrKey, int len );
    static Node* copyNodes(Node* current,const Node* Node_to_copy);
public:
    AvlTree():root(nullptr),iterator(nullptr),first(nullptr),last(nullptr),numOfNodes(0){};
    AvlTree(Element* arrElement, Key* arrKey, int num);
    ~AvlTree();
    AvlTree(const AvlTree& other);
    AvlTree& operator=(const AvlTree&)= default;

    AvlTreeResult insert (const Element& ele, const Key& key);
    AvlTreeResult remove (const Key& key);
    int getHeight(){ return root->getHeight();};
    Element* getElementptr(const Key& key);
    Element* getFirst();
    Element* getNext();
    Element* getLast();
    Element* getPrevious();
    const Key& getKey(){return iterator->key;}
    bool findKeyAlreadyExists(const Key& key);
    int getNumNodes() const { return numOfNodes;}

    //newt 2 functions for testing
    void clear(){
        if (root != nullptr) {
            deleteAllNodes(root);
        }
        root= nullptr;
        first= nullptr;
        last= nullptr;
        iterator= nullptr;
    }
    void printTreeInOrder(Node* startingNode);
    const Node* getRoot() const { return  root;}

};



/***
 * The copy ctor of the Tree, creates a new tree that looks exactly the same as th other tree
 * @param other-the AvlTree that need to be copied
 */
template <class Element,class Key>
AvlTree<Element,Key>::AvlTree(const AvlTree& other):root(nullptr),iterator(nullptr),first(nullptr),
                                                    last(nullptr),numOfNodes(0){
    root=copyNodes(root,other.getRoot());
    first=root;
    while (first &&first->left_son){
        first=first->left_son;
    }
    last=root;
    while(root &&root->right_son){
        root=root->right_son;
    }
    this->numOfNodes=other.getNumNodes();
    //root=new Node(other_root->data,other_root->key);
}

/***
 * a recursic helper fucntion, thats called from the copy ctor of the tree,
 * allocates new memory and copies all the nodes using recursion
 * @param current -The node we want to put in the arguments of Node_to_copy
 * @param Node_to_copy -The Node that we want to copy
 * @return -a pointer to current
 */
template <class Element,class Key>
typename AvlTree<Element,Key>::Node* AvlTree<Element,Key>::copyNodes(Node* current,const Node *Node_to_copy) {
    if(!Node_to_copy){
        return nullptr ;
    }
    current=new Node(Node_to_copy->data,Node_to_copy->key);
    current->right_son=copyNodes(current->right_son,Node_to_copy->right_son);
    if(current->right_son){
        current->right_son->parent=current;
    }
    current->left_son=copyNodes(current->left_son,Node_to_copy->left_son);
    if(current->left_son){
        current->left_son->parent=current;
    }
    current->size_sub_tree=Node_to_copy->size_sub_tree;
    if(Node_to_copy->size_right_sub_tree>0){
        current->size_right_sub_tree=Node_to_copy->size_right_sub_tree;
    }
    if(Node_to_copy->size_left_sub_tree>0){
        current->size_left_sub_tree=Node_to_copy->size_left_sub_tree;

    }
    current->hr=Node_to_copy->hr;
    current->hl=Node_to_copy->hl;
    return current;
}


/***
 * constractor to the tree that creaets a new tree with num Nodes, with complesity O(num),
 * because it enters  the nodes to the tree in such order that balancing wont be
 * necessery(using buildTreeFromArrays func)
 * @param arrElement- sorted array of elements
 * @param arrKey- sorted array of keys
 * @param num - the length of the 2 arrays
 */
template <class Element,class Key>
AvlTree<Element,Key>::AvlTree(Element *arrElement, Key *arrKey, int num):root(nullptr)
                                                ,iterator(nullptr),first(nullptr),last(nullptr){
    root=buildTreeFromArrays(arrElement,arrKey,num);
    first=root;
    while(first && first->left_son){
        first=first->left_son;
    }
    last=root;
    while(root &&root->right_son){
        root=root->right_son;
    }
}

/***
 * creates len nodes using recursion where in the node i there is element that equals to arrElement[i]
 * and the key equals to arrKey[i], the time complecity of the func is O(len),
 * than the first Node we created will be the root of the new tree we created in the constractor
 * that gets 3 arguments, balancing wont be necessery because we using the fact that the arrays are sorted.
 * @param arrElement- sorted array of elements
 * @param arrKey- sorted array of keys
 * @param len - the length of the 2 arrays
 */
template <class Element,class Key>
typename AvlTree<Element,Key>::Node* AvlTree<Element,Key>::
        buildTreeFromArrays (Element* arrElement, Key* arrKey, int len ){
            if(len==0){
                return nullptr;
            }
            int current_index=(int)(len/2);
            Node* currentNode=new Node(arrElement[current_index],arrKey[current_index]);
            currentNode->left_son=buildTreeFromArrays(arrElement,arrKey,current_index);
            currentNode->right_son=buildTreeFromArrays(arrElement+current_index+1,arrKey+current_index+1,len-current_index-1);
            if(currentNode->right_son!= nullptr){
                currentNode->right_son->parent=currentNode;
                currentNode->hr=currentNode->right_son->getHeight();
                currentNode->size_right_sub_tree=currentNode->right_son->size_sub_tree;
                currentNode->size_sub_tree=currentNode->size_sub_tree+currentNode->right_son->getSubTreeSize();
            }
            else{
                currentNode->hr=0;
            }
            if(currentNode->left_son!= nullptr){
                currentNode->left_son->parent= currentNode;
                currentNode->hl=currentNode->left_son->getHeight();
                currentNode->size_left_sub_tree=currentNode->left_son->size_left_sub_tree;
                currentNode->size_sub_tree=currentNode->size_sub_tree+currentNode->left_son->getSubTreeSize();
            } else{
                currentNode->hl=0;
            }
    return currentNode;
}

/***
 * sets the iterator to the minimal node(by key) in the tree and returns a pointer
 * to his data
 * @return -pointer to the data of the minimal Node in the tree, null_ptr if the tree is empty
 */
template <class Element,class Key>
Element* AvlTree<Element,Key>::getFirst() {
    if(root== nullptr){
        return nullptr;
    }
    iterator=first;
    return &iterator->data;
}
/***
 * sets the iterator to the maximal node(by key) in the tree and returns a pointer
 * to his data
 * @return -pointer to the data of the maximal Node in the tree, null_ptr if the tree is empty
 */
template <class Element,class Key>
Element* AvlTree<Element,Key>::getNext() {
    if(root== nullptr){
        return nullptr;
    }
    iterator=last;
    return &iterator->data;
}

/***
 * sess iterator to the next Node by order in the tree and returns its data, if
 * the iterator is already on the largest tree in the node, than it sets the iterator
 * to null_ptr
 * @return -the above if its possible, returns null_ptr if the iterator is null,
 * or if its in the largest Node in the tree,
 */
template <class Element,class Key>
Element* AvlTree<Element,Key>::getNext() {
    if(iterator== nullptr){
        return nullptr;
    }
    if(iterator->right_son){
        iterator=iterator->right_son;
        while (iterator->left_son){
            iterator=iterator->left_son;
        }
        return &iterator->data;
    }
    while (iterator->parent &&iterator->parent->right_son==iterator){
        iterator=iterator->parent;
    }
    if(iterator->parent== nullptr){
        iterator=iterator->parent;
        return nullptr;
    }
    iterator=iterator->parent;
    return &iterator->data;
}

template <class Element,class Key>
Element* AvlTree<Element,Key>::getPrevious() {
    if(iterator== nullptr){
        return nullptr;
    }
    if(iterator->left_son){
        iterator=iterator->left_son;
        while (iterator->right_son){
            iterator=iterator->right_son;
        }
        return &iterator->data;
    }
    if(!iterator->parent){//the case where we are in the root and no left sons
        iterator= nullptr;
        return nullptr;
    }
    if(iterator->parent->right_son==iterator){
        iterator=iterator->parent;
        return &iterator->data;
    }
    //we are in the minimal node
    iterator= nullptr;
    return nullptr;
}

/***
 *
 * @param key- the key of the data we want to get
 * @return - a pointer to the element of the node with Key of the key we get,
 * null_ptr if such dose'nt exicts
 */
template <class Element,class Key>
Element* AvlTree<Element,Key>::getElementptr(const Key &key) {
    if(!findKeyAlreadyExists(key)){
        return nullptr;
    }
    Node& wanted=root->getNodeFromKey(key);
    return &wanted.data;
}
///fixes the height + the size_sub_tree
template <class Element,class Key>
void AvlTree<Element,Key>:: fixHeightAfterInsert(Node& inserted_node){
    inserted_node.hl=0;
    inserted_node.hr=0;
    Node* parent=inserted_node.parent;
    Node*  tmp=&inserted_node;
    while (parent!=nullptr){
        if(parent->left_son==tmp){
            parent->hl=tmp->getHeight();
        } else if(parent->right_son==tmp){
            parent->hr=tmp->getHeight();
        }
        parent->size_sub_tree++;
        if(parent->right_son){
            parent->size_right_sub_tree=parent->right_son->size_sub_tree;
        }
        ir(parent->left_son){
            parent->size_left_sub_tree=parent->left_son->size_sub_tree;
        }
        tmp=parent;
        parent=tmp->parent;
    }
}

template <class Element,class Key>
void AvlTree<Element,Key>::fixHeightAfterRemove(Node* parent_of_removed) {
    if(!parent_of_removed){
        return;
    }
    Node* tmp=parent_of_removed;
    Node* parent=parent_of_removed->parent;
    if(parent_of_removed->right_son== nullptr){
        parent_of_removed->hr=0;
        parent_of_removed->size_right_sub_tree=0;

    } else{
        parent_of_removed->hr=parent_of_removed->right_son->getHeight();
        parent_of_removed->size_right_sub_tree=parent_of_removed->right_son->size_sub_tree;
    }
    if(parent_of_removed->left_son== nullptr){
        parent_of_removed->hl=0;
        parent_of_removed->size_left_sub_tree=0;
    } else{
        parent_of_removed->hl=parent_of_removed->left_son->getHeight();
        parent_of_removed->size_left_sub_tree=parent_of_removed->left_son->size_sub_tree;
    }
    parent_of_removed->size_sub_tree=1+parent_of_removed->size_left_sub_tree+parent_of_removed->size_right_sub_tree;
    while (parent!=nullptr){
        if(parent->left_son==tmp){
            parent->hl=tmp->getHeight();
            parent->size_left_sub_tree=parent->left_son->size_sub_tree;
        } else if(parent->right_son==tmp){
            parent->hr=tmp->getHeight();
            parent->size_right_sub_tree=parent->right_son->size_sub_tree;
        }
        tmp=parent;
        parent=tmp->parent;
    }
}

template <class Element,class Key>
void AvlTree<Element,Key>::fixHeightAfterRotation(Node* rotated_Node) {
    Node* tmp=rotated_Node->parent;
    if(!rotated_Node->left_son){
        rotated_Node->hl=0;
    }else{
        rotated_Node->hl=rotated_Node->left_son->getHeight();
    }
    if(!rotated_Node->right_son){
        rotated_Node->hr=0;
    } else{
        rotated_Node->hr=rotated_Node->right_son->getHeight();
    }
    while (tmp!= nullptr){
        if(tmp->left_son==rotated_Node){
            tmp->hl=rotated_Node->getHeight();
        }
        else{
            tmp->hr=rotated_Node->getHeight();
        }
        rotated_Node=tmp;
        tmp=rotated_Node->parent;
    }
}

template <class Element,class Key>
int AvlTree<Element,Key>::Node::getBalanceFactor() {
    if(!this){
        return 0;
    }
    if(this->right_son== nullptr){
        if(this->left_son== nullptr){
            return 0;
        }
        return left_son->getHeight();
    }
    if(this->left_son== nullptr){
        return -right_son->getHeight();
    }
    return left_son->getHeight()-right_son->getHeight();
}

//caleed only if we are sure there is a node
template <class Element,class Key>
typename AvlTree<Element,Key>::Node&  AvlTree<Element,Key>::Node::getNodeFromKey(const Key key){
    Node* tmp=this;
    while (tmp!= nullptr){
        if(tmp->key==key){
            return *tmp;
        }
        if(tmp->key<key){
            tmp=(tmp->right_son);
        }
        else{
            tmp= (tmp->left_son);
        }
    }

    // does not reach here - only for the compiler's warning
    return *tmp;
}

template <class Element,class Key>
typename AvlTree<Element,Key>::Node* AvlTree<Element,Key>::Node::FindNext() {
    Node *nextByOrder=this->right_son;
    if(nextByOrder== nullptr){
        return this;
    }
    while(nextByOrder->left_son){
        nextByOrder=nextByOrder->left_son;
    }
    return nextByOrder;
}
/***
 * the destractor of the tree, first deletes all the nodes so there won't be memoryLeak
 */
template <class Element,class Key>
AvlTree<Element,Key>::~AvlTree(){
    if(root){
        deleteAllNodes(root);
    }
    first= nullptr;
    last= nullptr;
    root= nullptr;
    iterator= nullptr;
}
/***
 * deletes all the nodes of the tree using postOrder algo,
 * @param node -the node we want to delete
 */
template <class Element,class Key>
void AvlTree<Element,Key>::deleteAllNodes(Node *node) {
    if(node){
        deleteAllNodes((node->right_son));
        deleteAllNodes((node->left_son));
        delete(node);
    }
}

template <class Element,class Key>
void AvlTree<Element,Key>::rotateLeft(AvlTree<Element, Key>::Node &node) {
    if(node.right_son== nullptr){
        return;
    }
    Node* B=node.right_son;
    Node* parent=node.parent;
    if(parent== nullptr){
        node.right_son=B->left_son;
        if(B->left_son){
            B->left_son->parent=&node;
            node.size_right_sub_tree=node.right_son->size_sub_tree;
            node.size_sub_tree=1+node.size_right_sub_tree+node.size_left_sub_tree;
        } else{
            node.size_right_sub_tree=0;
            node.size_sub_tree=1+node.size_right_sub_tree+node.size_left_sub_tree;
        }
        B->left_son=&node;
        B->parent= nullptr;
        node.parent=B;
        node.hr=node.hl;
        B->hl++;
        root=B;
        B->size_left_sub_tree=B->left_son->size_sub_tree;
        B->size_sub_tree=1+B->size_right_sub_tree+B->size_left_sub_tree;
        return;
    }
    //else
    if(parent->right_son==&node){
        node.right_son=B->left_son;
        if(B->left_son){
            B->left_son->parent=&node;
            node.size_right_sub_tree=node.right_son->size_sub_tree;
            node.size_sub_tree=1+node.size_right_sub_tree+node.size_left_sub_tree;
        }
        else{
            node.size_right_sub_tree=0;
            node.size_sub_tree=1+node.size_right_sub_tree+node.size_left_sub_tree;
        }
        B->left_son=&node;
        B->parent= parent;
        parent->right_son=B;
        node.parent=B;
        node.hr=node.hl;
        B->hl++;
        B->size_left_sub_tree=B->left_son->size_sub_tree;
        B->size_sub_tree=1+B->size_right_sub_tree+B->size_left_sub_tree;
        return;
    }
    node.right_son=B->left_son;
    if(B->left_son){
        B->left_son->parent=&node;
        node.size_right_sub_tree=node.right_son->size_sub_tree;
        node.size_sub_tree=1+node.size_right_sub_tree+node.size_left_sub_tree;
    }  else{
        node.size_right_sub_tree=0;
        node.size_sub_tree=1+node.size_right_sub_tree+node.size_left_sub_tree;
    }
    B->left_son=&node;
    B->parent= parent;
    parent->left_son=B;
    node.parent=B;
    node.hr=node.hl;
    B->hl++;
    B->size_left_sub_tree=B->left_son->size_sub_tree;
    B->size_sub_tree=1+B->size_right_sub_tree+B->size_left_sub_tree;
}
template <class Element,class Key>
void AvlTree<Element,Key>::rotateRight(AvlTree<Element, Key>::Node &node) {
    if(node.left_son== nullptr){
        return;
    }
    Node* A=node.left_son;
    Node*parent=node.getParent();
    if(parent== nullptr){
        node.left_son=A->right_son;
        if(A->right_son){
            A->right_son->parent=&node;
            node.size_left_sub_tree=node.left_son->size_sub_tree;
            node.size_sub_tree=1+node.size_left_sub_tree+node.size_right_sub_tree;
        }
        else{
            node.size_left_sub_tree=0;
            node.size_sub_tree=1+node.size_left_sub_tree+node.size_right_sub_tree;
        }
        A->right_son=&node;
        A->parent= nullptr;
        node.parent=A;
        node.hl=node.hr;
        A->hr++;
        A->size_right_sub_tree=node.size_sub_tree;
        A->size_sub_tree=1+A->size_left_sub_tree+A->size_right_sub_tree;
        root=A;
        return;
    }
    //else
    if(parent->right_son==&node){
        node.left_son=A->right_son;
        if(A->right_son){
            A->right_son->parent=&node;
            node.size_left_sub_tree=node.left_son->size_sub_tree;
            node.size_sub_tree=1+node.size_left_sub_tree+node.size_right_sub_tree;
        }
        else{
            node.size_left_sub_tree=0;
            node.size_sub_tree=1+node.size_left_sub_tree+node.size_right_sub_tree;
        }
        A->right_son=&node;
        A->parent=parent;
        parent->right_son=A;
        node.parent=A;
        node.hl=node.hr;
        A->hr++;
        A->size_right_sub_tree=node.size_sub_tree;
        A->size_sub_tree=1+A->size_left_sub_tree+A->size_right_sub_tree;
        return;
    }
    node.left_son=A->right_son;
    if(A->right_son){
        A->right_son->parent=&node;
        node.size_left_sub_tree=node.left_son->size_sub_tree;
        node.size_sub_tree=1+node.size_left_sub_tree+node.size_right_sub_tree;
    }
    A->right_son=&node;
    A->parent=parent;
    parent->left_son=A;
    node.parent=A;
    node.hl=node.hr;
    A->hr++;
    A->size_right_sub_tree=node.size_sub_tree;
    A->size_sub_tree=1+A->size_left_sub_tree+A->size_right_sub_tree;
}

template <class Element,class Key>
void AvlTree<Element,Key>::InsertNode(Node &newNode){
   if(root== nullptr){
        root=&newNode;
        return;
    }
    Node*tmp=root;
    while(tmp!= nullptr){
        if(tmp->key<newNode.key){
            if(tmp->right_son== nullptr){
                tmp->right_son=&newNode;
                newNode.parent=tmp;
                fixHeightAfterInsert(newNode);
                BalanceInsert(newNode);
                return;
            }
            tmp=tmp->right_son;
        }
        else {
            if(tmp->left_son== nullptr){
                tmp->left_son=&newNode;
                newNode.parent=tmp;
                fixHeightAfterInsert(newNode);
                BalanceInsert(newNode);
                //tmp->hl=tmp->hl+1;

                return;
            }
            tmp=tmp->left_son;

        }
    }
}

//deletes the node and returns a pointer to the father, null is such doesnt exists
template <class Element,class Key>
typename AvlTree<Element,Key>::Node* AvlTree<Element,Key>::removeBinarySearch(Node* node_to_del) {

    if(node_to_del->right_son!= nullptr &&node_to_del->left_son!=nullptr){
        Node* next_by_value=node_to_del->FindNext();
        swapNodes(node_to_del,next_by_value);
    }
    Node* parent=node_to_del->parent;

    if(parent== nullptr){//the tree has maximum 2 nodes
        if(node_to_del->right_son!= nullptr){
            node_to_del->right_son->parent= nullptr;
            root=node_to_del->right_son;
            delete(node_to_del);
            return root;
        } else if(node_to_del->left_son!= nullptr){
            node_to_del->left_son->parent= nullptr;
            root=node_to_del->left_son;
            delete(node_to_del);
            return root;
        } else{
            delete (node_to_del);
            root= nullptr;
            return nullptr;
        }

    }

    if(node_to_del->left_son==nullptr&& node_to_del->right_son== nullptr){//its a leaf
        if(parent->right_son==node_to_del){
            parent->right_son= nullptr;
            delete node_to_del;
            fixHeightAfterRemove(parent);
            return parent;
        }
        parent->left_son= nullptr;
        delete node_to_del;
        fixHeightAfterRemove(parent);
        return parent;
    }

    if(node_to_del->left_son== nullptr){//has only a right child
        if(parent->right_son==node_to_del){
            parent->right_son=node_to_del->right_son;
            node_to_del->right_son->parent=parent;
            delete node_to_del;
            fixHeightAfterRemove(parent);
            return parent;
        }
        parent->left_son=node_to_del->right_son;
        node_to_del->right_son->parent=parent;
        delete node_to_del;
        fixHeightAfterRemove(parent);
        return parent;
    }

    if(node_to_del->right_son== nullptr){//has only a left child

        if(parent->right_son==node_to_del){
            parent->right_son=node_to_del->left_son;
            node_to_del->left_son->parent=parent;
            delete node_to_del;
            fixHeightAfterRemove(parent);
            //parent->hr=parent->hr-1;
            return parent;
        }
        parent->left_son=node_to_del->left_son;
        node_to_del->left_son->parent=parent;
        delete node_to_del;
        fixHeightAfterRemove(parent);
        return parent;
    }

    // does not reach here - only for the compiler's warning
    return nullptr;

}

//we call the swap during just the removal
template <class Element,class Key>
void AvlTree<Element,Key>::swapNodes(Node* node_to_del,Node* next_by_value) {
    if(node_to_del==next_by_value){
        return;
    }
    if(node_to_del==root){
        root=next_by_value;
    }
    ////added this 3 lines
    next_by_value->size_left_sub_tree=node_to_del->size_left_sub_tree;
    next_by_value->size_right_sub_tree=node_to_del->size_right_sub_tree;
    next_by_value->size_sub_tree=node_to_del->size_sub_tree;


    if(node_to_del->right_son==next_by_value){
        next_by_value->left_son=node_to_del->left_son;
        if(next_by_value->left_son){
            next_by_value->left_son->parent=next_by_value;
        }
        next_by_value->hl=node_to_del->hl;
        node_to_del->left_son= nullptr;
        node_to_del->hl=0;
        node_to_del->hr=next_by_value->hr;
        next_by_value->hr++;

        Node* parent=node_to_del->parent;
        node_to_del->parent=next_by_value;
        node_to_del->right_son=next_by_value->right_son;
        next_by_value->right_son=node_to_del;
        if(parent!= nullptr){
            next_by_value->parent=parent;
            if(parent->right_son==node_to_del){
                parent->right_son=next_by_value;
            } else if(parent->left_son==node_to_del){
                parent->left_son=next_by_value;
            }
            return;
        }
        else{
            next_by_value->parent= nullptr;
            return;
        }
    }

    next_by_value->hr=node_to_del->hr;
    next_by_value->hl=node_to_del->hl;
    Node *parent=next_by_value->getParent();
    parent->left_son=next_by_value->right_son;
    next_by_value->right_son=node_to_del->right_son;
    next_by_value->left_son=node_to_del->left_son;
    if(next_by_value->left_son){
        next_by_value->left_son->parent=next_by_value;
    }
    if(next_by_value->right_son){
        next_by_value->right_son->parent=next_by_value;
    }
    next_by_value->parent=node_to_del->parent;
    node_to_del->left_son= nullptr;
    node_to_del->right_son=parent->left_son;
    parent->left_son=node_to_del;
    if(node_to_del->parent){
        if(node_to_del->parent->left_son==node_to_del){
            node_to_del->parent->left_son=next_by_value;
        }
        else{
            node_to_del->parent->right_son=next_by_value;
        }
    }
    node_to_del->parent=parent;
    if(next_by_value->parent== nullptr){
        root=next_by_value;
    }
    if(next_by_value->left_son==parent||next_by_value->right_son==parent){
        parent->parent=next_by_value;
    }
}

template <class Element,class Key>
void AvlTree<Element,Key>:: BalanceInsert(Node& insertedNode){
   Node *p=insertedNode.parent;
   Node *tmp=&insertedNode;
   int balance_factor=0;
   while (tmp!=root){
       p=tmp->parent;

       balance_factor=p->getBalanceFactor();
       if(balance_factor==2){
           if(p->left_son->getBalanceFactor()<0){
               rotateLeft(*(p->left_son));
               fixHeightAfterRotation(p->left_son);
           }
           rotateRight(*p);
           fixHeightAfterRotation(p);
           return;
       }
       if(balance_factor==-2){
           if(p->right_son->getBalanceFactor()>0){
               rotateRight(*(p->right_son));
               fixHeightAfterRotation(p->right_son);
           }
           rotateLeft(*p);
           fixHeightAfterRotation(p);
           return;
       }
       tmp=tmp->parent;
   }
 }





//now its the functions of the tree

template <class Element,class Key>
bool AvlTree<Element,Key>::findKeyAlreadyExists(const Key& key){
    if(root== nullptr){
        return false;
    }
    Node *tmp2=root;

    while(tmp2!= nullptr){
        if(tmp2->key==key){
            return true;
        }
        if(tmp2->key<key){
            tmp2=tmp2->right_son;
        }
        else{
            tmp2=tmp2->left_son;
        }
    }
    return false;
}

template <class Element,class Key>
AvlTreeResult AvlTree<Element,Key>::insert(const Element &ele, const Key& key) {
    if(findKeyAlreadyExists(key)){
        return  AVL_KEY_ALREADY_EXISTS;
    }
    Node* ptr=new Node(ele,key);
    if(root== nullptr){
        root=ptr;
        root->left_son= nullptr;
        root->right_son= nullptr;
        root->parent= nullptr;
        root->hr=0;
        root->hl=0;
        root->size_sub_tree=1;
        root->size_right_sub_tree=0;
        root->size_left_sub_tree=0;
        first=root;
        last=root;
        numOfNodes++;
        return AVL_SUCCESS;
    }
    InsertNode(*ptr);
    if(key<first->key){
        first=ptr;
    }
    if(key>last->key){
        last=ptr;
    }
    numOfNodes++;
    return AVL_SUCCESS;
}

template <class Element,class Key>
AvlTreeResult AvlTree<Element,Key>:: remove (const Key& key){

    if(!findKeyAlreadyExists(key)){
        return  AVL_KEY_DOESNT_EXISTS;
    }
    Node& node_to_del=root->getNodeFromKey(key);
    bool setFirst=(&node_to_del==first);
    bool setLast=(&node_to_del==last);
    Node* parent=removeBinarySearch(&node_to_del);
   // assert(findKeyAlreadyExists(key)== false);

    if(parent== nullptr){
        root= nullptr;
        first= nullptr;
        iterator= nullptr;
        numOfNodes--;
        return AVL_SUCCESS;
    }

    while (parent!= nullptr){
        if(parent->left_son){
            parent->hl=parent->left_son->getHeight();
            parent->size_left_sub_tree=parent->left_son->size_sub_tree;
        }
        else{
            parent->hl=0;
            parent->size_left_sub_tree=0;
        }
        if(parent->right_son){
            parent->hr=parent->right_son->getHeight();
            parent->size_right_sub_tree=parent->right_son->size_sub_tree;
        }
        else{
            parent->hr=0;
            parent->size_right_sub_tree=0;
        };
        parent->size_sub_tree=1+parent->size_left_sub_tree+parent->size_right_sub_tree;

        BalanceRemove(parent);

        parent=parent->parent;
    }

    if(setLast){
        if(root!= nullptr){
            last=root;
            while (last&&last->right_son){
                last=last->right_son;
            }
        } else{
            last= nullptr;
            first= nullptr;
        }

    }
    if(setFirst){
        if(root== nullptr){
            return AVL_SUCCESS;
        }
        first=root;

        while (first &&first->left_son){
            first=first->left_son;
        }
    }


    numOfNodes--;
    return AVL_SUCCESS;
}

template <class Element,class Key>
void AvlTree<Element,Key>::BalanceRemove(Node *node) {
    if(!node){
        return;
    }
    int balance_factor=0;
    Node* p=node->parent;
    balance_factor=p->getBalanceFactor();
    if(balance_factor==2){
        if(p->left_son->getBalanceFactor()<0){
            rotateLeft(*(p->left_son));
            fixHeightAfterRotation(p->left_son);
        }
        rotateRight(*p);
        fixHeightAfterRotation(p);
        return;
    }
    if(balance_factor==-2){
        if(p->right_son->getBalanceFactor()>0){
            rotateRight(*(p->right_son));
            fixHeightAfterRotation(p->right_son);
        }
        rotateLeft(*p);
        fixHeightAfterRotation(p);
        return;
    }
}

#endif //MIVNE_AVLTREE_H
