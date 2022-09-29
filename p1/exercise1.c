/***********************************************/
/* Program: exercise1     Date:                */
/* Authors:                                    */
/*                                             */
/* Program that generates two random nunmbers  */
/* between two given numbers                   */
/*                                             */
/* Input: Command Line                         */
/* -limInf: lower limit                        */
/* -limSup: upper limit                        */
/* -numN: ammount of numbers                   */
/* Output: 0: OK, -1: ERR                      */
/***********************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "permutations.h"

int main(int argc, char** argv)
{
  int i, k;
  int *reps;
  unsigned int inf, sup, num, j;

  srand(time(NULL));

  if (argc != 7) {
    fprintf(stderr, "Input parameter error:\n\n");
    fprintf(stderr, "%s -limInf <int> -limSup <int> -numN <int>\n", argv[0]);
    fprintf(stderr, "Where:\n");
    fprintf(stderr, " -limInf : Lower limit.\n");
    fprintf(stderr, " -limSup : Upper limit.\n");
    fprintf(stderr, " -numN : ammout of mumbers to generate.\n");
    exit(-1);
  }
  /**printf("Practice no 1, Section 1\n");
  printf("Done by: Your names\n");
  printf("Grupo: Your group\n");*/

  /* check command line */
  for(i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-limInf") == 0) {
      inf = atoi(argv[++i]);
    } else if (strcmp(argv[i], "-limSup") == 0) {
      sup = atoi(argv[++i]);
    } else if (strcmp(argv[i], "-numN") == 0) {
      num = atoi(argv[++i]);
    } else {
      fprintf(stderr, "Wrong Parameter %s \n", argv[i]);
    }
  }
  reps = (int *) calloc((sup-inf+1), sizeof(int));
  if (!reps)
    return 1;

  /* print data */
  for(j = 0; j < num; j++) {
    k = random_num(inf, sup);
    if (k < 0)
      return 1;
    reps[k - inf]++;
  }
  for ( i = 0; i < sup - inf; i++)
    printf("%d          %d\n", i+inf, reps[i]);
  free(reps);
  return 0;
}

