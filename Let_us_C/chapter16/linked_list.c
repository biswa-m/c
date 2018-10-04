// Implement linked list

#include <stdio.h>
#include <stdlib.h>

struct linked_list {
	int value;
	struct linked_list *link;
};

void display(struct linked_list *);
void add_end(struct linked_list *, int);
void add_begin(struct linked_list *, int);
void add_pos(struct linked_list *, int, int);
void edit_pos(struct linked_list *, int, int);

int main()
{
	struct linked_list node;
	node.value = 1;
	node.link = NULL;
	
	int choice, val, pos;

	while (1) {
		puts("1. Add at end");
		puts("2. Add at beginning");
		puts("3. Add at position");
		puts("4. Edit node");
		puts("5. Exit");
		scanf("%d", &choice);
		
		switch (choice) {
		case 1:
			puts("Enter an integer to put at the end");
			scanf(" %d", &val);
			add_end(&node, val);
			puts("after adding node at the end");
			display(&node);
			break;
		case 2:
			puts("Enter an integer to put at the beginning");
			scanf(" %d", &val);
			add_begin(&node, val);
			puts("after adding node at the beginning");
			display(&node);
			break;
		case 3:
			puts("Enter the position");
			scanf(" %d", &pos);
			puts("Enter an integer to put at that position");
			scanf(" %d", &val);
			add_pos(&node, val, pos);
			puts("after adding node at position");
			display(&node);
			break;
		case 4:
			puts("Enter the position");
			scanf(" %d", &pos);
			puts("Enter the new integer value");
			scanf(" %d", &val);
			edit_pos(&node, val, pos);
			puts("after editing");
			display(&node);
			break;
		case 5:
			exit(0);
		}
	}
	return 0;
}

void display(struct linked_list *node)
{
	do{
		printf("%6d", node->value);	
	} while((node = node->link) != NULL);
	putchar('\n');
}

void add_end(struct linked_list *node, int val)
{
	while(node->link != NULL) {
		node = node->link;
	}
	node->link = (struct linked_list *) malloc(sizeof(struct linked_list));
	node = node->link;

	node->value = val;
	node->link = NULL;
}

void add_begin(struct linked_list *node, int val)
{
	struct linked_list *tmp;
	tmp = (struct linked_list *) malloc(sizeof(struct linked_list));
	*tmp = *node;
	node->link = tmp;
	node->value = val;
}

void add_pos(struct linked_list *node, int val, int pos)
{
	--pos;
	if (pos == 0) {
		add_begin(node, val);
		return;
	}
	int n = 0;
	while(n < pos - 1) {
		if (node->link == NULL) {
			printf("Error: The list has only %d element\n", n + 1);
			return;
		}
		node = node->link;
		++n;
	}
	struct linked_list *tmp;
	tmp = (struct linked_list *) malloc(sizeof(struct linked_list));
	tmp->value = val; 
	tmp->link = node->link;
	node->link = tmp;
}

void edit_pos(struct linked_list *node, int val, int pos)
{
	--pos;
	int n = 0;
	while(n < pos) {
		if (node->link == NULL) {
			printf("Error: The list has only %d element\n", n + 1);
			return;
		}
		node = node->link;
		++n;
	}
	node->value = val;
}
