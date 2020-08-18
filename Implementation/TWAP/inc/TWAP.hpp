#ifndef _TWAP_HPP_
#define _TWAP_HPP_

//#include "../../utility/AVLTree/inc/AVLTree.hpp"
//#include "../../utility/Graph/inc/Graph.hpp"
#include "../../utility/Temp/inc/Temp.hpp"

class TWAP{
public:
    TWAP()
    { /* deliberately left blank. */  }

    void calculate(AVLTree<OrderBookId>* OBITree);
    void calculate_and_write(Graph<uint32_t,Graph<uint32_t,Value>>* graph,uint32_t bookId);

private:

    static double totalTypicalPrice;
    static int barCount;

};

#endif