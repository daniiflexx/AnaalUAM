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
/* Function: SelectSort    Date:                   */
/* Your comment                                    */
/***************************************************/
int SelectSort(int* array, int ip, int iu)
{
  int i, minim, aux, x, count;
  count = 0;
  if (!array || ip < 0 || ip > iu)
    return ERR;
  for(i = ip, x = 0; i < iu; i++)
  {
    x += iu - i;
    minim  = min(array, i, iu, &count);
    if (minim < 0)
      return ERR;
    aux = array[i];
    array[i] = array[minim];
    array[minim] = aux;
  }
  return (count);
}

/*int SelectSortInv(int* array, int ip, int iu)
{
  
}*/

int min(int* array, int ip, int iu, int *count)
{
  int i;
  int minim;

  if (!array || ip < 0 || ip > iu)
    return ERR;
  minim = ip;
  for(i = ip + 1; i <= iu; i++)
  {
    if (array[i] < array[minim])
      minim = i;
    (*count)++;
  }
  return minim;
}

