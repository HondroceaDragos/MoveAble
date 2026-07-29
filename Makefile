# Compiler and flags
CC = g++
CFLAGS = -O3 -Wall -std=c++20 -Wno-missing-braces
INCLUDES = -I C:/raylib/raylib/src
LDFLAGS = -L C:/raylib/raylib/src
LIBS = -lraylib -lopengl32 -lgdi32 -lwinmm

SRC = main.cpp $(wildcard src/*.cpp) $(wildcard src/*/*.cpp)
HEADERS = $(wildcard *.hpp) $(wildcard src/*.hpp) $(wildcard src/*/*.hpp) $(wildcard include/*.hpp) $(wildcard include/*/*.hpp) $(wildcard include/*/*/*.hpp)
TARGET = movable.exe

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(SRC) $(HEADERS)
	$(CC) $(SRC) -o $(TARGET) $(CFLAGS) $(INCLUDES) $(LDFLAGS) $(LIBS)

clean:
	del $(TARGET)

run: $(TARGET)
	.\$(TARGET)
