//Noorul Hasan Ali
//201851078

#include <stdio.h>
#include <string.h>

//works on single word plaintext, not yet implemented remove_spaces
//j not encoded

void printarray(char *arr) {
	for (int i=0; arr[i]!='\0'; i++)
		printf("%c ", arr[i]);
	printf("\n");
}
void printnumarr(int *arr, int len) {
	for (int i=0; i<len; i++)
		printf("%d ", arr[i]);
	printf("\n");
}
void printarrlen(char *arr, int len) {
	for (int i=0; i<len; i++)
		printf("%c ", arr[i]);
	printf("\n");
}
void printmatrix(char mat[5][5]) {
	for(int i=0; i<5; i++){
		for(int j=0; j<5; j++)
			printf("%c ", mat[i][j]);
		printf("\n");
	}
}
void removeDuplicatesFromKey(char *str) {
	char arr[26];
	char i;
	int j;
	for (i='A',j=0; i<='Z'; i++,j++) {
		arr[j]=i;
	}
	for(j=0; str[j]!='\0'; j++)	{
		if(arr[(int)(str[j]-'A') % 26]!= ' ')
			arr[(int)(str[j]-'A') % 26] = ' ';
		else
			str[j]=' ';
	}
	//printarray(str,8);
}
void createTable(char* key, char keytable[5][5]) {
	char arr[25];
	int j;
	char i;
	for (i='A',j=0; i<='Z'; i++,j++) {
		if(i!='J') {
			arr[j]=i;
		}
		else
			j--;
	}
	int p=0, q=0;
	for(j=0; key[j]!='\0'; j++)	{
		if(key[j]!='J'&&key[j]!=' ') {
			keytable[p][q]=key[j];
			q++;
			if(key[j]<'J')
				arr[(int)(key[j]-'A')] = (char)' ';
			else
				arr[(int)(key[j]-'A')-1] = (char)' ';
			if(q>4) {
				p++;
				q=0;
			}
		}
	}
	//printarray(arr,25);
	p=p%5;
	q=q%5;

	for(j=0; j<25; j++)	{
		if(arr[j]!=' ') {
			keytable[p][q]=arr[j];
			q++;
			if(q>4) {
				p++;
				q=0;
			}
		}
	}
}
void fixpt(char *pt) {
	// char x[100];
	// int j=0,i=0;
	// for(; pt[i]!='\0'; i++) {
	// 	if(pt[i]!=' ') {
	// 		x[j]=pt[i];
	// 		j++;
	// 	}
	// }
	// x[j]='\0';
	int len = strlen(pt);
	if(len%2!=0) {
		pt[len] = 'Z';
		pt[len+1] = '\0';
	}
}

void getIndex(char c, char keytable[5][5], int arr[2]) {
	for(int i=0; i<5; i++) {
		for(int j=0; j<5; j++)
			if(keytable[i][j]==c) {
				arr[0]=i;
				arr[1]=j;
			}
	}
}
void decrypt(char *ct, char keytable[5][5]) {
	for(int i=0; ct[i]!='\0'; i+=2) {
		if(ct[i]!='J' && ct[i+1]!='J') {
			int index_b[2], index_d[2];
			getIndex(ct[i],keytable,index_b);
			getIndex(ct[i+1],keytable,index_d);
			if(ct[i]!=ct[i+1]) {
				//SAME ROW DIFF COL
				if(index_b[0]==index_d[0]) {
					ct[i]=keytable[index_b[0]][(index_b[1]-1+5)%5];
					ct[i+1]=keytable[index_d[0]][(index_d[1]-1+5)%5];
				}
				else {
					//SAME COL DIFF ROW
					if(index_b[1]==index_d[1]) {
						ct[i]=keytable[(index_b[0]-1+5)%5][index_b[1]];
						ct[i+1]=keytable[(index_d[0]-1+5)%5][index_d[1]];

					}
					//DIFF ROW AND DIFF COL
					else {
						ct[i]=keytable[index_b[0]][index_d[1]];
						ct[i+1]=keytable[index_d[0]][index_b[1]];
					}
				}
			}
		}
	}
}

void encrypt(char *pt, char keytable[5][5]) {
	for(int i=0; pt[i]!='\0'; i+=2) {
		if(pt[i]!='J' && pt[i+1]!='J') {
			int index_b[2], index_d[2];
			getIndex(pt[i],keytable,index_b);
			getIndex(pt[i+1],keytable,index_d);
			if(pt[i]!=pt[i+1]) {
				//SAME ROW DIFF COL
				if(index_b[0]==index_d[0]) {
					pt[i]=keytable[index_b[0]][(index_b[1]+1)%5];
					pt[i+1]=keytable[index_d[0]][(index_d[1]+1)%5];
				}
				else {
					//SAME COL DIFF ROW
					if(index_b[1]==index_d[1]) {
						pt[i]=keytable[(index_b[0]+1)%5][index_b[1]];
						pt[i+1]=keytable[(index_d[0]+1)%5][index_d[1]];

					}
					//DIFF ROW AND DIFF COL
					else {
						pt[i]=keytable[index_b[0]][index_d[1]];
						pt[i+1]=keytable[index_d[0]][index_b[1]];
					}
				}
			}
		}
	}
}

int main() {
	char keystr[100],ptstr[100],keytable[5][5];
	char *key, *pt, *ct;

	printf("KEY: ");
	gets(keystr);

	printf("PLAINTEXT: ");
	gets(ptstr);

	key=strupr(keystr);
	pt=strupr(ptstr);
	removeDuplicatesFromKey(key);
	fixpt(pt);
	ct=pt;

	createTable(key,keytable);
	
	encrypt(ct,keytable);
	printf("CIPHERTEXT: %s\n", ct);
	decrypt(ct,keytable);
	printf("PLAINTEXT: %s\n", ct);

	return 0;
}