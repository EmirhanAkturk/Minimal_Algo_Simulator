#include "../inc/TWAP.hpp"

//initialize values
double TWAP:: totalTypicalPrice = 0;
int TWAP:: barCount = 0;

void TWAP:: calculate(AVLTree<OrderBookId>* OBITree){
    AVLTree<OrderBookId>::Node * OBIroot=OBITree->getRoot();
    
    if (OBIroot == NULL) 
       return; 
  
    //iterative preorder traversal

    // Create an empty stack and push root to it 
    std::stack<AVLTree<OrderBookId>::Node *> OBIstack; 
    OBIstack.push(OBIroot); 
  
    /* Pop all items one by one. Do following for every popped item 
       a) process it 
       b) push its right child 
       c) push its left child 
    Note that right child is pushed first so that left is processed first */


    while (OBIstack.empty() == false) 
    { 
        // Pop the top item from stack and process it 
        AVLTree<OrderBookId>::Node *node = OBIstack.top(); 

        calculate_and_write(node->graph,node->bookId);

        OBIstack.pop(); 
  
        // Push right and left children of the popped node to stack 
        if (node->right) 
            OBIstack.push(node->right); 
        if (node->left) 
            OBIstack.push(node->left); 
    } 
    
}

void TWAP:: calculate_and_write(Graph<uint32_t,Graph<uint32_t,Value>>* graph,uint32_t OrderBookId){
    double  totalTypicalPrice= 0;
    int barCount = 0;

    //the file to write the calculation result
    string out="./outputFiles/TWAP/"+std::to_string(OrderBookId)+".txt";
    
    ofstream outFile(out);

    if(!outFile.good()){
        cerr<<"File  "<<out<<" couldn't be opened.\n";
        exit(-1);
    }


    int weight=12;//for blanks in the table

    //the titles part of the table
    write_table_title(outFile,weight);

    std::map<uint32_t,Graph<uint32_t,Value>>::iterator keyItr;
    for(keyItr=graph->getMapBegin(); keyItr!=graph->getMapEnd(); ++keyItr){
        const time_t timestamp= keyItr->first;
        
        //Epoch time converting 
        struct tm *ts = localtime(&timestamp);

        //converted values ​​are assigned in variables.
        int second=ts->tm_sec;
        int minute=ts->tm_min;
        int hour= ts->tm_hour;
        int day= ts->tm_mday;
        int month= ts->tm_mon+1;
        int year= ts->tm_year+1900;

        //date is written to file
        write_date( outFile,weight,year,month,
                    hour,minute,day,second);


        bool isFirst=true;//for open value
        Bar *bar;//to save bar values
        
        //to calculate the number of messages in the timestamp
        int messageCount=0;

        //for iterative traversal
        std::map<uint32_t,Value>::iterator nanoItr;
        nanoItr=keyItr->second.getMapBegin();
        for(;nanoItr!=keyItr->second.getMapEnd();++nanoItr){
            
            Value *v=&nanoItr->second;
            
            ++messageCount;

            //go to the most current node
            while(v->next!=nullptr)
            {   
                v=v->next;
                ++messageCount;
            }

            if(isFirst){
                //Initialize Bar values ​​with first read value
                uint32_t open=v->bar.open;
                uint32_t quantity=v->bar.quantity;
                
                bar=new Bar(open,quantity);
                isFirst=false;
            }


            //update bar values

            if(v->bar.high > bar->high){
                bar->high=v->bar.high;
            }
            else if(v->bar.low < bar->low){
                bar->low=v->bar.low;
            }

            bar->close=v->bar.close;
            bar->quantity=v->bar.quantity;
            
        }

        //The values ​​in the bar are written to the file
        write_bar(outFile,weight,bar);


        //Typical price and twap calculation is made
        double typicalPrice= static_cast<double>(bar->open+bar->high+bar->low+bar->close)/4;

        totalTypicalPrice+=typicalPrice;
        ++barCount;
        
        double Twap=static_cast<double> (totalTypicalPrice)/static_cast<double> (barCount);

        //results are written to file
        write_result(outFile,weight,typicalPrice,Twap,messageCount);


        if(bar!=nullptr){
            delete bar;
            bar=nullptr;
        }
    }
}


inline void TWAP::write_table_title(ofstream & outFile,int weight){
    outFile <<std::setw(weight+1)<<"Date"<<std::setw(3*weight/2)<<"Open"
            <<std::setw(weight)<<"High"<<std::setw(weight)<<"Low"
            <<std::setw(weight)<< "Close"<<std::setw(3*weight/2)<< "Typical Price"
            <<std::setw(weight)<<"TWAP"<<std::setw(3*weight/2)<<"Message Count\n";

}


inline void TWAP::write_date( ofstream & outFile,int weight,
                        int year,int month,int day,
                        int hour,int minute,int second)
{
    outFile <<std::setw(2)<<day<<"/"<<std::setw(2)<<month<<"/"<<std::setw(4)<<year
            <<std::setw(3)<<hour<<":"<<std::setw(2)<<minute<<":"<<std::setw(2)<<second;
}


inline void TWAP::write_bar(ofstream & outFile,int weight,const Bar* bar){
    outFile <<std::setw(weight)<<bar->open<<std::setw(weight)<<bar->high
            <<std::setw(weight)<<bar->low<<std::setw(weight)<<bar->close;
}


inline void TWAP::write_result(   ofstream & outFile,int weight,
                            double typicalPrice,double Twap,int messageCount)
{
    outFile <<std::setw(3*weight/2)<<typicalPrice
            <<std::setw(weight)<<Twap
            <<std::setw(weight)<<messageCount<<endl;
}