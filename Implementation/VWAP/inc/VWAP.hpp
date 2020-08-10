#ifndef _VWAP_HPP_
#define _VWAP_HPP_

#include "../../utility/AVLTree/inc/AVLTree.hpp"

class VWAP{
public:
    VWAP()
    { /* deliberately left blank. */  }

    double calculate(AVLTree<AddOrder>::Node* node)const;              

private:

    void calculateTotalPrice(AVLTree<AddOrder>::Node* node)const;

    static uint32_t totalPrice;
    static int messageCount;

};

#endif