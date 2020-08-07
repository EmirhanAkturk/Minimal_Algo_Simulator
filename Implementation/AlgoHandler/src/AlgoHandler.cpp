#include "../inc/AlgoHandler.hpp"
#include <ctime>

double AlgoHandler::compute(const char* file,char calculateChoice){
    if(isRead==false){
        // FileManager fm(AddOrderTree,OrderExecutedTree,OrderDeleteTree);
        // fm.fileRead(file);

        
        clock_t tStart = clock();

        FileManager::fileRead(file,SecondsTree,AddOrderTree,OrderExecutedTree,OrderDeleteTree);
        
        clock_t runtime=clock() - tStart;
        cout<<"Time taken:"<<(double)1000*(runtime)/CLOCKS_PER_SEC<<"ms\n";
        //ofstream outFile("Seconds.txt");
        //SecondsTree.writeFile(outFile, INORDER);
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