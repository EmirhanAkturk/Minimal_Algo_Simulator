#include "../include/Message.h"
#include "../../Implementation/include/MessageImp.h"

Message::Message(){

}

Message::~Message(){

}

ClientSearch::ClientSearch( MessageImp* imp){
    _imp=imp;
}

ClientSearch::~ClientSearch(){

}

// void ClientSearch:: operation(const char* file){
//     _imp->operation(file);

// }

void ClientSearch::fileRead(const char * file){
    _imp->fileRead(file);
}

inline void ClientSearch::print(int treeChoice,int printChoice){
    _imp->print(treeChoice,printChoice);
}
    
inline void ClientSearch::writeFile(const char* outFile,int treeChoice,int writeChoice){
    _imp->writeFile(outFile,treeChoice,writeChoice);
}
    