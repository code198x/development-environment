all: hello.prg

hello.prg: hello.asm
	acme -f cbm -o hello.prg hello.asm

run: hello.prg
	x64sc hello.prg

clean:
	rm -f hello.prg

.PHONY: all run clean
