output: finder.o
	g++ finder.o -o finder

finder.o: finder.cpp
	g++ -c finder.cpp

clean:
	rm *.o

remove:
	rm *
