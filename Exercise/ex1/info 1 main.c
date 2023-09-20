#include <stdlib.h>

struct matrix {
    int rows;
    int cols;
    double *data;
};

void prod_per_scalare(struct matrix *mat, double k)
{
    for (int r = 0; r < mat->rows; ++r) {
        for (int c = 0; c < mat->cols; ++c) {
            mat->data[r * mat->cols + c] *= k;
        }
    }
}

struct matrix *mat_copy(struct matrix *dst, struct matrix const *src)
{
    int size = src->rows * src->cols;
    for (int i = 0; i < size; ++i) {
        dst->data[i] = src->data[i];
    }
    return dst;
}

struct matrix *mat_constructor(struct matrix *m, int rows, int cols)
{
    m->rows = rows;
    m->cols = cols;
    m->data = malloc(rows*cols * sizeof(double));
    return m;
}

void mat_destructor(struct matrix *m)
{
    free(m->data);
}

struct matrix *new_mat(int rows, int cols)
{
    return mat_constructor(malloc(sizeof(struct matrix)), 
        rows, cols);
}

void delete_mat(struct matrix *m)
{
    mat_destructor(m);
    free(m);
}

struct matrix *mat_create_copy(struct matrix *src)
{
    return mat_copy(new_mat(src->rows, src->cols), src);
}

extern struct matrix *mat_transpose(struct matrix *m);

int main(void)
{
    double Adata[3*2] = {
          3, 2.5 ,
          2, 4   ,
         -1, 7   ,
    };
    struct matrix A = { 3, 2, Adata };
    struct matrix *B = new_mat(3, 2);

    mat_copy(B, &A);

    prod_per_scalare(&A, 0.5);

    delete_mat(B);
    return 0;
}