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

    //double calculate(AVLTree<AddOrder>::Node* node);
    void calculate(Graph<uint32_t,Graph<uint32_t,Bar>>* graph);

private:

    static double totalTypicalPrice;
    static int barCount;

};

#endif