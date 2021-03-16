//Noorul Hasan Ali
//201851078

#include<stdio.h>  

const int a = 17; //keys
const int b = 20;   

void encrypt(char* pt) 
{ 
    for (int i = 0; pt[i]!='\0'; i++) 
    { 
        if(pt[i]!=' ')  {
            pt[i] =  (char) ((((a * (pt[i]-'A') ) + b) % 26) + 'A'); // -A to get integers in [0,25],+A for 65 ASCII ENCODING
        }
    } 
} 
void decrypt(char* ct) 
{ 
    int a_inv = 0; 
    int test = 0; 
    for (int i = 0; i < 26; i++) // finding a inverse by trial and error
    { 
        test = (a * i) % 26; 
        if (test == 1) {
            a_inv = i;
            break;
        }
    } 
    for (int i = 0; ct[i]!='\0'; i++) 
    { 
        if(ct[i]!=' ') {
            ct[i] =  (char) (((a_inv * ((ct[i]-'A' - b + 26)) % 26)) + 'A');   //adding 26 for negative numbers, adding 26 then modulo 26 has no overall effect
        }
    } 
} 
 
int main() 
{ 
    char text[100];
    gets(text);
    encrypt(text); 
    printf("Encrypted Message is : %s\n",text); 
    decrypt(text);
    printf("Decrypted Message is : %s\n",text); 
  
    return 0; 
} 