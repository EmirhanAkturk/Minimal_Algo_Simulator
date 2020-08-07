#include "../../AbstractImp/inc/AbstractImp.hpp"
#include "../../TWAP/inc/TWAP.hpp"
#include "../../VWAP/inc/VWAP.hpp"
#include "../../FileManager/inc/FileManager.hpp"

class AlgoHandler:public AbstractImp{
public:
    AlgoHandler():isRead{false}
    { /* deliberately left blank. */  }

    virtual double compute(const char* file,char calculateChoice)override;
    
private:
    AVLTree<Seconds>SecondsTree;
    AVLTree<AddOrder>AddOrderTree;
    AVLTree<OrderDelete>OrderDeleteTree;
    AVLTree<OrderExecuted>OrderExecutedTree;

    bool isRead;

};
