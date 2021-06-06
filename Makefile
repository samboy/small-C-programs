all: bin2hex hex2bin

clean:
	rm -f bin2hex hex2bin *.exe

bin2hex: bin2hex.c
	cc -Wall -O3 -o bin2hex bin2hex.c

hex2bin: hex2bin.c
	cc -Wall -O3 -o hex2bin hex2bin.c
