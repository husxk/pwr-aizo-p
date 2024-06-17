
all: build/ compile

compile: build/
	make -C build/ -j$(nproc)

build/: 
	cmake -B build/

run:
	./build/testing

clean:
	rm -rf build/


.PHONY: all clean run compile
