#ifndef _GRAPH_HPP_
#define _GRAPH_HPP_

#include "../../inc/std.hpp"
#include "GraphPod.hpp"

// Class to represent a graph 
template<class K, class V>
class Graph;

template<>
class Graph<uint32_t, Bar> {   
public: 
	Graph();// Constructor 

	// function to add an edge to graph 
	void addEdge(uint32_t vertex,const Bar& value); 
	
    void addEdge(uint32_t vertex,uint32_t newPrice);

    void removeEdge(uint32_t vertex);

    void print();

    void writeFile(std::ofstream &outFile);

    inline std::unordered_map<uint32_t,Bar>::iterator getMapBegin(){
        return map->begin();
    }

    inline std::unordered_map<uint32_t,Bar>::iterator getMapEnd(){
        return map->end();
    }

private:
    std::unordered_map<uint32_t,Bar>*map;
};

//#include "../src/Graph.inl"
#endif