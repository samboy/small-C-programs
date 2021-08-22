// Public domain.  By Sam Trenholme, 2021
// Generate 160 bits of entropy as 32 ASCII bytes.  Use -DMINGW when
// compiling as a native Windows binary via MinGW

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#ifdef MINGW
#include <winsock.h>
#include <wincrypt.h>
#endif // MINGW

int main() {
	char noise[23];
	// Gather 20 bytes of raw entropy from the underlying OS
#ifndef MINGW
	// Linux/UNIX/MaxOS use /dev/urandom for entropy
        int a = 0;
        FILE *rfile = NULL;
        rfile = fopen("/dev/urandom","rb");
        if(rfile == NULL) {
                printf("You do not have /dev/urandom");
                printf("I refuse to run under these conditions");
                exit(1);
        }
        for(a=0;a<20;a++) {
                int b;
                b = getc(rfile);
                noise[a] = b;
        }
        noise[20] = 0;
#else // MINGW
	// Windows uses its own thing for entropy
        HCRYPTPROV CryptContext;
        int q;
        q = CryptAcquireContext(&CryptContext, NULL, NULL, PROV_RSA_FULL,
                CRYPT_VERIFYCONTEXT);
        if(q == 1) {
                q = CryptGenRandom(CryptContext, 20, noise);
        }
        if(q == 0) {
                printf("I can not generate strong random numbers");
                printf("I refuse to run under these conditions");
                exit(1);
        }
        CryptReleaseContext(CryptContext,0);
	noise[20] = 0;
#endif
	// Quick and dirty conversion of five 8-bit numbers in to
	// eight ASCII 5-bit numbers
	int count,subCount;
	char toAscii[34];
	// Each count "tick" is 5 bytes in the source noise and 8
	// bytes in destination string
	for(count = 0 ; count < 4; count++) {
		toAscii[count * 8] = noise[count * 5] & 31;
		toAscii[count * 8 + 1] =
			((noise[count * 5] & 0xe0) >> 5) |
			((noise[count * 5 + 1] & 3) << 3);
		toAscii[count * 8 + 2] = (noise[count * 5 + 1] & 0x7c) >> 2;
		toAscii[count * 8 + 3] =
			((noise[count * 5 + 1] & 0x80) >> 7) |
			((noise[count * 5 + 2] & 15) << 1);
		toAscii[count * 8 + 4] =
			((noise[count * 5 + 2] & 0xf0) >> 4) |
			((noise[count * 5 + 3] & 1) << 4);
		toAscii[count * 8 + 5] = (noise[count * 5 + 3] & 0x3e) >> 1;
		toAscii[count * 8 + 6] =
			((noise[count * 5 + 3] & 0xc0) >> 6) |
			((noise[count * 5 + 4] & 7) << 2);
		toAscii[count * 8 + 7] = (noise[count * 5 + 4] & 0xf8) >> 3;
		for(subCount = 0; subCount < 8; subCount++) {
			// This is a very simple 5-bit binary to ASCII
			// conversion; it's a very compact way of
			// representing "23456789abcdefghijklmnopqrstuvwx"
			char i;
			i = toAscii[count * 8 + subCount];
			i+=i<8?50:89;
			toAscii[count * 8 + subCount] = i;
		}
	}
	toAscii[32] = 0;
	printf("%s",toAscii);
}
