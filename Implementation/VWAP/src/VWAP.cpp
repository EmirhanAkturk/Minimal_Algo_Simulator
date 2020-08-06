#include "../inc/VWAP.hpp"

uint32_t VWAP:: totalPrice=0;
int VWAP:: messageCount =0;

// AVLTree<AddOrder> Tree::AddOrderTree;
// AVLTree<OrderDelete> Tree::OrderDeleteTree;
// AVLTree<OrderExecuted> Tree::OrderExecutedTree;

void VWAP:: calculate(AVLTree<AddOrder>::Node* node)const{
    if(node == nullptr)
        return;
    
    totalPrice += node->orderPrice;
    ++messageCount;

    calculate(node->left);
    
    calculate(node->right);
}

double VWAP:: compute(const char *file ){
    if(Tree::isRead == false){
        cout<<"VWAP reading...\n";
        fileRead(file);
        Tree::isRead = true;
    }
    calculate(Tree::AddOrderTree.getRoot());
    ofstream outFile("VwapAddOrder.txt");
    Tree::AddOrderTree.writeFile(outFile,INORDER);
    return (static_cast<double>(totalPrice)/static_cast<double>(messageCount));
}