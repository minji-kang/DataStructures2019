#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#pragma warning(disable:4996)

typedef struct threadedTree *threadedPointer;
typedef struct threadedTree {
	short int leftThread;
	threadedPointer leftChild;
	char data;
	threadedPointer rightChild;
	short int rightThread;
} threadedTree;

void Traversal(threadedPointer);
void InsertRight(threadedPointer, threadedPointer);
void InsertLeft(threadedPointer, threadedPointer);
threadedPointer insucc(threadedPointer);
threadedPointer search(threadedPointer, int);

int main()
{
	FILE* fp;
	int parentData, childData;
	char flag;
	threadedPointer temp, parent, child, ptr = (threadedPointer)malloc(sizeof(threadedTree));
	ptr->data = 0;
	ptr->rightThread = true;
	ptr->leftThread = true;

	fp = fopen("Input.txt", "r");
	while (1) {
		fscanf(fp, "%c", &flag);
		if (flag == 'E') break;
		fscanf(fp, "%d", &parentData);
		fscanf(fp, "%d", &childData);
		switch (flag) {
		case 'L': parent = search(ptr, parentData);
			child = (threadedPointer)malloc(sizeof(threadedTree));
			child->data = childData;
			InsertLeft(parent, child);
			break;
		case 'R': parent = search(ptr, parentData);
			child = (threadedPointer)malloc(sizeof(threadedTree));
			child->data = childData;
			InsertRight(parent, child);
			break;
		case 'S': parent = ptr;
			child = (threadedPointer)malloc(sizeof(threadedTree));
			child->data = childData;
			InsertRight(parent, child);
		}
	}
	fclose(fp);
	temp = search(ptr, childData);
	temp->rightChild = ptr;

	Traversal(ptr);

	system("pause");
	return 0;
}

void Traversal(threadedPointer tree)
{
	threadedPointer temp = tree;
	while (1) {
		temp = insucc(temp);
		if (temp == tree) break;
		printf("%d\n", temp->data);
	}
}

void InsertRight(threadedPointer parent, threadedPointer child)
{
	threadedPointer temp;
	child->rightChild = parent->rightChild;
	child->rightThread = parent->rightThread;
	child->leftChild = parent;
	child->leftThread = true;
	parent->rightChild = child;
	parent->rightThread = false;
	if (!child->rightThread) {
		temp = insucc(child);
		temp->leftChild = child;
	}
}

void InsertLeft(threadedPointer parent, threadedPointer child)
{
	threadedPointer temp;
	child->leftChild = parent->leftChild;
	child->leftThread = parent->leftThread;
	child->rightChild = parent;
	child->rightThread = true;
	parent->leftChild = child;
	parent->leftThread = false;
	if (!child->leftThread) {
		temp = insucc(child);
		temp->rightChild = child;
	}
}

threadedPointer insucc(threadedPointer tree)
{
	threadedPointer temp;
	temp = tree->rightChild;
	if (!tree->rightThread) while (!temp->leftThread) temp = temp->leftChild;
	return temp;
}

threadedPointer search(threadedPointer tree, int searchnum)
{
	while (searchnum != tree->data) tree = insucc(tree);
	return tree;
}
