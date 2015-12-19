all:
	make -C src

clean:
	make -C src clean
	rm -f ./roms/*.v64
