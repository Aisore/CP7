#include "matrix.h"

#define  FORMAT 3

int get_lambda(int n, int i, int j) { 
	return (i-1) * n + j-1; 
}

int is_zero(double x, double y) {
	return (x == 0 && y == 0) ? 1 : 0;
}

int lambda_i(int lambda,int n) {
	return lambda/n;
}

int lambda_j(int lambda,int n) {
	return lambda%n;
}

Matrix *matrix_create(int n, int m)
{
	Matrix *tmp = (Matrix *)malloc(sizeof(Matrix));
	if(!tmp) {
        fprintf(stderr, "%s\n", "Error: no memory");
        exit(0);
    }
	Node *first = node_create();
	tmp->first = first;
	first->prev = NULL;
	tmp->last = first;
	tmp->n = n;
	tmp->m = m;

	return tmp;
}

Node *node_create(void)
{
	Node *new = (Node *)malloc(sizeof(Node));
	if(!new) {
        fprintf(stderr, "%s\n", "Error: no memory");
        exit(0);
    }
	new->lambda = -1;
	new->next = NULL;
	new->prev = NULL;
	new->value = 0;

	return new;
}

void matrix_push(Matrix *matrix, data_type value, int lambda)
{
	Node *last_node = node_create();

	matrix->last->lambda = lambda;
	matrix->last->value = value;
	matrix->last->next = last_node;

	last_node->prev = matrix->last;
	matrix->last = last_node;
	
}


data_type find_node(Node* tmp, int i, int j, int n)
{
    do {
        if(tmp->lambda == get_lambda(n, i, j)) { 
        	return tmp->value;
        }
        tmp = tmp->next;
    } while(tmp->next != NULL);
	return 0.0;
}

void matrix_internal(Node *tmp)
{
	if (!tmp->next) return;
	printf("lambda =%3d; data = (%.2lf + %.2lfi)\n", tmp->lambda, creal(tmp->value), cimag(tmp->value));
	matrix_internal(tmp->next);
}

void matrix_external(Matrix *tmp)
{
	if (!tmp) return;
	int n = tmp->n;
	int m = tmp->m;
	data_type curr_val = 0 + 0*I;

	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			curr_val = find_node(tmp->first, j, i, m);
			printf(" < %3.2lf + %3.2lfi > ", creal(curr_val), cimag(curr_val));
		} 
		printf("\n");
	}
}

double find_max_divine(Node *tmp, double max) 
{
	if (!tmp->next) return max;
	data_type curr_val = tmp->value;
	if (creal(curr_val) >= max) {
		max = creal(curr_val);
	}
	find_max_divine(tmp->next, max);
}

int divine(Node *tmp, double max, int n)
{
	while (tmp->next) {
		data_type curr_val = tmp->value;
		if (creal(curr_val) == max) {
			return lambda_j(tmp->lambda, n);
		}
		tmp = tmp->next;
	}
	return -1;
}

void find_node_divine(Node* tmp, int i, int j, int n, double max)
{
	do {
     	if(tmp->lambda == get_lambda(n, i, j)) { 
    	   	tmp->value = creal(tmp->value) / max + cimag(tmp->value)*I;
   	 	}
   		tmp = tmp->next;
	} while (tmp->next);
} 

