
all: build/ compile

compile: build/
	make -C build/ -j${nproc}

build/: 
	cmake -B build/

run:
	./build/sort

clean:
	rm -rf build/

dump: build/
	objdump -M intel -S -d build/sort > dump.txt

.PHONY: clean run compile dump
