#include "../../AbstractImp/inc/AbstractImp.hpp"
#include "../../utility/AVLTree/include/AVLTree.hpp"

class VWAP:public AbstractImp{
private:
    virtual double compute(const char* file)override;
};