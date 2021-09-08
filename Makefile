make:
	mkdir -p build && cd build && cmake .. && make -j && cd ..

run:
	./build/bin/hw1_app
