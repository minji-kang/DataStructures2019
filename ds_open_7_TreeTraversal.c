#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)
#define MAX_STACK_SIZE 100
#define MAX_QUEUE_SIZE 100

typedef struct node *tree_pointer;
typedef struct node {
	char data[2];
	tree_pointer left_child;
	tree_pointer right_child;
} node;

void add(tree_pointer, int*, tree_pointer);
tree_pointer pop(tree_pointer, int*);
void addq(tree_pointer, int, int*, tree_pointer);
tree_pointer popq(tree_pointer, int*, int);
void Inorder(tree_pointer);
void Preorder(tree_pointer);
void Postorder(tree_pointer);
void IterativeInorder(tree_pointer);
void Levelorder(tree_pointer);

int main()
{
	FILE* fp;
	int num_nodes, i;
	char data[2];
	tree_pointer temp;
	tree_pointer stack[MAX_STACK_SIZE];

	fp = fopen("Tree.txt", "r");
	fscanf(fp, "%d", &num_nodes);
	
	for (i = 0; i < num_nodes; i++) {
		temp = (tree_pointer)malloc(sizeof(node));
		fscanf(fp, "%s", &data);
		strcpy(temp->data, data);
		temp->left_child = NULL;
		temp->right_child = NULL;
		stack[i] = temp;
	}
	fclose(fp);

	for (i = 0; ; i++) {
		if ((2 * i + 1) == num_nodes) break;
		stack[i]->left_child = stack[2 * i + 1];
		if ((2 * i + 2) == num_nodes) break;
		stack[i]->right_child = stack[2 * i + 2];
	}

	printf("Inorder : "); Inorder(stack[0]); printf("\n");
	printf("Preorder : "); Preorder(stack[0]); printf("\n");
	printf("Postorder : "); Postorder(stack[0]); printf("\n");
	printf("Iterative Inorder : "); IterativeInorder(stack[0]); printf("\n");
	printf("Level order : "); Levelorder(stack[0]); printf("\n");

	system("pause");
	return 0;
}

void add(tree_pointer *stack, int *top, tree_pointer ptr)
{
	if ((*top) >= MAX_STACK_SIZE - 1) {
		fprintf(stderr, "Stack is full.\n"); system("pause"); exit(1);
	}
	stack[++(*top)] = ptr;
}

tree_pointer pop(tree_pointer *stack, int *top)
{
	if ((*top) == -1) {
		fprintf(stderr, "Stack is empty.\n"); system("pause"); exit(1);
	}
	return stack[(*top)--];
}

void addq(tree_pointer *q, int front, int *rear, tree_pointer node)
{
	*rear = ((*rear) + 1) % MAX_QUEUE_SIZE;
	if (front == (*rear)) {
		fprintf(stderr, "Queue is full.\n"); system("pause"); exit(1);
	}
	q[*rear] = node;
}

tree_pointer popq(tree_pointer *q, int *front, int rear)
{
	if ((*front) == rear) {
		fprintf(stderr, "Queue is empty.\n"); system("pause");  exit(1);
	}
	*front = ((*front) + 1) % MAX_QUEUE_SIZE;
	return q[*front];
}

void Inorder(tree_pointer ptr)
{
	if (ptr) {
		Inorder(ptr->left_child);
		printf("%s", ptr->data);
		Inorder(ptr->right_child);
	}
}

void Preorder(tree_pointer ptr)
{
	if (ptr) {
		printf("%s", ptr->data);
		Preorder(ptr->left_child);
		Preorder(ptr->right_child);
	}
}

void Postorder(tree_pointer ptr)
{
	if (ptr) {
		Postorder(ptr->left_child);
		Postorder(ptr->right_child);
		printf("%s", ptr->data);
	}
}

void IterativeInorder(tree_pointer ptr)
{
	int top = -1;
	tree_pointer stack[MAX_STACK_SIZE];
	while (1) {
		for (; ptr; ptr = ptr->left_child) add(stack, &top, ptr);
		if (top == -1) break;
		ptr = pop(stack, &top);
		if (!ptr) break;
		printf("%s", ptr->data);
		ptr = ptr->right_child;
	}
}

void Levelorder(tree_pointer ptr)
{
	int front = 0, rear = 0;
	tree_pointer queue[MAX_QUEUE_SIZE];
	if (!ptr) return;
	addq(queue, front, &rear, ptr);
	while (1) {
		if (front == rear) break;
		ptr = popq(queue, &front, rear);
		if (ptr) {
			printf("%s", ptr->data);
			if (ptr->left_child) addq(queue, front, &rear, ptr->left_child);
			if (ptr->right_child) addq(queue, front, &rear, ptr->right_child);
		}
	}
}
