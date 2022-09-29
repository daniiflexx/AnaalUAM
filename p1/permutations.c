/**
 *
 * Descripcion: Implementation of function that generate permutations
 *
 * File: permutations.c
 * Autor: Carlos Aguirre
 * Version: 1.1
 * Fecha: 21-09-2019
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "permutations.h"

/***************************************************/
/* Function: random_num Date:                      */
/* Authors: Daniel Birsan y Daniel Cruz            */
/*                                                 */
/* Rutine that generates a random number           */
/* between two given numbers                       */
/*                                                 */
/* Input: Upper and lower limits as parameters     */
/* int inf: lower limit                            */
/* int sup: upper limit                            */
/* Output: Generated rand number                   */
/* int: random number                              */
/***************************************************/
int random_num(int inf, int sup)
{
  if (inf > sup || inf < 0)
    return -1;

  return ((rand() % (sup - inf)) + inf);
}

/***************************************************/
/* Function: generate_perm Date:                   */
/* Authors:                                        */
/*                                                 */
/* Rutine that generates a random permutation      */
/*                                                 */
/* Input:                                          */
/* int n: number of elements in the permutation    */
/* Output:                                         */
/* int *: pointer to integer array                 */
/* that contains the permitation                   */
/* or NULL in case of error                        */
/***************************************************/
int* generate_perm(int N)
{
  int i, *perm, n, n2;

  if (N <= 0)
    return (NULL);

  perm = (int *)calloc(sizeof(int), (N));
  if (!perm)
    return NULL;

  for ( i = 0; i < N; i++)
    perm[i] = i;

  for ( i = 0; i < N; i++)
  {
    n = perm[i];
    n2 = random_num(i, N);
    if (n2 < 0){
      free(perm);
      return NULL;
    }
    perm[i] = perm[n2];
    perm[n2] = n;
  }
  return perm;
}

/***************************************************/
/* Function: generate_permutations Date:           */
/* Authors:                                        */
/*                                                 */
/* Function that generates n_perms random          */
/* permutations with N elements                    */
/*                                                 */
/* Input:                                          */
/* int n_perms: Number of permutations             */
/* int N: Number of elements in each permutation   */
/* Output:                                         */
/* int**: Array of pointers to integer that point  */
/* to each of the permutations                     */
/* NULL en case of error                           */
/***************************************************/
int** generate_permutations(int n_perms, int N)
{
	int **perms, i, j;
  if (n_perms <= 0 || N <= 0)
		return NULL;

	perms = (int **) malloc(sizeof(int*)*n_perms);
	if (!perms)
		return NULL;
	
	for ( i = 0; i < n_perms; i++) {
		perms[i] = generate_perm(N);
    if (!perms[i]) {
      for (j = 0; j < i; j++) {
        free(perms[j]);
      }
      free(perms);
      return NULL;
    }
  }
	return perms;
}
