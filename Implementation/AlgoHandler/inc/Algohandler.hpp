#ifndef _ALGO_HANDER_HPP_
#define _ALGO_HANDER_HPP_

#include "../../AbstractImp/inc/AbstractImp.hpp"
#include "../../utility/inc/std.hpp"
//#include "../../utility/Graph/inc/Graph.hpp"
#include "../../utility/AVLTree/inc/AVLTree.hpp"

enum choice{
    TWAP_CALCULATE='T',
    VWAP_CALCULATE='V'
};

template<class T>
class AVLTree;

template<class K,class V>
class Graph;

struct Value;
struct Bar;
struct Seconds;
struct AddOrder;
struct OrderDelete;
struct OrderExecuted;

class AlgoHandler:public AbstractImp{
public:
    AlgoHandler();

    virtual void compute(const char* file,char calculateChoice)override;
    
private:
    AVLTree<Seconds>*STree;
    AVLTree<AddOrder>*AOTree;
    AVLTree<OrderDelete>*ODTree;
    AVLTree<OrderExecuted>*OETree;

    Graph<uint32_t ,Graph<uint32_t, Value>> *graph;

    bool isRead;

    void fillTimestampGraph();
    void fillNanosecondGraph(AVLTree<Seconds>::Node *node);
};

#endif