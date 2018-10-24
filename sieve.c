#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int sieve(int max){//15485863
    const char bytebois[8] = {0x1,0x2,0x4,0x8,0x10,0x20,0x40,0x80};
    unsigned int guy = 5, primepos = 3, len = max*log(max)*23/20;
    unsigned char* sievy_boi = calloc(1,(len>>4));
    while(primepos++<max){
        char shifty = 1;
        for(unsigned int i = guy;i<len;i+=guy<<(1+shifty),shifty=!shifty)
            sievy_boi[(i>>4)] |= bytebois[(i>>1)&0x7];
        shifty = 2-guy%3;
        while(sievy_boi[((guy+=2<<shifty)>>4)]&bytebois[(guy>>1)&0x7]) shifty = !shifty;
    }
    return guy;
}
