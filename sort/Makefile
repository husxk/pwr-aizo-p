
all: build/ compile

compile: build/
	make -C build/ -j${nproc}

build/: 
	cmake -B build/

run:
	./build/sort

clean:
	rm -rf build/

.PHONY: clean run compile
