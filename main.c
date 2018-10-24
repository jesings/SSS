#include <stdio.h>
#include <stdlib.h>
#include "sieve.h"

int main(int argc, char * argv[]){
  int iterations = 1;
  int target = 1000000;
  if(argc > 1){
    target = atoi(argv[1]);
  }
  if(argc > 2){
    iterations = atoi(argv[2]);
  }


  int ans = 0;
  while(iterations>0){
    ans=sieve(target);
    iterations--;
    printf("The n=%d prime is %d\n", target, ans );

    //this is to modify which prime to
    //potentially avoid CPU caching
    target++;

  }
  return 0;

}
