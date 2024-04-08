TESTDIR=../../src/sample
TESTOBJS=$(TESTDIR)/sample.o 
TESTINC=-I$(TESTDIR)/.
OBJS=sample_test.o
OBJS+=$(TESTOBJS)
SRCS=$(OBJS:%.o=%.c)
CFLAGS=-std=c++11
CFLAGS+=$(TESTINC)
LDLIBS=-L/usr/local/lib -lgtest -lgtest_main -lpthread
TARGET=utest
CC=g++
$(TARGET):$(OBJS) 
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDLIBS) 
clean:
	rm $(TARGET) $(OBJS) 
