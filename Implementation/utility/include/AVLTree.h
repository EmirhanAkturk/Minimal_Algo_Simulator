#ifndef _AVLTREE_H_
#define _AVLTREE_H_

#include<iostream>
#include<fstream>

using namespace std;

struct node {
    uint64_t orderId;
    uint32_t orderPrice;
        
    int height;
    
    node* left;
    node* right;

};

class AVLTree {

public:
    AVLTree() {
        root = nullptr;
    }

    ~AVLTree() {
        root = makeEmpty(root);
    }

    void insert(uint64_t orderId,uint32_t orderPrice) {
    //     if(root!=nullptr)
    //         Insert(root,orderId,orderPrice);
    //     else root = Insert(root,orderId,orderPrice);
        root=insert(root,orderId,orderPrice);
    }

    bool remove(uint64_t orderId) {
        root = remove(root,orderId);//return değerlerini kontrol et!!
        if(root!=nullptr)
            return true;
        
        else return false;
    }

    void writeFile(ofstream & outFile){
        writeInorder(root,outFile);

    }

    void display() {
        inorder(root);
        cout << endl;
    }

    bool search(uint64_t orderId) {
        node *query=find(root, orderId);
        
        if(query!=nullptr)
            return true;

        else
            return false;
    }

private:

    node* root;

    node* makeEmpty(node* t);
    
    int height(node *t);
    int getBalance(node *t); 

    node* doBalanced(node *t,uint64_t newOrderId);
    
    node* doBalanced(node *t);

    node* newNode(uint64_t newOrderId,uint32_t newOrderPrice); 
    
    node* insert( node* t,uint64_t newOrderId,uint32_t newOrderPrice);

    node *rightRotate(node *t);

    node *leftRotate(node *x);

   /*  
    node* Insert(node* root, uint64_t newOrderId,uint32_t newOrderPrice);
 */
    
    node* findMin(node* t);

    node* findMax(node* t);
    node* remove(node* t,uint64_t orderId);

    void  writeInorder(node * rootPtr,ofstream & outFile)const;

    void inorder(node* t);

    node* find(node* t, uint64_t orderId);

};


#endif