//NOORUL HASAN ALI 201851078

#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include<inttypes.h>
unsigned long long expand(unsigned long val) {
    unsigned long long last=(val&1)<<32;
    unsigned long long first=val>>31;
    val=val|last; //33bit
    val=(val<<1)|first; //34bit
    //32 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 1
    
    //32  1  2  3  4  5
    //4   5  6  7  8  9 
    //8   9 10 11 12 13 
    //12 13 14 15 16 17
    //16 17 18 19 20 21
    //20 21 22 23 24 25
    //24 25 26 27 28 29
    //28 29 30 31 32 1
    
    unsigned long long temp=0,ans=0;
    for(int i=0;i<8;i++)
    {
    temp=(val&(63<<4*i))<<2*i;//
    ans=ans|temp;
    }
    return ans;
}
unsigned long sbox(unsigned long long val)
{
    unsigned long b[8];
    unsigned long t2=val & 16777215;
    unsigned long t1=val >> 24;
    unsigned long t12=t1 & 4095;
    unsigned long t11=t1 >> 12;
    unsigned long t22=t2 & 4095;
    unsigned long t21=t2 >>12;
     b[1]=t11 & 63;
     b[0]=t11 >> 6;
     b[3]=t12 & 63;
     b[2]=t12 >> 6;
     b[5]=t21 & 63;
     b[4]=t21 >> 6;
     b[7]=t22 & 63;
     b[6]=t22 >> 6;
    

    int s[8][4][16] = { { 14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7, 
                          0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8, 
                          4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0, 
                          15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13 },

                        { 15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10, 
                          3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5, 
                          0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15, 
                          13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9 }, 
  
                        { 10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8, 
                          13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1, 
                          13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7, 
                          1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12 },

                        { 7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15, 
                          13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9, 
                          10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4, 
                          3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14 },

                        { 2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9, 
                          14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6, 
                          4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14, 
                          11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3 },

                        { 12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11, 
                          10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8, 
                          9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6, 
                          4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13 },

                        { 4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1, 
                          13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6, 
                          1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2, 
                          6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12 },

                        { 13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7, 
                          1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2, 
                          7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8, 
                          2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11 } 
                    };
    
    //box1=b1b2b3b4b5b6 r=2*b1+b6 ,col=b2b3b4b5
    int row=0;
    int col=0;
    unsigned long ans=0;
    for(int i=0;i<8;i++)
    {
        row=(b[i]>>5)*2+b[i]&1;
        col=(b[i]>>1)&15;
        ans=s[i][row][col]>>(28-4*i)|ans;
    }
return ans;
}
unsigned long permute(unsigned long val)
{
    unsigned long ans=0;
    int per[32] = { 16, 7, 20, 21, 
                    29, 12, 28, 17, 
                    1, 15, 23, 26, 
                    5, 18, 31, 10, 
                    2, 8, 24, 14, 
                    32, 27, 3, 9, 
                    19, 13, 30, 6, 
                    22, 11, 4, 25 };
    for(int i=0;i<32;i++)
    {
    ans=ans|(((val>>(32-per[i]))&1)<<(31-i));
    }
    return ans;
}
unsigned long f(unsigned long r0,unsigned long long key)
{
    unsigned long long temp=expand(r0);//r0 was 32 bit converting it in 48 bit
    temp=temp^key;
    temp=sbox(temp);
    temp=permute(temp);
    return temp;
}
unsigned long long en(unsigned long long pt,unsigned long key)
{
    unsigned long l0=pt>>32;
    unsigned long r0=pt & 0xffffffff;
    unsigned long l1=r0;
    unsigned long y0=f(r0,key);
    unsigned long r1=l0 ^ y0;
    unsigned long long ans=(l1<<32)|r1;
    return ans;

}
int main()
{
    unsigned long long pt= 39;//1025872731371558909; // 64 bit plain text
    unsigned long long key=12;//252192837533951; //48 bit key
    unsigned long long ans=en(pt,key);
    printf("%lld \n",ans);
    printf("\n");
}