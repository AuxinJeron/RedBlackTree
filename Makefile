all : bbst
bbst : clean main.o rbTree.o
	g++ main.o -o bbst
main.o : main.cpp
	g++ -c -std=c++11 main.cpp
rbTree.o : rbTree.cpp
	g++ -c -std=c++11 rbTree.cpp
clean :
	rm -f bbst *.o