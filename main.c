#include <stdio.h>
#include "matrix.h"
#include "matrix.c"


int main(void)
{
    int n, m, line;
    double x = 0.0, y = 0.0, max_num;
    data_type data, a, b, c;


    printf("Enter the size of the input matrix: ");
    scanf("%d %d", &n, &m);

    Matrix *matrix = matrix_create(n, m);

    printf("Enter the matrix:\n");
    for (int j = 1; j <= m; ++j) {
        for (int i = 1; i <= n; ++i) {
            scanf("%lf %lf", &x, &y);
            if (is_zero(x, y)) continue;
            data = x +y*I;
            matrix_push(matrix, data, get_lambda(m, i, j));
        }
    }


    printf("Matrix internal performance\n");
    matrix_internal(matrix->first);
    printf("Matrix external performance\n");
    matrix_external(matrix);
    printf("Matrix after transformation\n");
    max_num = find_max_divine(matrix->first, 0);
    for (int i = 0; i <= n; i++) {    
        line = divine(matrix->first, max_num, n);
        if (line != -1) {    
            for (int j = 0; j <= m; j++) {
                find_node_divine(matrix->first, j, line + 1, n, max_num);
            }
        }
    } 
    matrix_external(matrix);


    free(matrix->first);
    free(matrix->last);
    free(matrix);
    return 0;

}
