#define _TEST_

#ifdef _TEST_
#include "Client/src/Message.cpp"
#include "Implementation/src/Search.cpp"
#include "Implementation/utility/src/AVLTree.cpp"
#endif

#ifndef _TEST_
#include "Client/include/Message.h"
#include "Implementation/include/Search.h"
#endif

int main(){
    MessageImp* imp=new Search();
    Message* cSearch=new ClientSearch(imp);

    //const char *file="message.txt";
    const char *file="./documentation/AddOrderMessage.txt";
    cSearch->operation(file);

    return 0;
}