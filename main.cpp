#include "Message.cpp"
//#include "MessageImp.h"
#include "Search.cpp"
#include "Bst.cpp"

#include<iostream>

using namespace std;

int main(){
    MessageImp* imp=new Search();
    Message* cSearch=new ClientSearch(imp);

    const char *file="message.txt";
    cSearch->operation(file);
    
    return 0;
}