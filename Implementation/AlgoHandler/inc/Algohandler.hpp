#include "../../AbstractImp/inc/AbstractImp.hpp"

enum choice{
    TWAP_CALCULATE='T',
    VWAP_CALCULATE='V'
};

template<class T>
class AVLTree;

struct Seconds;
struct AddOrder;
struct OrderDelete;
struct OrderExecuted;

class AlgoHandler:public AbstractImp{
public:
    AlgoHandler();

    virtual double compute(const char* file,char calculateChoice)override;
    
private:
    AVLTree<Seconds>*STree;
    AVLTree<AddOrder>*AOTree;
    AVLTree<OrderDelete>*ODTree;
    AVLTree<OrderExecuted>*OETree;

    bool isRead;

};
