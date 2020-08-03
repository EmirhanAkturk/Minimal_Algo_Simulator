# run: main
# 	./main

main: main.o Search.o Message.o
	g++-10 main.o Search.o Message.o -o main

main.o: main.cpp Client/include/Message.h Implementation/include/Search.h \
 Implementation/include/MessageImp.h \
 Implementation/include/../utility/include/AVLTree.hpp \
 Implementation/include/../utility/include/../../include/SearchPod.h
	g++-10 -c main.cpp

Search.o: Implementation/src/Search.cpp \
 Implementation/src/../include/search.h \
 Implementation/src/../include/MessageImp.h \
 Implementation/src/../include/../utility/include/AVLTree.hpp \
 Implementation/src/../include/../utility/include/../../include/SearchPod.h \
 Implementation/src/../utility/include/AVLTree.inl
	g++-10 -c ./Implementation/src/Search.cpp

Message.o: Client/src/Message.cpp Client/src/../include/Message.h \
 Client/src/../../Implementation/include/MessageImp.h
	g++-10 -c ./Client/src/Message.cpp

run: main
	./main

clear.o:
	rm *.o

clear.txt:
	rm *.txt