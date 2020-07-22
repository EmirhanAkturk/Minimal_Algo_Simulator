#include<iostream>
#include<fstream>
#include<string>

using namespace std;

class Message{
public:

    Message(int64_t newOrderId=0):orderId{newOrderId}
    {/* nothing was deliberately written */}

    void setOrderId(int64_t newOrderId){
        orderId=newOrderId;
    }

protected:
    int64_t orderId;
};

class AddOrderMessage:public Message{

    friend ofstream& operator<<(ofstream& file,const AddOrderMessage& message){
        file<<message.orderId<<";"<<message.orderPrice<<endl;
        return file;
    }

public:
    AddOrderMessage(int64_t newOrderId=0,int32_t newOrderPrice=0):Message{newOrderId},orderPrice{newOrderPrice}
    {/* nothing was deliberately written */}


    void setPrice(int32_t newOrderPrice){
        orderPrice=newOrderPrice;
    }

private:

    int32_t orderPrice;
};

int main(){
    ifstream fin;
    
    
    int64_t orderId;
    int32_t orderPrice;

    fin.open("AddOrderMessage.txt");

    if(!fin){
        cerr<<"Error opening hello.txt for reading\n";
        return 1;
    }

    AddOrderMessage messageA;

    ofstream fout;

    fout.open("addOrder.txt");

    if(!fout){
        cerr<<"Error opening hello.txt for writing\n";
        return 1;
    }

    
    char c;
    //fin.get(c);
    
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

    fin.close();
    fout.close();
    return 0;
}
