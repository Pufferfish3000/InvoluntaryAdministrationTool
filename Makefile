.PHONY: bearssl clean

bearssl:
	cd external/bearssl && make

clean:
	cd external/bearssl && make clean