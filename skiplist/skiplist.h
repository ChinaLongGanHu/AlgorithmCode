#ifndef SKIPLIST_H
#define SKIPLIST_H
#define SKIPLIST_MAXEVEL 8

typedef struct skiplistNode{
  double score;
  struct skiplistNode *backward;
  struct skiplistLevel{
    struct skiplistNode *forward;
  }level[];

}skiplistNode;
typedef struct skiplist{
  struct skiplistNode *header,*tail;
  unsigned long length;
  int level;
}skiplist;
#endif