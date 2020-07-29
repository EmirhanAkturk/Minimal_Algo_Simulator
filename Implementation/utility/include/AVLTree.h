#ifndef _AVLTREE_H_
#define _AVLTREE_H_

#include<iostream>
#include<fstream>

using namespace std;

//template<typename T>
class Node {
public:
    Node(uint64_t newOrderId,uint32_t newOrderPrice):orderId{newOrderId},orderPrice{newOrderPrice},
    height{0},left{nullptr},right{nullptr}
    { /* deliberately left blank */}

    uint64_t orderId;
    uint32_t orderPrice;
        
    int height;
    
    Node* left;
    Node* right;

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
        root=insertNode(root,orderId,orderPrice);
    }

    bool remove(uint64_t orderId) {
        root = remove(root,orderId);//return değerlerini kontrol et!!
        if(root!=nullptr)
            return true;
        
        else return false;
    }

    void writeFile(ofstream & outFile,int c){//1:inorder,2:preorder,3:postorder
        if(c==1)
            writeInorder(root,outFile);
        else if(c==2)
            writePreorder(root,outFile);
        else if(c==3)
            writePostorder(root,outFile);
        
        else cout<<"invalid selection!\n";
    }

    void print(int c) {//1:inorder,2:preorder,3:postorder
        if(c==1)
            inorder(root);
        else if(c==2)
            preorder(root);
        else if(c==3)
            postorder(root);
        else cout<<"invalid selection!\n";
        
        cout << endl;
    }

    bool search(uint64_t orderId) {
        Node *query=find(root, orderId);
        
        if(query!=nullptr)
            return true;

        else
            return false;
    }

private:

    Node* root;

    Node* makeEmpty(Node* t);

    Node* doBalanced(Node *t);
    
    Node* doBalanced(Node *t,uint64_t newOrderId);

    //Node* newNode(uint64_t newOrderId,uint32_t newOrderPrice); 
    
    Node* insertNode( Node* t,uint64_t newOrderId,uint32_t newOrderPrice);

    Node *rightRotate(Node *t);

    Node *leftRotate(Node *t);

   /*  
    Node* Insert(Node* root, uint64_t newOrderId,uint32_t newOrderPrice);
 */
    
    Node* findMin(Node* t);

    Node* findMax(Node* t);
    Node* remove(Node* t,uint64_t orderId);

    Node* find(Node* t, uint64_t orderId);

    void  writeInorder(Node * rootPtr,ofstream & outFile)const;
    void  writePreorder(Node * rootPtr,ofstream & outFile)const;
    void  writePostorder(Node * rootPtr,ofstream & outFile)const;

    void inorder(Node* t);
    void preorder(Node* t);
    void postorder(Node* t);
    
    int height(Node *t);
    int getBalance(Node *t); 

};


#endif