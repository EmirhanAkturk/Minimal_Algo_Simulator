#include "../inc/VWAP.hpp"

uint32_t VWAP:: totalPrice=0;
int VWAP:: messageCount =0;

double VWAP:: calculate(AVLTree<AddOrder>::Node* node)const{
    calculateTotalPrice(node);
    
    return (static_cast<double>(totalPrice)/static_cast<double>(messageCount));
}

void VWAP:: calculateTotalPrice(AVLTree<AddOrder>::Node* node)const{
    if(node == nullptr)
        return;
    
    totalPrice += node->orderPrice;
    ++messageCount;

    calculateTotalPrice(node->left);
    
    calculateTotalPrice(node->right);
}