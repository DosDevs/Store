PROJECT_ROOT=..

all: libback.a store.back

include ../Makefile.inc

OBJECTS=base-shard.o

libback.a: $(OBJECTS)
	ar -r $@ $(OBJECTS)

store.back: main.o libback.a
	$(LINK) main.o -L. -lback -o $@

