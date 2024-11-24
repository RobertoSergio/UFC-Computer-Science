output: main.o methods.o
	g++ main.o methods.o -o output

main.o: main.cpp
	g++ -c main.cpp

mehtods.o: methods.cpp methods.h
	g++ -c methods.cpp

clean:
	rm *.o output