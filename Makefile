OFILES =  main.o AlgoHandler.o TWAP.o VWAP.o AVLTree.o
TARGET = main
COMPILER = g++-10
# TXTFILES = TwapAddOrder.txt VwapAddOrder.txt

$(TARGET): $(OFILES)
	$(COMPILER) $(OFILES) -o $@

clean:
	rm $(OFILES) $(TARGET) $(TXTFILES)

# below this is the output of "g++10 -MM":
main.o: main.cpp Implementation/AlgoHandler/inc/Algohandler.hpp \
 Implementation/AlgoHandler/inc/../../AbstractImp/inc/AbstractImp.hpp \
 Implementation/AlgoHandler/inc/../../TWAP/inc/TWAP.hpp \
 Implementation/AlgoHandler/inc/../../TWAP/inc/../../utility/AVLTree/inc/AVLTree.hpp \
 Implementation/AlgoHandler/inc/../../TWAP/inc/../../utility/AVLTree/inc/AVLTreePod.hpp \
 Implementation/AlgoHandler/inc/../../VWAP/inc/VWAP.hpp \
 Implementation/AlgoHandler/inc/../../VWAP/inc/../../utility/AVLTree/inc/AVLTree.hpp
	g++-10 main.cpp -c
AlgoHandler.o: Implementation/AlgoHandler/src/AlgoHandler.cpp \
 Implementation/AlgoHandler/src/../inc/Algohandler.hpp \
 Implementation/AlgoHandler/src/../inc/../../AbstractImp/inc/AbstractImp.hpp \
 Implementation/AlgoHandler/src/../inc/../../TWAP/inc/TWAP.hpp \
 Implementation/AlgoHandler/src/../inc/../../TWAP/inc/../../utility/AVLTree/inc/AVLTree.hpp \
 Implementation/AlgoHandler/src/../inc/../../TWAP/inc/../../utility/AVLTree/inc/AVLTreePod.hpp \
 Implementation/AlgoHandler/src/../inc/../../VWAP/inc/VWAP.hpp \
 Implementation/AlgoHandler/src/../inc/../../VWAP/inc/../../utility/AVLTree/inc/AVLTree.hpp
	g++-10 Implementation/AlgoHandler/src/AlgoHandler.cpp -c
TWAP.o: Implementation/TWAP/src/TWAP.cpp \
 Implementation/TWAP/src/../inc/TWAP.hpp \
 Implementation/TWAP/src/../inc/../../utility/AVLTree/inc/AVLTree.hpp \
 Implementation/TWAP/src/../inc/../../utility/AVLTree/inc/AVLTreePod.hpp
	g++-10 Implementation/TWAP/src/TWAP.cpp -c
VWAP.o: Implementation/VWAP/src/VWAP.cpp \
 Implementation/VWAP/src/../inc/VWAP.hpp \
 Implementation/VWAP/src/../inc/../../utility/AVLTree/inc/AVLTree.hpp \
 Implementation/VWAP/src/../inc/../../utility/AVLTree/inc/AVLTreePod.hpp
	g++-10 Implementation/VWAP/src/VWAP.cpp -c
AVLTree.o: Implementation/utility/AVLTree/src/AVLTree.cpp \
 Implementation/utility/AVLTree/src/../inc/AVLTree.hpp \
 Implementation/utility/AVLTree/src/../inc/AVLTreePod.hpp
	g++-10 Implementation/utility/AVLTree/src/AVLTree.cpp -c