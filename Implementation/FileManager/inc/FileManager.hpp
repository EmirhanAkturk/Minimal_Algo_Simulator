#include "../../utility/AVLTree/inc/AVLTree.hpp"

class FileManager{
public:
    // /* FileManager(AVLTree<AddOrder>& AddOrderTree,
    //             AVLTree<OrderExecuted>& OrderExecutedTree,
    //             AVLTree<OrderDelete>& OrderDeleteTree)
    //             :_AddOrderTree{&AddOrderTree},
    //             _OrderExecutedTree{&OrderExecutedTree},
    //             _OrderDeleteTree{&OrderDeleteTree}
    // {/* deliberately left blank */} */

    FileManager()=delete;
    FileManager(FileManager&)=delete;

    static void fileRead(const char * file, 
                        AVLTree<AddOrder>&AddOrderTree,
                        AVLTree<OrderExecuted>&OrderExecutedTree,
                        AVLTree<OrderDelete>&OrderDeleteTree);

private:

    static inline string readLine(ifstream& inFile);

    static void findValues(const string & line,
                        AVLTree<AddOrder>&AOTree,
                        AVLTree<OrderExecuted>&OETree,
                        AVLTree<OrderDelete>&ODTree);

    static int findColumn(istringstream& inString,int flag,int collumn);

    static AddOrder fileAddOrder(istringstream &inString,int flag);
    static OrderExecuted fileOrderExecute(istringstream &inString,int flag);
    static OrderDelete fileOrderDelete(istringstream &inString,int flag);

    template<class T>
    static inline void addMessage(AVLTree<T>& tree,const T& message);
};