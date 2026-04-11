CC     = gcc
CFLAGS = -O2
LIBS   = -lncurses -lcdk
TARGET = pong
SRCS   = pong.c
OBJS   = $(SRCS:.c=.o)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(LIBS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: clean
