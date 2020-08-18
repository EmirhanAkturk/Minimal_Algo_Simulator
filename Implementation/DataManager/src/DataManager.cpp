#include "../../utility/AVLTree/inc/AVLTree.hpp"
#include "../inc/DataManager.hpp"

using std::istringstream;
using std::ifstream;

//initialize curTimestamp value
uint32_t DataManager::curTimestamp=0;

template<class T>
inline void DataManager::addMessage(AVLTree<T>* tree,const T& message){
    tree->insert(message);
}

void  DataManager::fillTrees(const char * file,
                            AVLTree<Seconds>*STree,
                            AVLTree<OrderBookId>*OBITree,
                            AVLTree<OrderExecuted>*OETree,
                            AVLTree<OrderDelete>*ODTree)
{

    ifstream inFile(file);

    if(!inFile.good()){
        cerr<<"File  "<<file<< "  couldn't be opened.\n";
        exit(-1);
    }

    while(!inFile.eof()){

        string line=readLine(inFile);

        if(line.size()>1){
            findValues(line,STree,OBITree,OETree,ODTree);
        }
    }

}

inline string DataManager::readLine(ifstream& inFile){
    string line;
    inFile>>line;
    return line;
}


void DataManager::findValues(const string & line,
                        AVLTree<Seconds>*STree,
                        AVLTree<OrderBookId>*OBITree,
                        AVLTree<OrderExecuted>*OETree,
                        AVLTree<OrderDelete>*ODTree)
{
    istringstream inString(line);

    int flag=1;
    flag=findColumn(inString,flag,2);
    
    if(flag!=2){
        cerr<<"Incorrect column value:"<<flag<<endl;
        exit(1);
    }

    char c;
    inString>>c;
    switch(c){
        case SECONDS:{
            Seconds messageT = fillSecondsTree(inString,flag);
            curTimestamp=messageT.timestamp;
            addMessage(STree,messageT);
            break;
            }
        case ADD_ORDER_TYPE:{ 
            AddOrder messageA = fillAddOrderTree(inString,flag);
            AVLTree<Seconds>::Node* query=STree->search(curTimestamp);
            query->AOTree->insert(messageA);
            OBITree->insert(messageA.orderBookId);
            break;
            }
        
        case ORDER_EXECUTED_TYPE:{
            OrderExecuted messageE = fillOrderExecutedTree(inString,flag);
            addMessage(OETree,messageE);
            break;
            }
        case ORDER_DELETE_TYPE:{
            OrderDelete messageD = fillOrderDeleteTree(inString,flag);
            addMessage(ODTree,messageD);
            break;
            }
        default:
            cout<<"invalid message type!!\n";
            
    }
        
        
}


int DataManager::findColumn(istringstream& inString,int flag,int collumn){
    char c;
    while(!inString.eof() && flag<collumn){
        inString>>c;
        if(c==';')
            ++flag;
    }

    return flag;
}


Seconds DataManager::fillSecondsTree(istringstream &inString,int flag){
    
    Seconds messageT;
    
    flag=findColumn(inString,flag,3);
    if(flag!=3){
        cerr<<"Incorrect column value!!\n";
        exit(1);
    }
    inString>>messageT.timestamp;

    return messageT;
}


AddOrder DataManager::fillAddOrderTree(istringstream &inString,int flag){
    
    AddOrder messageA;
    
    messageA.timestamp=curTimestamp;

    flag=findColumn(inString,flag,3);
    if(flag!=3){
        cerr<<"Incorrect column value!!\n";
        exit(1);
    }
    inString>>messageA.nanosecond;

    flag=findColumn(inString,flag,4);
    if(flag!=4){
        cerr<<"Incorrect column value!!\n";
        exit(1);
    }
    inString>>messageA.orderId;

    flag=findColumn(inString,flag,5);
    if(flag!=5){
        cerr<<"Incorrect column value!!\n";
        exit(1);
    }
    inString>>messageA.orderBookId;

    flag=findColumn(inString,flag,8);
    if(flag!=8){
        cerr<<"Incorrect column value!!\n";
        exit(1);
    }
    inString>>messageA.quantity;

    flag=findColumn(inString,flag,9);
    if(flag!=9){
        cerr<<"Incorrect column value!!\n";
        exit(1);
    }
    inString>>messageA.orderPrice;

    return messageA;
}


OrderExecuted DataManager::fillOrderExecutedTree(istringstream &inString,int flag){
    OrderExecuted messageE;

    flag=findColumn(inString,flag,3);
    if(flag!=3){
        cerr<<"Incorrect column value!!\n";
        exit(1);
    }
    inString>>messageE.nanosecond;

    flag=findColumn(inString,flag,4);
    if(flag!=4){
        cerr<<"Incorrect column value!!\n";
        exit(1);
    }

    inString>>messageE.orderId;

    return messageE;
}


OrderDelete DataManager::fillOrderDeleteTree(istringstream &inString,int flag){
    OrderDelete messageD;

    flag=findColumn(inString,flag,3);
    if(flag!=3){
        cerr<<"Incorrect column value!!\n";
        exit(1);
    }
    inString>>messageD.nanosecond;

    flag=findColumn(inString,flag,4);
    if(flag!=4){
        cerr<<"Incorrect column value!!\n";
        exit(1);
    }

    inString>>messageD.orderId;

    return messageD;
}
