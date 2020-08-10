#include "../../utility/AVLTree/inc/AVLTree.hpp"
#include "../inc/FileManager.hpp"

using std::istringstream;
using std::ifstream;

template<class T>
inline void FileManager::addMessage(AVLTree<T>* tree,const T& message){
    tree->insert(message);
}

void  FileManager::fileRead(const char * file,
                            AVLTree<Seconds>*STree,
                            AVLTree<AddOrder>*AOTree,
                            AVLTree<OrderExecuted>*OETree,
                            AVLTree<OrderDelete>*ODTree)
{

    ifstream inFile(file);
    while(!inFile.eof()){
        // clock_t start=clock();
        string line=readLine(inFile);
        findValues(line,STree,AOTree,OETree,ODTree);
    
        // if(line == ";")//tekrar bak
        //         break; */
    }

}

inline string FileManager::readLine(ifstream& inFile){
    string line;
    inFile>>line;
    //cout<<line<<endl;
    return line;
}


void FileManager::findValues(const string & line,
                        AVLTree<Seconds>*STree,
                        AVLTree<AddOrder>*AOTree,
                        AVLTree<OrderExecuted>*OETree,
                        AVLTree<OrderDelete>*ODTree)
{
    istringstream inString(line);

    int flag=1;
    flag=findColumn(inString,flag,2);
    
    if(flag!=2){
        cerr<<flag<<"Incorrect column value!!\n";
        exit(1);
    }

    char c;
    inString>>c;

    switch(c){
        case SECONDS:{
            Seconds messageT = fileSeconds(inString,flag);
            addMessage(STree,messageT);
            break;
            }
        case ADD_ORDER_TYPE:{ 
            AddOrder messageA = fileAddOrder(inString,flag);
            addMessage(AOTree,messageA);
            break;
            }
        
        case ORDER_EXECUTED_TYPE:{
            OrderExecuted messageE = fileOrderExecute(inString,flag);
            addMessage(OETree,messageE);
            break;
            }
        case ORDER_DELETE_TYPE:{
            OrderDelete messageD = fileOrderDelete(inString,flag);
            addMessage(ODTree,messageD);
            break;
            }
        default:
            cout<<"invalid message type!!\n";
            
    }
        
        
}


int FileManager::findColumn(istringstream& inString,int flag,int collumn){
    char c;
    while(!inString.eof() && flag<collumn){
        inString>>c;
        if(c==';')
            ++flag;
    }

    return flag;
}


Seconds FileManager::fileSeconds(istringstream &inString,int flag){
    
    Seconds messageT;
    
    flag=findColumn(inString,flag,3);
    if(flag!=3){
        cerr<<"Incorrect column value!!\n";
        exit(1);
    }
    inString>>messageT.timestamp;

    return messageT;
}


AddOrder FileManager::fileAddOrder(istringstream &inString,int flag){
    
    AddOrder messageA;
    
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

    flag=findColumn(inString,flag,9);
    if(flag!=9){
        cerr<<"Incorrect column value!!\n";
        exit(1);
    }
    inString>>messageA.orderPrice;

    return messageA;
}


OrderExecuted FileManager::fileOrderExecute(istringstream &inString,int flag){
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


OrderDelete FileManager::fileOrderDelete(istringstream &inString,int flag){
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
