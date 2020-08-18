#ifndef _VWAP_HPP_
#define _VWAP_HPP_

//#include "../../utility/AVLTree/inc/AVLTree.hpp"
//#include "../../utility/Graph/inc/Graph.hpp"
#include "../../utility/Temp/inc/Temp.hpp"

class VWAP{
public:
    VWAP()
    { /* deliberately left blank. */  }

    void calculate(AVLTree<OrderBookId>* OBITree);
    void calculate_and_write(Graph<uint32_t,Graph<uint32_t,Value>>* graph,uint32_t bookId);


private:

    static uint64_t totalVolume;
    static uint64_t totalVP;

};

#endif