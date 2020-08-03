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

    cout<<"Add Order messages reading\n";
    cSearch->fileRead(fileA);

    cout<<"Order Delete messages reading\n";
    cSearch->fileRead(fileD);

    cout<<"Order Executed messages reading\n";
    cSearch->fileRead(fileE);

    const char *outFileA="addOrder.txt";
    const char *outFileD="orderDelete.txt";
    const char *outFileE="orderExecute.txt";

    cout<<"Add Order messages writing\n";
    cSearch->writeFile(outFileA,ADD_ORDER_TREE,INORDER);

    cout<<"Order Delete messages writing\n";
    cSearch->writeFile(outFileD,ORDER_DELETE_TREE,INORDER);

    cout<<"Order Executed messages writing\n";
    cSearch->writeFile(outFileE,ORDER_EXECUTED_TREE,INORDER);

    return 0;
}