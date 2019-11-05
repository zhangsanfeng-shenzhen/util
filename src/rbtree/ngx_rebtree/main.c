#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "ngx_rbtree.h"

int main()
{
	ngx_rbtree_t tree;
	ngx_rbtree_node_t sentinel;
    ngx_rbtree_init(&tree,&sentinel,ngx_rbtree_insert_value);
    ngx_rbtree_node_t *rbnode = (ngx_rbtree_node_t *)malloc(sizeof(ngx_rbtree_node_t)*100);
    for(int i = 99; i >= 0 ;i--){
        rbnode[i].key = i;
        rbnode[i].parent = NULL;
        rbnode[i].left = NULL;
        rbnode[i].right = NULL;
        ngx_rbtree_insert(&tree,&rbnode[i]);
    }
    for(int i = 0; i < 100; i++) {
		ngx_rbtree_node_t *p = ngx_rbtree_min(tree.root,&sentinel);
		printf("%ld\n",p->key);
		ngx_rbtree_delete(&tree,p);
	}
	free(rbnode);
    return 0;
}

