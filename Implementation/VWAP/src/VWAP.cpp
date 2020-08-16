#include "../inc/VWAP.hpp"

uint32_t VWAP:: totalVolume=0;
uint32_t VWAP:: totalVP=0;

void VWAP:: calculate(Graph<uint32_t,Graph<uint32_t,Value>>* graph){
    
    ofstream outFile("outputFiles/VWAP.txt");

    int weight=12;

    outFile<<std::setw(weight+1)<<"Date"<<std::setw(3*weight/2)<<"Open"<<std::setw(weight)
            <<"High"<<std::setw(weight)<<"Low"<<std::setw(weight)<< "Close"
            <<std::setw(weight)<< "Volume"<<std::setw(weight+5)<< "Typical Price"
            <<std::setw(weight)<< "V*P"<<std::setw(weight)<< "Total VP"
            <<std::setw(weight)<< "Total V"<<std::setw(weight+5)<<"VWAP\n";
    
    std::map<uint32_t,Graph<uint32_t,Value>>::iterator keyItr;
    for(keyItr=graph->getMapBegin(); keyItr!=graph->getMapEnd(); ++keyItr){
        const time_t timestamp= keyItr->first;
        struct tm *ts = localtime(&timestamp);
        int second=ts->tm_sec;
        int minute=ts->tm_min;
        int hour= ts->tm_hour;
        int day= ts->tm_mday;
        int month= ts->tm_mon+1;
        int year= ts->tm_year+1900;
        
        outFile <<std::setw(2)<<day<<"/"<<std::setw(2)<<month<<"/"<<std::setw(4)<<year
                <<std::setw(3)<<hour<<":"<<std::setw(2)<<minute<<":"<<std::setw(2)<<second
                <<std::setw(weight-9);
        std::map<uint32_t,Value>::iterator nanoItr;
        
        nanoItr=keyItr->second.getMapBegin();
        
        bool isFirst=true;
        Bar *bar;
        for(;nanoItr!=keyItr->second.getMapEnd();++nanoItr){
            
            Value *v=&nanoItr->second;

            while(v->next!=nullptr)//go to the most current node
                v=v->next;

            if(isFirst){
                uint32_t open=v->bar.open;
                uint32_t quantity=v->bar.quantity;
                
                bar=new Bar(open,quantity);
                isFirst=false;
            }

            if(v->bar.high > bar->high){
                bar->high=v->bar.high;
            }
            else if(v->bar.low < bar->low){
                bar->low=v->bar.low;
            }

            bar->close=v->bar.close;
            bar->quantity=v->bar.quantity;
            
        }
        // cout<<keyItr->first<<std::setw(weight)<<bar->open<<std::setw(weight)<<bar->high<<
        //     std::setw(weight)<<bar->low<<std::setw(weight)<<bar->close<<"\n";
    
        outFile <<std::setw(weight)<<bar->open<<std::setw(weight)<<bar->high
                <<std::setw(weight)<<bar->low<<std::setw(weight)<<bar->close
                <<std::setw(weight)<<bar->quantity;
        
        double typicalPrice= static_cast<double>(bar->high+bar->low+bar->close)/3;

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
