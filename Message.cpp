#include "Message.h"
#include "MessageImp.h"

Message::Message(){

}

Message::~Message(){

}

ClientSearch::ClientSearch( MessageImp* imp){
    _imp=imp;
}

ClientSearch::~ClientSearch(){

}

void ClientSearch:: operation(const char* file){
    _imp->operation(file);

}