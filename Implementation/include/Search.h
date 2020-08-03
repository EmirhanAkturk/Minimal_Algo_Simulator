#ifndef _SEARCH_H_
#define _SEARCH_H_

#include "MessageImp.h"

//#include "../utility/include/AVLTree.hpp"

enum{
  ADD_ORDER_TREE=1,
  ORDER_EXECUTED_TREE=2,
  ORDER_DELETE_TREE=3,
};
class Search:public MessageImp{
public:
    Search();
    ~Search();

    // virtual void operation(const char* file);

    //virtual void fileRead(ifstream & inFile);
    virtual void fileRead(const char * file);
    virtual inline void print(int treeChoice,int printChoice);

    virtual inline void writeFile(const char* outFile,int treeChoice,int writeChoice);
    
private:
    

    virtual inline string readLine(ifstream& infile);
    virtual void findValues(const string & line);
    int findColumn(istringstream& inString,int flag,int collumn);
    
    virtual void fileAddOrder(istringstream &inString,int flag);
    virtual void fileOrderExecute(istringstream &inString,int flag);
    virtual void fileOrderDelete(istringstream &inString,int flag);
    
    template<class T>
    inline void addMessage(AVLTree<T>& tree,const T& message);
    
    // AVLTree<AddOrder> AddOrderTree;
    // AVLTree<OrderExecute> OrderExecuteTree;
    // AVLTree<OrderDelete> OrderDeleteTree;

    
};

#endif
