

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "sm4.h"

void bin2hex(char *s, void *p, int len) {
    int i;
    printf("%-10s : ", s);
    for (i=0; i<len; i++) {
      printf ("%02x ", ((uint8_t*)p)[i]);
    }
    printf("\n");
}

uint8_t tv_plain[]=
{ 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef,
  0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10 };

uint8_t tv_cipher2[]=
{ 0x59, 0x52, 0x98, 0xc7, 0xc6, 0xfd, 0x27, 0x1f,
  0x04, 0x02, 0xf8, 0x04, 0xc3, 0x3d, 0x3f, 0x66 };

uint8_t tv_cipher[]=  
{ 0x68, 0x1e, 0xdf, 0x34, 0xd2, 0x06, 0x96, 0x5e,
  0x86, 0xb3, 0xe9, 0x4f, 0x53, 0x6e, 0x42, 0x46 };
  
uint8_t tv_key[]=
{ 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef,
  0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10 };
  
void sm4(void*,void*);

int main(void)
{
  sm4_ctx  c;
  //uint32_t i;
  int      equ;
  
  //sm4_setkey(&c, tv_key, SM4_ENCRYPT);
  
  //for (i=0; i<1000000; i++) {
    sm4(tv_key, tv_plain);
  //}
  
  bin2hex("ciphertext", tv_cipher,16);
  bin2hex("result", tv_plain,16);
  equ = memcmp(tv_cipher, tv_plain, 16)==0;
  printf ("SM4 Test %s\n", equ ? "succeeded" : "failed");
  
  return 0;
}
