/**
 * @file libMultimedia.h
 *
 * @brief Library that uses multimedia instruction to speedup array processing
 *
 * @author Edgar Domingues (39026)
 * @author Mario Antunes   (39372)
 *
 * @version 1.0
 *
 */

#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

#ifndef LIB_MULTIMEDIA_H
#define LIB_MULTIMEDIA_H

char sumelem_char(char *a, int size);
char sumelem_char_sse2(char *a, int size);
char sumelem_char_unrolled_sse2(char *a, int size);

int sumelem_int(int *a, int size);
int sumelem_int_sse2(int *a, int size);
int sumelem_int_unrolled_sse2(int *a, int size);

float sumelem_float(float *a, int size);
float sumelem_float_sse2(float *a, int size);
float sumelem_float_unrolled_sse2(float *a, int size);

double sumelem_double(double *a, int size);
double sumelem_double_sse2(double *a, int size);
double sumelem_double_unrolled_sse2(double *a, int size);

void sumarray_char(char *a, char *b, char *c, int size);
void sumarray_char_sse2(char *a, char *b, char *c, int size);
void sumarray_char_unrolled_sse2(char *a, char *b, char *c, int size);

void sumarray_int(int *a, int *b, int *c, int size);
void sumarray_int_sse2(int *a, int *b, int *c, int size);
void sumarray_int_unrolled_sse2(int *a, int *b, int *c, int size);

void sumarray_float(float *a, float *b, float *c, int size);
void sumarray_float_sse2(float *a, float *b, float *c, int size);
void sumarray_float_unrolled_sse2(float *a, float *b, float *c, int size);

void sumarray_double(double *a, double *b, double *c, int size);
void sumarray_double_sse2(double *a, double *b, double *c, int size);
void sumarray_double_unrolled_sse2(double *a, double *b, double *c, int size);

void summatrix_char(char **a, char **b, char **c, int rows, int cols);
void summatrix_char_sse2(char **a, char **b, char **c, int rows, int cols);
void summatrix_char_unrolled_sse2(char **a, char **b, char **c, int rows, int cols);
void sum_linear_matrix_char(char *a, char *b, char *c, int rows, int cols);
void sum_linear_matrix_char_sse2(char *a, char *b, char *c, int rows, int cols);
void sum_linear_matrix_char_unrolled_sse2(char *a, char *b, char *c, int rows, int cols);

void summatrix_int(int **a, int **b, int **c, int rows, int cols);
void summatrix_int_sse2(int **a, int **b, int **c, int rows, int cols);
void summatrix_int_unrolled_sse2(int **a, int **b, int **c, int rows, int cols);
void sum_linear_matrix_int(int *a, int *b, int *c, int rows, int cols);
void sum_linear_matrix_int_sse2(int *a, int *b, int *c, int rows, int cols);
void sum_linear_matrix_int_unrolled_sse2(int *a, int *b, int *c, int rows, int cols);

void summatrix_float(float **a, float **b, float **c, int rows, int cols);
void summatrix_float_sse2(float **a, float **b, float **c, int rows, int cols);
void summatrix_float_unrolled_sse2(float **a, float **b, float **c, int rows, int cols);
void sum_linear_matrix_float(float *a, float *b, float *c, int rows, int cols);
void sum_linear_matrix_float_sse2(float *a, float *b, float *c, int rows, int cols);

void summatrix_double(double **a, double **b, double **c, int rows, int cols);
void summatrix_double_sse2(double **a, double **b, double **c, int rows, int cols);
void sum_linear_matrix_double(double *a, double *b, double *c, int rows, int cols);
void sum_linear_matrix_double_sse2(double *a, double *b, double *c, int rows, int cols);

void mularray_float(float *a, float *b, float *c, int size);
void mularray_float_sse2(float *a, float *b, float *c, int size);
void mularray_float_unrolled_sse2(float *a, float *b, float *c, int size);

void mularray_double(double *a, double *b, double *c, int size);
void mularray_double_sse2(double *a, double *b, double *c, int size);
void mularray_double_unrolled_sse2(double *a, double *b, double *c, int size);

float dotProduct_float(float *a, float *b, int size);
float dotProduct_float_sse2(float *a, float *b, int size);
float dotProduct_float_unrolled_sse2(float *a, float *b, int size);

float dotProduct_double(double *a, double *b, int size);
float dotProduct_double_sse2(double *a, double *b, int size);
double dotProduct_double_unrolled_sse2(double *a, double *b, int size);

void mulmatrix_float(float **a, float **b, float **c, int i, int j, int k);
void mulmatrix_float_sse2(float **a, float **b, float **c, int i, int j, int k);

void mulmatrix_double(double **a, double **b, double **c, int i, int j, int k);
void mulmatrix_double_sse2(double **a, double **b, double **c, int i, int j, int k);

float maxelem_float(float *a, int size);
float maxelem_float_sse2(float *a, int size);

double maxelem_double(double *a, int size);
double maxelem_double_sse2(double *a, int size);

float minelem_float(float *a, int size);
float minelem_float_sse2(float *a, int size);

double minelem_double(double *a, int size);
double minelem_double_sse2(double *a, int size);

void cmp_equal_char(char *a, char *b, char *c, int size);
void cmp_equal_char_sse2(char *a, char *b, char *c, int size);

void cmp_equal_int(int *a, int *b, int *c, int size);
void cmp_equal_int_sse2(int *a, int *b, int *c, int size);

void cmp_equal_float(float *a, float *b, float *c, int size);
void cmp_equal_float_sse2(float *a, float *b, float *c, int size);

void cmp_equal_double(double *a, double *b, double *c, int size);
void cmp_equal_double_sse2(double *a, double *b, double *c, int size);

void cmp_greater_char(char *a, char *b, char *c, int size);
void cmp_greater_char_sse2(char *a, char *b, char *c, int size);

void cmp_greater_int(int *a, int *b, int *c, int size);
void cmp_greater_int_sse2(int *a, int *b, int *c, int size);

void cmp_greater_float(float *a, float *b, float *c, int size);
void cmp_greater_float_sse2(float *a, float *b, float *c, int size);

void cmp_greater_double(double *a, double *b, double *c, int size);
void cmp_greater_double_sse2(double *a, double *b, double *c, int size);

void cmp_greater_unrolled_char_sse2(char *a, char *b, char *c, int size);

void cmp_less_char(char *a, char *b, char *c, int size);
void cmp_less_char_sse2(char *a, char *b, char *c, int size);

void cmp_less_int(int *a, int *b, int *c, int size);
void cmp_less_int_sse2(int *a, int *b, int *c, int size);

void cmp_less_float(float *a, float *b, float *c, int size);
void cmp_less_float_sse2(float *a, float *b, float *c, int size);

void cmp_less_double(double *a, double *b, double *c, int size);
void cmp_less_double_sse2(double *a, double *b, double *c, int size);

void cmp_less_unrolled_char_sse2(char *a, char *b, char *c, int size);

void memcpy_sse2(void *dst, void *src, int size);
void memcpy_unrolled_sse2(void *dst, void *src, int size);

void matrix2linear_matrix_float_sse2(float **a, float *b, int rows, int cols);
void matrix2linear_matrix_double_sse2(double **a, double *b, int rows, int cols);
void linear_matrix2matrix_float_sse2(float *a, float **b, int rows, int cols);
void linear_matrix2matrix_double_sse2(double *a, double **b, int rows, int cols);

void convolution_linear_float(float *a, float *b, float *c, int size_a, int size_b);
void convolution_linear_float_sse2(float *a, float *b, float *c, int size_a, int size_b);

void convolution_linear_double(double *a, double *b, double *c, int size_a, int size_b);
void convolution_linear_double_sse2(double *a, double *b, double *c, int size_a, int size_b);

void convolution_matrix_float(float **a, float **b, float **c, int rows_a, int cols_a, int rows_b, int cols_b);
void convolution_matrix_float_sse2(float **a, float **b, float **c, int rows_a, int cols_a, int rows_b, int cols_b);

void convolution_matrix_double(double **a, double **b, double **c, int rows_a, int cols_a, int rows_b, int cols_b);
void convolution_matrix_double_sse2(double **a, double **b, double **c, int rows_a, int cols_a, int rows_b, int cols_b);

void transpose_matrix_float(float **a, float **b, int rows, int cols);
void transpose_matrix_float_sse2(float **a, float **b, int rows, int cols);

void transpose_matrix_double(double **a, double **b, int rows, int cols);
void transpose_matrix_double_sse2(double **a, double **b, int rows, int cols);

#endif
