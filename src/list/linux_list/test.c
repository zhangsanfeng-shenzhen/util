#include "list.h"
#include <stdio.h>
#include <stdlib.h>

#define SZ 32

#define CNT 66

struct ourstu {
    char name[SZ];
    int num;
    struct list_head list;
};

LIST_HEAD(head);

static int demo_init(void)
{
    int i;
    struct ourstu *stu;

    struct list_head *pos, *n;

    for (i = 0; i < CNT; i++) {
        stu = malloc(sizeof(struct ourstu));
        if (NULL == stu) {
            goto error0;
        }
        stu->num = 9527 + i;
        sprintf(stu->name, "spring%d", i);

        list_add_tail(&stu->list, &head);
    }

    list_for_each (pos, &head) {
        stu = container_of(pos, struct ourstu, list);            
        printf("%s's number %d\n", stu->name, stu->num);
    }


    return 0;
    
error0:
    list_for_each_safe(pos, n, &head) {
        stu = container_of(pos, struct ourstu, list);    
        printf("%s see bye...\n", stu->name);
        free(stu);
    }

    return -1;
}



static void demo_exit(void)
{
    struct list_head *n, *pos;
    struct ourstu *stu;

    list_for_each_safe(pos, n, &head) {
        stu = container_of(pos, struct ourstu, list);    
        printf("%s say bye...\n", stu->name);
        free(stu);
    }

    printf("see you, kernel...\n");
}

int main()
{

    demo_init();
    demo_exit();
}