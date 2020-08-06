#include "Implementation/TWAP/inc/TWAP.hpp"
#include "Implementation/VWAP/inc/VWAP.hpp"
AVLTree<AddOrder> Tree::AddOrderTree;
AVLTree<OrderDelete> Tree::OrderDeleteTree;
AVLTree<OrderExecuted> Tree::OrderExecutedTree;
bool Tree::isRead=false;

int main(){
    AbstractImp * imp = new TWAP();

    const char *file = "documentation/AddOrderMessage.txt";

    double averagePrice=imp->compute(file);

    cout<<"AveragePrice:"<<averagePrice<<endl;

    imp = new VWAP();

    averagePrice=imp->compute(file);

    cout<<"AveragePrice:"<<averagePrice<<endl;

    return 0;
}