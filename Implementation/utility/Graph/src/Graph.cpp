#include "../inc/Graph.hpp"

/* 
##############################################
##############################################
## Template Specialization for nanoseconds ###
##############################################
##############################################
*/

Graph<uint32_t,Value>:: Graph():map{new std::map<uint32_t,Value>} // Constructor 
{/* deliberately left blank */} 

Graph<uint32_t,Value>:: ~Graph()// Destructor 
{
    if(map!=nullptr)
        map=nullptr;
        //std::cout<<"nanosecond destructor\n";
        //delete map;
    
} 


void Graph<uint32_t,Value>::addEdge(uint32_t key, const Value& value) 
{    
    typename std::map<uint32_t, Value>::iterator itr= map->find(key);
    
    if(itr!=map->end()){//if found, update value
        
        Value * vItr=itr->second.next;
        
        while(vItr->next!=nullptr)//go to the most current node
            vItr=vItr->next;

        Bar b{vItr->bar};

        if(value.bar.high > b.high)
            b.high=value.bar.high;

        else if(value.bar.low < b.low)
            b.low=value.bar.low;

        b.close=value.bar.close;
        b.quantity=value.bar.quantity;
        
        Value *v= new Value{b};

        vItr->next=v;
        return;
    }

    else //else, insert value
    {  
        map->insert({key,value});
    }
}


//void Graph<uint32_t,Value>::addEdge(uint32_t timestamp, Graph<uint32_t,Value> nanoseconds) 
void Graph<uint32_t,Value>::addEdge(uint32_t key, uint32_t newPrice,uint32_t newQuantity ) 
{    
    typename std::map<uint32_t, Value>::iterator itr= map->find(key);
    
    if(itr!=map->end()){//if found, update value
       
        Value * vItr=&itr->second;
        
        while(vItr->next!=nullptr)//go to the most current node
            vItr=vItr->next;

        Bar b{vItr->bar};

        if(newPrice > b.high)
            b.high=newPrice;

        else if(newPrice < b.low)
            b.low=newPrice;

        b.close=newPrice;
        b.quantity=newQuantity;
        
        Value *v= new Value{b};

        vItr->next=v;
        return;
    }

    else //else, insert value
    {   Value v{newPrice,newQuantity};
        map->insert({key,v});
    }
} 


void Graph<uint32_t,Value>::removeEdge(uint32_t key) 
{ 
    map->erase(key);
} 


void Graph<uint32_t,Value>::print(){
    
    
    for (auto& i: *map) 
    { 
        std::cout<<"\tnanosecond:"<<i.first<<":{\n";
        
        Value *v=&i.second;
        
        while(v!=nullptr){
            std::cout<<"\t{"<<v->bar.open<<","<<v->bar.high<<","
                    <<v->bar.low<<","<<v->bar.close<<","
                    <<v->bar.quantity<<"}\n";
            v=v->next;
        }
        std::cout<<"\t}\n";
    } 
}

void Graph<uint32_t,Value> ::writeFile(std::ofstream &outFile){
    
    for (auto& i: *map) 
    { 
        outFile<<"\tnanosecond:"<<i.first<<":{\n";
        
        Value *v=&i.second;
        
        while(v!=nullptr){
            outFile <<"\t{"<<v->bar.open<<","<<v->bar.high<<","
                    <<v->bar.low<<","<<v->bar.close<<","
                    <<v->bar.quantity<<"}\n";
            v=v->next;
        }
        outFile<<"\t}\n";
    } 
}





/* 
##############################################
##############################################
### Template Specialization for timestamp ####
##############################################
##############################################
*/

Graph<uint32_t,Graph<uint32_t, Value>>:: Graph():
map{new std::map<uint32_t,Graph<uint32_t, Value>>} // Constructor 
{/* deliberately left blank */} 

Graph<uint32_t,Graph<uint32_t, Value>>:: ~Graph()// Destructor 
{   
     if(map!=nullptr)
        map=nullptr;
        //std::cout<<"timestamp destructor\n";
        //delete map;
    
} 

//void Graph<uint32_t,Value>::addEdge(uint32_t timestamp, Graph<uint32_t,Value> nanoseconds) 
void Graph<uint32_t,Graph<uint32_t, Value>>::addEdge(uint32_t key, uint32_t newNanosecond,
                                            uint32_t newPrice,uint32_t newQuantity ) 
{    
    typename std::map<uint32_t, Graph<uint32_t, Value>>::iterator keyItr= map->find(key);
    
    if(keyItr!=map->end()){//if timestamp found, update value
        keyItr->second.addEdge(newNanosecond,newPrice,newQuantity);
        
        return;

    }
    
    else{//else, insert value
        Graph<uint32_t,Value> nano;
        nano.addEdge(newNanosecond,newPrice,newQuantity);
        map->insert({key,nano});
    }

} 


void Graph<uint32_t,Graph<uint32_t, Value>>::removeEdge(uint32_t key) 
{ 
    map->erase(key);
} 


void Graph<uint32_t,Graph<uint32_t, Value>>::print(){
    
    for(auto& key:*map){
        std::cout<<key.first<<":{";
        key.second.print();
        std::cout<<"}\n";
    
    }
}

void Graph<uint32_t,Graph<uint32_t, Value>> ::writeFile(std::ofstream &outFile){
    
    for(auto& key:*map){
        outFile<<"timestamp:"<<key.first<<":{\n";
        key.second.writeFile(outFile);
        outFile<<"}\n";
    
    }
} 
