CC = gcc
CFLAGS = -Wall -Wextra
LDFLAGS = -lncurses -lcdk

TARGET = pong
SRC = pong.c

all: $(TARGET)

$(TARGET): $(SRC)
  $(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

clean:
  rm -f $(TARGET)

.PHONY: all clean
