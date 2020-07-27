#include "Message.h"
#include "MessageImp.h"

Message::Message()
{/*    Deliberately left blank  */}

Message::~Message()
{/*    Deliberately left blank  */}

ClientSearch::ClientSearch( MessageImp* imp){
    _imp=imp;
}

ClientSearch::~ClientSearch()
{/*    Deliberately left blank  */}

void ClientSearch:: operation(const char* file){
    _imp->operation(file);

}