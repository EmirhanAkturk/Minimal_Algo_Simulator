#include "../inc/TWAP.hpp"
//#include "../../utility/AVLTree/inc/AVLTree.hpp"

//uint32_t TWAP:: totalPrice=0;
//int TWAP:: messageCount =0;

uint32_t TWAP:: totalAverageBarPrice=0;
int TWAP:: barCount =0;


double TWAP:: calculate(AVLTree<AddOrder>::Node* node){
    Graph<uint32_t,Bar>* graph= new Graph<uint32_t,Bar>;
    //insertBar(node,map);

    clock_t tStart = clock();

    insertBar(node,graph);
    
    clock_t runtime=clock() - tStart;
    std::cout<<"insertBart Time taken:"<<(double)1000*(runtime)/CLOCKS_PER_SEC<<"ms\n";

    ofstream outFile("outputFiles/Bar.txt");

    tStart = clock();

    graph->writeFile(outFile);
    
    runtime=clock() - tStart;
    std::cout<<"writeFile Time taken:"<<(double)1000*(runtime)/CLOCKS_PER_SEC<<"ms\n";

    //map.print();
    
    calculateAveragePrice(graph);
    //calculateTotalPrice(node);

    //return (static_cast<double>(totalPrice)/static_cast<double>(messageCount));
    return (static_cast<double>(totalAverageBarPrice)/static_cast<double>(barCount));
}

void TWAP:: calculateAveragePrice(Graph<uint32_t,Bar> *graph){
    std::unordered_map<uint32_t,Bar>::iterator itr;
    double totalBarPrice;
    double averageBarPrice;

    for (itr = graph->getMapBegin(); itr!= graph->getMapEnd(); ++itr) 
    {   
        totalBarPrice =  itr->second.open+itr->second.high+
                         itr->second.low+itr->second.close;

        averageBarPrice = static_cast<double>(totalBarPrice)/4;

        totalAverageBarPrice+=averageBarPrice;
        ++barCount;

    }     
}

/* void TWAP:: calculateTotalPrice(AVLTree<AddOrder>::Node* node){
    if(node == nullptr)
        return;
    
    totalPrice += node->orderPrice;
    ++messageCount;

    calculateTotalPrice(node->left);
    
    calculateTotalPrice(node->right);
}
 */
void TWAP::insertBar(AVLTree<AddOrder>::Node* node,Graph<uint32_t,Bar>* graph){
    if(node == nullptr)
        return;

    insertBar(node->left, graph);
    insertBar(node->right, graph);

    graph->addEdge(node->nanosecond,node->orderPrice);
}