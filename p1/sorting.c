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

/***************************************************/
/* Function: SelectSort    Date:                   */
/* Your comment                                    */
/***************************************************/
int SelectSort(int* array, int ip, int iu)
{
  int i, minim, aux;

  if (!array || ip < 0 || ip > iu)
    return ERR;

  for(i = ip; i < iu; i++)
  {
    minim  = min(array, i, iu);
    if (minim < 0)
      return ERR;
    aux = array[i];
    array[i] = array[minim];
    array[minim] = aux;
  }
  return (i - ip);
}

/*int SelectSortInv(int* array, int ip, int iu)
{
  
}*/

int min(int* array, int ip, int iu)
{
  int i;
  int minim;

  if (!array || ip < 0 || ip > iu)
    return ERR;
  
  minim = ip;
  for(i = ip; i <= iu; i++)
  {
    if (array[i] < array[minim])
      minim = i;
  }
  return minim;
}

