#ifndef _DATA_MANAGER_
#define _DATA_MANAGER_

#include "../../utility/inc/std.hpp"

template<class T>
class AVLTree;

class DataManager{
public:

    DataManager()=delete;
    DataManager(DataManager&)=delete;

    static void fillTrees(const char * file,
                        AVLTree<Seconds>*STree,
                        AVLTree<OrderExecuted>*OETree,
                        AVLTree<OrderDelete>*ODTree);

private:

    static inline std::string readLine(std::ifstream& inFile);

    static void findValues(const std::string & line,
                        AVLTree<Seconds>*STree,
                        AVLTree<OrderExecuted>*OETree,
                        AVLTree<OrderDelete>*ODTree);

    static int findColumn(std::istringstream& inString,int flag,int collumn);

    static Seconds fillSecondsTree(std::istringstream &inString,int flag);
    static AddOrder fillAddOrderTree(std::istringstream &inString,int flag);
    static OrderExecuted fillOrderExecutedTree(std::istringstream &inString,int flag);
    static OrderDelete fillOrderDeleteTree(std::istringstream &inString,int flag);

    template<class T>
    static inline void addMessage(AVLTree<T>* tree,const T& message);
    static uint32_t curTimestamp;//current timestamp
};

#endif