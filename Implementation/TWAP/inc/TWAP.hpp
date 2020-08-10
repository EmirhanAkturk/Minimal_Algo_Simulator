#ifndef _TWAP_HPP_
#define _TWAP_HPP_

#include "../../utility/AVLTree/inc/AVLTree.hpp"
// template <class T>
// class AVLTree;

// struct AddOrder;


class TWAP{
public:
    TWAP()
    { /* deliberately left blank. */  }

    double calculate(AVLTree<AddOrder>::Node* node)const;              

private:

    //virtual double compute(const char* file)override;

    void calculateTotalPrice(AVLTree<AddOrder>::Node* node)const;

    static uint32_t totalPrice;
    static int messageCount;

};

#endif