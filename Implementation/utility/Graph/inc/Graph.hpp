#ifndef _GRAPH_HPP_
#define _GRAPH_HPP_

#include "../../inc/std.hpp"
#include "GraphPod.hpp"

// Class to represent a graph 
template<class K, class V>
class Graph;


/* 
##############################################
##############################################
## Template Specialization for nanoseconds ###
##############################################
##############################################
*/

template<>
class Graph<uint32_t, Value> {   
public: 
	Graph();// Constructor 

    ~Graph();// Destructor

	// function to add an edge to graph 
	void addEdge(uint32_t nanosecond,const Value& value); 
	
    void addEdge(uint32_t vertex,uint32_t newPrice,uint32_t newQuantity);

    void removeEdge(uint32_t vertex);

    inline std::map<uint32_t,Value>::iterator search(uint32_t vertex){
        return map->find(vertex);
    }

    void print();

    void writeFile(std::ofstream &outFile);

    inline std::map<uint32_t,Value>::iterator getMapBegin(){
        return map->begin();
    }

    inline std::map<uint32_t,Value>::iterator getMapEnd(){
        return map->end();
    }

private:
    std::map<uint32_t,Value>*map;
};




/* 
##############################################
##############################################
### Template Specialization for timestamp ####
##############################################
##############################################
*/

template<>
class Graph<uint32_t, Graph<uint32_t, Value>> {  
    //Graph<timestamp, Graph<nanoseconds, Value> > 
public: 
	Graph();// Constructor 

	~Graph();// Destructor

	// function to add an edge to graph 
	//void addEdge(uint32_t vertex,const Value& value); 
	
    void addEdge(uint32_t newTimestamp,uint32_t newNanosecond,uint32_t newPrice,uint32_t newQuantity);

    void removeEdge(uint32_t timestamp);

    inline std::map<uint32_t,Graph<uint32_t, Value>>::iterator search(uint32_t timestamp){
        return map->find(timestamp);
    }
    void print();

    void writeFile(std::ofstream &outFile);

    inline std::map<uint32_t, Graph<uint32_t, Value>>::iterator getMapBegin(){
        return map->begin();
    }

    inline std::map<uint32_t, Graph<uint32_t, Value>>::iterator getMapEnd(){
        return map->end();
    }

private:
    std::map<uint32_t,Graph<uint32_t, Value>>*map;
};


//#include "../src/Graph.inl"
#endif