#ifndef _TWAP_HPP_
#define _TWAP_HPP_

#include "../../AbstractImp/inc/AbstractImp.hpp"
#include "../../utility/AVLTree/include/AVLTree.hpp"

class TWAP:public AbstractImp {
public:
    TWAP()
    { /* deliberately left blank. */  }

private:

    virtual double compute(const char* file)override;
    void calculate(AVLTree<AddOrder>::Node* node)const;              

    static uint32_t totalPrice;
    static int messageCount;

};

#endif