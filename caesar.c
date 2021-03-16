//Noorul Hasan Ali
//201851078

#include<stdio.h>
 
void encrypt(char *m, int key) {
	char ch;
	int i;

	for(int i = 0; m[i] != '\0'; ++i){
		ch = m[i];
		
		if(ch >= 'a' && ch <= 'z'){
			ch = ch + key;
			
			if(ch > 'z'){
				ch = ch - 'z' + 'a' - 1;
			}
			
			m[i] = ch;
		}
		else if(ch >= 'A' && ch <= 'Z'){
			ch = ch + key;
			
			if(ch > 'Z'){
				ch = ch - 'Z' + 'A' - 1;
			}
			
			m[i] = ch;
		}
	}
}

void decrypt(char *m, int key) {
	char ch;
	int i;

	for(i = 0; m[i] != '\0'; ++i){
		ch = m[i];
		
		if(ch >= 'a' && ch <= 'z'){
			ch = ch - key;
			
			if(ch < 'a'){
				ch = ch + 'z' - 'a' + 1;
			}
			
			m[i] = ch;
		}
		else if(ch >= 'A' && ch <= 'Z'){
			ch = ch - key;
			
			if(ch < 'A'){
				ch = ch + 'Z' - 'A' + 1;
			}
			
			m[i] = ch;
		}
	}
}
int main()
{
	char message[100];
	int key;
	
	printf("Enter a message to encrypt: ");
	gets(message);
	printf("Enter key: ");
	scanf("%d", &key);
	//encrypt(message,key);
	printf("Encrypted message: %s\n", message);
	decrypt(message,key);
	printf("Decrypted message: %s\n", message);
	return 0;
}