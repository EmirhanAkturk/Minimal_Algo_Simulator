#ifndef _TWAP_HPP_
#define _TWAP_HPP_

#include "../../utility/AVLTree/inc/AVLTree.hpp"
#include "../../utility/Graph/inc/Graph.hpp"

class TWAP{
public:
    TWAP()
    { /* deliberately left blank. */  }

    void calculate(Graph<uint32_t,Graph<uint32_t,Value>>* graph);

private:

    static double totalTypicalPrice;
    static int barCount;

};

#endif