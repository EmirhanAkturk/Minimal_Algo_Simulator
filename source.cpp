#include "AddOrderImp.cpp"

int main(){
    ifstream inFile;
    
    //inFile.open("./documentation/AddOrderMessage.txt");
    inFile.open("message.txt");

    if(!inFile){
        cerr<<"Error opening hello.txt for reading\n";
        return 1;
    }
    
    BinarySearchTree tree;
    fileRead(inFile,tree,'A');
    
    
    tree.printInorder(tree.getRoot());
    uint64_t queryId=6987443128057031513;
    Node* query=tree.searchNode(tree.getRoot(),queryId);

    if(query!= nullptr){
        cout<<"Found and deleted:"<<query->orderId<<";"<<query->orderPrice<<endl;
        tree.deleteNode(tree.getRoot(),queryId);
    }
    else cout<<"Not found\n";

    ofstream outFile;
    
    outFile.open("addOrder.txt");
    tree.writeInorder(tree.getRoot(), outFile);

    if(!outFile){
        cerr<<"Error opening hello.txt for writing\n";
        return 1;
    }

    inFile.close();
    outFile.close();
    return 0;
}
