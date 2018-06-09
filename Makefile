SRC = src/main.cpp src/controlewe.cpp src/interewe.cpp
OBJ = $(SRC:.cpp = .o)

controlewe: $(OBJ)
		$(CXX) -std=c++11 -o controlewe $(OBJ) -lrt -lpthread
		
clean:
	rm -f controlewe
	rm -f src/*.o src/*~

