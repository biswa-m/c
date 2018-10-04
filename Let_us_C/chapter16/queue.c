// Implementation of queue using linked list

#include <stdio.h>
#include <stdlib.h>

struct queue {
	int value;
	struct queue *next;
};

void addition(struct queue **, struct queue **, int);
int deletion(struct queue **, struct queue **);
void display(struct queue *);

int main()
{
	struct queue *front = NULL;
	struct queue *rear = NULL;
	int choice, val;

	while (1) {
		puts("\n\n1. Add new element");
		puts("2. Obtain element");
		puts("3. View queue");
		puts("4. Exit");

		scanf(" %d", &choice);

		switch (choice) {
		case 1:
			puts("Enter integer to add");
			scanf(" %d", &val);
			addition(&front, &rear, val);
			puts("Queue after addition");
			display(front);
			break;
		case 2:
			printf("Obtained value = %d\n", 
					deletion(&front, &rear));
			puts("Queue after deletion");
			display(front);
			break;
		case 3:
			display(front);
			break;
		case 4:
			exit(0);
		}
	}
	return 0;
}

void addition(struct queue **front, struct queue **rear, int val)
{
	struct queue *node = (struct queue *) malloc(sizeof(struct queue));

	node->value = val;
	node->next = NULL; 

	if (*rear == NULL) {
		*front = node;
	} else {
		struct queue *p = *rear;
		p->next = node;
	}
	*rear = node;
}

int deletion(struct queue **front, struct queue **rear)
{
	if (*front == NULL) {
		puts("Stack Empty");
		return 0;
	} 
	int val;
	struct queue *p = *front;
	val = p->value;
	*front = p->next;

	if (*front == NULL)
		*rear = NULL;
	
	return val;
}

void display(struct queue *qp)
{
	if (qp == NULL)
		return;
        do{
                printf("%6d\n", qp->value);
        } while((qp = qp->next) != NULL);
        putchar('\n');
}
