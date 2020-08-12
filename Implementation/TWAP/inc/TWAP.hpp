#ifndef _TWAP_HPP_
#define _TWAP_HPP_

#include "../../utility/AVLTree/inc/AVLTree.hpp"
#include "../../utility/Graph/inc/Graph.hpp"
// template <class T>
// class AVLTree;

// struct AddOrder;


class TWAP{
public:
    TWAP()
    { /* deliberately left blank. */  }

    double calculate(AVLTree<AddOrder>::Node* node);              

private:


    void calculateAveragePrice(Graph<uint32_t,Bar>* graph);
    //void calculateTotalPrice(AVLTree<AddOrder>::Node* node);

    void insertBar(AVLTree<AddOrder>::Node* node,Graph<uint32_t,Bar>* graph);
    
    //static uint32_t totalPrice;
    static uint32_t totalAverageBarPrice;

    //static int messageCount;
    static int barCount;

};

#endif