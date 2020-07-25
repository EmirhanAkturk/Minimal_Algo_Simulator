#include "MessageImp.h"
#include <iostream> 
#include <sstream>
#include <fstream>
using namespace std;

class AddOrderImp:MessageImp{

    friend ofstream& operator<<(ofstream& file,const AddOrderImp& message){
        file<<message.orderId<<";"<<message.orderPrice<<endl;
        return file;
    }

public:
    AddOrderImp(uint64_t newId=0,uint32_t newPrice=0):MessageImp{newId},orderPrice{newPrice}
    {/* intentionally left blank */}

    AddOrderImp(AddOrderImp & otherMessage){
        orderId=otherMessage.orderId;
        orderPrice=otherMessage.orderPrice;
    }

    uint64_t getOrderId()const{
        return orderId;
    }

    uint32_t getOrderPrice()const{
        return orderPrice;
    }

    
    virtual bool searchMessage(const string &line);
    virtual void print();

private:
    uint32_t orderPrice;

};


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

    Node* insertNode(Node* rootPtr,uint64_t orderId, uint64_t orderPrice);
    Node* addNewNode(uint64_t orderId, uint64_t orderPrice);
    
    Node* searchNode(Node* rootPtr,uint64_t orderId)const;
    Node* searchNode(Node* rootPtr,uint32_t orderPrice)const;

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

void fileRead(ifstream &inFile,Node* rootPtr);

