#include "../include/search.h"

#include <sstream>
#include <ctime>

MessageImp::MessageImp(){
    
}

MessageImp::~MessageImp(){

}


Search::Search(){

}

Search::~Search(){
    
}

void Search::operation(const char * file){
    cout<<"Search operation\n";

    ifstream inFile(file);
    if(!inFile){
        cerr<<"Error opening:"<<file<<endl;
        exit(1);
    }

    clock_t tstart=clock();

    fileRead(inFile);

    clock_t runtime=clock()-tstart;
    cout<<"fileRead runTime:"<<(double)1000*(runtime)/CLOCKS_PER_SEC<<"ms\n";

    //AddOrdertree.display();
    uint64_t queryId=6987443128057031513;
    
    //tstart=clock();
    
    if(AddOrderTree.search(queryId)){
            cout<<"Found:"<<queryId<<endl;
    }
    else cout<<"Not found\n";
    
    /*//  runtime=clock()-tstart;

    // cout<<"Search runTime:"<<(double)1000*(runtime)/CLOCKS_PER_SEC<<"ms\n";

    // tstart=clock();

    
    // if(AddOrdertree.remove(queryId)){
    //     cout<<"removed:"<<queryId<<endl;
    // }
    
    // else cout<<"Not removed\n";
    
    // runtime=clock()-tstart;
    // cout<<"remove runTime:"<<(double)1000*(runtime)/CLOCKS_PER_SEC<<"ms\n";

    // ofstream outFile;
    
    // outFile.open("message.txt");
    // AddOrdertree.writeFile(outFile,1);

    // if(!outFile){
    //     cerr<<"Error opening hello.txt for writing\n";
    //     exit(2);
    // }
 */
    ofstream outFileA;
    ofstream outFileD;
    ofstream outFileE;
    
    outFileA.open("AddOrder.txt"); 
    outFileD.open("orderDelete.txt"); 
    outFileE.open("OrderExecute.txt"); 

    AddOrderTree.writeFile(outFileA,1);
    OrderDeleteTree.writeFile(outFileD,1);
    OrderExecuteTree.writeFile(outFileE,1);


    inFile.close();
    outFileA.close();
    outFileE.close();
    outFileD.close();

}

inline string Search:: readLine(ifstream& inFile){
    string line;
    inFile>>line;
    return line;
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

    AddOrderTree.insert(messageA);
}


void Search::fileOrderExecute(istringstream &inString,int flag){
    OrderExecute messageE;

    flag=findColumn(inString,flag,4);
    if(flag!=4){
        cerr<<"Incorrect column value!!\n";
        exit(1);
    }

    inString>>messageE.orderId;

    OrderExecuteTree.insert(messageE);
}


void Search::fileOrderDelete(istringstream &inString,int flag){
    OrderDelete messageD;

    flag=findColumn(inString,flag,4);
    if(flag!=4){
        cerr<<"Incorrect column value!!\n";
        exit(1);
    }

    inString>>messageD.orderId;

    OrderDeleteTree.insert(messageD);
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
        case 'A': fileAddOrder(inString,flag);
            break;
        
        case 'E': fileOrderExecute(inString,flag);
            break;

        case 'D': fileOrderDelete(inString,flag);
            break;
        
        default:
            cout<<"invalid message type!!\n";
            
    }
        
        
}

void Search:: fileRead(ifstream &inFile){
/*     //    string line;
    // clock_t totalReadTime=0;
    // clock_t totalInsertTime=0;
 */
    
    while(!inFile.eof()){
        // clock_t start=clock();

        string line=readLine(inFile);
    
        findValues(line);
        /* // clock_t readTime=clock()-start;
            // totalReadTime+=readTime;

            // start=clock();
            
            //tree.insert(orderId,orderPrice);

            // clock_t insertTime=clock()-start;

            // totalInsertTime+=insertTime;
            
        

        // if(line == ";")//tekrar bak
        //         break; */
    }

    // cout<<"Read time taken:"<<(double)1000*(totalReadTime)/CLOCKS_PER_SEC<<"ms\n";
    // cout<<"Insert time taken:"<<(double)1000*(totalInsertTime)/CLOCKS_PER_SEC<<"ms\n";

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
