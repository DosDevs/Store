all: back front

clean:
	cd back && make clean
	cd front && make clean

back:
	cd back && make

front:
	cd front && make

.PHONY: clean back front

