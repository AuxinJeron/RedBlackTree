all : bbst
bbst : clean main.o rbTree.o
	g++ main.o -o bbst
main.o : main.cpp
	g++ -c main.cpp
rbTree.o : rbTree.cpp
	g++ -c rbTree.cpp
clean :
	rm -f bbst *.o