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
    cout<<"Seach operation\n";
    ifstream inFile(file);
    if(!inFile){
        cerr<<"Error opening:"<<file<<endl;
        exit(2);
    }

    AVLTree AddOrdertree;
    clock_t tstart=clock();

    fileRead(inFile,AddOrdertree,'A');

    clock_t runtime=clock()-tstart;
    cout<<"fileRead runTime:"<<(double)1000*(runtime)/CLOCKS_PER_SEC<<"ms\n";

    //AddOrdertree.display();
    uint64_t queryId=6987443128057031513;
    
    tstart=clock();
    
    if(AddOrdertree.search(queryId)){
        cout<<"Found:"<<queryId<<endl;
    }
    else cout<<"Not found\n";
    
    runtime=clock()-tstart;

    cout<<"Search runTime:"<<(double)1000*(runtime)/CLOCKS_PER_SEC<<"ms\n";

    tstart=clock();

    
    if(AddOrdertree.remove(queryId)){
        cout<<"removed:"<<queryId<<endl;
    }
    
    else cout<<"Not removed\n";
    
    runtime=clock()-tstart;
    cout<<"remove runTime:"<<(double)1000*(runtime)/CLOCKS_PER_SEC<<"ms\n";

    ofstream outFile;
    
    outFile.open("addOrder.txt");
    AddOrdertree.writeFile(outFile);

    if(!outFile){
        cerr<<"Error opening hello.txt for writing\n";
        exit(2);
    }

    inFile.close();
    outFile.close();


}

void Search:: fileRead(ifstream &inFile, AVLTree &tree,char messageType){
    string line;
    // clock_t totalReadTime=0;
    // clock_t totalInsertTime=0;

    while(inFile>>line){
        // clock_t start=clock();

        istringstream inString(line);
        int flag=1;
        flag=findColumn(inString,flag,2);
        
        if(flag!=2){
            cerr<<"Incorrect column value!!\n";
            exit(1);
        }

        char c;
        inString>>c;

        if(messageType =='A' && c=='A'){
            uint64_t orderId;
            uint32_t orderPrice;
            
            flag=findColumn(inString,flag,4);
            if(flag!=4){
                cerr<<"Incorrect column value!!\n";
                exit(1);
            }
            inString>>orderId;

            flag=findColumn(inString,flag,9);
            if(flag!=9){
                cerr<<"Incorrect column value!!\n";
                exit(1);
            }
            inString>>orderPrice;

            // clock_t readTime=clock()-start;
            // totalReadTime+=readTime;

            // start=clock();
            
            tree.insert(orderId,orderPrice);

            // clock_t insertTime=clock()-start;

            // totalInsertTime+=insertTime;
            
        }

        if(line == ";")//tekrar bak
                break;
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
