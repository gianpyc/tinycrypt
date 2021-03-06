/**
  Copyright � 2017 Odzhan. All Rights Reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are
  met:

  1. Redistributions of source code must retain the above copyright
  notice, this list of conditions and the following disclaimer.

  2. Redistributions in binary form must reproduce the above copyright
  notice, this list of conditions and the following disclaimer in the
  documentation and/or other materials provided with the distribution.

  3. The name of the author may not be used to endorse or promote products
  derived from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY AUTHORS "AS IS" AND ANY EXPRESS OR
  IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT,
  INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE. */

#define F(a,b)for(a=0;a<b;a++)
#define R(v,n)(((v)<<(n))|((v)>>(64-(n))))
typedef unsigned long long W;
typedef unsigned char B;

void threefish(void*mk, void*data) {
    W c[8],i,j,r,*x=(W*)data,t,
      rc[2]=
      { 0x203a2e190517340eULL,
        0x20160c2125283910ULL };

    c[4]=0x1BD11BDAA9FC1A22ULL;
    
    // initialize key and tweak
    F(i,4)c[4]^=c[i]=((W*)mk)[i];
    F(i,2)c[i+5]=((W*)mk)[i+4];
    c[7]=c[5]^c[6];
    
    // apply 72 rounds
    for(i=0;;i++) {
      // add key every 4 rounds
      if((i&3)==0) {
        t=0;F(j,4)x[j]+=c[((i/4)+j)%5]+t,
        t=(j<2)?c[(((i/4)+j)%3)+5]:i/4;
      }
      if(i==72)break;
      // mixing function
      for(j=0;j<4;j+=2)
        r=((B*)rc)[(i%8)+(j<<2)],x[j]+=x[j+1],
        x[j+1]=R(x[j+1],r),x[j+1]^=x[j];
      // permute
      t=x[1],x[1]=x[3],x[3]=t;
    }
}

