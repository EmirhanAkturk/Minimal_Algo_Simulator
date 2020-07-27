#ifndef _BST_H_
#define _BST_H_

#include<iostream>
#include<fstream>

using namespace std;

class Node {
public:	
    Node(uint64_t newOrderId=0,Node* newLeft=nullptr,Node* newRight=nullptr):orderId{newOrderId},left{newLeft},right{newRight}
    {/*    Deliberately left blank  */}

    uint64_t orderId;
	//uint32_t orderPrice;
	Node* left;
	Node* right;
};

class BinarySearchTree{
public:
    BinarySearchTree(Node *newRootPtr=nullptr):rootPtr{newRootPtr}
    {/* intentionally left blank */}

    Node* insertNode(Node* rootPtr,uint64_t orderId);
    Node* addNewNode(uint64_t orderId);
    
    Node* searchNode(Node* rootPtr,uint64_t orderId)const;
    //Node* searchNode(Node* rootPtr,uint32_t orderPrice)const;

    Node* minValueNode(Node* node)const; 
    Node* maxValueNode(Node* node)const;

    Node* deleteNode(Node* rootPtr, uint64_t orderId);

    virtual Node* getRoot()const{
        return rootPtr;
    }

    virtual bool setRoot(Node* newRootPtr){
        if(newRootPtr!=nullptr){
            rootPtr=newRootPtr;
            return true;
        }

        return false;
    }

    virtual void writePostorder(Node * rootPtr,ofstream & outFile)const;
    virtual void writeInorder(Node * rootPtr,ofstream & outFile)const;

    virtual void printPostorder(Node * rootPtr)const;
    virtual void printInorder(Node * rootPtr)const;



private:
    Node *rootPtr;

};

class AddOrderNode:public Node{
public:
    AddOrderNode(uint64_t newOrderId=0,uint32_t newOrderPrice=0,AddOrderNode* newLeft=nullptr,AddOrderNode* newRight=nullptr):
    Node(newOrderId,newLeft,newRight),orderPrice{newOrderPrice}
    {/*    Deliberately left blank  */}

    uint32_t orderPrice;
    AddOrderNode* left;
	AddOrderNode* right;
};

class AddOrderBts:public BinarySearchTree{
public:
    AddOrderBts(AddOrderNode *newRootPtr=nullptr):rootPtr{newRootPtr}
    {/* intentionally left blank */}
    
    AddOrderNode* insertNode(AddOrderNode* rootPtr,uint64_t orderId, uint32_t orderPrice);
    AddOrderNode* addNewNode(uint64_t orderId, uint32_t orderPrice);
    
    virtual AddOrderNode* getRoot()const{
        return rootPtr;
    }

    virtual bool setRoot(AddOrderNode* newRootPtr){
        if(newRootPtr!=nullptr){
            rootPtr=newRootPtr;
            return true;
        }

        return false;
    }


    virtual void writePostorder(AddOrderNode * rootPtr,ofstream & outFile)const;
    virtual void writeInorder(AddOrderNode * rootPtr,ofstream & outFile)const;

    virtual void printPostorder(AddOrderNode * rootPtr)const;
    virtual void printInorder(AddOrderNode * rootPtr)const;


private:
    AddOrderNode *rootPtr;
};

#endif