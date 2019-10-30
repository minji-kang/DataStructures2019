#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
#define MAX_SIZE 50

typedef enum {head, entry} tagfield;
typedef struct matrix_node *matrix_pointer;
typedef struct entry_node {
  int row;
  int col;
  int value;
} entry_node;
typedef struct matrix_node {
  matrix_pointer down;
  matrix_pointer right;
  tagfield tag;
  union {
    matrix_pointer next;
    struct entry_node entry;
  } u;
} matrix_node;

/* Global Variables */
matrix_pointer hdnode[MAX_SIZE];

/* Functions to be implemented by students */
matrix_pointer mread(FILE*); // file 에서 matrix 자료를 읽어 리스트에 저장한다.
void mwrite(matrix_pointer); // 행렬을 적절한 포맷 (2차원 행렬형태)으로 출력한다.
void merase(matrix_pointer*); // NULL parameter 인 경우 적절히 처리.

int main() {

  matrix_pointer a, b;
  FILE *fp_A, *fp_B;

  fp_A = fopen("A.txt", "r");
  fp_B = fopen("B.txt", "r");
  a = mread(fp_A);
  b = mread(fp_B);
  mwrite(a);
  mwrite(b);
  merase(&a);
  merase(&b);
  mwrite(a);
  mwrite(b);

    
  fclose(fp_A);
  fclose(fp_B);

  system("pause");
  return 0;
}

matrix_pointer new_node() {
  matrix_pointer node = (matrix_pointer)malloc(sizeof(matrix_node));
  if (!node) {
      fprintf(stderr, "There is no available memory for allocation.\n");
      fprintf(stderr, "Program will be shutdown.\n");
      exit(0);
  }
  return node;
}

matrix_pointer mread(FILE* fp)
{
	int num_rows, num_cols, num_terms, num_heads, i;
	int row=0, col=-1, value, current_row;
	matrix_pointer temp, node, last;

	fscanf(fp, "%d %d", &num_rows, &num_cols);
	num_heads=(num_cols>num_rows)? num_cols: num_rows;
	num_terms=num_rows*num_cols;
	node=new_node(); node->tag=entry;
	node->u.entry.row=num_rows; node->u.entry.col=num_cols;
	
	if(!num_heads) node->right=node;
	else {
		for(i=0; i<num_heads; i++) {
			temp=new_node(); hdnode[i]=temp;
			hdnode[i]->tag=head; hdnode[i]->right=temp;
			hdnode[i]->u.next=temp;
		}
		current_row=0; last=hdnode[0];
		for(i=0; i<num_terms; i++) {
			fscanf(fp, "%d", &value);
			col++;
			if(col==num_cols) {
				col=0; row++;
			}
			if(row>current_row) {
				last->right=hdnode[current_row];
				current_row=row; last=hdnode[row];
			}
			if(!value) continue;
			temp=new_node(); temp->tag=entry;
			temp->u.entry.row=row; temp->u.entry.col=col;
			temp->u.entry.value=value; last->right=temp; last=temp;
			hdnode[col]->u.next->down=temp;
			hdnode[col]->u.next=temp;
		}
		last->right=hdnode[current_row];
		for(i=0; i<num_cols; i++) hdnode[i]->u.next->down=hdnode[i];
		for(i=0; i<num_heads-1; i++) hdnode[i]->u.next=hdnode[i+1];
		hdnode[num_heads-1]->u.next=node;
		node->right=hdnode[0];
	}
	return node;
}

void mwrite(matrix_pointer node)
{
	int i, col_count=0, num_cols;
	matrix_pointer temp, head = node->right;
	num_cols=node->u.entry.col;
	for(i=0; i<node->u.entry.row; i++) {
		temp=head->right;
		for(col_count=0; col_count<num_cols; col_count++) {
			if(col_count!=temp->u.entry.col) {
				printf("0 "); continue;
			}
			printf("%d ", temp->u.entry.value);
			temp=temp->right;
		}
		printf("\n");
		head=head->u.next;
	}
	printf("\n");
}

void merase(matrix_pointer* node)
{
	int i;
	matrix_pointer x, y, head=(*node)->right;

	for(i=0; i<(*node)->u.entry.row; i++) {
		y=head->right;
		while(y!=head) {
			x=y; y=y->right; free(x);
		}
		x=head; head=head->u.next; free(x);
	}

	y=head;
	while(y!=(*node)) {
		x=y; y=y->u.next; free(x);
	}
	free(*node); *node=NULL;
}