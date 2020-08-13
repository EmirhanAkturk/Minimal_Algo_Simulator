#ifndef _AVLTREE_HPP_
#define _AVLTREE_HPP_
//#pragma once

#include "../../inc/std.hpp"
#include "AVLTreePod.hpp"


using std::string;
using std::ofstream;
using std::cout;
using std::cerr;
using std::endl;


template<class T>
class AVLTree;


/* 
############################################
Template Specialization for Seconds
############################################
*/


template <>
class AVLTree<Seconds>{
public:
    class Node{
    public:
        Node(const Seconds& newData ):
        timestamp{newData.timestamp},
        right{nullptr},left{nullptr},height{0}
        { /* deliberately left blank */}
        
        Node(uint32_t newTimestamp):
        timestamp{newTimestamp},
        right{nullptr},left{nullptr},height{0}
        { /* deliberately left blank */}
        
        int height;
        uint32_t timestamp;
        Node *right;
        Node *left;
    };

    AVLTree(){
        root=nullptr;
    }
    
    ~AVLTree(){
        root=makeEmpty(root);
    }

    Node* getRoot()const{
        return root;
    }
    
    void insert(const Seconds& data){
        root = insertNode(root,data);
    }

    bool remove(const Seconds& data){
        Node *query = searchNode(root, data.timestamp);
        if(query==nullptr){
            return false;//If not found, it cannot be deleted
        }

        root = removeNode(root,data.timestamp);
        
        return true;
    }

    bool remove(uint32_t timestamp){
        Node *query = searchNode(root, timestamp);
        if(query==nullptr){
            return false;//If not found, it cannot be deleted
        }

        root = removeNode(root,timestamp);
        
        return true;
    }


    bool search(const Seconds& data) {
        Node *query = searchNode(root, data.timestamp);
        
        if(query!=nullptr)
            return true;

        else
            return false;
    }

    bool search(uint32_t timestamp) {
        Node *query = searchNode(root, timestamp);
        
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

    Node* insertNode(Node* node, const Seconds& data);

    //Node* removeNode(Node* node,const Seconds& data);
    Node* removeNode(Node* node,uint32_t timestamp);

    //Node* searchNode(Node* node, const Seconds& data);
    Node* searchNode(Node* node, uint32_t timestamp);

    Node* makeEmpty(Node* node);

    Node* doBalanced(Node* node);
    Node* doBalanced(Node* node, const Seconds& data);
    
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
Template Specialization for AddOrder
############################################
*/


template <>
class AVLTree<AddOrder>{
public:
class Node{
public:
    Node(const AddOrder& newData ):
    timestamp{newData.timestamp},nanosecond{newData.nanosecond},
    orderId{newData.orderId},quantity{newData.quantity},
    orderPrice{newData.orderPrice},right{nullptr},left{nullptr},height{0}
    { /* deliberately left blank */}
    
    Node(   uint32_t newTimestampt,uint32_t newNanosecond,uint64_t newOrderId,
            uint32_t quantity,uint32_t newOrderPrice):
    timestamp{newTimestampt},nanosecond{newNanosecond},orderId{newOrderId},
    orderPrice{newOrderPrice},right{nullptr},left{nullptr},height{0}
    { /* deliberately left blank */}
    
    int height;
    uint32_t timestamp;
    uint32_t nanosecond;
    uint32_t quantity;
    uint32_t orderPrice;
    uint64_t orderId;
    Node *right;
    Node *left;
};
    
    AVLTree(){
        root=nullptr;
    }
    
    ~AVLTree(){
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

        root = removeNode(root,data.orderId);
        
        return true;
    }

    bool remove(uint64_t orderId){
        Node *query = searchNode(root, orderId);
        if(query==nullptr){
            return false;//If not found, it cannot be deleted
        }

        root = removeNode(root,orderId);
        
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
    void  writeItrPreorder(Node * node,ofstream & outFile)const;
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
        Node(const OrderExecuted& newData ):
        nanosecond{newData.nanosecond},orderId{newData.orderId},
        right{nullptr},left{nullptr},height{0}
        { /* deliberately left blank */}
        
        Node(uint32_t newNanosecond,uint64_t newOrderId ):
        nanosecond{newNanosecond},orderId{newOrderId},
        right{nullptr},left{nullptr},height{0}
        { /* deliberately left blank */}
        
        int height;
        uint32_t nanosecond;
        uint64_t orderId;
        Node *right;
        Node *left;
    };

    AVLTree(){
        root=nullptr;
    }
    
    ~AVLTree(){
        root=makeEmpty(root);
    }

    Node* getRoot()const{
        return root;
    }
    
    void insert(const OrderExecuted& data){
        root = insertNode(root,data);
    }

    bool remove(const OrderExecuted& data){
        Node *query = searchNode(root, data.orderId);
        if(query==nullptr){
            return false;//If not found, it cannot be deleted
        }

        root = removeNode(root,data.orderId);
        
        return true;
    }

    bool remove(uint64_t orderId){
        Node *query = searchNode(root, orderId);
        if(query==nullptr){
            return false;//If not found, it cannot be deleted
        }

        root = removeNode(root,orderId);
        
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
        Node(const OrderDelete& newData ):
        nanosecond{newData.nanosecond},orderId{newData.orderId},
        right{nullptr},left{nullptr},height{0}
        { /* deliberately left blank */}
        
        Node(uint32_t newNanosecond, uint64_t newOrderId ):
        nanosecond{newNanosecond},orderId{newOrderId},
        right{nullptr},left{nullptr},height{0}
        { /* deliberately left blank */}
        
        int height;
        uint32_t nanosecond;
        uint64_t orderId;
        Node *right;
        Node *left;
    };

    AVLTree(){
        root=nullptr;
    }
    
    ~AVLTree(){
        root=makeEmpty(root);
    }

    Node* getRoot()const{
        return root;
    }
    
    void insert(const OrderDelete& data){
        root = insertNode(root,data);
    }

    bool remove(const OrderDelete& data){
        Node *query = searchNode(root, data.orderId);
        if(query==nullptr){
            return false;//If not found, it cannot be deleted
        }

        root = removeNode(root,data.orderId);
        
        return true;
    }

    bool remove(uint64_t orderId){
        Node *query = searchNode(root, orderId);
        if(query==nullptr){
            return false;//If not found, it cannot be deleted
        }

        root = removeNode(root,orderId);
        
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

#endif