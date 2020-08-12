#ifndef _GRAPH_HPP_
#define _GRAPH_HPP_

#include "../../inc/std.hpp"

struct Bar{
    Bar(uint32_t newPrice):open{newPrice},
    high{newPrice},low{newPrice},close{newPrice}
    {}
    
    Bar(uint32_t o,uint32_t h,uint32_t l,uint32_t c):
    open{o},high{h},low{l},close{c}
    {}
    uint32_t open;
    uint32_t high;
    uint32_t low;
    uint32_t close;
};

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

private:
    std::unordered_map<uint32_t,Bar>*map;
};

//#include "../src/Graph.inl"
#endif