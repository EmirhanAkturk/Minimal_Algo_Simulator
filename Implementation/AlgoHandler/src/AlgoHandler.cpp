#include "../inc/AlgoHandler.hpp"
#include "../../FileManager/inc/FileManager.hpp"
#include "../../utility/AVLTree/inc/AVLTree.hpp"
#include "../../TWAP/inc/TWAP.hpp"
#include "../../VWAP/inc/VWAP.hpp"


AlgoHandler::AlgoHandler():isRead{false},AOTree{new AVLTree<AddOrder>},
OETree{new AVLTree<OrderExecuted>},ODTree{new AVLTree<OrderDelete>}
{ /* deliberately left blank. */  }

double AlgoHandler::compute(const char* file,char calculateChoice){
    if(isRead==false){
        
        clock_t tStart = clock();

        FileManager::fileRead(file,STree,AOTree,OETree,ODTree);
        
        clock_t runtime=clock() - tStart;
        cout<<"Time taken:"<<(double)1000*(runtime)/CLOCKS_PER_SEC<<"ms\n";

        isRead=true;
    }

    if(calculateChoice == TWAP_CALCULATE){
        TWAP twap;
        double result = twap.calculate(AOTree->getRoot());
        return result;
    }

    else if(calculateChoice == VWAP_CALCULATE){
        VWAP vwap;
        double result = vwap.calculate(AOTree->getRoot());
        return result;
    }

    cerr<<"Invalid calculate choice!!\n";
    return -1;

}