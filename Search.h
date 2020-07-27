#ifndef _SEARCH_H_
#define _SEARCH_H_

#include "MessageImp.h"


//struct Node;
class Search:public MessageImp{
public:
    Search();
    ~Search();

    virtual void operation(const char* file);

    virtual void fileRead(ifstream & inFile,BinarySearchTree *tree,char messageType);
    virtual int findColumn(istringstream& inString,int flag,int collumn);
    
};

#endif
