#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <stdlib.h>
#include <complex.h>

typedef complex double data_type;
typedef struct matrix_node Node;
typedef struct matrix Matrix;

struct matrix{
	int n,m;
	Node *first;
	Node *last;
};

struct matrix_node{
	data_type value;
	int lambda;
	Node *next;
	Node *prev;
};

int get_lambda(int n, int i, int j);
int is_zero(double x, double y);
int lambda_i(int lambda,int n);
int lambda_j(int lambda,int n);
Matrix *matrix_create(int n, int m);
void matrix_push(Matrix *matrix, data_type value, int lambda);
Node *node_create(void);
void matrix_internal(Node *tmp);
void matrix_external(Matrix *tmp);

#endif