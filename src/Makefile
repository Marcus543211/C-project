SAN_FLAGS = -fsanitize=address,undefined,leak
CFLAGS = -Wall -g -O2 $(SAN_FLAGS)
LDLIBS = -lm
LDFLAGS = $(SAN_FLAGS)

OBJS = cycleDetection.o Graph.o LinkedList.o main.o

detectCycles: $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

.PHONY: clean
clean:
	rm -f *.o detectCycles

