/*插入排序的实现*/
/*issort.c*/
#include <stdlib.h>
#include <string.h>
#include "sort.h"

int issort(void *data,int size,int eszie,int (*compare)(const void *key1,const void *key2)){
  char *a=data;
  void *key;
  int i,j;
  if((key=(char *)malloc(esize))==NULL)
    return -1;
  for(j=1;j<size;j++){
    memcpy(key,&a[j*esize],esize);
	i=j-1;
	while(i>=0;&&compare(&a[i*eszie],key)>0){
	  memcpy(&a[(i+1)*esize],&a[i*esize],esize);
	  i--;
	}
	memcpy(&a[(i+1)*esize],key,esize);
  }
  free(key);
  return 0;
}