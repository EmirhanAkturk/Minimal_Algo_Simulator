#ifndef _MESSAGEIMP_H_
#define _MESSAGEIMP_H_

#include<string>
#include<fstream>
#include<sstream>
#include "../utility/include/AVLTree.hpp"

using namespace std;

class MessageImp{
public:
    ~MessageImp(){

    }
    
    // virtual void operation(const char * file)=0;

    //virtual void fileRead(ifstream & inFile)=0;
    virtual void fileRead(const char * file)=0;
    virtual inline void print(int treeChoice,int printChoice)=0;
    virtual inline void writeFile(const char* outFile,int treeChoice,int writeChoice)=0;

protected:
    MessageImp(){

    }

    virtual inline string readLine(ifstream& infile)=0;
    virtual void findValues(const string & line)=0;

    virtual void fileAddOrder(istringstream &inString,int flag)=0;
    virtual void fileOrderExecute(istringstream &inString,int flag)=0;
    virtual void fileOrderDelete(istringstream &inString,int flag)=0;
    
    static AVLTree<AddOrder> AddOrderTree;
    static AVLTree<OrderExecute> OrderExecuteTree;
    static AVLTree<OrderDelete> OrderDeleteTree;
    

};

#endif
