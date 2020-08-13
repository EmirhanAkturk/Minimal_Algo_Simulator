#include "../inc/VWAP.hpp"

uint32_t VWAP:: totalVolume=0;
uint32_t VWAP:: totalVP=0;

void VWAP:: calculate(Graph<uint32_t,Graph<uint32_t,Bar>>* graph){
    
    ofstream outFile("outputFiles/VWAP.txt");

    int weight=12;

    outFile<<std::setw(weight/2)<<"Time"<<std::setw(weight+2)<<"Open"<<std::setw(weight)
            <<"High"<<std::setw(weight)<<"Low"<<std::setw(weight)<< "Close"
            <<std::setw(weight)<< "Volume"<<std::setw(weight+5)<< "Typical Price"
            <<std::setw(weight)<< "V*P"<<std::setw(weight)<< "Total VP"
            <<std::setw(weight)<< "Total V"<<std::setw(weight+5)<<"VWAP\n";
    
    std::map<uint32_t,Graph<uint32_t,Bar>>::iterator keyItr;
    for(keyItr=graph->getMapBegin(); keyItr!=graph->getMapEnd(); ++keyItr){
        uint32_t timestamp=keyItr->first;
        int second=timestamp%60;
        timestamp/=60;
        int minute=timestamp%60;
        timestamp/=60;
        int hour=timestamp%24;
        
        outFile<<std::setw(2)<<hour<<":"<<std::setw(2)<<minute<<":"<<std::setw(2)<<second<<std::setw(weight-8);

        std::map<uint32_t,Bar>::iterator nanoItr;
        
        nanoItr=keyItr->second.getMapBegin();
        
        bool isFirst=true;
        Bar *bar;
        for(;nanoItr!=keyItr->second.getMapEnd();++nanoItr){
            if(isFirst){
                uint32_t open=nanoItr->second.open;
                uint32_t quantity=nanoItr->second.quantity;
                bar=new Bar(open,quantity);
                isFirst=false;
            }

            if(nanoItr->second.high > bar->high){
                bar->high=nanoItr->second.high;
            }
            else if(nanoItr->second.low < bar->low){
                bar->low=nanoItr->second.low;
            }

            bar->close=nanoItr->second.close;
            bar->quantity=nanoItr->second.quantity;
            
        }
        // cout<<keyItr->first<<std::setw(weight)<<bar->open<<std::setw(weight)<<bar->high<<
        //     std::setw(weight)<<bar->low<<std::setw(weight)<<bar->close<<"\n";
    
        outFile <<std::setw(weight)<<bar->open<<std::setw(weight)<<bar->high
                <<std::setw(weight)<<bar->low<<std::setw(weight)<<bar->close
                <<std::setw(weight)<<bar->quantity;
        
        double typicalPrice= static_cast<double>(bar->high+bar->low+bar->close)/3/1000;

        outFile<<std::setw(weight+5)<<typicalPrice;

        uint32_t VP=bar->quantity *typicalPrice;
        outFile<<std::setw(weight)<<VP;
        
        totalVP+=VP;
        outFile<<std::setw(weight)<<totalVP;
        
        totalVolume+=bar->quantity;
        outFile<<std::setw(weight)<<totalVolume;

        double Vwap=static_cast<double>(totalVP)/static_cast<double>(totalVolume);
        outFile<<std::setw(weight+5)<<Vwap<<endl;
        
        if(bar!=nullptr){
            delete bar;
            bar=nullptr;
        }
    }
}
