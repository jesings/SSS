#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <time.h>
#include <sys/types.h>
#define MAINLOOP() asm volatile( \
                ".marksieve%=:\n\t" \
                "movl %0, %%r10d\n\t" \
                "shrl $4, %%r10d\n\t" \
                "cmpl %4, %%r10d\n\t" \
                "jnl .endsloop%=\n\t" \
                "movl %0, %%ecx\n\t" \
                "andl $0xf, %%ecx\n\t" \
                "shrl %%ecx\n\t" \
                "movl $1, %%r8d\n\t" \
                "shll %%cl, %%r8d\n\t" \
                "orb %%r8b, (%3, %%r10)\n\t" \
                "addl %1, %0\n\t" \
                "movl %1, %%r10d\n\t" \
                "movl %2, %1\n\t" \
                "movl %%r10d, %2\n\t" \
                "jmp .marksieve%=\n\t" \
                ".endsloop%=:" \
                : "+r" (mult), "+r" (dprime), "+r" (qprime) \
                : "r" (c), "r" (len) \
                : "%rcx", "%r8", "%r10" \
           );
#define MAINLOOPC() for(unsigned int tmp; mult>>4 < len ;){ \
            c[mult>>4] |= 1<<((mult&0xf)>>1); \
            mult += dprime; \
            tmp = dprime; \
            dprime = qprime; \
            qprime = tmp; \
        }
struct markinfo{
    unsigned int len;
    unsigned char* c;
    unsigned int nno;
    unsigned int n[16];
};
void* markthread(void* mi2){
    struct markinfo* mi = (struct markinfo*) mi2;
    unsigned int len = mi->len;
    unsigned char* c = mi->c;
    unsigned int cprime;
    unsigned int dprime;
    unsigned int qprime;
    unsigned int mult;
    for(int i = 0; i < mi->nno; i++){
        cprime = mi->n[i];
        mult = cprime;
        dprime = cprime * 4;
        qprime = cprime * 2;
        MAINLOOP();
    }
};
int sieve(unsigned int max){
    unsigned const int len = ((int) (max * log(max) + max * (log(log(max)) - .9385))) >> 4;
    unsigned char* c = malloc(len);
    unsigned int nprime = 34;
    unsigned int cprime = 149;
    unsigned int dprime;
    unsigned int qprime;
    unsigned int mult;
    struct markinfo m2 = {len, c, 3, {5, 17, 23}};
    struct markinfo m3 = {len, c, 4, {7, 11, 13, 31}};
    struct markinfo m4 = {len, c, 10, {29, 37, 101, 103, 107, 109, 113, 127, 131, 137}};
    struct markinfo m5 = {len, c, 7, {41, 43, 47, 53, 59, 61, 67}};
    struct markinfo m6 = {len, c, 7, {71, 73, 79, 83, 89, 97, 19}};
    pthread_t p1, p2, p3, p4, p5, p6;
    pthread_create(&p2, NULL, markthread, &m2);
    pthread_create(&p3, NULL, markthread, &m3);
    pthread_create(&p4, NULL, markthread, &m4);
    pthread_create(&p5, NULL, markthread, &m5);
    pthread_create(&p6, NULL, markthread, &m6);
    pthread_join(p2, NULL);
    pthread_join(p3, NULL);
    pthread_join(p4, NULL);
    pthread_join(p5, NULL);
    pthread_join(p6, NULL);

    while(nprime < max){
        mult = cprime;
        dprime = cprime * 4;
        qprime = cprime * 2;
        MAINLOOP();
        //while(c[(cprime+=2)>>3] & (1 << (cprime&0x7))) ;
        dprime = (cprime%3)==1?4:2;
        asm volatile(
                ".nprloop%=:\n\t"
                "addl %1, %0\n\t"
                "xor $6, %1\n\t"
                "movl %0, %%r10d\n\t"
                "shrl $4, %%r10d\n\t"
                "movl (%2, %%r10), %%r10d\n\t"
                "movl %0, %%ecx\n\t"
                "andl $0xf, %%ecx\n\t"
                "shrl %%ecx\n\t"
                "movl $1, %%r8d\n\t"
                "shll %%cl, %%r8d\n\t"
                "andb %%r8b, %%r10b\n\t"
                "jnz .nprloop%=\n\t"
                : "+r" (cprime), "+r" (dprime)
                : "r" (c)
                : "%rcx", "%r8", "%r10"

            );
        ++nprime;
    }
    return cprime;
}
