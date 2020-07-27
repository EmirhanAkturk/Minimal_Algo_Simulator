#ifndef _MESSAGEIMP_H_
#define _MESSAGEIMP_H_

#include "Bst.h" 

class MessageImp{
public:
    virtual ~MessageImp()
    {/*    Deliberately left blank  */}
    virtual void operation(const char * file)=0;

protected:
    MessageImp()
    {/*    Deliberately left blank  */}

    virtual void fileRead(ifstream & inFile,BinarySearchTree * tree,char messageType)=0;
    virtual int findColumn(istringstream& inString,int flag,int collumn)=0;
    
    
};

#endif
