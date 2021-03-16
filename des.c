#include<stdio.h>
#include<stdint.h>

void printBits(size_t const size, void const * const ptr)
{
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;
    
    for (i = size-1; i >= 0; i--) {
        for (j = 7; j >= 0; j--) {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
        }
    }
    puts("");
}

uint8_t sbox(uint8_t n, int i) {	//n<=15 (1111)
	uint8_t s[8][16] = {
		{14, 7, 2, 8, 0, 4, 1, 6, 13, 12, 15, 3, 11, 10, 9, 5},
		{2, 10, 15, 7, 0, 5, 3, 1, 9, 6, 4, 11, 13, 14, 8, 12},
		{2, 1, 6, 4, 15, 14, 12, 11, 10, 5, 3, 8, 0, 7, 13, 9},
		{14, 3, 9, 13, 10, 6, 11, 5, 0, 1, 12, 15, 8, 2, 7, 4},
		{10, 4, 11, 2, 3, 7, 1, 5, 12, 6, 9, 15, 13, 14, 8, 0},
		{1, 10, 0, 14, 3, 8, 9, 5, 11, 13, 6, 4, 15, 2, 7, 12},
		{8, 6, 13, 3, 14, 7, 12, 4, 9, 1, 11, 0, 5, 10, 2, 15},
		{6, 2, 9, 7, 1, 15, 12, 0, 11, 13, 10, 4, 3, 14, 8, 5},
	};
	if(n<16) 
		return s[i][n];
	else
		return 0;
}

unsigned long f0(uint32_t key, uint32_t r) {
	uint32_t output=0;
	uint32_t t = r ^ key;
	uint32_t mask[8] = {
		0xf0000000,
		0x0f000000,
		0x00f00000,
		0x000f0000,
		0x0000f000,
		0x00000f00,
		0x000000f0,
		0x0000000f,
	};
	uint8_t block[8];
	for(int i=0; i<8; i++) {
		block[i]=(uint8_t)(mask[i]&t) >> ((7-i)*4);
		block[i]=sbox(block[i],i);
		output |= block[i]<<((7-i)*4);
	}
	return output;
}
uint64_t initperm(uint64_t pt) {
	uint64_t output=0;
	char bitarray[64] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
	unsigned int pbox[64] = {	4, 50, 14, 37, 47, 55, 20, 3, 8, 27, 29, 12, 38, 28, 31, 15,
								21, 58, 42, 13, 18, 26, 36, 44, 59, 19, 30, 43, 34, 57, 33, 22,
								48, 2, 54, 40, 16, 62, 1, 61, 6, 63, 35, 49, 41, 10, 23, 52,
								51, 0, 56, 32, 9, 25, 7, 5, 53, 45, 39, 24, 11, 17, 60, 46	};
	for (int i=0; i<64; i++) {
		unsigned char bit = (char)(pt >> (63 - pbox[i])) & (long long)1;
		bitarray[pbox[i]] = bit;
	}
	for (int i=0; i<63; i--) {
		output |= bitarray[i];
		if(i!=63)
			output = output << 1;
	}
	return output; 
}
uint64_t finalperm(uint64_t pt) {
	uint64_t output=0;
	char bitarray[64]={-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
	unsigned int pbox[64] = {	49, 38, 33, 7, 0, 55, 40, 54, 8, 52, 45, 60, 11, 19, 2, 15,
								36, 61, 20, 25, 6, 16, 31, 46, 59, 53, 21, 9, 13, 10, 26, 14,
								51, 30, 28, 42, 22, 3, 12, 58, 35, 44, 18, 27, 23, 57, 63, 4,
								32, 43, 1, 48, 47, 56, 34, 5, 50, 29, 17, 24, 62, 39, 37, 41	};
	for (int i=0; i<64; i++) {
		unsigned char bit = (char)(pt >> (63 - pbox[i])) & (long long)1;
		bitarray[pbox[i]] = bit;
	}
	for (int i=0; i<63; i--) {
		output |= bitarray[i];
		if(i!=63)
			output = output << 1;
	}
	return output; 
}
uint64_t encryption(uint64_t pt, uint32_t key) {
	uint64_t ct = initperm(pt);
	//use key schedule array
	//implement more complicated permutation

	for (int i=0; i<16; i++) {
		uint32_t l0 = ct >> 32;
		uint32_t r0 = ct & 0xffffffff;
		uint64_t output = r0;
		output = output << 32;
		output|= (l0 ^ f0(key,r0));
		ct=output;
	}
	
	ct=finalperm(ct);
	return ct;
}
uint64_t decryption(uint64_t ct, uint32_t key) {
	uint64_t pt = finalperm(ct);
	for(int i=0; i<16; i++) {
		uint32_t l1 = pt >> 32;
		uint32_t r1 = pt & 0xffffffff;
		uint64_t output = (r1 ^ f0(key,l1));
		output = output << 32;
		output = output | l1;
		pt=output;
	}
	pt=initperm(pt);
	return pt;
}

int main() {
	
    uint64_t plaintext = 512353245213059126; //64 bit plaintext
   	uint32_t key = 22341221; // 32 bit key
  	uint64_t ciphertext = encryption(plaintext,key);	//ciphertext
  	uint64_t de_ct = decryption(ciphertext,key);	//decrypted ciphertext
  	printf("%lld \n", ciphertext);
  	if(de_ct == plaintext)
  		printf("Successful encryption\n");
	return 0;
}

//23 22 4 10 0 13 7 26 15 18 24 31 25 19 21 9 16 27 28 30 11 3 29 17 2 5 1 6 8 20 14 12   # random permutation