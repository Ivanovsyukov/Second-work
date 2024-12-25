CC=g++
CFLAGS=-c -pedantic-errors -gdwarf-4 -std=c++20
LDFLAGS=-lws2_32
SOURCES=main.cpp Player.cpp TicTacToe.cpp TSBool.cpp TSQueue.cpp TSVector.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=TicTacToe

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

.PHONY: clean

clean:
	rm -rf *.o $(EXECUTABLE)
