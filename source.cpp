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
    fileRead(inFile,tree);
    
    
    tree.printInorder(tree.getRoot());

    ofstream outFile;
    
    outFile.open("addOrder.txt");
    tree.writeInorder(tree.getRoot(), outFile);

    if(!outFile){
        cerr<<"Error opening hello.txt for writing\n";
        return 1;
    }

 /*    
    while(!fin.eof()){

        int flag=1;
        
        while(flag!=2){
            fin.get(c);
            if(c==EOF)
            {   
                fin.close();
                return 0;
            }
        //cout<<c<<" ";
            if(c==';')
                ++flag;
        }
        
        if(c==EOF)
        {   fin.close();
            return 0;
        }
        fin.get(c);
        //cout<<c<<endl;
        //cout<<c;
        if(c=='A'){//Add order message check
            
            while(flag!=4){
                if(c==EOF)
                {   fin.close();
                    return 0;
                }
                fin.get(c);
                if(c==';')
                    ++flag;
            }
            
            fin>>orderId;
            //cout<<orderId<<" ";
            messageA.setOrderId(orderId);

            while(flag!=9){
                fin.get(c);
                if(c==';')
                    ++flag;
            }

            fin>>orderPrice;
            //cout<<orderPrice<<endl;

            messageA.setPrice(orderPrice);

            fout<<messageA;

            do{
                fin.get(c);
            }
            while(!fin.eof() && c!='\n');
            
            
        }
        else{
            
            do{
                fin.get(c);
            }
            while(!fin.eof() && c!='\n');
            
        }
        
    }
 */
    inFile.close();
    outFile.close();
    return 0;
}
