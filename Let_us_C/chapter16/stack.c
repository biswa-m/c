// Implementation of stack using linked list

#include <stdio.h>
#include <stdlib.h>

struct stack {
	int value;
	struct stack *next;
};

void push(struct stack **, int);
int pop(struct stack **);
void display(struct stack *sp);

int main()
{
	struct stack *sp = NULL;
	int choice, val;

	while (1) {
		puts("\n\n1. Push");
		puts("2. Pop");
		puts("3. View stack");
		puts("4. Exit");

		scanf(" %d", &choice);

		switch (choice) {
		case 1:
			puts("Enter integer to push");
			scanf(" %d", &val);
			push(&sp, val);
			puts("Stack after push");
			display(sp);
			break;
		case 2:
			printf("Obtained value = %d\n", pop(&sp));
			puts("Stack after pop");
			display(sp);
			break;
		case 3:
			display(sp);
			break;
		case 4:
			exit(0);
		}
	}
	return 0;
}

void push(struct stack **sp, int val)
{
	struct stack *node = (struct stack *) malloc(sizeof(struct stack));

	node->value = val;
	node->next = *sp; 
	*sp = node;
}

int pop(struct stack **sp)
{
	if (*sp == NULL) {
		puts("Stack Empty");
		return 0;
	}
		
	int val;
	struct stack *p;

	p = *sp;
	val = p->value;
	*sp = p->next;

	return val;
}

void display(struct stack *sp)
{
	if (sp == NULL)
		return;
        do{
                printf("%6d\n", sp->value);
        } while((sp = sp->next) != NULL);
        putchar('\n');
}

