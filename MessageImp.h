#include<fstream>

class MessageImp{
public:

    virtual MessageImp* search(std::ifstream & file)=0;

protected:
    MessageImp(int64_t newId=0):orderId{newId}
    { /* intentionally left blank */}

    int64_t orderId;
};