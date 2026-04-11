CC      = gcc
CFLAGS  = -Wall -Wextra -O2
LIBS    = -lncurses -lcdk
TARGET  = pong
SRCS    = pong.c
OBJS    = $(SRCS:.c=.o)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(LIBS) -o $(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: clean
