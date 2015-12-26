all:  spritemap milestest
clean: spritemap-clean milestest-clean

milestest:
	make -C milestest
	make -C milestest copy
milestest-clean:
	make -C milestest clean

spritemap:
	make -C spritemap
	make -C spritemap copy
spritemap-clean:
	make -C spritemap clean

.PHONY: milestest milestest-clean spritemap spritemap-clean
