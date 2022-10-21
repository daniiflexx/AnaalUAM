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
