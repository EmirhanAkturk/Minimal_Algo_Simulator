#include "../../utility/inc/std.hpp"

template<class T>
class AVLTree;

class FileManager{
public:

    FileManager()=delete;
    FileManager(FileManager&)=delete;

    static void fileRead(const char * file,
                        AVLTree<Seconds>*STree,
                        AVLTree<AddOrder>*AOTree,
                        AVLTree<OrderExecuted>*OETree,
                        AVLTree<OrderDelete>*ODTree);

private:

    static inline std::string readLine(std::ifstream& inFile);

    static void findValues(const std::string & line,
                        AVLTree<Seconds>*STree,
                        AVLTree<AddOrder>*AOTree,
                        AVLTree<OrderExecuted>*OETree,
                        AVLTree<OrderDelete>*ODTree);

    static int findColumn(std::istringstream& inString,int flag,int collumn);

    static Seconds fileSeconds(std::istringstream &inString,int flag);
    static AddOrder fileAddOrder(std::istringstream &inString,int flag);
    static OrderExecuted fileOrderExecute(std::istringstream &inString,int flag);
    static OrderDelete fileOrderDelete(std::istringstream &inString,int flag);

    template<class T>
    static inline void addMessage(AVLTree<T>* tree,const T& message);
};