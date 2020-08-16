#ifndef _ALGO_HANDER_HPP_
#define _ALGO_HANDER_HPP_

#include "../../AbstractImp/inc/AbstractImp.hpp"
#include "../../utility/inc/std.hpp"
#include "../../utility/AVLTree/inc/AVLTree.hpp"
//AVLTree.hpp, Included to be able to access "AVL Tree <Seconds> :: Node".

enum choice{
    TWAP_CALCULATE='T',
    VWAP_CALCULATE='V'
};

//forward declaration
template<class T>
class AVLTree;

//forward declaration
template<class K,class V>
class Graph;

//forward declarations
struct Value;
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
    //AVLTree<AddOrder>*AOTree;  //Inside the Stree.

    AVLTree<OrderDelete>*ODTree;
    AVLTree<OrderExecuted>*OETree;

    Graph<uint32_t ,Graph<uint32_t, Value>> *graph;

    bool isRead;

    void fillGraph();
    void fillNanosecondGraph(AVLTree<Seconds>::Node *node);
};

#endif