OBJS = src/main.o
CFLAGS =
LDFLAGS = -lm

esp32-apll-cal: $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@