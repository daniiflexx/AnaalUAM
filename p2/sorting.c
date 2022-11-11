/**
 *
 * Descripcion: Implementation of sorting functions
 *
 * Fichero: sorting.c
 * Autor: Carlos Aguirre
 * Version: 1.0
 * Fecha: 16-09-2019
 *
 */


#include "sorting.h"
#include <stdio.h>
/***************************************************/
/* Function: SelectSort Date: 21/10/2022           */
/* Authors: Daniel Birsan y Daniel Cruz            */
/*                                                 */
/* Sorts increasingly                              */
/* a given array                                   */
/*                                                 */
/* Input: An array and its first and last indexes  */
/* int *array: the array                           */
/* int ip: first index of the array                */
/* int iu: last index of the array                 */
/* Output: Number of iterated OB                   */
/* int: OB times                                   */
/***************************************************/
int SelectSort(int* array, int ip, int iu)
{
  int i, minim, aux, x;

  if (!array || ip < 0 || ip > iu)
    return ERR;
  
  minim = 0;
  for(i = ip, x = 0; i < iu; i++)
  {
    x += iu - i;
    minim  = min(array, i, iu);
    if (minim == ERR)
      return ERR;
    aux = array[i];
    array[i] = array[minim];
    array[minim] = aux;
  }
  return (x);
}

/***************************************************/
/* Function: SelectSort Date: 21/10/2022           */
/* Authors: Daniel Birsan y Daniel Cruz            */
/*                                                 */
/* Sorts decreasingly                              */
/* a given array                                   */
/*                                                 */
/* Input: An array and its first and last indexes  */
/* int *array: the array                           */
/* int ip: first index of the array                */
/* int iu: last index of the array                 */
/* Output: Number of iterated OB                   */
/* int: OB times                                   */
/***************************************************/
int SelectSortInv(int *array, int ip, int iu)
{
  int i, maxim, aux, x;
  
  if (!array || ip < 0 || ip > iu)
    return ERR;

  for (i = ip, x = 0; i < iu; i++)
  {
    x += iu - i;
    
    maxim = max(array, i, iu);
    if (maxim == ERR)
      return ERR;
    
    aux = array[i];
    array[i] = array[maxim];
    array[maxim] = aux;
  }

  return x;
}

/***************************************************/
/* Function: min Date: 21/10/2022                  */
/* Authors: Daniel Birsan y Daniel Cruz            */
/*                                                 */
/* Returns the minimum from                        */
/* a given array                                   */
/*                                                 */
/* Input: An array and its first and last indexes  */
/* int *array: the array                           */
/* int ip: first index of the array                */
/* int iu: last index of the array                 */
/* Output: minimum of the array                    */
/* int: the minimum                                */
/***************************************************/
int min(int* array, int ip, int iu)
{
  int i = 0;
  int minim = 0;

  if (!array || ip < 0 || ip > iu)
    return ERR;

  minim = ip;
  for(i = ip + 1; i <= iu; i++)
  {
    if (array[i] < array[minim])
      minim = i;
  }
  return minim;
}

/***************************************************/
/* Function: max Date: 21/10/2022                  */
/* Authors: Daniel Birsan y Daniel Cruz            */
/*                                                 */
/* Returns the maximum from                        */
/* a given array                                   */
/*                                                 */
/* Input: An array and its first and last indexes  */
/* int *array: the array                           */
/* int ip: first index of the array                */
/* int iu: last index of the array                 */
/* Output: maximum of the array                    */
/* int: the maximum                                */
/***************************************************/
int max(int *array, int ip, int iu)
{
  int i;
  int minim;

  if (!array || ip < 0 || ip > iu)
    return ERR;
  
  minim = ip;
  
  for (i = ip + 1; i <= iu; i++)
  {
    if (array[i] > array[minim])
      minim = i;
  }
  
  return minim;
}

int quicksort(int* tabla, int ip, int iu)
{
  int n;
  int m;

  n = 0;
  if (ip > iu)
    return ERR;

  if (ip == iu)
    return n;
  else 
  {
    n += partition(tabla, ip, iu, &m);
    if (ip < m - 1)
    n += quicksort(tabla, ip, m - 1);
    if(m + 1 < iu)
    n += quicksort(tabla, m + 1, iu);
  }
  return n;
}

int partition(int* tabla, int ip, int iu,int *pos)
{
  int i, n, k, aux;
  
  n = 0;
  n = median(tabla, ip, iu, pos);
  k = tabla[*pos];
  tabla[*pos] = tabla[ip];
  tabla[ip] = k;
  *pos = ip;
  for (i = ip+1; i <= iu; i++) 
  {
    if (tabla[i] < k)
    {
      (*pos)++;
      aux = tabla[i];
      tabla[i] = tabla[*pos];
      tabla[*pos] = aux;
    }
    aux = tabla[*pos];
    n++;
  }
  tabla[*pos] = tabla[ip];
  tabla[ip] = aux;
  return n;
}

int median(int *tabla, int ip, int iu,int *pos)
{
  *pos = ip;
  return (0);
}

int median_avg(int *tabla, int ip, int iu, int *pos) {
  *pos = (ip + iu)/2;
  return (0);
}

int median_stat(int *tabla, int ip, int iu, int *pos) {
  median_avg(tabla, ip, iu, pos);
  if ((tabla[iu] > tabla[*pos] && tabla[ip] > tabla[iu]) || (tabla[iu] > tabla[ip] && tabla[*pos] > tabla[iu])) {
    *pos = iu;
    return (4);
  }
  if ((tabla[ip] > tabla[*pos] && tabla[iu] > tabla[ip]) || (tabla[ip] > tabla[iu] && tabla[*pos] > tabla[ip]))
    *pos = ip;
  return (8);
}