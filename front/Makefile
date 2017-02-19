LINK_DEPEND=-lPocoNet -lPocoFoundation
PROJECT_ROOT=..

all: libfront.a store.front

include ../../Makefile.inc

OBJECTS=http-server.o

libfront.a: http-server.o
	ar -r $@ $(OBJECTS)

store.front: main.o libfront.a
	$(LINK) main.o -L. -lfront -o $@

