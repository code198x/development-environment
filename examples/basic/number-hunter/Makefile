all: number-hunter.prg

number-hunter.prg: number-hunter.bas
	petcat -w2 -o number-hunter.prg -- number-hunter.bas

run: number-hunter.prg
	x64sc number-hunter.prg

clean:
	rm -f number-hunter.prg

.PHONY: all run clean
