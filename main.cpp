#include "Client/AbstractClient/inc/AbstractClient.hpp"
#include "Implementation/AlgoHandler/inc/AlgoHandler.hpp"

int main(){
    using std::cout;
    using std::endl;
    
    AbstractImp * imp = new AlgoHandler();
    
    AbstractClient * abs= new RefinedAbstractClient(imp);

    const char *file = "documentation/AddOrderMessage.txt";

    cout<<"Twap calculating...\n";

    abs->compute(file,TWAP_CALCULATE);

    cout<<"calculation result was written to the TWAP.txt file..\n";

    cout<<"VWAP calculating...\n";

    abs->compute(file,VWAP_CALCULATE);

    cout<<"calculation result was written to the VWAP.txt file..\n";

    return 0;
}