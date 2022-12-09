/**
 *
 * Description: Implementation of functions for search
 *
 * File: search.c
 * Author: Carlos Aguirre and Javier Sanz-Cruzado
 * Version: 1.0
 * Date: 14-11-2016
 *
 */

#include "search.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
 *  Key generation functions
 *
 *  Description: Receives the number of keys to generate in the n_keys
 *               parameter. The generated keys go from 1 to max. The
 * 				 keys are returned in the keys parameter which must be 
 *				 allocated externally to the function.
 */
  
/**
 *  Function: uniform_key_generator
 *               This function generates all keys from 1 to max in a sequential
 *               manner. If n_keys == max, each key will just be generated once.
 */
void uniform_key_generator(int *keys, int n_keys, int max)
{
  int i;

  for(i = 0; i < n_keys; i++) keys[i] = 1 + (i % max);

  return;
}

/**
 *  Function: potential_key_generator
 *               This function generates keys following an approximately
 *               potential distribution. The smaller values are much more 
 *               likely than the bigger ones. Value 1 has a 50%
 *               probability, value 2 a 17%, value 3 the 9%, etc.
 */
void potential_key_generator(int *keys, int n_keys, int max)
{
  int i;

  for(i = 0; i < n_keys; i++) 
  {
    keys[i] = .5+max/(1 + max*((double)rand()/(RAND_MAX)));
  }

  return;
}

PDICT init_dictionary (int size, char order)
{
	PDICT dic;

  dic = (PDICT) malloc(sizeof(DICT));
  if (!dic)
    return NULL;

  dic->table = (int *) malloc(sizeof(int)*size);
  if (!dic->table) {
    free(dic);
    return NULL;
  }
  dic->size = size;
  dic->n_data = 0;
  dic->order = order;
  return dic;
}

void free_dictionary(PDICT pdict)
{
	if (!pdict)
    return;
  
  if (pdict->table != NULL)
    free(pdict->table);
  free(pdict);
}

int insert_dictionary(PDICT pdict, int key)
{
  int a, j;

	if (!pdict)
    return ERR;
  
  if (pdict->n_data == pdict->size) {
    if (realloc(pdict->table, sizeof(pdict->table)*2 + 100) == NULL) {
      free(pdict->table);
      return ERR;
    }
    pdict->size *= 2;
    pdict->size += 100;
  }
  a = 0; j = 0;
  pdict->table[++pdict->n_data - 1] = key;
  if (pdict->order == SORTED) {
    a = pdict->table[pdict->n_data-1];
    j = pdict->n_data-2;
    while (j >= 0 && pdict->table[j] > a) {
      pdict->table[j+1] = pdict->table[j];
      j--;
    }
    pdict->table[j+1] = a;
  }
  return OK;
}

int massive_insertion_dictionary (PDICT pdict,int *keys, int n_keys)
{
  int i;

	if (!pdict || !keys || n_keys <= 0)
    return ERR;
  
  i = 0;
  while (i < n_keys) {
    if (insert_dictionary(pdict, keys[i]) == ERR)
      return ERR;
    i++;
  }
  return OK;
}

int search_dictionary(PDICT pdict, int key, int *ppos, pfunc_search method)
{
  return method(pdict->table, 0, pdict->size - 1, key, ppos);
}


/* Search functions of the Dictionary ADT */
int bin_search(int *table,int F,int L,int key, int *ppos)
{
  int m = 0;
  int c = 0;

  if (!table || F > L || !ppos)
    return ERR;

  while(F <= L)
  {
    c++;
    m = (F+L)/2;
    if (table[m] == key)
    {
      (*ppos) = m;
      return c;
    }
    else if (key < table[m])
    {
      L = m--;
    }
    else
    {
      F = m++;
    }
  }

  (*ppos) = NOT_FOUND;
  return NOT_FOUND;
}

int lin_search(int *table,int F,int L,int key, int *ppos)
{
  int i;
  int j = 0;

	if (!table || !ppos)
    return ERR;
  
  i = 0;
  for (i = F; i <= L; i++) {
    if (table[i] == key) {
      *ppos = i;
      return i+1;
    }
  }
  *ppos = NOT_FOUND;
  while (j <= L) {
    printf("%d ", table[j++]);
  }
  printf("\n\n");
  return i;
}

int lin_auto_search(int *table,int F,int L,int key, int *ppos)
{
  int aux = 0;
  int c = 0;

  if (!table || F > L || !ppos) return ERR;

  if(table[0] == key)
  {
    (*ppos) = 0;
    return ++c; 
  }
  
  F++;
  while (F <= L) 
  {
    c++;
    if (table[F] == key)
    {
      aux = table[F];
      table[F] = table[F-1];
      table[F-1] = aux;
      (*ppos) = F;
      return ++c;
    }
    F++;
  } 
  return ERR;
}


