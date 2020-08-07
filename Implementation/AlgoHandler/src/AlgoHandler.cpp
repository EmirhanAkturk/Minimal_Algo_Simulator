#include "../inc/AlgoHandler.hpp"

double AlgoHandler::compute(const char* file,char calculateChoice){
    if(isRead==false){
        fileRead(file);
        isRead=true;
    }

    if(calculateChoice == TWAP_CALCULATE){
        TWAP twap;
        double result = twap.calculate(AddOrderTree.getRoot());
        return result;
    }

    else if(calculateChoice == VWAP_CALCULATE){
        VWAP vwap;
        double result = vwap.calculate(AddOrderTree.getRoot());
        return result;
    }

    cerr<<"Invalid calculate choice!!\n";
    return -1;

}

template<class T>
inline void AlgoHandler::addMessage(AVLTree<T>& tree,const T& message){
    tree.insert(message);
}

void AlgoHandler::fileRead(const char * file ){

    ifstream inFile(file);
    while(!inFile.eof()){
        // clock_t start=clock();
        string line=readLine(inFile);
        findValues(line);
    
        // if(line == ";")//tekrar bak
        //         break; */
    }

}

inline string AlgoHandler::readLine(ifstream& inFile){
    string line;
    inFile>>line;
    return line;
}


void  AlgoHandler::findValues(const string & line){
    istringstream inString(line);

    int flag=1;
    flag=findColumn(inString,flag,2);
    
    if(flag!=2){
        cerr<<"Incorrect column value!!\n";
        exit(1);
    }

    char c;
    inString>>c;

    switch(c){
        case ADD_ORDER_TYPE: fileAddOrder(inString,flag);
            break;
        
        case ORDER_EXECUTED_TYPE: fileOrderExecute(inString,flag);
            break;

        case ORDER_DELETE_TYPE: fileOrderDelete(inString,flag);
            break;
        
        default:
            cout<<"invalid message type!!\n";
            
    }
        
        
}


int AlgoHandler::findColumn(istringstream& inString,int flag,int collumn){
    char c;
    while(!inString.eof() && flag<collumn){
        inString>>c;
        if(c==';')
            ++flag;
    }

    return flag;
}


void AlgoHandler::fileAddOrder(istringstream &inString,int flag){
    
    AddOrder messageA;

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

    //AddOrderTree.insert(messageA);
    addMessage(AddOrderTree,messageA);
}


void AlgoHandler::fileOrderExecute(istringstream &inString,int flag){
    OrderExecuted messageE;

    flag=findColumn(inString,flag,4);
    if(flag!=4){
        cerr<<"Incorrect column value!!\n";
        exit(1);
    }

    inString>>messageE.orderId;

    //OrderExecutedTree.insert(messageE);
    addMessage(OrderExecutedTree,messageE);
}


void AlgoHandler::fileOrderDelete(istringstream &inString,int flag){
    OrderDelete messageD;

    flag=findColumn(inString,flag,4);
    if(flag!=4){
        cerr<<"Incorrect column value!!\n";
        exit(1);
    }

    inString>>messageD.orderId;

    //OrderDeleteTree.insert(messageD);
    addMessage(OrderDeleteTree,messageD);
}
