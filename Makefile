# Which compiler to use
CC = gcc
# Compiler flags
CFLAGS = -m32 -Wall -I. -g -Werror=vla
# Final executable
TARGET = webster
# Constituent object files
OBJS = dictionary.o sh.o

# Default Make recipe
default: $(TARGET)

# part 1
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Clean recipe: removes all build artifacts
clean:
	$(RM) $(TARGET) $(OBJS)
