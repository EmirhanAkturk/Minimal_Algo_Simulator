#ifndef _VWAP_HPP_
#define _VWAP_HPP_

//#include "../../utility/AVLTree/inc/AVLTree.hpp"
//#include "../../utility/Graph/inc/Graph.hpp"
#include "../../utility/Temp/inc/Temp.hpp"

class VWAP{
public:
    VWAP()
    { /* deliberately left blank. */  }

    void calculate(AVLTree<OrderBookId>* OBITree);


private:

    void calculate_and_write(Graph<uint32_t,Graph<uint32_t,Value>>* graph,uint32_t bookId);

    inline void write_table_title(ofstream & outFile,int weight);

    inline void write_date( ofstream & outFile,int weight,
                            int year,int month,int day,
                            int hour,int minute,int second);

    inline void write_bar(ofstream & outFile,int weight,const Bar* bar);

    inline void write_result( ofstream & outFile,int weight,double typicalPrice,uint64_t VP,
                                    uint64_t totalVp,uint32_t totalVolume,double Vwap,int messageCount);
};

#endif