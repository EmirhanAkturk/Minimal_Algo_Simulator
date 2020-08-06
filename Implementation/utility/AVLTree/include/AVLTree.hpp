#ifndef _AVLTREE_HPP_
#define _AVLTREE_HPP_
//#pragma once

#include<iostream>
#include<fstream>
#include<sstream>

#include "AVLTreePod.hpp"

using namespace std;
enum PRINT{
    INORDER=1,
    PREORDER=2,
    POSTORDER=3
};

template<class T>
class AVLTree;

void fileRead(const char * file );
inline string readLine(ifstream& inFile);

void findValues(const string & line);
int findColumn(istringstream& inString,int flag,int collumn);

void fileAddOrder(istringstream &inString,int flag);
void fileOrderExecute(istringstream &inString,int flag);
void fileOrderDelete(istringstream &inString,int flag);

template<class T>
inline void addMessage(AVLTree<T>& tree,const T& message);

/* 
############################################
Template Specialization for AddOrder
############################################
*/


template <>
class AVLTree<AddOrder>{
public:
class Node{
public:
    Node(const AddOrder& newData ):orderId{newData.orderId},
    orderPrice{newData.orderPrice},right{nullptr},left{nullptr},height{0}
    { /* deliberately left blank */}
    
    Node(uint64_t newOrderId,uint32_t newOrderPrice ):orderId{newOrderId},
    orderPrice{newOrderPrice},right{nullptr},left{nullptr},height{0}
    { /* deliberately left blank */}
    
    uint64_t orderId;
    uint32_t orderPrice;
    Node *right;
    Node *left;
    int height;
};
    
    AVLTree(){
        //cout<<"AddOrder constructor\n";
        root=nullptr;
    }
    
    ~AVLTree(){
        //cout<<"AddOrder destructor\n";
        root=makeEmpty(root);
    }

    Node* getRoot()const{
        return root;
    }

    void insert(const AddOrder& data){
        root = insertNode(root,data);
    }

    bool remove(const AddOrder& data){
        Node *query = searchNode(root, data.orderId);
        if(query==nullptr){
            return false;//If not found, it cannot be deleted
        }

        root = removeNode(query,data.orderId);
        
        return true;
    }

    bool remove(uint64_t orderId){
        Node *query = searchNode(root, orderId);
        if(query==nullptr){
            return false;//If not found, it cannot be deleted
        }

        root = removeNode(query,orderId);
        
        return true;
    }

    bool search(const AddOrder& data) {
        Node *query = searchNode(root, data.orderId);
        
        if(query!=nullptr)
            return true;

        else
            return false;
    }

    bool search(uint64_t orderId) {
        Node *query = searchNode(root, orderId);
        
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
    Node * root;

    Node* insertNode(Node* node, const AddOrder& data);

    // Node* removeNode(Node* node,const AddOrder& data);
    Node* removeNode(Node* node,uint64_t orderId);

    // Node* searchNode(Node* node, const AddOrder& data);
    Node* searchNode(Node* node, uint64_t orderId);

    Node* makeEmpty(Node* node);

    Node* doBalanced(Node* node);
    Node* doBalanced(Node* node, const AddOrder& data);
    
    Node* rightRotate(Node* node);
    Node* leftRotate(Node* node);

    Node* findMin(Node* node);
    Node* findMax(Node* node);

    void fileRead(const char * file);

    int getBalance(Node* node);
    int height(Node * node);

    void inorder(Node* node)const;
    void preorder(Node* node)const;
    void postorder(Node* node)const;
    
    void  writeInorder(Node * node,ofstream & outFile)const;
    void  writePreorder(Node * node,ofstream & outFile)const;
    void  writePostorder(Node * node,ofstream & outFile)const;
};



/* 
############################################
Template Specialization for OrderExecuted
############################################
*/

template <>
class AVLTree<OrderExecuted>{
public:
    class Node{
    public:
        Node(const OrderExecuted& newData ):orderId{newData.orderId},
        right{nullptr},left{nullptr},height{0}
        { /* deliberately left blank */}
        
        Node(uint64_t newOrderId ):
        orderId{newOrderId},right{nullptr},left{nullptr},height{0}
        { /* deliberately left blank */}
        
        uint64_t orderId;
        Node *right;
        Node *left;
        int height;
    };

    AVLTree(){
        //cout<<"OrderExecuted constructor\n";
        root=nullptr;
    }
    
    ~AVLTree(){
        //cout<<"OrderExecuted destructor\n";
        root=makeEmpty(root);
    }

    Node* getRoot()const{
        return root;
    }
    
    void insert(const OrderExecuted& data){
        root = insertNode(root,data);
    }

        bool remove(const AddOrder& data){
        Node *query = searchNode(root, data.orderId);
        if(query==nullptr){
            return false;//If not found, it cannot be deleted
        }

        root = removeNode(query,data.orderId);
        
        return true;
    }

    bool remove(uint64_t orderId){
        Node *query = searchNode(root, orderId);
        if(query==nullptr){
            return false;//If not found, it cannot be deleted
        }

        root = removeNode(query,orderId);
        
        return true;
    }


    bool search(const OrderExecuted& data) {
        Node *query = searchNode(root, data.orderId);
        
        if(query!=nullptr)
            return true;

        else
            return false;
    }

    bool search(uint64_t orderId) {
        Node *query = searchNode(root, orderId);
        
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
    Node* root;

    Node* insertNode(Node* node, const OrderExecuted& data);

    //Node* removeNode(Node* node,const OrderExecuted& data);
    Node* removeNode(Node* node,uint64_t orderId);

    //Node* searchNode(Node* node, const OrderExecuted& data);
    Node* searchNode(Node* node, uint64_t orderId);

    Node* makeEmpty(Node* node);

    Node* doBalanced(Node* node);
    Node* doBalanced(Node* node, const OrderExecuted& data);
    
    Node* rightRotate(Node* node);
    Node* leftRotate(Node* node);

    Node* findMin(Node* node);
    Node* findMax(Node* node);

    int getBalance(Node* node);
    int height(Node * node);

    void inorder(Node* node)const;
    void preorder(Node* node)const;
    void postorder(Node* node)const;
    
    void  writeInorder(Node * node,ofstream & outFile)const;
    void  writePreorder(Node * node,ofstream & outFile)const;
    void  writePostorder(Node * node,ofstream & outFile)const;
};


/* 
############################################
Template Specialization for OrderDelete
############################################
*/

template <>
class AVLTree<OrderDelete>{
public:
    class Node{
    public:
        Node(const OrderDelete& newData ):orderId{newData.orderId},
        right{nullptr},left{nullptr},height{0}
        { /* deliberately left blank */}
        
        Node(uint64_t newOrderId ):
        orderId{newOrderId},right{nullptr},left{nullptr},height{0}
        { /* deliberately left blank */}
        
        uint64_t orderId;
        Node *right;
        Node *left;
        int height;
    };

    AVLTree(){
        //cout<<"OrderDelete constructor\n";
        root=nullptr;
    }
    
    ~AVLTree(){
        //cout<<"OrderDelete destructor\n";
        root=makeEmpty(root);
    }

    Node* getRoot()const{
        return root;
    }
    
    void insert(const OrderDelete& data){
        root = insertNode(root,data);
    }

        bool remove(const AddOrder& data){
        Node *query = searchNode(root, data.orderId);
        if(query==nullptr){
            return false;//If not found, it cannot be deleted
        }

        root = removeNode(query,data.orderId);
        
        return true;
    }

    bool remove(uint64_t orderId){
        Node *query = searchNode(root, orderId);
        if(query==nullptr){
            return false;//If not found, it cannot be deleted
        }

        root = removeNode(query,orderId);
        
        return true;
    }


    bool search(const OrderDelete& data) {
        Node *query = searchNode(root, data.orderId);
        
        if(query!=nullptr)
            return true;

        else
            return false;
    }

    bool search(uint64_t orderId) {
        Node *query = searchNode(root, orderId);
        
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
    Node* root;

    Node* insertNode(Node* node, const OrderDelete& data);

    //Node* removeNode(Node* node,const OrderDelete& data);
    Node* removeNode(Node* node,uint64_t orderId);

    //Node* searchNode(Node* node, const OrderDelete& data);
    Node* searchNode(Node* node, uint64_t orderId);

    Node* makeEmpty(Node* node);

    Node* doBalanced(Node* node);
    Node* doBalanced(Node* node, const OrderDelete& data);
    
    Node* rightRotate(Node* node);
    Node* leftRotate(Node* node);

    Node* findMin(Node* node);
    Node* findMax(Node* node);

    int getBalance(Node* node);
    int height(Node * node);

    void inorder(Node* node)const;
    void preorder(Node* node)const;
    void postorder(Node* node)const;
    
    void  writeInorder(Node * node,ofstream & outFile)const;
    void  writePreorder(Node * node,ofstream & outFile)const;
    void  writePostorder(Node * node,ofstream & outFile)const;
};

class Tree{
public:
    static AVLTree<AddOrder> AddOrderTree;
    static AVLTree<OrderDelete> OrderDeleteTree;
    static AVLTree<OrderExecuted> OrderExecutedTree;
    static bool isRead;
};
//#include "AVLTree.inl"
#endif