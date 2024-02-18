CFLAGS = -Wall
SRCDIR = src
OBJDIR = obj

SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))

all: main test

main: $(OBJS)
	$(CC) $(CFLAGS) main.c $^ -o $@
test: $(OBJS)
	$(CC) $(CFLAGS) test.c $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f main test $(OBJS)