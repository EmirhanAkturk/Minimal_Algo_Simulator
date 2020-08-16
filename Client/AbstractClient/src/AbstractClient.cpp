#include "../inc/AbstractClient.hpp"
#include "../../../Implementation/AbstractImp/inc/AbstractImp.hpp"

AbstractClient::AbstractClient() {
}

AbstractClient::~AbstractClient() {
}

RefinedAbstractClient::RefinedAbstractClient(AbstractImp* imp) {
    _imp = imp;
}

RefinedAbstractClient::~RefinedAbstractClient() {
}

void RefinedAbstractClient::compute(const char* file,char calculateChoice){
    _imp->compute(file,calculateChoice);
}