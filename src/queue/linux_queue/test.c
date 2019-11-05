#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>

struct task_t {
	int data;
	SIMPLEQ_ENTRY(task_t) entries;
};

SIMPLEQ_HEAD(taskqueue_t, task_t);

int main(int argc, const char *argv[])
{
	struct task_t t[5];
	int i;
	struct taskqueue_t task_head;

	SIMPLEQ_INIT(&task_head);
	for (i = 0; i < 5; i++) {
		memset(&t[i], 0, sizeof(t[i]));
		t[i].data = i;
		SIMPLEQ_INSERT_TAIL(&task_head, &t[i], entries);
	}
	
	SIMPLEQ_REMOVE(&task_head, &t[3], task_t, entries);

	struct task_t *item;
	SIMPLEQ_FOREACH(item, &task_head, entries) {
		printf("data: %i\n", item->data);
	}
	return 0;
}
