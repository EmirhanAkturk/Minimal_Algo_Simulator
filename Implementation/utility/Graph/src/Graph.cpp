#include "../inc/Graph.hpp"

Graph<uint32_t,Value>:: Graph():map{new std::unordered_map<uint32_t,Value>} // Constructor 
{/* deliberately left blank */} 


// void Graph<uint32_t,Value>::addEdge(uint32_t key, const Value& value) 
// {    
//     typename std::unordered_map<uint32_t, Value>::iterator itr= map->find(key);
    
//     if(itr!=map->end()){//if found, update value
        
//         if(value.high > itr->second.high)
//             itr->second.high=value.high;

//         if(value.low < itr->second.low)
//             itr->second.low=value.low;

//         itr->second.close=value.close;    
//         return;
//     }

//     else //else, insert value
//     {  
//         Bar b{newPrice};
//         map->insert({key,b});
//     }
// }


//void Graph<uint32_t,Bar>::addEdge(uint32_t timestamp, Graph<uint32_t,Bar> nanoseconds) 
void Graph<uint32_t,Value>::addEdge(uint32_t key, uint32_t newNanosecond,uint32_t newPrice) 
{    
    typename std::unordered_map<uint32_t, Value>::iterator itr= map->find(key);
    
    if(itr!=map->end()){//if found, update value

        if(itr->second.nanosecond!=newNanosecond)
            itr->second.nanosecond=newNanosecond;

        if(newPrice > itr->second.bar.high)
            itr->second.bar.high=newPrice;

        else if(newPrice < itr->second.bar.low)
            itr->second.bar.low=newPrice;

        itr->second.bar.close=newPrice;    
        return;
    }

    else //else, insert value
     {   
        //Bar b{newPrice};
        Value v{newNanosecond,newPrice};
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
        std::cout<<i.first<<": {nanosecond:"<<i.second.nanosecond<<","<<i.second.bar.open<<","<<i.second.bar.high<<","
            <<i.second.bar.low<<","<<i.second.bar.close<<"}"<<std::endl; 
    } 
}

void Graph<uint32_t,Value> ::writeFile(std::ofstream &outFile){
    
    for (auto& i: *map) 
    { 
        outFile<<i.first<<": {nanosecond:"<<i.second.nanosecond<<","<<i.second.bar.open<<","<<i.second.bar.high<<","
            <<i.second.bar.low<<","<<i.second.bar.close<<"}"<<std::endl; 
    }     

}
// /* Graph<uint32_t,Bar>:: Graph():map{new std::unordered_map<uint32_t,Bar>} // Constructor 
// {/* deliberately left blank */} 

/*
// void Graph<uint32_t,Bar>::addEdge(uint32_t key, const Bar& value) 
// {    
//     typename std::unordered_map<uint32_t, Bar>::iterator itr= map->find(key);
    
//     if(itr!=map->end()){//if found, update value
        
//         if(value.high > itr->second.high)
//             itr->second.high=value.high;

//         if(value.low < itr->second.low)
//             itr->second.low=value.low;

//         itr->second.close=value.close;    
//         return;
//     }

//     else //else, insert value
//     {  
//         map->insert({key,value});
//     }
// }


// //void Graph<uint32_t,Bar>::addEdge(uint32_t timestamp, Graph<uint32_t,Bar> nanoseconds) 
// void Graph<uint32_t,Bar>::addEdge(uint32_t key, uint32_t newPrice) 
// {    
//     typename std::unordered_map<uint32_t, Bar>::iterator itr= map->find(key);
    
//     if(itr!=map->end()){//if found, update value
        
//         if(newPrice > itr->second.high)
//             itr->second.high=newPrice;

//         else if(newPrice < itr->second.low)
//             itr->second.low=newPrice;

//         itr->second.close=newPrice;    
//         return;
//     }

//     else //else, insert value
//     {   Bar b{newPrice};
//         map->insert({key,b});
//     }
// } 


// void Graph<uint32_t,Bar>::removeEdge(uint32_t key) 
// { 
//     map->erase(key);
// } 


// void Graph<uint32_t,Bar>::print(){
    
//     for (auto& i: *map) 
//     { 
//         std::cout<<i.first<<": {"<<i.second.open<<","<<i.second.high<<","
//             <<i.second.low<<","<<i.second.close<<"}"<<std::endl; 
//     } 
// }

// void Graph<uint32_t,Bar> ::writeFile(std::ofstream &outFile){
    
//     for (auto& i: *map) 
//     { 
//         outFile<<i.first<<": {"<<i.second.open<<","<<i.second.high<<","
//             <<i.second.low<<","<<i.second.close<<"}"<<std::endl; 
//     }     

// } */