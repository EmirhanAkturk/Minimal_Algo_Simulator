#include "Implementation/AlgoHandler/inc/AlgoHandler.hpp"

int main(){
    AbstractImp * imp = new AlgoHandler();

    const char *file = "documentation/AddOrderMessage.txt";

    cout<<"Twap calculating...\n";

    double result=imp->compute(file,TWAP_CALCULATE);

    cout<<"TWAP result:"<<result<<endl;

    cout<<"VWAP calculating...\n";

    result=imp->compute(file,VWAP_CALCULATE);

    cout<<"VWAP result:"<<result<<endl;

    return 0;
}