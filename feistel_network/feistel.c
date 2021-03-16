//NOORUL HASAN ALI 201851078
//FEISTEL
#include<stdio.h>

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

unsigned int sbox(unsigned int n) {	//n<=15 (1111)
	unsigned int s[16];
	for(int i=0; i<16; i++)
		s[i]=(i+1)%16;
	return s[n];
}

unsigned long f0(unsigned long key, unsigned long r) {
	unsigned long output=0;
	unsigned long t = r ^ key;
	unsigned long mask[8] = {
		0xf0000000,
		0x0f000000,
		0x00f00000,
		0x000f0000,
		0x0000f000,
		0x00000f00,
		0x000000f0,
		0x0000000f,
	};
	unsigned int block[8];
	for(int i=0; i<8; i++) {
		block[i]=(mask[i]&t) >> ((7-i)*4);
		block[i]=sbox(block[i]);
		output |= block[i]<<((7-i)*4);
	}
	return output;
}
unsigned long long encryption(unsigned long long pt, unsigned long key) {
	unsigned long l0 = pt >> 32;
	unsigned long r0 = pt & 0xffffffff;
	unsigned long long output = r0;
	output = output << 32;
	output|= (l0 ^ f0(key,r0));
	return output;
}
unsigned long long decryption(unsigned long long ct, unsigned long key) {
	unsigned long l1 = ct >> 32;
	unsigned long r1 = ct & 0xffffffff;
	unsigned long long output = (r1 ^ f0(key,l1));
	output = output << 32;
	output = output | l1;
	return output;
}

int main() {
	
    unsigned long long int plaintext = 512353245213059126; //64 bit plaintext
   	unsigned long key = 22341221; // 32 bit key
  	unsigned long long ciphertext = encryption(plaintext,key);	//ciphertext
  	unsigned long long de_ct = decryption(ciphertext,key);	//decrypted ciphertext
  	if(de_ct == plaintext)
  		printf("Successful encryption\n");
	return 0;
}