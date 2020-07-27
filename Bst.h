#ifndef _BST_H_
#define _BST_H_

#include<iostream>
#include<fstream>

using namespace std;

struct Node {
	uint64_t orderId;
	uint32_t orderPrice;

	Node* left;
	Node* right;
};

class BinarySearchTree{
public:
    BinarySearchTree(Node *newRootPtr=nullptr):rootPtr{newRootPtr}
    {/* intentionally left blank */}

    Node* insertNode(Node* rootPtr,uint64_t orderId, uint32_t orderPrice);
    Node* addNewNode(uint64_t orderId, uint32_t orderPrice);
    
    // Node* insertNode(Node* rootPtr,uint64_t orderId);
    // Node* addNewNode(uint64_t orderId);
    
    Node* searchNode(Node* rootPtr,uint64_t orderId)const;
    //Node* searchNode(Node* rootPtr,uint32_t orderPrice)const;

    Node* minValueNode(Node* node)const; 
    Node* maxValueNode(Node* node)const;

    Node* deleteNode(Node* rootPtr, uint64_t orderId);

    Node* getRoot()const{
        return rootPtr;
    }

    bool setRoot(Node* newRootPtr){
        if(newRootPtr!=nullptr){
            rootPtr=newRootPtr;
            return true;
        }

        return false;
    }

    void writePostorder(Node * rootPtr,ofstream & outFile)const;
    void writeInorder(Node * rootPtr,ofstream & outFile)const;

    void printPostorder(Node * rootPtr)const;
    void printInorder(Node * rootPtr)const;


private:
    Node *rootPtr;

};

#endif