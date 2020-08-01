#ifndef _SEARCH_H_
#define _SEARCH_H_

#include "MessageImp.h"

//struct Node;
class Search:public MessageImp{
public:
    Search();
    ~Search();

    virtual void operation(const char* file);

private:
    virtual void fileRead(ifstream & inFile);

    virtual inline string readLine(ifstream& infile);
    virtual void findValues(const string & line);
    int findColumn(istringstream& inString,int flag,int collumn);
    

    virtual void fileAddOrder(istringstream &inString,int flag);
    virtual void fileOrderExecute(istringstream &inString,int flag);
    virtual void fileOrderDelete(istringstream &inString,int flag);
    
};

#endif
