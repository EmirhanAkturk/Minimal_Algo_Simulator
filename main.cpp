//#define _TEST_

#ifdef _TEST_
#include "Client/src/Message.cpp"
#include "Implementation/src/Search.cpp"
#endif

#ifndef _TEST_
#include "Client/include/Message.h"
#include "Implementation/include/Search.h"
#endif

int main(){
    MessageImp* imp=new Search();
    Message* cSearch=new ClientSearch(imp);

    //const char *file="text.txt";
    const char *fileA="./documentation/AddOrderMessage.txt";
    const char *fileD="./documentation/OrderDeleteMessage.txt";
    const char *fileE="./documentation/OrderExecutedMessage.txt";
    cSearch->operation(fileA);
    cSearch->operation(fileD);
    cSearch->operation(fileE);


    return 0;
}