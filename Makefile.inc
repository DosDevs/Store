CC=clang++ -c -std=c++1z -I/usr/local/include -iquote $(PROJECT_ROOT)
LINK=clang++ -lstdc++ $(LINK_DEPEND) -L/usr/local/lib

clean:
	rm -fv *.o

.cpp.o:
	$(CC) $< -o $@

.PHONY: all clean

