/*解决旅行商问题的实现*/
/*tsp.c*/
#include <float.h>
#include <math.h>
#include <stdlib.h>

#include "graph.h"
#include "graphalg.h"
#include "list.h"



int tsp(List *vertices,const TspVertex *start,List *tour,int (*match)(const void *key1,const void *key2)){
    TspVertex *tsp_vertex,*tsp_start,*selection;
	ListElmt *element;
	double minimum,distance,x,y;
	int found,i;
	list_init(tour,NULL);
	found=0;
	for(element=list_head(vertices);element!=NULL;element=list_next(element)){
	  tsp_vertex=list_data(element);
	  if(match(tsp_vertex,start)){
	     if(list_ins_next(tour,list_tail(tour),tsp_vertes)!=0){
		   list_destroy(tour);
		   return -1;
		 }
		 tsp_start=tsp_vertex;
		 x=tsp_vertex->x;
		 y=tsp_vertex->y;
		 tsp_vertex->color=black;
		 found=1;
	  }else{
	     tsp_vertex->color=write;
	  }
	}
	if(!found){
	  list_destroy(tour);
	  return -1;
	}
	i=0;
	while(i<list_size(vertices)-1){
	  minimum=DBL_MAX;
	  for(element=list_head(vertices);element!=NULL;element=list_next(element)){
	    tsp_vertex=list_data(element);
		if(tsp_vertex->color==white)
		{
		   distance=sqrt(pow(tsp_vertex->x-x,2.0)+pow(tsp_vertex->y-y,2.0));
		   if(distance<minimum){
		      minimum=distance;
			  selection=tsp_vertex;
		   }
		}
	  }
	x=selection->x;
	y=selection->y;
	selection->color=black;
	if(list_ins_next(tour,list_tail(tour),selection)!=0)
	{
	  list_destroy(tour);
	  return -1;
	}
	i++;
	}
	/*insert the start vertex again to complete the tour*/
	if(list_ins_next(tour,list_tail(tour),tsp_start)!=0)
	{
	  list_destroy(tour);
	  return -1;;
	}
	return 0;

}