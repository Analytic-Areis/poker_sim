CC = gcc
CFLAGS = -Wall -Wextra -O3
TARGET = poker_sim

SRCS = simulator.c deck.c evaluate.c monte_carlo.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
