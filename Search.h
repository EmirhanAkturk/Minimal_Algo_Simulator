#ifndef _SEARCH_H_
#define _SEARCH_H_

#include "MessageImp.h"
#include "Bst.h"

//struct Node;
class Search:public MessageImp{
public:
    Search();
    ~Search();

    virtual void operation(const char* file);

private:
    void fileRead(ifstream & inFile,BinarySearchTree & tree,char messageType);
    int findColumn(istringstream& inString,int flag,int collumn);
    
};

#endif
