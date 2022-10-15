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

#include "times.h"
#include "sorting.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "times.h"
#include "sorting.h"
#include "permutations.h"

/***************************************************/
/* Function: average_sorting_time Date:            */
/*                                                 */
/* Your documentation                              */
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
  ptime->time = time;
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
/* Function: generate_sorting_times Date:          */
/*                                                 */
/* Your documentation                              */
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
  fprintf(f, "EXERCISE 5\n");
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
/* Function: save_time_table Date:                 */
/*                                                 */
/* Your documentation                              */
/***************************************************/
short save_time_table(char* file, PTIME_AA ptime, int n_times)
{
  FILE *f;

  f = fopen(file, "a+");
  if (!f)
    return ERR;
  fprintf(f, "SIZE: %d:\nAverage time: %f\nAverage OB: %f\nMax_ob: %d\nMin_ob:%d\n\n", n_times, ptime->time, ptime->average_ob, ptime->max_ob, ptime->min_ob);
  fclose(f);
  return OK;
}
