OFILES =  main.o AbstractClient.o AlgoHandler.o DataManager.o TWAP.o VWAP.o AVLTree.o Graph.o
TARGET = main
COMPILER = g++-10
# TXTFILES = TwapAddOrder.txt VwapAddOrder.txt

$(TARGET): $(OFILES)
	$(COMPILER) $(OFILES) -o $@

clean:
	rm $(OFILES) $(TXTFILES)

# below this is the output of "g++10 -MM":
main.o: main.cpp Client/AbstractClient/inc/AbstractClient.hpp \
 Implementation/AlgoHandler/inc/AlgoHandler.hpp \
 Implementation/AlgoHandler/inc/../../AbstractImp/inc/AbstractImp.hpp \
 Implementation/AlgoHandler/inc/../../utility/inc/std.hpp
	$(COMPILER) main.cpp -c
TWAP.o: Implementation/TWAP/src/TWAP.cpp \
 Implementation/TWAP/src/../inc/TWAP.hpp \
 Implementation/TWAP/src/../inc/../../utility/AVLTree/inc/AVLTree.hpp \
 Implementation/TWAP/src/../inc/../../utility/AVLTree/inc/../../inc/std.hpp \
 Implementation/TWAP/src/../inc/../../utility/AVLTree/inc/AVLTreePod.hpp \
 Implementation/TWAP/src/../inc/../../utility/Graph/inc/Graph.hpp \
 Implementation/TWAP/src/../inc/../../utility/Graph/inc/../../inc/std.hpp \
 Implementation/TWAP/src/../inc/../../utility/Graph/inc/GraphPod.hpp
	$(COMPILER) Implementation/TWAP/src/TWAP.cpp -c
VWAP.o: Implementation/VWAP/src/VWAP.cpp \
 Implementation/VWAP/src/../inc/VWAP.hpp \
 Implementation/VWAP/src/../inc/../../utility/AVLTree/inc/AVLTree.hpp \
 Implementation/VWAP/src/../inc/../../utility/AVLTree/inc/../../inc/std.hpp \
 Implementation/VWAP/src/../inc/../../utility/AVLTree/inc/AVLTreePod.hpp
	$(COMPILER) Implementation/VWAP/src/VWAP.cpp -c
AVLTree.o: Implementation/utility/AVLTree/src/AVLTree.cpp \
 Implementation/utility/AVLTree/src/../inc/AVLTree.hpp \
 Implementation/utility/AVLTree/src/../inc/../../inc/std.hpp \
 Implementation/utility/AVLTree/src/../inc/AVLTreePod.hpp
	$(COMPILER) Implementation/utility/AVLTree/src/AVLTree.cpp -c
DataManager.o: Implementation/DataManager/src/DataManager.cpp \
 Implementation/DataManager/src/../../utility/AVLTree/inc/AVLTree.hpp \
 Implementation/DataManager/src/../../utility/AVLTree/inc/../../inc/std.hpp \
 Implementation/DataManager/src/../../utility/AVLTree/inc/AVLTreePod.hpp \
 Implementation/DataManager/src/../inc/DataManager.hpp \
 Implementation/DataManager/src/../inc/../../utility/inc/std.hpp
	$(COMPILER) Implementation/DataManager/src/DataManager.cpp  -c
AlgoHandler.o: Implementation/AlgoHandler/src/AlgoHandler.cpp \
 Implementation/AlgoHandler/src/../inc/AlgoHandler.hpp \
 Implementation/AlgoHandler/src/../inc/../../AbstractImp/inc/AbstractImp.hpp \
 Implementation/AlgoHandler/src/../../DataManager/inc/DataManager.hpp \
 Implementation/AlgoHandler/src/../../DataManager/inc/../../utility/inc/std.hpp \
 Implementation/AlgoHandler/src/../../utility/AVLTree/inc/AVLTree.hpp \
 Implementation/AlgoHandler/src/../../utility/AVLTree/inc/../../inc/std.hpp \
 Implementation/AlgoHandler/src/../../utility/AVLTree/inc/AVLTreePod.hpp \
 Implementation/AlgoHandler/src/../../TWAP/inc/TWAP.hpp \
 Implementation/AlgoHandler/src/../../TWAP/inc/../../utility/AVLTree/inc/AVLTree.hpp \
 Implementation/AlgoHandler/src/../../VWAP/inc/VWAP.hpp \
 Implementation/AlgoHandler/src/../../VWAP/inc/../../utility/AVLTree/inc/AVLTree.hpp
	$(COMPILER) Implementation/AlgoHandler/src/AlgoHandler.cpp -c
Graph.o: Implementation/utility/Graph/src/Graph.cpp \
 Implementation/utility/Graph/src/../inc/Graph.hpp \
 Implementation/utility/Graph/src/../inc/../../inc/std.hpp \
 Implementation/utility/Graph/src/../inc/GraphPod.hpp
	$(COMPILER) Implementation/utility/Graph/src/Graph.cpp -c
AbstractClient.o: Client/AbstractClient/src/AbstractClient.cpp \
 Client/AbstractClient/src/../inc/AbstractClient.hpp \
 Client/AbstractClient/src/../../../Implementation/AbstractImp/inc/AbstractImp.hpp
	$(COMPILER) Client/AbstractClient/src/AbstractClient.cpp -c