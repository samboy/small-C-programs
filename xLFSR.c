// Public domain by Sam Trenholme 2021
// cc -o xLFSR xLFSR.c
#include <stdio.h>
#include <stdint.h>

// This is a Galoris LFSR with a twist: If the low bit is 0 (not 1), we
// can apply a mask.  Y is the XOR we apply to the 8-bit state if the low
// bit is 1; Z is the XOR we apply if the low bit is 0 (if we make Z 0, we
// have a standard Galoris LFSR)
int period(unsigned int y, unsigned int z) {
	uint8_t num;
	int count;
	num = 1;
	count = 0;
	while(count <= 256) {
		if(num & 1) {
			num >>= 1;
			num ^= y;
		} else {
			num >>= 1;
			num ^= z;
		}
		count++;
		if(num == 1) {
			break;
		}
	}
	return count;
}

int main() {
	int y, z;
	for(z = 0; z < 256; z++) {
		for(y = 0; y < 256; y++) {
			printf("%02x %02x %d\n",y,z,period(y,z));
		}
	}
}
