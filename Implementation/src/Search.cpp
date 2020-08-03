#include "../include/search.h"
#include "../utility/include/AVLTree.inl"

#include <sstream>
#include <ctime>

AVLTree<AddOrder> MessageImp:: AddOrderTree;
AVLTree<OrderExecute> MessageImp::OrderExecuteTree;
AVLTree<OrderDelete> MessageImp::OrderDeleteTree;
    
Search::Search(){

}

Search::~Search(){
    
}

/* void Search::operation(const char * file){
    cout<<"Search operation\n";

    ifstream inFile(file);
    if(!inFile){
        cerr<<"Error opening:"<<file<<endl;
        exit(1);
    }

    clock_t tstart=clock();

    //fileRead(inFile);

    clock_t runtime=clock()-tstart;
    cout<<"fileRead runTime:"<<(double)1000*(runtime)/CLOCKS_PER_SEC<<"ms\n";

    //AddOrdertree.display();
    uint64_t queryId=6987443128057031513;
    
    //tstart=clock();
    
    if(AddOrderTree.search(queryId)){
            cout<<"Found:"<<queryId<<endl;
    }
    else cout<<"Not found\n";
    
    //  runtime=clock()-tstart;

    // cout<<"Search runTime:"<<(double)1000*(runtime)/CLOCKS_PER_SEC<<"ms\n";

    // tstart=clock();

    
    if(AddOrderTree.remove(queryId)){
        cout<<"removed:"<<queryId<<endl;
    }
    
    else cout<<"Not removed\n";
    
    runtime=clock()-tstart;
    cout<<"remove runTime:"<<(double)1000*(runtime)/CLOCKS_PER_SEC<<"ms\n";

    // ofstream outFile;
    
    // outFile.open("message.txt");
    // AddOrdertree.writeFile(outFile,1);

    // if(!outFile){
    //     cerr<<"Error opening hello.txt for writing\n";
    //     exit(2);
    // }
 
    ofstream outFileA;
    ofstream outFileD;
    ofstream outFileE;
    
    outFileA.open("AddOrder.txt"); 
    outFileD.open("orderDelete.txt"); 
    outFileE.open("OrderExecute.txt"); 

    AddOrderTree.writeFile(outFileA,INORDER);
    OrderDeleteTree.writeFile(outFileD,INORDER);
    OrderExecuteTree.writeFile(outFileE,INORDER);


    inFile.close();
    outFileA.close();
    outFileE.close();
    outFileD.close();

}
 */

void Search:: fileRead(const char * file ){

    ifstream inFile(file);
    while(!inFile.eof()){
        // clock_t start=clock();
        string line=readLine(inFile);
        findValues(line);
    
        // if(line == ";")//tekrar bak
        //         break; */
    }

}

inline string Search:: readLine(ifstream& inFile){
    string line;
    inFile>>line;
    return line;
}


void Search:: findValues(const string & line){
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
        
        case ORDER_EXECUTE_TYPE: fileOrderExecute(inString,flag);
            break;

        case ORDER_DELETE_TYPE: fileOrderDelete(inString,flag);
            break;
        
        default:
            cout<<"invalid message type!!\n";
            
    }
        
        
}


int Search:: findColumn(istringstream& inString,int flag,int collumn){
    char c;
    while(!inString.eof() && flag<collumn){
        inString>>c;
        if(c==';')
            ++flag;
    }

    return flag;
}


void Search::fileAddOrder(istringstream &inString,int flag){
    
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


void Search::fileOrderExecute(istringstream &inString,int flag){
    OrderExecute messageE;

    flag=findColumn(inString,flag,4);
    if(flag!=4){
        cerr<<"Incorrect column value!!\n";
        exit(1);
    }

    inString>>messageE.orderId;

    //OrderExecuteTree.insert(messageE);
    addMessage(OrderExecuteTree,messageE);
}


void Search::fileOrderDelete(istringstream &inString,int flag){
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

template<class T>
inline void Search::addMessage(AVLTree<T>& tree,const T& message){
    tree.insert(message);
}

inline void Search::print(int treeChoice,int printChoice){
    switch(treeChoice){
        case ADD_ORDER_TREE:
            AddOrderTree.print(printChoice);
            break;
        
        case ORDER_DELETE_TREE:
            OrderDeleteTree.print(printChoice);
            break;
        
        case ORDER_EXECUTED_TREE:
            OrderExecuteTree.print(printChoice);
            break;
        
        default:
            cout<<"invalid tree choice!!\n";
    }
}

inline void Search::writeFile(const char* file,int treeChoice,int writeChoice){
    ofstream outFile(file);

    switch(treeChoice){
        case ADD_ORDER_TREE:
            AddOrderTree.writeFile(outFile,writeChoice);
            break;
        
        case ORDER_DELETE_TREE:
            OrderDeleteTree.writeFile(outFile,writeChoice);
            break;
        
        case ORDER_EXECUTED_TREE:
            OrderExecuteTree.writeFile(outFile,writeChoice);
            break;
        
        default:
            cout<<"invalid tree choice!!\n";
    }
}
