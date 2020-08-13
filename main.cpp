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

    imp->compute(file,TWAP_CALCULATE);

    cout<<"calculation result was written to the TWAP.txt file..\n";

    cout<<"VWAP calculating...\n";

    imp->compute(file,VWAP_CALCULATE);

    cout<<"calculation result was written to the VWAP.txt file..\n";

    return 0;
}