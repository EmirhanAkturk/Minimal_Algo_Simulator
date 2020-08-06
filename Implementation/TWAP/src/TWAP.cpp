#include "../inc/TWAP.hpp"
#include "../../utility/AVLTree/src/AVLTree.cpp"

uint32_t TWAP:: totalPrice=0;
int TWAP:: messageCount =0;

void TWAP:: calculate(AVLTree<AddOrder>::Node* node)const{
    if(node == nullptr)
        return;
    
    totalPrice += node->orderPrice;
    ++messageCount;

    calculate(node->left);
    
    calculate(node->right);
}

double TWAP:: compute(const char *file ){
    fileRead(file);
    calculate(AddOrderTree.getRoot());
    ofstream outFile("TwapAddOrder.txt");
    AddOrderTree.writeFile(outFile,INORDER);
    return (static_cast<double>(totalPrice)/static_cast<double>(messageCount));
}