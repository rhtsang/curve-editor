all: draw

clean:
	rm -f draw filemanipulation.o bezier.o

draw: main.cpp filemanipulation.o bezier.o
	g++ main.cpp -lglut -lGL -o draw filemanipulation.o bezier.o

filemanipulation.o: filemanipulation.cpp filemanipulation.h
	g++ -std=c++11 -c filemanipulation.cpp

bezier.o: bezier.cpp bezier.h
	g++ -c bezier.cpp
