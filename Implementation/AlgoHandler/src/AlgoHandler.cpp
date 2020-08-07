#include "../inc/AlgoHandler.hpp"

double AlgoHandler::compute(const char* file,char calculateChoice){
    if(isRead==false){
        // FileManager fm(AddOrderTree,OrderExecutedTree,OrderDeleteTree);
        // fm.fileRead(file);
        FileManager::fileRead(file,AddOrderTree,OrderExecutedTree,OrderDeleteTree);
        isRead=true;
    }

    if(calculateChoice == TWAP_CALCULATE){
        TWAP twap;
        double result = twap.calculate(AddOrderTree.getRoot());
        return result;
    }

    else if(calculateChoice == VWAP_CALCULATE){
        VWAP vwap;
        double result = vwap.calculate(AddOrderTree.getRoot());
        return result;
    }

    cerr<<"Invalid calculate choice!!\n";
    return -1;

}