#include <stdlib.h>
#include<string.h>
#include "bistree.h"

static void destroy_right(BisTree *tree,BiTreeNode *node);

/*rotate_left*/
static void rotate_left(BiTreeNode **node)
{
  BiTreeNode *left,*grandchild;
  left=bistree_left(*node);

}