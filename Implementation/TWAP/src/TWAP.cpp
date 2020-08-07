#include "../inc/TWAP.hpp"

uint32_t TWAP:: totalPrice=0;
int TWAP:: messageCount =0;

// AVLTree<AddOrder> Tree::AddOrderTree;
// AVLTree<OrderDelete> Tree::OrderDeleteTree;
// AVLTree<OrderExecuted> Tree::OrderExecutedTree;

double TWAP:: calculate(AVLTree<AddOrder>::Node* node)const{
    calculateTotalPrice(node);
    
    return (static_cast<double>(totalPrice)/static_cast<double>(messageCount));
}

void TWAP:: calculateTotalPrice(AVLTree<AddOrder>::Node* node)const{
    if(node == nullptr)
        return;
    
    totalPrice += node->orderPrice;
    ++messageCount;

    calculate(node->left);
    
    calculate(node->right);
}

// double TWAP:: compute(const char *file ){
//     if(Tree::isRead == false){
//         cout<<"TWAP reading...\n";
//         fileRead(file);
//         Tree::isRead = true;
//     }
//     calculate(Tree::AddOrderTree.getRoot());
//     ofstream outFile("TwapAddOrder.txt");
//     Tree::AddOrderTree.writeFile(outFile,INORDER);
//     return (static_cast<double>(totalPrice)/static_cast<double>(messageCount));
// }