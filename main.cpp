#include "Implementation/TWAP/inc/TWAP.hpp"

int main(){
    AbstractImp * imp = new TWAP();

    const char *file = "documentation/AddOrderMessage.txt";

    double averagePrice=imp->compute(file);

    cout<<"AveragePrice:"<<averagePrice<<endl;

    ofstream outFile("addOrder.txt");
    


    return 0;
}