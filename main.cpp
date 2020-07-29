#include "Client/include/Message.h"
#include "Implementation/include/Search.h"

int main(){
    MessageImp* imp=new Search();
    Message* cSearch=new ClientSearch(imp);

    //const char *file="message.txt";
    const char *file="./documentation/AddOrderMessage.txt";
    cSearch->operation(file);

    return 0;
}