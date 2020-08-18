#include "../inc/AlgoHandler.hpp"
#include "../../DataManager/inc/DataManager.hpp"
#include "../../utility/AVLTree/inc/AVLTree.hpp"
#include "../../TWAP/inc/TWAP.hpp"
#include "../../VWAP/inc/VWAP.hpp"


//constructor is doing memory allocation.
AlgoHandler::AlgoHandler():isRead{false},OBITree{new AVLTree<OrderBookId>},
STree{new AVLTree<Seconds>},OETree{new AVLTree<OrderExecuted>},
ODTree{new AVLTree<OrderDelete>},graph{new Graph<uint32_t, Graph<uint32_t,Value> >}
{ /* deliberately left blank. */  }


void AlgoHandler::compute(const char* file,char calculateChoice){
    clock_t computeStart=clock();

    //It is checked if it has been read before in order not to read it again.
    if(isRead==false){
        
        clock_t tStart = clock();

        DataManager::fillTrees(file,STree,OBITree,OETree,ODTree);
        
        clock_t runtime=clock() - tStart;
        cout<<"Fill Trees Time taken:"<<(double)1000*(runtime)/CLOCKS_PER_SEC<<"ms\n";

        tStart = clock();

        fillGraph();
        
        runtime=clock() - tStart;
        cout<<"fill Timestamp Graph time taken:"<<(double)1000*(runtime)/CLOCKS_PER_SEC<<"ms\n";
        
        ofstream outFileB("outputFiles/OrderBookId.txt");
        
        OBITree->writeFile(outFileB,INORDER);

        tStart = clock();

        ofstream outFile("outputFiles/timestamps.txt");

        if(!outFile.good()){
            cerr<<"File  outputFiles/timestamps.txt  couldn't be opened.\n";
            exit(-1);
        }
        
        graph->writeFile(outFile);
        
        runtime=clock() - tStart;
        cout<<"Timestamp Graph writeFile time taken:"<<(double)1000*(runtime)/CLOCKS_PER_SEC<<"ms\n";

        isRead=true;
    }

    //The graph object is sent to the class that will calculate.
    
    
    if(calculateChoice == TWAP_CALCULATE){
        TWAP twap;
        twap.calculate(graph);
        //the calculation results are written in the TWAP.txt file.    
    }

    else if(calculateChoice == VWAP_CALCULATE){
        VWAP vwap;
        vwap.calculate(graph);
        //the calculation results are written in the VWAP.txt file.    
    }

    else
        cerr<<"Invalid calculate choice!!\n";

    clock_t computeRuntime=clock() - computeStart;

    cout<<"compute Time taken:"<<(double)1000*(computeRuntime)/CLOCKS_PER_SEC<<"ms\n";

}


void AlgoHandler::fillGraph(){
    AVLTree<Seconds>::Node * Sroot=STree->getRoot();
    
    if (Sroot == NULL) 
       return; 
  
    //iterative preorder traversal

    // Create an empty stack and push root to it 
    std::stack<AVLTree<Seconds>::Node *> Sstack; 
    Sstack.push(Sroot); 
  
    /* Pop all items one by one. Do following for every popped item 
       a) process it 
       b) push its right child 
       c) push its left child 
    Note that right child is pushed first so that left is processed first */


    while (Sstack.empty() == false) 
    { 
        // Pop the top item from stack and process it 
        AVLTree<Seconds>::Node *node = Sstack.top(); 

        fillNanosecondGraph(node);

        Sstack.pop(); 
  
        // Push right and left children of the popped node to stack 
        if (node->right) 
            Sstack.push(node->right); 
        if (node->left) 
            Sstack.push(node->left); 
    } 
}



void AlgoHandler::fillNanosecondGraph(AVLTree<Seconds>::Node *Snode){
    AVLTree<AddOrder>::Node * AOroot=Snode->AOTree->getRoot();
    
    if (AOroot == NULL) 
       return; 
  
    //iterative preorder traversal

    // Create an empty stack and push root to it 
    std::stack<AVLTree<AddOrder>::Node *> AOstack; 
    AOstack.push(AOroot); 
  
    /* Pop all items one by one. Do following for every popped item 
       a) process it 
       b) push its right child 
       c) push its left child 
    Note that right child is pushed first so that left is processed first */

    while (AOstack.empty() == false) 
    { 
        // Pop the top item from stack and process it 
        AVLTree<AddOrder>::Node *node = AOstack.top(); 
        
        //Calculations will be made only for messages with 73616 order book id.
        if(node->orderBookId==73616){
            graph->addEdge(Snode->timestamp,node->nanosecond,node->orderPrice,node->quantity);
        }

        AOstack.pop(); 
  
        // Push right and left children of the popped node to stack 
        if (node->right) 
            AOstack.push(node->right); 
        if (node->left) 
            AOstack.push(node->left); 
    } 
}