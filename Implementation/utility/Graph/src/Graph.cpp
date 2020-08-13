#include "../inc/Graph.hpp"

/* 
##############################################
##############################################
## Template Specialization for nanoseconds ###
##############################################
##############################################
*/

Graph<uint32_t,Bar>:: Graph():map{new std::unordered_map<uint32_t,Bar>} // Constructor 
{/* deliberately left blank */} 


void Graph<uint32_t,Bar>::addEdge(uint32_t key, const Bar& value) 
{    
    typename std::unordered_map<uint32_t, Bar>::iterator itr= map->find(key);
    
    if(itr!=map->end()){//if found, update value
        
        if(value.high > itr->second.high)
            itr->second.high=value.high;

        if(value.low < itr->second.low)
            itr->second.low=value.low;

        itr->second.close=value.close;    
        return;
    }

    else //else, insert value
    {  
        map->insert({key,value});
    }
}


//void Graph<uint32_t,Bar>::addEdge(uint32_t timestamp, Graph<uint32_t,Bar> nanoseconds) 
void Graph<uint32_t,Bar>::addEdge(uint32_t key, uint32_t newPrice) 
{    
    typename std::unordered_map<uint32_t, Bar>::iterator itr= map->find(key);
    
    if(itr!=map->end()){//if found, update value
        
        if(newPrice > itr->second.high)
            itr->second.high=newPrice;

        else if(newPrice < itr->second.low)
            itr->second.low=newPrice;

        itr->second.close=newPrice;    
        return;
    }

    else //else, insert value
    {   Bar b{newPrice};
        map->insert({key,b});
    }
} 


void Graph<uint32_t,Bar>::removeEdge(uint32_t key) 
{ 
    map->erase(key);
} 


void Graph<uint32_t,Bar>::print(){
    
    for (auto& i: *map) 
    { 
        std::cout<<i.first<<": {"<<i.second.open<<","<<i.second.high<<","
            <<i.second.low<<","<<i.second.close<<"}"<<std::endl; 
    } 
}

void Graph<uint32_t,Bar> ::writeFile(std::ofstream &outFile){
    
    for (auto& i: *map) 
    { 
        outFile<<i.first<<": {"<<i.second.open<<","<<i.second.high<<","
            <<i.second.low<<","<<i.second.close<<"}"<<std::endl; 
    }     

}





/* 
##############################################
##############################################
### Template Specialization for timestamp ####
##############################################
##############################################
*/

Graph<uint32_t,Graph<uint32_t, Bar>>:: Graph():
map{new std::unordered_map<uint32_t,Graph<uint32_t, Bar>>} // Constructor 
{/* deliberately left blank */} 

//void Graph<uint32_t,Bar>::addEdge(uint32_t timestamp, Graph<uint32_t,Bar> nanoseconds) 
void Graph<uint32_t,Graph<uint32_t, Bar>>::addEdge(uint32_t key, uint32_t newNanosecond,uint32_t newPrice) 
{    
    typename std::unordered_map<uint32_t, Graph<uint32_t, Bar>>::iterator keyItr= map->find(key);
    
    if(keyItr!=map->end()){//if timestamp found, update value
        keyItr->second.addEdge(newNanosecond,newPrice);
        
        return;

    }
    
    else{//else, insert value
        Graph<uint32_t,Bar> nano;
        nano.addEdge(newNanosecond,newPrice);
        map->insert({key,nano});
    }

} 


void Graph<uint32_t,Graph<uint32_t, Bar>>::removeEdge(uint32_t key) 
{ 
    map->erase(key);
} 


void Graph<uint32_t,Graph<uint32_t, Bar>>::print(){
    
    for(auto& key:*map){
        std::cout<<key.first<<":{";
        key.second.print();
        std::cout<<"}\n";
    
    }
}

void Graph<uint32_t,Graph<uint32_t, Bar>> ::writeFile(std::ofstream &outFile){
    
    for(auto& key:*map){
        outFile<<"timestamp:"<<key.first<<":{\n";
        key.second.writeFile(outFile);
        outFile<<"}\n";
    
    }
} 
