CC = g++
CFLAGS = -Wall -Wextra -std=c++20
TARGET = src/*.cpp
BIN = i2a
LIBS = 

all:
	$(CC) $(CFLAGS) -o $(BIN) $(TARGET) $(LIBS)

# Clean up object files and executable (Windows Support)
clean:
	del $(BIN) $(BIN).exe
