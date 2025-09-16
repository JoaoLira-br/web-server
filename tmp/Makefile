# Target executable name
TARGET = test

# C compiler
CC = gcc

# Source files
SRCS = test.c Server.c

# Object files (derived from source files)
OBJS = $(SRCS:.c=.o)

# Build the target	
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)