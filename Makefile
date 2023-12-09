CXX = g++
CXXFLAGS = -Wall -std=c++17 $(shell pkg-config --cflags opencv4)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp


grid.o: grid.cpp grid.h
	$(CXX) $(CXXFLAGS) -c grid.cpp

image.o: image.cpp image.h
	$(CXX) $(CXXFLAGS) -c image.cpp

cell.o: cell.cpp cell.h
	$(CXX) $(CXXFLAGS) -c cell.cpp

all: main.o grid.o image.o cell.o
	$(CXX) main.o grid.o image.o cell.o -o simulation $(shell pkg-config --libs opencv4)

clean:
	rm -f *.o simulation