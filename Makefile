CC = gcc
CFLAGS = -Wall -Wextra -g

OBJS = main.o dna.o crossovers.o competition.o fitness.o inputs.o
TARGET = ga

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

main.o: main.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
