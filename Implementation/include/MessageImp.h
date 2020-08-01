#ifndef _MESSAGEIMP_H_
#define _MESSAGEIMP_H_

#include "../utility/include/AVLTree.hpp"

class MessageImp{
public:
    virtual ~MessageImp();
    virtual void operation(const char * file)=0;
    
protected:
    MessageImp();

    virtual inline string readLine(ifstream& infile)=0;
    virtual void findValues(const string & line)=0;

    virtual void fileAddOrder(istringstream &inString,int flag)=0;
    virtual void fileOrderExecute(istringstream &inString,int flag)=0;
    virtual void fileOrderDelete(istringstream &inString,int flag)=0;
    
    virtual void fileRead(ifstream & inFile)=0;
    
    AVLTree<AddOrder> AddOrderTree;
    AVLTree<OrderExecute> OrderExecuteTree;
    AVLTree<OrderDelete> OrderDeleteTree;

};

#endif
