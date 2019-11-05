#include <stdio.h>
#include <stdlib.h>

#include "list.h"

//自定义的数据结构
typedef struct list_test_struct
{
	struct list_head	list;

	int key;
	int data;
}list_test_struct;

int main()
{
	struct list_head list = {0};  //定义链表（头） 
	struct list_head *pos = NULL; 
	struct list_head *n = NULL; 

	int i=0;

	printf("定义链表\n"); 

	printf("初始化链表！\r\n"); 
	INIT_LIST_HEAD(&list);  //初始化链表（头尾相接，形成空链表循环） 

	//判断链表是否为空 
	printf("判断链表是否为空：");  
	if(list_empty(&list)){ 
		printf("空\r\n"); 
	}else{ 
		printf("非空\r\n"); 
	} 

	//批量添加节点 
	printf("批量添加节点：\r\n");  
	for(i=0;i<200;i++) {
		struct list_test_struct *st;
		st = (list_test_struct *)malloc(sizeof(list_test_struct));
		if (st == NULL) {
			printf("error\n");
			return 1;
		}
		st->data=i;
		st->key=i;
		list_add(&st->list, &list); 
	} 

	//显示列表所有节点 
	printf("显示列表所有节点：\r\n");   
	list_for_each(pos,&list)
	{ 
		struct list_test_struct *st=list_entry(pos,struct list_test_struct,list); 
		printf( "\t node:key(%d),data(%d)\r\n",st->key,st->data); 
	} 

	//释放所有节点资源 
	printf("释放所有节点资源！\r\n"); 
	list_for_each_safe(pos,n,&list)
	{ 
		struct list_test_struct *st=list_entry(pos,struct list_test_struct,list); 
		list_del(pos);  //删除节点，删除节点必须在删除节点内存之前 
		free(st);   //释放节点内存 
	} 

	return 1;

}