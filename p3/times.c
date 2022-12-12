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
#include "search.h"
#include "permutations.h"


short average_search_time(pfunc_search metodo, pfunc_key_generator generator, int order, int N, int n_times, PTIME_AA ptime) 
{
  PDICT dic;
  int *perm, *keys, i, pos = 0, ob = 0;
  int maxob = -2147483648, minob = 2147483647;
  clock_t start, end;
  float avg = 0, avgob = 0;

  dic = init_dictionary(N, order);
  if (!dic)
    return ERR;
  
  perm = generate_perm(N);
  if (!perm) {
    free_dictionary(dic);
    return ERR;
  }

  if (massive_insertion_dictionary(dic, perm, N) == ERR) {
    free_dictionary(dic);
    free(perm);
    return ERR;
  }

  keys = (int *) malloc(sizeof(int)*(N*n_times));
  if (!keys) {
    free_dictionary(dic);
    free(perm);
    return ERR;
  }

  uniform_key_generator(keys, N*n_times, N*n_times);
  ptime->N = N;
  ptime->n_elems = N*n_times;
  for (i = 0; i < ptime->n_elems; i++) 
  {
    start = clock();
    if ((ob = search_dictionary(dic, keys[i], &pos, metodo)) == ERR) {
      free_dictionary(dic);
      free(perm);
      free(keys);
      return ERR;
    }
    end = clock();
    if (ob <= minob)
      minob = ob;
    if (ob >= maxob)
      maxob = ob;
    avgob += ob;
    avg += (end - start);
  }
  ptime->time = (float) avg / ptime->n_elems;
  ptime->average_ob = (float) avgob / ptime->n_elems;
  ptime->max_ob = maxob;
  ptime->min_ob = minob;
  free_dictionary(dic);
  free(perm);
  free(keys);
  return OK;
}


short generate_search_times(pfunc_search method, pfunc_key_generator generator, int order, char* file, int num_min, int num_max, int incr, int n_times)
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
    if (average_search_time(method, generator, order, i, n_times ,&times) == ERR)
      return ERR;
    if (save_time_table(file, &times, i) == ERR)
      return ERR;
  }
  return OK;
}

short save_time_table(char* file, PTIME_AA ptime, int n_times)
{
  FILE *f;

  f = fopen(file, "a+");
  if (!f)
    return ERR;
  fprintf(f, "%d %f\n", n_times, ptime->average_ob);
  fclose(f);
  return OK;
}
