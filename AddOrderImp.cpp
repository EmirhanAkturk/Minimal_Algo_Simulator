#include "MessageImp.h"
#include <iostream> 
#include <sstream>
#include <fstream>
using namespace std;

class AddOrderImp:MessageImp{

    friend ofstream& operator<<(ofstream& file,const AddOrderImp& message){
        file<<message.orderId<<";"<<message.orderPrice<<endl;
        return file;
    }
public:
    AddOrderImp(uint64_t newId=0,uint32_t newPrice=0):MessageImp{newId},orderPrice{newPrice}
    {/* intentionally left blank */}

    AddOrderImp(AddOrderImp & otherMessage){
        orderId=otherMessage.orderId;
        orderPrice=otherMessage.orderPrice;
    }

    virtual bool searchMessage(const string &line);
    virtual void print();

private:
    uint32_t orderPrice;

};

bool  AddOrderImp:: searchMessage(const string & line){
    istringstream sin(line);
    int flag=1;
    auto findColumn=[&flag,&sin](int collumn){
        char c;
        while(!sin.eof() && flag<collumn){
            sin>>c;
            if(c==';')
                ++flag;
        }
    };

    char messageType;
    findColumn(2);
    sin>>messageType;

    if(messageType=='A'){
        
        findColumn(4);
        sin>>orderId;
        findColumn(9);
        sin>>orderPrice;

        return true;
    }

    else return false;
       
}

void AddOrderImp::print(){
    cout<<orderId<<" "<<orderPrice<<endl;
}