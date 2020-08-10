#include "../inc/TWAP.hpp"
//#include "../../utility/AVLTree/inc/AVLTree.hpp"

uint32_t TWAP:: totalPrice=0;
int TWAP:: messageCount =0;


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
