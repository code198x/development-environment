all: skyfall.prg

skyfall.prg: skyfall.asm
	acme -f cbm -o skyfall.prg skyfall.asm

run: skyfall.prg
	x64sc skyfall.prg

clean:
	rm -f skyfall.prg

.PHONY: all run clean
