CXX = g++
TARGET = spookIt
SRC = main.cpp functions.cpp globals.cpp

# Raylib libraries and flags for Linux/WSL
LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

all:
	$(CXX) $(SRC) -o $(TARGET) $(LIBS)

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET)