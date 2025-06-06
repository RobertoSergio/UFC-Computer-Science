output: main.o Format.o Methods.o
	g++ main.o Format.o Methods.o -o output

main.o: main.cpp
	g++ -c main.cpp

Format.o: Format.cpp Format.h
	g++ -c Format.cpp

Methods.o: Methods.cpp Methods.h
	g++ -c Methods.cpp

clean:
	rm *.o output