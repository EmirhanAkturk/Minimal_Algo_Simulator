#ifndef _VWAP_HPP_
#define _VWAP_HPP_

#include "../../AbstractImp/inc/AbstractImp.hpp"
#include "../../utility/AVLTree/include/AVLTree.hpp"

class VWAP:public AbstractImp {
public:
    VWAP()
    { /* deliberately left blank. */  }

private:

    virtual double compute(const char* file)override;
    void calculate(AVLTree<AddOrder>::Node* node)const;              

    static uint32_t totalPrice;
    static int messageCount;

};

#endif