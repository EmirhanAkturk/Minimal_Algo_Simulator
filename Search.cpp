#include "MessageImp.h"
#include "Search.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

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
    BinarySearchTree *a;

    AddOrderBts *AddOrdertree=new AddOrderBts();
    fileRead(inFile,AddOrdertree,'A');

    AddOrdertree->printInorder(AddOrdertree->getRoot());
    uint64_t queryId=6987443128057031513;
    Node* query=AddOrdertree->searchNode(AddOrdertree->getRoot(),queryId);


    if(query!= nullptr){
        cout<<"Found and deleted:"<<query->orderId<<endl;
        AddOrdertree->deleteNode(AddOrdertree->getRoot(),queryId);
    }
    else cout<<"Not found\n";

    ofstream outFile;
    
    outFile.open("addOrder.txt");
    AddOrdertree->writeInorder(AddOrdertree->getRoot(), outFile);

    if(!outFile){
        cerr<<"Error opening hello.txt for writing\n";
        exit(1);
    }

    inFile.close();
    outFile.close();


}

void Search:: fileRead(ifstream &inFile, BinarySearchTree *tree,char messageType){
    string line;
    while(inFile>>line){
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
            AddOrderBts *bts=dynamic_cast<AddOrderBts*>(tree);
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

            bts->setRoot( bts->insertNode(bts->getRoot(), orderId,orderPrice));
                //tree.insertNode(tree.getRoot(), messageA.getOrderId(),messageA.getOrderPrice());
            
        }

        if(line == ";")//tekrar bak
                break;
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
