#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int sieve(int max){//15485863
    unsigned int guy = 5, primepos = 3, len = max*log(max)*23/20;
    unsigned char sievy_boi[len>>4];
    while(primepos++<max){
        char shifty = 1;
        for(unsigned int i = guy;i<len;i+=guy<<(1+shifty),shifty=!shifty)
            sievy_boi[(i>>4)] |= 1 <<((i>>1)&0x7);
        shifty = 2-guy%3;
        while(sievy_boi[((guy+=2<<shifty)>>4)]&(1 <<((guy>>1)&0x7))) shifty = !shifty;
    }
    return guy;
}
