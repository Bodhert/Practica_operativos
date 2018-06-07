CXXFLAGS=-std=c++11
CC = g++
SRC = src/main.cpp src/controlewe.cpp
OBJ = $(SRC:.cpp = .o)
controlewe: $(OBJ)
		$(CXX) -std=c++11 -o controlewe $(OBJ) -lrt
clean:
	rm -f controlewe
	rm -f src/*.o src/*~

