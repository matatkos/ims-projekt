CXX = g++
CXXFLAGS = -Wall -std=c++11 $(shell pkg-config --cflags opencv4)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

grid.o: grid.cpp
	$(CXX) $(CXXFLAGS) -c grid.cpp

image.o: image.cpp
	$(CXX) $(CXXFLAGS) -c image.cpp

all: main.o grid.o image.o
	$(CXX) main.o grid.o image.o -o simulation $(shell pkg-config --libs opencv4)

clean:
	rm -f *.o simulation