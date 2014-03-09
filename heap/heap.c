#include <stdlib.h>
#include<string.h>

#include "heap.h"
#define heap_parent(npos) ((int)(((npos)-1)/2))
#define heap_left(npos) (((npos)*2)+1)
#define heap_right(npos) (((npos)*2)+2)

void heap_init(Heap *heap,int (*compare)(const void *key1,const void *key2),void (*destroy)(void *data)){
   heap->size=0;
   heap->compare=compare;
   heap->destroy=destroy;
   heap->tree=NULL;
   return;
}

void heap_destroy(Heap *heap){
   int i;
   if(heap->destroy!=NULL){
     for(i=0;i<heap_size(heap);i++)
	 {
	   heap->destroy(heap->tree[i]);
	 }
   }
   free(heap->tree);
   memset(heap,0,sizeof(Heap));
   return;
}
int heap_insert(Heap *heap,const void *data){
  void *temp;
  int ipos,ppos;
  if((temp(void **)realloc(heap->tree,(heap_size(heap)+1)*sizeof(void *)))==NULL)
    return -1;
  else
    heap->tree=temp;

  heap->tree[heap_size(heap)]=(void *)data;
  ipos=heap_size(heap);
  ppos=heap_parent(ipos);
  while(ipos>0&&heap->compare(heap->tree[ppos],heap->tree[ipos])<0){
    temp=heap->tree[ppos];
	heap->tree[ppos]=heap->tree[ipos];
	heap->tree[ipos]=temp;
	ipos=ppos;
	ppos=heap=heap_parent(ipos);
  }
  heap->size++;
  return 0;
}


int heap_extract(Heap *heap,void **data){


}
