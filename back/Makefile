PROJECT_ROOT=..

all: libback.a store.back

include ../../Makefile.inc

OBJECTS=shard.o

libback.a: shard.o
	ar -r $@ $(OBJECTS)

store.back: main.o libback.a
	$(LINK) main.o -L. -lback -o $@

