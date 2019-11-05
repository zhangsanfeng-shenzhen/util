#include <stdio.h>
#include <stdlib.h>
#include "rbtree.h"

struct rbt_data
{
    struct rb_node data_node;
	int num;
};

struct rbt_data* rbt_search(struct rb_root *root, int num)
{
    struct rb_node *node = root->rb_node;

    while(node)
    {
        struct rbt_data *data = container_of(node, struct rbt_data, data_node);

		if (num < data->num)
			node = node->rb_left;
		else if (num > data->num)
			node = node->rb_right;
		else
			return data;
    }
	
    return NULL;
}

int rbt_insert(struct rb_root *root, struct rbt_data *data)
{
    struct rb_node **tmp = &(root->rb_node);
	struct rb_node *parent = NULL;

	while (*tmp)
	{
	    struct rbt_data *cur = container_of(*tmp, struct rbt_data, data_node);

		parent = *tmp;
		if(data->num < cur->num)
			tmp = &((*tmp)->rb_left);
		else if(data->num > cur->num)
			tmp = &((*tmp)->rb_right);
		else
			return -1;
	}

	rb_link_node(&(data->data_node), parent, tmp);
	rb_insert_color(&(data->data_node), root);

    return 0;
}

void rbt_delete(struct rb_root *root, int num)
{
	struct rbt_data *data = rbt_search(root, num);
	if (!data)
	{
	    fprintf(stderr, "Not fount %d.\n", num);
		return;
	}

	rb_erase(&(data->data_node), root);
	free(data);
	
}

void print_rbtree(struct rb_root *root)
{
    struct rb_node *node;

	for(node = rb_first(root); node; node = rb_next(node))
		printf("%d ", rb_entry(node, struct rbt_data, data_node)->num);

	printf("\n");
}

int main(int argc, char*argv[])
{
	struct rb_root root = RB_ROOT;

	struct rbt_data *data;
	int i;

	printf("please enter 5 integers:\n");
	for(i=0; i<5; i++)
	{
	    data = malloc(sizeof(struct rbt_data));
		if(!data)
		{
			perror("fail to malloc.");
		}

		scanf("%d", &data->num);

		int ret = rbt_insert(&root, data);
		if (ret < 0)
		{
		    fprintf(stderr, "the %d already exists.\n", data->num);
			i--;
			free(data);
		}
	}

	printf("\nthe first output:\n");
	print_rbtree(&root);

    int num;
	printf("\nplease enter the num to delete:\n");
	scanf("%d", &num);
	rbt_delete(&root, num);

    printf("\nthe second output:\n");
	print_rbtree(&root);
    
	return 0;
}