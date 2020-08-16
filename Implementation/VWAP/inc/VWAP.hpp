#ifndef _VWAP_HPP_
#define _VWAP_HPP_

#include "../../utility/AVLTree/inc/AVLTree.hpp"
#include "../../utility/Graph/inc/Graph.hpp"

class VWAP{
public:
    VWAP()
    { /* deliberately left blank. */  }

    void calculate(Graph<uint32_t,Graph<uint32_t,Value>>* graph);              

private:

    static uint32_t totalVolume;
    static uint32_t totalVP;

};

#endif