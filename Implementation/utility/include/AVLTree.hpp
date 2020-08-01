#ifndef _AVLTREE_H_
#define _AVLTREE_H_
//#pragma once

#include<iostream>
#include<fstream>
#include "../../include/SearchPod.h"

using namespace std;

template<class T>
class Node;

template<class T>
class AVLTree;


/* 
############################################
Template Specialization for AddOrder
############################################
*/

template <>
class Node<AddOrder>{
public:
    Node(const AddOrder& newData ):data{newData},right{nullptr},left{nullptr},height{0}
    { /* deliberately left blank */}
    
    AddOrder data;
    Node<AddOrder> *right;
    Node<AddOrder> *left;
    int height;
};

template <>
class AVLTree<AddOrder>{
public:
    AVLTree(){
        //cout<<"AddOrder constructor\n";
        root=nullptr;
    }
    
    ~AVLTree(){
        //cout<<"AddOrder destructor\n";
        root=makeEmpty(root);
    }

    void insert(const AddOrder& data){
        root = insertNode(root,data);
    }

    bool remove(const AddOrder& data){
        root = removeNode(root,data);//return değerlerini kontrol et!!
        
        if(root!=nullptr)
            return true;
        
        else return false;
    }

    bool search(const AddOrder& data) {
        Node<AddOrder> *query = searchNode(root, data);
        
        if(query!=nullptr)
            return true;

        else
            return false;
    }

    bool search(uint64_t orderId) {
        Node<AddOrder> *query = searchNode(root, orderId);
        
        if(query!=nullptr)
            return true;

        else
            return false;
    }

    void print(int choice)const{//1:inorder,2:preorder,3:postorder
        if(choice == 1)
            inorder(root);
        else if(choice==2)
            preorder(root);
        else if(choice==3)
            postorder(root);
        else cout<<"invalid selection!\n";

        cout << endl;
    }

    void writeFile(ofstream & outFile,int choice)const{//1:inorder,2:preorder,3:postorder
        if(choice==1)
            writeInorder(root,outFile);
        else if(choice==2)
            writePreorder(root,outFile);
        else if(choice==3)
            writePostorder(root,outFile);
        
        else cout<<"invalid selection!\n";
    }

private:
    Node<AddOrder>* root;


    Node<AddOrder>* insertNode(Node<AddOrder>* node, const AddOrder& data);
    Node<AddOrder>* removeNode(Node<AddOrder>* node,const AddOrder& data);

    Node<AddOrder>* searchNode(Node<AddOrder>* node, const AddOrder& data);
    Node<AddOrder>* searchNode(Node<AddOrder>* node, uint64_t orderId);

    Node<AddOrder>* makeEmpty(Node<AddOrder>* node);

    Node<AddOrder>* doBalanced(Node<AddOrder>* node);
    Node<AddOrder>* doBalanced(Node<AddOrder>* node, const AddOrder& data);
    
    Node<AddOrder>* rightRotate(Node<AddOrder>* node);
    Node<AddOrder>* leftRotate(Node<AddOrder>* node);

    Node<AddOrder>* findMin(Node<AddOrder>* node);
    Node<AddOrder>* findMax(Node<AddOrder>* node);

    int getBalance(Node<AddOrder>* node);
    int height(Node<AddOrder> * node);

    void inorder(Node<AddOrder>* node)const;
    void preorder(Node<AddOrder>* node)const;
    void postorder(Node<AddOrder>* node)const;
    
    void  writeInorder(Node<AddOrder> * node,ofstream & outFile)const;
    void  writePreorder(Node<AddOrder> * node,ofstream & outFile)const;
    void  writePostorder(Node<AddOrder> * node,ofstream & outFile)const;
};



/* 
############################################
Template Specialization for OrderExecute
############################################
*/

template <>
class Node<OrderExecute>{
public:
    Node(const OrderExecute& newData ):data{newData},right{nullptr},left{nullptr},height{0}
    { /* deliberately left blank */}
    
    OrderExecute data;
    Node<OrderExecute> *right;
    Node<OrderExecute> *left;
    int height;
};

template <>
class AVLTree<OrderExecute>{
public:
    AVLTree(){
        //cout<<"OrderExecute constructor\n";
        root=nullptr;
    }
    
    ~AVLTree(){
        //cout<<"OrderExecute destructor\n";
        root=makeEmpty(root);
    }

    void insert(const OrderExecute& data){
        root = insertNode(root,data);
    }

    bool remove(const OrderExecute& data){
        root = removeNode(root,data);//return değerlerini kontrol et!!
        
        if(root!=nullptr)
            return true;
        
        else return false;
    }

    bool search(const OrderExecute& data) {
        Node<OrderExecute> *query = searchNode(root, data);
        
        if(query!=nullptr)
            return true;

        else
            return false;
    }

    bool search(uint64_t orderId) {
        Node<OrderExecute> *query = searchNode(root, orderId);
        
        if(query!=nullptr)
            return true;

        else
            return false;
    }


    void print(int choice)const{//1:inorder,2:preorder,3:postorder
        if(choice == 1)
            inorder(root);
        else if(choice==2)
            preorder(root);
        else if(choice==3)
            postorder(root);
        else cout<<"invalid selection!\n";

        cout << endl;
    }

    void writeFile(ofstream & outFile,int choice)const{//1:inorder,2:preorder,3:postorder
        if(choice==1)
            writeInorder(root,outFile);
        else if(choice==2)
            writePreorder(root,outFile);
        else if(choice==3)
            writePostorder(root,outFile);
        
        else cout<<"invalid selection!\n";
    }

private:
    Node<OrderExecute>* root;

    Node<OrderExecute>* insertNode(Node<OrderExecute>* node, const OrderExecute& data);
    Node<OrderExecute>* removeNode(Node<OrderExecute>* node,const OrderExecute& data);

    Node<OrderExecute>* searchNode(Node<OrderExecute>* node, const OrderExecute& data);
    Node<OrderExecute>* searchNode(Node<OrderExecute>* node, uint64_t orderId);

    Node<OrderExecute>* makeEmpty(Node<OrderExecute>* node);

    Node<OrderExecute>* doBalanced(Node<OrderExecute>* node);
    Node<OrderExecute>* doBalanced(Node<OrderExecute>* node, const OrderExecute& data);
    
    Node<OrderExecute>* rightRotate(Node<OrderExecute>* node);
    Node<OrderExecute>* leftRotate(Node<OrderExecute>* node);

    Node<OrderExecute>* findMin(Node<OrderExecute>* node);
    Node<OrderExecute>* findMax(Node<OrderExecute>* node);

    int getBalance(Node<OrderExecute>* node);
    int height(Node<OrderExecute> * node);

    void inorder(Node<OrderExecute>* node)const;
    void preorder(Node<OrderExecute>* node)const;
    void postorder(Node<OrderExecute>* node)const;
    
    void  writeInorder(Node<OrderExecute> * node,ofstream & outFile)const;
    void  writePreorder(Node<OrderExecute> * node,ofstream & outFile)const;
    void  writePostorder(Node<OrderExecute> * node,ofstream & outFile)const;
};


/* 
############################################
Template Specialization for OrderDelete
############################################
*/

template <>
class Node<OrderDelete>{
public:
    Node(const OrderDelete& newData ):data{newData},right{nullptr},left{nullptr},height{0}
    { /* deliberately left blank */}
    
    OrderDelete data;
    Node<OrderDelete> *right;
    Node<OrderDelete> *left;
    int height;
};

template <>
class AVLTree<OrderDelete>{
public:
    AVLTree(){
        //cout<<"OrderDelete constructor\n";
        root=nullptr;
    }
    
    ~AVLTree(){
        //cout<<"OrderDelete destructor\n";
        root=makeEmpty(root);
    }

    void insert(const OrderDelete& data){
        root = insertNode(root,data);
    }

    bool remove(const OrderDelete& data){
        root = removeNode(root,data);//return değerlerini kontrol et!!
        
        if(root!=nullptr)
            return true;
        
        else return false;
    }

    bool search(const OrderDelete& data) {
        Node<OrderDelete> *query = searchNode(root, data);
        
        if(query!=nullptr)
            return true;

        else
            return false;
    }


    bool search(uint64_t orderId) {
        Node<OrderDelete> *query = searchNode(root, orderId);
        
        if(query!=nullptr)
            return true;

        else
            return false;
    }

    void print(int choice)const{//1:inorder,2:preorder,3:postorder
        if(choice == 1)
            inorder(root);
        else if(choice==2)
            preorder(root);
        else if(choice==3)
            postorder(root);
        else cout<<"invalid selection!\n";

        cout << endl;
    }

    void writeFile(ofstream & outFile,int choice)const{//1:inorder,2:preorder,3:postorder
        if(choice==1)
            writeInorder(root,outFile);
        else if(choice==2)
            writePreorder(root,outFile);
        else if(choice==3)
            writePostorder(root,outFile);
        
        else cout<<"invalid selection!\n";
    }

private:
    Node<OrderDelete>* root;

    Node<OrderDelete>* insertNode(Node<OrderDelete>* node, const OrderDelete& data);
    Node<OrderDelete>* removeNode(Node<OrderDelete>* node,const OrderDelete& data);

    Node<OrderDelete>* searchNode(Node<OrderDelete>* node, const OrderDelete& data);
    Node<OrderDelete>* searchNode(Node<OrderDelete>* node, uint64_t orderId);

    Node<OrderDelete>* makeEmpty(Node<OrderDelete>* node);

    Node<OrderDelete>* doBalanced(Node<OrderDelete>* node);
    Node<OrderDelete>* doBalanced(Node<OrderDelete>* node, const OrderDelete& data);
    
    Node<OrderDelete>* rightRotate(Node<OrderDelete>* node);
    Node<OrderDelete>* leftRotate(Node<OrderDelete>* node);

    Node<OrderDelete>* findMin(Node<OrderDelete>* node);
    Node<OrderDelete>* findMax(Node<OrderDelete>* node);

    int getBalance(Node<OrderDelete>* node);
    int height(Node<OrderDelete> * node);

    void inorder(Node<OrderDelete>* node)const;
    void preorder(Node<OrderDelete>* node)const;
    void postorder(Node<OrderDelete>* node)const;
    
    void  writeInorder(Node<OrderDelete> * node,ofstream & outFile)const;
    void  writePreorder(Node<OrderDelete> * node,ofstream & outFile)const;
    void  writePostorder(Node<OrderDelete> * node,ofstream & outFile)const;
};

#include "AVL.inl"
#endif