OBJS=main.o
SRCS=$(OBJS:%.o=%.c)
CFLAGS=-g -Wall -DDEBUG
LDLIBS=
TARGET=ssddrv
$(TARGET):$(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(TARGET) $(OBJS) $(LDLIBS)
clean:
	rm $(TARGET) $(OBJS) 
