#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

typedef struct tree_node *tree_pointer;
typedef struct tree_node {
	tree_pointer leftChild;
	int key;
	char value;
	tree_pointer rightChild;
} tree_node;

tree_pointer SearchBST(tree_pointer, int);
void InorderBST(tree_pointer);
void InsertBST(tree_pointer, int, char);

int main()
{
	FILE *fp;
	int key;
	char tag, value;
	tree_pointer root = (tree_pointer)malloc(sizeof(tree_node)), search;
	root->leftChild = NULL;
	root->rightChild = NULL;
	root->key = 0;
	root->value = 'h';

	fp = fopen("BST.txt", "r");

	while ((tag = fgetc(fp)) != EOF) {
		switch (tag) {
		case 'I': fscanf(fp, "%d %c", &key, &value);
			InsertBST(root, key, value);
			break;
		case 'S': fscanf(fp, "%d", &key);
			search = SearchBST(root, key);
			printf("%c\n", search->value);
			break;
		case 'T': InorderBST(root->rightChild);
		}
	}

	fclose(fp);

	system("pause");
	return 0;
}

tree_pointer SearchBST(tree_pointer ptr, int key)
{
	tree_pointer last = NULL;
	while (ptr) {
		last = ptr;
		if (ptr->key == key) return ptr;
		if (ptr->key < key) ptr = ptr->rightChild;
		else ptr = ptr->leftChild;
	}
	return last;
}

void InorderBST(tree_pointer ptr)
{
	if (ptr) {
		InorderBST(ptr->leftChild);
		printf("(%d, %c)\n", ptr->key, ptr->value);
		InorderBST(ptr->rightChild);
	}
}

void InsertBST(tree_pointer ptr, int key, char value)
{
	tree_pointer parent, node = (tree_pointer)malloc(sizeof(tree_node));
	node->leftChild = NULL;
	node->rightChild = NULL;
	node->key = key;
	node->value = value;
	parent = SearchBST(ptr, key);
	if (key < parent->key) parent->leftChild = node;
	else parent->rightChild = node;
}
