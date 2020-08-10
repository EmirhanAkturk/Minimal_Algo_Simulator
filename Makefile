OFILES =  main.o AlgoHandler.o FileManager.o TWAP.o VWAP.o AVLTree.o
TARGET = main
COMPILER = g++-10
# TXTFILES = TwapAddOrder.txt VwapAddOrder.txt

$(TARGET): $(OFILES)
	$(COMPILER) $(OFILES) -o $@

clean:
	rm $(OFILES) $(TXTFILES)

# below this is the output of "g++10 -MM":
main.o: main.cpp Implementation/AlgoHandler/inc/AlgoHandler.hpp \
 Implementation/AlgoHandler/inc/../../AbstractImp/inc/AbstractImp.hpp \
 Implementation/utility/inc/std.hpp
	g++-10 main.cpp -c
TWAP.o: Implementation/TWAP/src/TWAP.cpp \
 Implementation/TWAP/src/../inc/TWAP.hpp \
 Implementation/TWAP/src/../inc/../../utility/AVLTree/inc/AVLTree.hpp \
 Implementation/TWAP/src/../inc/../../utility/AVLTree/inc/../../inc/std.hpp \
 Implementation/TWAP/src/../inc/../../utility/AVLTree/inc/AVLTreePod.hpp
	g++-10 Implementation/TWAP/src/TWAP.cpp -c
VWAP.o: Implementation/VWAP/src/VWAP.cpp \
 Implementation/VWAP/src/../inc/VWAP.hpp \
 Implementation/VWAP/src/../inc/../../utility/AVLTree/inc/AVLTree.hpp \
 Implementation/VWAP/src/../inc/../../utility/AVLTree/inc/../../inc/std.hpp \
 Implementation/VWAP/src/../inc/../../utility/AVLTree/inc/AVLTreePod.hpp
	g++-10 Implementation/VWAP/src/VWAP.cpp -c
AVLTree.o: Implementation/utility/AVLTree/src/AVLTree.cpp \
 Implementation/utility/AVLTree/src/../inc/AVLTree.hpp \
 Implementation/utility/AVLTree/src/../inc/../../inc/std.hpp \
 Implementation/utility/AVLTree/src/../inc/AVLTreePod.hpp
	g++-10 Implementation/utility/AVLTree/src/AVLTree.cpp -c
FileManager.o: Implementation/FileManager/src/FileManager.cpp \
 Implementation/FileManager/src/../../utility/AVLTree/inc/AVLTree.hpp \
 Implementation/FileManager/src/../../utility/AVLTree/inc/../../inc/std.hpp \
 Implementation/FileManager/src/../../utility/AVLTree/inc/AVLTreePod.hpp \
 Implementation/FileManager/src/../inc/FileManager.hpp \
 Implementation/FileManager/src/../inc/../../utility/inc/std.hpp
	g++-10 Implementation/FileManager/src/FileManager.cpp  -c
AlgoHandler.o: Implementation/AlgoHandler/src/AlgoHandler.cpp \
 Implementation/AlgoHandler/src/../inc/AlgoHandler.hpp \
 Implementation/AlgoHandler/src/../inc/../../AbstractImp/inc/AbstractImp.hpp \
 Implementation/AlgoHandler/src/../../FileManager/inc/FileManager.hpp \
 Implementation/AlgoHandler/src/../../FileManager/inc/../../utility/inc/std.hpp \
 Implementation/AlgoHandler/src/../../utility/AVLTree/inc/AVLTree.hpp \
 Implementation/AlgoHandler/src/../../utility/AVLTree/inc/../../inc/std.hpp \
 Implementation/AlgoHandler/src/../../utility/AVLTree/inc/AVLTreePod.hpp \
 Implementation/AlgoHandler/src/../../TWAP/inc/TWAP.hpp \
 Implementation/AlgoHandler/src/../../TWAP/inc/../../utility/AVLTree/inc/AVLTree.hpp \
 Implementation/AlgoHandler/src/../../VWAP/inc/VWAP.hpp \
 Implementation/AlgoHandler/src/../../VWAP/inc/../../utility/AVLTree/inc/AVLTree.hpp
	g++-10 Implementation/AlgoHandler/src/AlgoHandler.cpp -c