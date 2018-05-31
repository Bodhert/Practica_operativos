CXXFLAGS=-std=c++11

all: memoryCreator

memoryCreator: memoryCreator.o
		$(CXX) -o $@ $^ -lrt

memoryCreator.o: memoryCreator.cpp


clean:
	rm -f memoryCreator
	rm -f *.o *.*~ *~ 

