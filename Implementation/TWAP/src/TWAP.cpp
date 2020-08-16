#include "../inc/TWAP.hpp"

// uint32_t TWAP:: totalPrice=0;
// int TWAP:: messageCount =0;

double TWAP:: totalTypicalPrice=0;
int TWAP:: barCount =0;


void TWAP:: calculate(Graph<uint32_t,Graph<uint32_t,Value>>* graph){

    ofstream outFile("outputFiles/TWAP.txt");

    int weight=12;

    outFile<<std::setw(weight+1)<<"Date"<<std::setw(3*weight/2)<<"Open"<<std::setw(weight)
            <<"High"<<std::setw(weight)<<"Low"<<std::setw(weight)<< "Close"
            <<std::setw(weight+5)<< "Typical Price"<<std::setw(weight+5)<<"TWAP\n";
    
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

        // int second=timestamp%60;
        // timestamp/=60;
        // int minute=timestamp%60;
        // timestamp/=60;
        // int hour=timestamp%24;
        
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
                <<std::setw(weight)<<bar->low<<std::setw(weight)<<bar->close;
        
        double typicalPrice= static_cast<double>(bar->open+bar->high+bar->low+bar->close)/4;

        outFile<<std::setw(weight+5)<<typicalPrice;

        totalTypicalPrice+=typicalPrice;
        ++barCount;
        
        double Twap=static_cast<double> (totalTypicalPrice)/static_cast<double> (barCount);

        outFile<<std::setw(weight+5)<<Twap<<endl;
        
        if(bar!=nullptr){
            delete bar;
            bar=nullptr;
        }
    }
}