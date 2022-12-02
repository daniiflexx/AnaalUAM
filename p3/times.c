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


short average_search_time(pfunc_search metodo, pfunc_key_generator generator, int order, int N, int n_times, PTIME_AA ptime) 
{
  PDICT dic;
  int *perm, *keys, i;
  clock_t start, end;
  float avg;

  dic = init_dictionary(N, order);
  if (!dic)
    return ERR;
  
  perm = generate_perm(N);
  if (!perm) {
    free_dictionary(dic)
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
  for (i = 0; i < N*n_times; i++) {
    start = clock();
    if (metodo(dic) == ERR) {
      for (i < ptime->n_elems) {
        
      }
    }
    end = clock();
    avg += (float) start / end;
  }
}


short generate_search_times(pfunc_search method, pfunc_key_generator generator, int order, char* file, int num_min, int num_max, int incr, int n_times)
{
  return OK;
}