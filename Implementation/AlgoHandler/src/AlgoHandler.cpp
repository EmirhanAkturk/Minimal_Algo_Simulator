#include "../inc/AlgoHandler.hpp"
#include "../../FileManager/inc/FileManager.hpp"
#include "../../utility/AVLTree/inc/AVLTree.hpp"
#include "../../TWAP/inc/TWAP.hpp"
#include "../../VWAP/inc/VWAP.hpp"


AlgoHandler::AlgoHandler():isRead{false},STree{new AVLTree<Seconds>},
AOTree{new AVLTree<AddOrder>},OETree{new AVLTree<OrderExecuted>},
ODTree{new AVLTree<OrderDelete>},graph{new Graph<uint32_t, Value>}
{ /* deliberately left blank. */  }

double AlgoHandler::compute(const char* file,char calculateChoice){
    if(isRead==false){
        
        clock_t tStart = clock();

        FileManager::fileRead(file,STree,AOTree,OETree,ODTree);
        
        clock_t runtime=clock() - tStart;
        cout<<"Time taken:"<<(double)1000*(runtime)/CLOCKS_PER_SEC<<"ms\n";

        tStart = clock();

        functionSeconds();
        // AOTree->writeFile(outFileA,INORDER);
        
        runtime=clock() - tStart;
        cout<<"function seconds time taken:"<<(double)1000*(runtime)/CLOCKS_PER_SEC<<"ms\n";
        
        ofstream outFileA("newAddOrder.txt");
        
        graph->writeFile(outFileA);



        ofstream outFileB("newSeconds.txt");
        STree->writeFile(outFileB,INORDER);

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

void AlgoHandler::functionSeconds(){
    AVLTree<Seconds>::Node * Sroot=STree->getRoot();

    //uint32_t timestamp = Sroot->timestamp;
    
    if (Sroot == NULL) 
       return; 
  
    // Create an empty stack and push root to it 
    std::stack<AVLTree<Seconds>::Node *> Sstack; 
    Sstack.push(Sroot); 
  
    /* Pop all items one by one. Do following for every popped item 
       a) print it 
       b) push its right child 
       c) push its left child 
    Note that right child is pushed first so that left is processed first */

    ofstream outFile("timestamp.txt");

    while (Sstack.empty() == false) 
    { 
        // Pop the top item from stack and print it 
        AVLTree<Seconds>::Node *node = Sstack.top(); 

        //cout<<node->timestamp<<endl;
        functionAddOrder(node->timestamp,outFile);

        Sstack.pop(); 
  
        // Push right and left children of the popped node to stack 
        if (node->right) 
            Sstack.push(node->right); 
        if (node->left) 
            Sstack.push(node->left); 
    } 
}



void AlgoHandler::functionAddOrder(uint32_t timestamp,ofstream& outFile){
    //AVLTree<Seconds>::Node * Sroot=STree->getRoot();

    AVLTree<AddOrder>::Node * AOroot=AOTree->getRoot();

    //uint32_t timestamp = Sroot->timestamp;
    
    if (AOroot == NULL) 
       return; 
  
    // Create an empty stack and push root to it 
    std::stack<AVLTree<AddOrder>::Node *> AOstack; 
    AOstack.push(AOroot); 
  
    /* Pop all items one by one. Do following for every popped item 
       a) print it 
       b) push its right child 
       c) push its left child 
    Note that right child is pushed first so that left is processed first */

    while (AOstack.empty() == false) 
    { 
        // Pop the top item from stack and print it 
        AVLTree<AddOrder>::Node *node = AOstack.top(); 
        // if(node->timestamp==timestamp){
        //     outFile << node->timestamp<<";"<<node->nanosecond<<";"
        //             <<node->orderId<<";"<<node->orderPrice<<endl;
        // }
        if(node->timestamp==timestamp){
            graph->addEdge(timestamp,node->nanosecond,node->orderPrice);
        }

        AOstack.pop(); 
  
        // Push right and left children of the popped node to stack 
        if (node->right) 
            AOstack.push(node->right); 
        if (node->left) 
            AOstack.push(node->left); 
    } 
}