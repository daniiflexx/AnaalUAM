/**
 *
 * Descripcion: Implementation of time measurement functions
 *
 * Fichero: times.c
 * Autor: Carlos Aguirre Maeso
 * Version: 1.0
 * Fecha: 16-09-2019
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "times.h"
#include "sorting.h"
#include "permutations.h"


/***************************************************/
/*                                                 */
/* Function: AverageSortingTime Date: 21/10/2022   */
/* Authors: Daniel Birsan y Daniel Cruz            */
/*                                                 */
/* Input: A sorting method, perms and time DataStr.*/
/* pfunc_sort: sorting method                      */
/* int n_perms: number of permutations             */
/* int N: number of executions                     */
/* PTIME_AA: Time data structure                   */
/* Output: OK if everything ran correctly,         */
/*    otherwise ERR                                */
/* short: OK, ERR                                  */
/***************************************************/
short average_sorting_time(pfunc_sort metodo, 
                              int n_perms,
                              int N, 
                              PTIME_AA ptime)
{
  int **perms, **aux;
  int i, OB = 0, min_OB = 2147483647, max_OB = -2147483648;
  double av_OB = 0;
  clock_t begin, end;
  double time = 0.0;

  if (!metodo || n_perms < 0 || N < 0 || ptime == NULL)
    return ERR;
  perms = generate_permutations(n_perms, N);
  if (!perms)
    return ERR;
  aux = perms;
  for (i = 0; i < n_perms; i++) {
    SelectSort(*perms, 0, N - 1);
    begin = clock();
    if ((OB = metodo(*perms, 0, N - 1) ) == ERR) {
      for ( i = 0; i < n_perms; i++) {
        free(aux[i]);
      }
      free(aux);
      return ERR;
    }
    end = clock();
    av_OB += OB;
    if (OB <= min_OB)
      min_OB = OB;
    if (OB >= max_OB)
      max_OB = OB;
    time += (double) (end - begin);
    perms++;
  }
  
  av_OB /= n_perms;
  time /= n_perms;
  ptime->min_ob = min_OB;
  ptime->max_ob = max_OB;
  ptime->average_ob = av_OB;
  ptime->time = time / CLOCKS_PER_SEC;
  ptime->n_elems = n_perms;
  ptime->N = N;
  
  for ( i = 0; i < n_perms; i++)
  {
    free(aux[i]);
  }
  free(aux);
  return OK;
}

/***************************************************/
/*                                                 */
/* Function: GenerateSortingTimes Date: 21/10/2022 */
/* Authors: Daniel Birsan y Daniel Cruz            */
/*                                                 */
/* Input: A sorting method, OBs data and a file    */
/* pfunc_sort: sorting method                      */
/* int n_perms: number of permutations             */
/* int num_min: minimun number of OB               */
/* int num_max: maximum number of OB               */
/* char* file: file where data will be written     */
/* int incr: increase                              */
/* Output: OK if everything ran correctly,         */
/*    otherwise ERR                                */
/* short: OK, ERR                                  */
/***************************************************/
short generate_sorting_times(pfunc_sort method, char* file, 
                                int num_min, int num_max, 
                                int incr, int n_perms)
{
  int i;
  TIME_AA times;
  FILE *f;

  f = fopen(file, "w");
  if (!f)
    return ERR;
  fclose(f);
  for ( i = num_min; i <= num_max; i+=incr)
  {
    if (average_sorting_time(method, n_perms, i, &times) == ERR)
      return ERR;
    if (save_time_table(file, &times, i) == ERR)
      return ERR;
  }
  return OK;
}

/***************************************************/
/*                                                 */
/* Function: SaveTimeTable Date: 21/10/2022        */
/* Authors: Daniel Birsan y Daniel Cruz            */
/*                                                 */
/* Input: file, number of inputs and time DataStr. */
/* int n_times: number of times to write           */
/* PTIME_AA: Time data structure                   */
/* char* file: file where data is written          */
/* Output: OK if everything ran correctly,         */
/*    otherwise ERR                                */
/* short: OK, ERR                                  */
/***************************************************/

short save_time_table(char* file, PTIME_AA ptime, int n_times)
{
  FILE *f;

  f = fopen(file, "a+");
  if (!f)
    return ERR;
  fprintf(f, "%d %d\n", n_times, ptime->min_ob);
  fclose(f);
  return OK;
}
