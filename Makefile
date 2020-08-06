OFILES =  main.o VWAP.o TWAP.o AVLTree.o
TARGET = main
COMPILER = g++-10
TXTFILES = addOrder.txt orderDelete.txt OrderExecuted.txt

$(TARGET): $(OFILES)
	$(COMPILER) $(OFILES) -o $@

clean.o:
	rm $(OFILES)

clean.txt:
	rm $(TXTFILES)
# below this is the output of "g++10 -MM":
main.o: main.cpp Implementation/TWAP/inc/TWAP.hpp \
 Implementation/TWAP/inc/../../AbstractImp/inc/AbstractImp.hpp \
 Implementation/TWAP/inc/../../utility/AVLTree/include/AVLTree.hpp \
 Implementation/TWAP/inc/../../utility/AVLTree/include/AVLTreePod.hpp \
 Implementation/VWAP/inc/VWAP.hpp \
 Implementation/VWAP/inc/../../AbstractImp/inc/AbstractImp.hpp \
 Implementation/VWAP/inc/../../utility/AVLTree/include/AVLTree.hpp
	g++-10 main.cpp -c
VWAP.o: Implementation/VWAP/src/VWAP.cpp \
 Implementation/VWAP/src/../inc/VWAP.hpp \
 Implementation/VWAP/src/../inc/../../AbstractImp/inc/AbstractImp.hpp \
 Implementation/VWAP/src/../inc/../../utility/AVLTree/include/AVLTree.hpp \
 Implementation/VWAP/src/../inc/../../utility/AVLTree/include/AVLTreePod.hpp \
 Implementation/VWAP/src/../../utility/AVLTree/include/AVLTree.hpp
	g++-10 Implementation/VWAP/src/VWAP.cpp -c
AVLTree.o: Implementation/utility/AVLTree/src/AVLTree.cpp \
 Implementation/utility/AVLTree/src/../include/AVLTree.hpp \
 Implementation/utility/AVLTree/src/../include/AVLTreePod.hpp
	g++-10 Implementation/utility/AVLTree/src/AVLTree.cpp -c
TWAP.o: Implementation/TWAP/src/TWAP.cpp \
 Implementation/TWAP/src/../inc/TWAP.hpp \
 Implementation/TWAP/src/../inc/../../AbstractImp/inc/AbstractImp.hpp \
 Implementation/TWAP/src/../inc/../../utility/AVLTree/include/AVLTree.hpp \
 Implementation/TWAP/src/../inc/../../utility/AVLTree/include/AVLTreePod.hpp
	g++-10 Implementation/TWAP/src/TWAP.cpp -c