CC = g++ -std=c++11
CFLAGS = -c 
LDFLAGS = -lrt -lpthread
CONTROL_SOURCES = src/mainEweControl.cpp src/controlewe.cpp
CONTROL_OBJECTS = $(CONTROL_SOURCES:.cpp=.o)
CONTROL_EXECUTABLE = controlewe
INTERPRETER_SOURCES = src/mainInterEwe.cpp src/interewe.cpp
INTERPRETER_OBJECTS = $(INTERPRETER_SOURCES:.cpp=.o)
INTERPRETER_EXECUTABLE = interewe

.PHONY: all control interpreter

all: control interpreter

control: $(CONTROL_EXECUTABLE)

interpreter: $(INTERPRETER_EXECUTABLE)


$(CONTROL_EXECUTABLE): $(CONTROL_OBJECTS)
	$(CC) $^ -o $@ $(LDFLAGS)


$(INTERPRETER_EXECUTABLE): $(INTERPRETER_OBJECTS)
	$(CC) $^ -o $@ $(LDFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f controlewe interewe
	rm -f src/*.o src/*~
