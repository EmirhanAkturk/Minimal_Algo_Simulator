#include "../../AbstractImp/inc/AbstractImp.hpp"
#include "../../TWAP/inc/TWAP.hpp"
#include "../../VWAP/inc/VWAP.hpp"

class AlgoHandler:public AbstractImp{
public:
    AlgoHandler():isRead{false}
    { /* deliberately left blank. */  }

    virtual double compute(const char* file,char calculateChoice)override;
    
private:
    AVLTree<AddOrder>AddOrderTree;
    AVLTree<OrderDelete>OrderDeleteTree;
    AVLTree<OrderExecuted>OrderExecutedTree;

    bool isRead;

    void fileRead(const char * file );
    inline string readLine(ifstream& inFile);

    void findValues(const string & line);
    int findColumn(istringstream& inString,int flag,int collumn);

    void fileAddOrder(istringstream &inString,int flag);
    void fileOrderExecute(istringstream &inString,int flag);
    void fileOrderDelete(istringstream &inString,int flag);

    template<class T>
    inline void addMessage(AVLTree<T>& tree,const T& message);

};
