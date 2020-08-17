#define _DEBUG_
#ifdef _DEBUG_
#include "Implementation/TWAP/src/TWAP.cpp"
#include "Implementation/VWAP/src/VWAP.cpp"
#include "Implementation/utility/AVLTree/src/AVLTree.cpp"
#include "Implementation/DataManager/src/DataManager.cpp"
#include "Implementation/AlgoHandler/src/AlgoHandler.cpp"
#include "Implementation/utility/Graph/src/Graph.cpp"
#include "Client/AbstractClient/src/AbstractClient.cpp"
#endif

#ifndef _DEBUG_
#include "Client/AbstractClient/inc/AbstractClient.hpp"
#include "Implementation/AlgoHandler/inc/AlgoHandler.hpp"
#endif
int main(){
    using std::cout;
    using std::endl;
    
    AbstractImp * imp = new AlgoHandler();
    
    AbstractClient * abs= new RefinedAbstractClient(imp);

    const char *file = "documentation/SecondsandAddOrderMessage.txt";

    cout<<"Twap calculating...\n";

    abs->compute(file,TWAP_CALCULATE);

    cout<<"calculation result was written to the TWAP.txt file..\n";

    cout<<"VWAP calculating...\n";

    abs->compute(file,VWAP_CALCULATE);

    cout<<"calculation result was written to the VWAP.txt file..\n";

    return 0;
}