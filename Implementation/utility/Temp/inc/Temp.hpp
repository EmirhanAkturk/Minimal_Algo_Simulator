#ifndef _TEMP_HPP_

#define _TEMP_HPP_

#include "../../Graph/inc/Graph.hpp"
#include "../../AVLTree/inc/AVLTree.hpp"

/* 
############################################
Template Specialization for OrderBookId
############################################
*/


template <>
class AVLTree<OrderBookId>{
public:
    class Node{
    public:
        Node(const OrderBookId& newData );

        Node(uint32_t newBookId);
        
        int height;
        uint32_t bookId;
        Graph<uint32_t ,Graph<uint32_t, Value>> *graph;
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
    
    void insert(const OrderBookId& data){
        root = insertNode(root,data);
    }

    void insert(uint32_t newOrderBookId){
        OrderBookId bookId;
        bookId.orderBookId=newOrderBookId;
        root=insertNode(root,bookId);
    }

    bool remove(const OrderBookId& data){
        Node *query = searchNode(root, data.orderBookId);
        if(query==nullptr){
            return false;//If not found, it cannot be deleted
        }

        root = removeNode(root,data.orderBookId);
        
        return true;
    }

    bool remove(uint32_t orderBookId){
        Node *query = searchNode(root, orderBookId);
        if(query==nullptr){
            return false;//If not found, it cannot be deleted
        }

        root = removeNode(root,orderBookId);
        
        return true;
    }


    bool search(const OrderBookId& data) {
        Node *query = searchNode(root, data.orderBookId);
        
        if(query!=nullptr)
            return true;

        else
            return false;
    }

    Node* search(uint32_t timestamp) {
        Node *query = searchNode(root, timestamp);
    
        return query;
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

    Node* insertNode(Node* node, const OrderBookId& data);

    Node* removeNode(Node* node,uint32_t orderBookId);

    Node* searchNode(Node* node, uint32_t orderBookId);

    Node* makeEmpty(Node* node);

    Node* doBalanced(Node* node);
    Node* doBalanced(Node* node, const OrderBookId& data);
    
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