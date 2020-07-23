#include "MessageImp.h"

using namespace std;

class AddOrderImp:MessageImp{
public:
    AddOrderImp(int64_t newId=0,int64_t newPrice=0):MessageImp{newId},orderPrice{newPrice}
    {/* intentionally left blank */}
    
    MessageImp* search(ifstream& fin);

private:
    int32_t orderPrice;

};