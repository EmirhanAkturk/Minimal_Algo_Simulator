#include<string>

class MessageImp{
public:

    virtual bool searchMessage(const std:: string &line)=0;
    virtual void print()=0;

protected:
    MessageImp(uint64_t newId=0):orderId{newId}
    { /* intentionally left blank */}

    uint64_t orderId;
};