#include "Implementation/AlgoHandler/inc/AlgoHandler.hpp"
#include "Implementation/utility/inc/std.hpp"


int main(){
    using std::cout;
    using std::endl;
    
    AbstractImp * imp = new AlgoHandler();

    //const char *file = "documentation/SecondsMessage.txt";
    const char *file = "documentation/AddOrderMessage.txt";
    //const char *file = "documentation/NewSecAdd.txt";

    cout<<"Twap calculating...\n";

    double result=imp->compute(file,TWAP_CALCULATE);

    cout<<"TWAP result:"<<result<<endl;

    // cout<<"VWAP calculating...\n";

    // result=imp->compute(file,VWAP_CALCULATE);

    // cout<<"VWAP result:"<<result<<endl;

    return 0;
}