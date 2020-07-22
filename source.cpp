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
    ifstream read;
    ofstream write;
    
    int64_t orderId;
    int32_t orderPrice;

    read.open("hello.txt");
    write.open("addOrder.txt");

    AddOrderMessage messageA;
    string id,price;
    getline(read,id,';');
    getline(read,price,'\n');
    
    //cout<<id<<";"<<price<<endl;
    
    orderId=stoll(id,0,20);
    orderPrice=stoi(price);
    messageA.setOrderId(orderId);
    messageA.setPrice(orderPrice);

    for(int i=0;i<10;++i)    
        write<<messageA;

    return 0;
}
