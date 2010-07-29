/**
 * @file dataStructure.h
 *
 * @brief Library with auxiliary functions to manage data types.
 *
 * @author Edgar Domingues (39026)
 * @author Mario Antunes   (39372)
 *
 * @version 1.0
 *
 */

#ifndef DATA_STRUCTURE_H
#define DATA_STRUCTURE_H

char* create_array_char(int size);
int* create_array_int(int size);
float* create_array_float(int size);
double* create_array_double(int size);
void fill_array_random_char(char *array, int size);
void fill_array_random_int(int *array, int size);
void fill_array_random_float(float *array, int size);
void fill_array_random_double(double *array, int size);
void destroy_array_char(char **array);
void destroy_array_int(int **array);
void destroy_array_float(float **array);
void destroy_array_double(double **array);

char** create_matrix_char(int rows, int cols);
int** create_matrix_int(int rows, int cols);
float** create_matrix_float(int rows, int cols);
double** create_matrix_double(int rows, int cols);
void fill_matrix_random_char(char **matrix, int rows, int cols);
void fill_matrix_random_int(int **matrix, int rows, int cols);
void fill_matrix_random_float(float **matrix, int rows, int cols);
void fill_matrix_random_double(double **matrix, int rows, int cols);
void destroy_matrix_char(char ***matrix, int rows);
void destroy_matrix_int(int ***matrix, int rows);
void destroy_matrix_float(float ***matrix, int rows);
void destroy_matrix_double(double ***matrix, int rows);

char* create_linear_matrix_char(int rows, int cols);
int* create_linear_matrix_int(int rows, int cols);
float* create_linear_matrix_float(int rows, int cols);
double* create_linear_matrix_double(int rows, int cols);
void fill_linear_matrix_random_char(char *matrix, int rows, int cols);
void fill_linear_matrix_random_int(int *matrix, int rows, int cols);
void fill_linear_matrix_random_float(float *matrix, int rows, int cols);
void fill_linear_matrix_random_double(double *matrix, int rows, int cols);
void destroy_linear_matrix_char(char **matrix);
void destroy_linear_matrix_int(int **matrix);
void destroy_linear_matrix_float(float **matrix);
void destroy_linear_matrix_double(double **matrix);

void print_matrix_char(char **a, int rows, int cols);
void print_matrix_int(int **a, int rows, int cols);
void print_matrix_float(float **a, int rows, int cols);
void print_matrix_double(double **a, int rows, int cols);

void print_linear_matrix_char(char *a, int rows, int cols);
void print_linear_matrix_int(int *a, int rows, int cols);
void print_linear_matrix_float(float *a, int rows, int cols);
void print_linear_matrix_double(double *a, int rows, int cols);

void print_array_char(char *a, int size);
void print_array_int(int *a, int size);
void print_array_float(float *a, int size);
void print_array_double(double *a, int size);

bool isEqual_array_char(char *a, char *b, int size);
bool isEqual_array_int(int *a, int *b, int size);
bool isEqual_array_float(float *a, float *b, int size);
bool isEqual_array_double(double *a, double *b, int size);

bool isEqual_matrix_char(char **a, char **b, int rows, int cols);
bool isEqual_matrix_int(int **a, int **b, int rows, int cols);
bool isEqual_matrix_float(float **a, float **b, int rows, int cols);
bool isEqual_matrix_double(double **a, double **b, int rows, int cols);

bool isEqual_linear_matrix_char(char *a, char *b, int rows, int cols);
bool isEqual_linear_matrix_int(int *a, int *b, int rows, int cols);
bool isEqual_linear_matrix_float(float *a, float *b, int rows, int cols);
bool isEqual_linear_matrix_double(double *a, double *b, int rows, int cols);

#endif
