all: bin2hex hex2bin entropy xLFSR

clean:
	rm -f bin2hex hex2bin entropy xLFSR *.exe

bin2hex: bin2hex.c
	cc -Wall -O3 -o bin2hex bin2hex.c

hex2bin: hex2bin.c
	cc -Wall -O3 -o hex2bin hex2bin.c

entropy: entropy.c
	cc -Wall -O3 -o entropy entropy.c

xLFSR: xLFSR.c
	cc -Wall -O3 -o xLFSR xLFSR.c
