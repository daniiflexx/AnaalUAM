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
#include <stdlib.h>
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

/***************************************************/
/* Function: quicksort Date: 21/10/2022            */
/* Authors: Daniel Birsan y Daniel Cruz            */
/*                                                 */
/* sorts the array                                 */
/*                                                 */
/* Input: An array and its first and last indexes  */
/* int *tabla: the array                           */
/* int ip: first index of the array                */
/* int iu: last index of the array                 */
/* Output: OB count or error                       */
/* int: the maximum                                */
/***************************************************/
int quicksort(int* tabla, int ip, int iu)
{
  int n;
  int m;

  n = 0;
  if (ip > iu || !tabla || ip < 0)
    return ERR;

  if (ip == iu)
    return n;
  else 
  {
    n += partition(tabla, ip, iu, &m);
    if (n == ERR)
      return ERR;
    if (ip < m - 1) {
      n += quicksort(tabla, ip, m - 1);
      if (n == ERR)
        return ERR;
    }
    if(m + 1 < iu) {
      n += quicksort(tabla, m + 1, iu);
      if (n == ERR)
        return ERR;
    }
  }
  return n;
}

/***************************************************/
/* Function: partition Date: 21/10/2022            */
/* Authors: Daniel Birsan y Daniel Cruz            */
/*                                                 */
/* partition of the array                          */
/*                                                 */
/* Input: An array and its first and last indexes  */
/* int *tabla: the array                           */
/* int ip: first index of the array                */
/* int iu: last index of the array                 */
/* Output: number of OB                            */
/* int: OB                                         */
/***************************************************/
int partition(int* tabla, int ip, int iu, int *pos)
{
  int i, n, k, aux;
  
  if (!tabla || !pos || ip < 0 || ip > iu)
    return ERR;

  n = 0;
  n = median_stat(tabla, ip, iu, pos);
  if (n == ERR)
    return ERR;
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

/***************************************************/
/* Function: median Date: 21/10/2022               */
/* Authors: Daniel Birsan y Daniel Cruz            */
/*                                                 */
/* median pivot                                    */
/*                                                 */
/* Input: An array and its first and last indexes  */
/* int *tabla: the array                           */
/* int ip: first index of the array                */
/* int iu: last index of the array                 */
/* int *pos: pivot                                 */
/* Output: number of OB                            */
/* int: OB                                         */
/***************************************************/
int median(int *tabla, int ip, int iu,int *pos)
{
  if (!pos || !tabla || ip < 0 || ip > iu)
    return ERR;
  *pos = ip;
  return (0);
}

/***************************************************/
/* Function: median_avg Date: 21/10/2022           */
/* Authors: Daniel Birsan y Daniel Cruz            */
/*                                                 */
/* median_avg pivot                                    */
/*                                                 */
/* Input: An array and its first and last indexes  */
/* int *tabla: the array                           */
/* int ip: first index of the array                */
/* int iu: last index of the array                 */
/* int *pos: pivot                                 */
/* Output: number of OB                            */
/* int: OB                                         */
/***************************************************/
int median_avg(int *tabla, int ip, int iu, int *pos) {
  if (!pos || !tabla || ip < 0 || ip > iu)
    return ERR;
  *pos = (ip + iu)/2;
  return (0);
}

/***************************************************/
/* Function: median_stat Date: 21/10/2022           */
/* Authors: Daniel Birsan y Daniel Cruz            */
/*                                                 */
/* median_stat pivot                               */
/*                                                 */
/* Input: An array and its first and last indexes  */
/* int *tabla: the array                           */
/* int ip: first index of the array                */
/* int iu: last index of the array                 */
/* int *pos: pivot                                 */
/* Output: number of OB                            */
/* int: OB                                         */
/***************************************************/
int median_stat(int *tabla, int ip, int iu, int *pos) {
  if (!pos || !tabla || ip < 0 || ip > iu)
    return ERR;

  *pos = (ip + iu)/2;
  if ((tabla[iu] > tabla[*pos] && tabla[ip] > tabla[iu]) || (tabla[iu] > tabla[ip] && tabla[*pos] > tabla[iu])) {
    *pos = iu;
    return (4);
  }
  if ((tabla[ip] > tabla[*pos] && tabla[iu] > tabla[ip]) || (tabla[ip] > tabla[iu] && tabla[*pos] > tabla[ip]))
    *pos = ip;
  return (8);
}

/***************************************************/
/* Function: MergeSort Date: 21/10/2022            */
/* Authors: Daniel Birsan y Daniel Cruz            */
/*                                                 */
/* sorts the array                                 */
/*                                                 */
/* Input: An array and its first and last indexes  */
/* int *tabla: the array                           */
/* int ip: first index of the array                */
/* int iu: last index of the array                 */
/* Output: OB count or error                       */
/* int: count                                      */
/***************************************************/
int MergeSort(int* tabla, int ip, int iu){
  int m, bo1=0, bo2=0, bo3=0;

  if(!tabla||ip<0||iu<0||ip>iu) return ERR;

  if(ip==iu) return OK;

  m=(ip+iu)/2;

  bo1 += MergeSort(tabla,ip,m);
  if(bo1==ERR) return ERR;

  bo2 += MergeSort(tabla,m+1,iu);
  if(bo2==ERR) return ERR;

  bo3 += merge(tabla,ip,iu,m);
  if(bo3==ERR) return ERR;

  return bo1+bo2+bo3;
}

/***************************************************/
/* Function: quicksort Date: 21/10/2022            */
/* Authors: Daniel Birsan y Daniel Cruz            */
/*                                                 */
/* merges the array                                */
/*                                                 */
/* Input: An array and its first and last indexes  */
/* int *tabla: the array                           */
/* int ip: first index of the array                */
/* int iu: last index of the array                 */
/* int imedio: medium index of the array           */
/* Output: OB count or error                       */
/* int: OB                                         */
/***************************************************/
int merge(int* tabla, int ip, int iu, int imedio){
  int* tabla_aux=NULL;
  int i,j,k=0,c=0;

  if(!tabla||ip<0||iu<0||ip>iu||imedio>iu) return ERR;

  tabla_aux=(int*)malloc((iu-ip+1)*sizeof(int));
  if(tabla_aux==NULL) return ERR;

  i=ip;
  j=imedio+1;

  while(i<=imedio && j<=iu){
    if(tabla[i]<tabla[j]){
      tabla_aux[k]=tabla[i];
      i++;
      c++;
    }
    else{
      tabla_aux[k]=tabla[j];
      j++;
      c++;
    }
    k++;
  }

  while(j<=iu){
    tabla_aux[k]=tabla[j];
    j++;
    k++;
  }

  while(i<=imedio){
    tabla_aux[k]=tabla[i];
    i++;
    k++;
  }

  for(i=ip;i<=iu;i++){
    tabla[i]=tabla_aux[i-ip];
  }

  free(tabla_aux);
  return c;
}
