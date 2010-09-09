/**
 * @file dataStructure.cpp
 *
 * @brief Library with auxiliary functions to manage data types.
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
#include <cmath>
#include <malloc.h>

#include "dataStructure.h"

using namespace std;

/**
 * Create an aligned array of chars.
 *
 * @param[in]	size	size of the array
 * @return		Array of chars.
 */
char* create_array_char(int size)
{
	char *array;
	
	array = (char*)memalign(16, sizeof(char)*size);

	return array;
}

/**
 * Create an aligned array of ints.
 *
 * @param[in]	size	size of the array
 * @return		Array of ints.
 */
int* create_array_int(int size)
{
	int *array;
	
	array = (int*)memalign(16, sizeof(int)*size);

	return array;
}

/**
 * Create an aligned array of floats.
 *
 * @param[in]	size	size of the array
 * @return		Array of floats.
 */
float* create_array_float(int size)
{
	float *array;
	
	array = (float*)memalign(16, sizeof(float)*size);

	return array;
}

/**
 * Create an aligned array of doubles.
 *
 * @param[in]	size	size of the array
 * @return		Array of doubles.
 */
double* create_array_double(int size)
{
	double *array;
	
	array = (double*)memalign(16, sizeof(double)*size);

	return array;
}

/**
 * Fill an array of chars with random values.
 *
 * @param[in]	array	the array to fill
 * @param[in]	size	size of the array
 */
void fill_array_random_char(char *array, int size)
{
	for(int i=0; i<size; i++)
		array[i]=(char)random();
}

/**
 * Fill an array of ints with random values.
 *
 * @param[in]	array	the array to fill
 * @param[in]	size	size of the array
 */
void fill_array_random_int(int *array, int size)
{
	for(int i=0; i<size; i++)
		array[i]=(int)random();
}

/**
 * Fill an array of floats with random values.
 *
 * @param[in]	array	the array to fill
 * @param[in]	size	size of the array
 */
void fill_array_random_float(float *array, int size)
{
	for(int i=0; i<size; i++)
		array[i]=(float)random();
}

/**
 * Fill an array of doubles with random values.
 *
 * @param[in]	array	the array to fill
 * @param[in]	size	size of the array
 */
void fill_array_random_double(double *array, int size)
{
	for(int i=0; i<size; i++)
		array[i]=(double)random();
}

/**
 * Free the memory of an array.
 *
 * @param[in]	array	the array
 */
void destroy_array_char(char **array)
{
	free (*array);
	*array = NULL;
}

/**
 * Free the memory of an array.
 *
 * @param[in]	array	the array
 */
void destroy_array_int(int **array)
{
	free (*array);
	*array = NULL;
}


/**
 * Free the memory of an array.
 *
 * @param[in]	array	the array
 */
void destroy_array_float(float **array)
{
	free (*array);
	*array = NULL;
}

/**
 * Free the memory of an array.
 *
 * @param[in]	array	the array
 */
void destroy_array_double(double **array)
{
	free (*array);
	*array = NULL;
}

/**
 * Create an aligned matrix of chars.
 *
 * @param[in]	rows	number of rows of the matrix
 * @param[in]	cols	number of columns of the matrix
 * @return		Matrix.
 */
char** create_matrix_char(int rows, int cols)
{
	int i = 0;
	char **matrix;

	matrix = (char**)calloc(rows, sizeof(char*));

	for(i = 0; i < rows; i++)
		matrix[i] = (char*)memalign(16, cols*sizeof(char));

	return matrix;
}

/**
 * Create an aligned matrix of ints.
 *
 * @param[in]	rows	number of rows of the matrix
 * @param[in]	cols	number of columns of the matrix
 * @return		Matrix.
 */
int** create_matrix_int(int rows, int cols)
{
	int i = 0;
	int **matrix;

	matrix = (int**)calloc(rows, sizeof(int*));

	for(i = 0; i < rows; i++)
		matrix[i] = (int*)memalign(16, cols*sizeof(int));

	return matrix;
}

/**
 * Create an aligned matrix of floats.
 *
 * @param[in]	rows	number of rows of the matrix
 * @param[in]	cols	number of columns of the matrix
 * @return		Matrix.
 */
float** create_matrix_float(int rows, int cols)
{
	int i = 0;
	float **matrix;

	matrix = (float**)calloc(rows, sizeof(float*));

	for(i = 0; i < rows; i++)
		matrix[i] = (float*)memalign(16, cols*sizeof(float));

	return matrix;
}

/**
 * Create an aligned matrix of doubles.
 *
 * @param[in]	rows	number of rows of the matrix
 * @param[in]	cols	number of columns of the matrix
 * @return		Matrix.
 */
double** create_matrix_double(int rows, int cols)
{
	int i = 0;
	double **matrix;

	matrix = (double**)calloc(rows, sizeof(double*));

	for(i = 0; i < rows; i++)
		matrix[i] = (double*)memalign(16, cols*sizeof(double));

	return matrix;
}

/**
 * Fill a matrix of chars with random values.
 *
 * @param[in]	array	the matrix to fill
 * @param[in]	rows	number of rows
 * @param[in]	cols	number of columns
 */
void fill_matrix_random_char(char **array, int rows, int cols)
{
	for(int i=0; i<rows; i++)
		for(int j=0; j<cols; j++)
			array[i][j] = (char)random();
}

/**
 * Fill a matrix of ints with random values.
 *
 * @param[in]	array	the matrix to fill
 * @param[in]	rows	number of rows
 * @param[in]	cols	number of columns
 */
void fill_matrix_random_int(int **array, int rows, int cols)
{
	for(int i=0; i<rows; i++)
		for(int j=0; j<cols; j++)
			array[i][j] = (int)random();
}

/**
 * Fill a matrix of floats with random values.
 *
 * @param[in]	array	the matrix to fill
 * @param[in]	rows	number of rows
 * @param[in]	cols	number of columns
 */
void fill_matrix_random_float(float **array, int rows, int cols)
{
	for(int i=0; i<rows; i++)
		for(int j=0; j<cols; j++)
			array[i][j] = (float)random();
}

/**
 * Fill a matrix of doubles with random values.
 *
 * @param[in]	array	the matrix to fill
 * @param[in]	rows	number of rows
 * @param[in]	cols	number of columns
 */
void fill_matrix_random_double(double **array, int rows, int cols)
{
	for(int i=0; i<rows; i++)
		for(int j=0; j<cols; j++)
			array[i][j] = (double)random();
}

/**
 * Free the memory occupied by a matrix of chars.
 *
 * @param[in]	matrix	the matrix
 * @param[in]	rows	number of rows
 */
void destroy_matrix_char(char ***matrix, int rows)
{
	int i = 0;

	for(i = 0; i < rows; i++)
		free((*matrix)[i]);

	free(*matrix);
	*matrix = NULL;
}

/**
 * Free the memory occupied by a matrix of ints.
 *
 * @param[in]	matrix	the matrix
 * @param[in]	rows	number of rows
 */
void destroy_matrix_int(int ***matrix, int rows)
{
	int i = 0;

	for(i = 0; i < rows; i++)
		free((*matrix)[i]);

	free(*matrix);
	*matrix = NULL;
}

/**
 * Free the memory occupied by a matrix of floats.
 *
 * @param[in]	matrix	the matrix
 * @param[in]	rows	number of rows
 */
void destroy_matrix_float(float ***matrix, int rows)
{
	int i = 0;

	for(i = 0; i < rows; i++)
		free((*matrix)[i]);

	free(*matrix);
	*matrix = NULL;
}

/**
 * Free the memory occupied by a matrix of doubles.
 *
 * @param[in]	matrix	the matrix
 * @param[in]	rows	number of rows
 */
void destroy_matrix_double(double ***matrix, int rows)
{
	int i = 0;

	for(i = 0; i < rows; i++)
		free((*matrix)[i]);

	free(*matrix);
	*matrix = NULL;
}

/**
 * Create an aligned linear matrix of chars.
 *
 * @param[in]	rows	number of rows of the matrix
 * @param[in]	cols	number of columns of the matrix
 * @return		linerar matrix.
 */
char* create_linear_matrix_char(int rows, int cols)
{
	char *matrix;
	
	matrix = (char*)memalign(16, rows*cols*sizeof(char));

	return matrix;
}

/**
 * Create an aligned linear matrix of ints.
 *
 * @param[in]	rows	number of rows of the matrix
 * @param[in]	cols	number of columns of the matrix
 * @return		linear matrix.
 */
int* create_linear_matrix_int(int rows, int cols)
{
	int *matrix;
	
	matrix = (int*)memalign(16, rows*cols*sizeof(int));

	return matrix;
}

/**
 * Create an aligned linear matrix of floats.
 *
 * @param[in]	rows	number of rows of the matrix
 * @param[in]	cols	number of columns of the matrix
 * @return		linear matrix.
 */
float* create_linear_matrix_float(int rows, int cols)
{
	float *matrix;
	
	matrix = (float*)memalign(16, rows*cols*sizeof(float));

	return matrix;
}

/**
 * Create an aligned linear matrix of doubles.
 *
 * @param[in]	rows	number of rows of the matrix
 * @param[in]	cols	number of columns of the matrix
 * @return		linear matrix.
 */
double* create_linear_matrix_double(int rows, int cols)
{
	double *matrix;
	
	matrix = (double*)memalign(16, rows*cols*sizeof(double));

	return matrix;
}

/**
 * Fill an linear matrix of chars with random values.
 *
 * @param[in]	matrix	the linear matrix to fill
 * @param[in]	rows	number of rows the linear matrix
 * @param[in]	cols	number of columns of the linear matrix
 */
void fill_linear_matrix_random_char(char *matrix, int rows, int cols)
{
	int size = rows*cols;
	int i = 0;
	
	for(i = 0; i < size; i++)
		matrix[i]=(char)random();
}

/**
 * Fill an linear matrix of ints with random values.
 *
 * @param[in]	matrix	the linear matrix to fill
 * @param[in]	rows	number of rows the linear matrix
 * @param[in]	cols	number of columns of the linear matrix
 */
void fill_linear_matrix_random_int(int *matrix, int rows, int cols)
{
	int size = rows*cols;
	int i = 0;
	
	for(i = 0; i < size; i++)
		matrix[i]=(int)random();
}

/**
 * Fill an linear matrix of floats with random values.
 *
 * @param[in]	matrix	the linear matrix to fill
 * @param[in]	rows	number of rows the linear matrix
 * @param[in]	cols	number of columns of the linear matrix
 */
void fill_linear_matrix_random_float(float *matrix, int rows, int cols)
{
	int size = rows*cols;
	int i = 0;
	
	for(i = 0; i < size; i++)
		matrix[i]=(float)random();
}

/**
 * Fill an linear matrix of doubles with random values.
 *
 * @param[in]	matrix	the linear matrix to fill
 * @param[in]	rows	number of rows the linear matrix
 * @param[in]	cols	number of columns of the linear matrix
 */
void fill_linear_matrix_random_double(double *matrix, int rows, int cols)
{
	int size = rows*cols;
	int i = 0;
	
	for(i = 0; i < size; i++)
		matrix[i]=(double)random();
}

/**
 * Free the memory of an linear matrix.
 *
 * @param[in]	matrix	the linear matrix
 */
void destroy_linear_matrix_char(char **matrix)
{
	free (*matrix);
	*matrix = NULL;
}

/**
 * Free the memory of an linear matrix.
 *
 * @param[in]	matrix	the linear matrix
 */
void destroy_linear_matrix_int(int **matrix)
{
	free (*matrix);
	*matrix = NULL;
}

/**
 * Free the memory of an linear matrix.
 *
 * @param[in]	matrix	the linear matrix
 */
void destroy_linear_matrix_float(float **matrix)
{
	free (*matrix);
	*matrix = NULL;
}

/**
 * Free the memory of an linear matrix.
 *
 * @param[in]	matrix	the linear matrix
 */
void destroy_linear_matrix_double(double **matrix)
{
	free (*matrix);
	*matrix = NULL;
}

/**
 * Prints the content of a matrix of chars.
 *
 * @param[in]	a	the matrix
 * @param[in]	rows	number of rows
 * @param[in]	cols	number of cols
 */
void print_matrix_char(char **a, int rows, int cols)
{
	int i = 0, j = 0;

	cout<<"Matrix:\n";

	for(i = 0; i < rows; i++)
	{
		cout<<"|";
		for(j = 0; j < cols; j++)
		{
			cout<<" "<<a[i][j]<<"|";
		}
		cout<<"\n";
	}

	cout<<"\n";
}

/**
 * Prints the content of a matrix of ints.
 *
 * @param[in]	a	the matrix
 * @param[in]	rows	number of rows
 * @param[in]	cols	number of cols
 */
void print_matrix_int(int **a, int rows, int cols)
{
	int i = 0, j = 0;

	cout<<"Matrix:\n";

	for(i = 0; i < rows; i++)
	{
		cout<<"|";
		for(j = 0; j < cols; j++)
		{
			cout<<" "<<a[i][j]<<"|";
		}
		cout<<"\n";
	}

	cout<<"\n";
}

/**
 * Prints the content of a matrix of floats.
 *
 * @param[in]	a	the matrix
 * @param[in]	rows	number of rows
 * @param[in]	cols	number of cols
 */
void print_matrix_float(float **a, int rows, int cols)
{
	int i = 0, j = 0;

	cout<<"Matrix:\n";

	for(i = 0; i < rows; i++)
	{
		cout<<"|";
		for(j = 0; j < cols; j++)
		{
			cout<<" "<<a[i][j]<<"|";
		}
		cout<<"\n";
	}

	cout<<"\n";
}

/**
 * Prints the content of a matrix of doubles.
 *
 * @param[in]	a	the matrix
 * @param[in]	rows	number of rows
 * @param[in]	cols	number of cols
 */
void print_matrix_double(double **a, int rows, int cols)
{
	int i = 0, j = 0;

	cout<<"Matrix:\n";

	for(i = 0; i < rows; i++)
	{
		cout<<"|";
		for(j = 0; j < cols; j++)
		{
			cout<<" "<<a[i][j]<<"|";
		}
		cout<<"\n";
	}

	cout<<"\n";
}

/**
 * Prints the content of a linear matrix of chars.
 *
 * @param[in]	a	the linear matrix
 * @param[in]	rows	number of rows
 * @param[in]	cols	number of cols
 */
void print_linear_matrix_char(char *a, int rows, int cols)
{
	int i = 0, j = 0;

	cout<<"Matrix:\n";

	for(i = 0; i < rows; i++)
	{
		cout<<"|";
		for(j = 0; j < cols; j++)
		{
			cout<<" "<<a[i*cols+j]<<"|";
		}
		cout<<"\n";
	}

	cout<<"\n";
}

/**
 * Prints the content of a linear matrix of ints.
 *
 * @param[in]	a	the linear matrix
 * @param[in]	rows	number of rows
 * @param[in]	cols	number of cols
 */
void print_linear_matrix_int(int *a, int rows, int cols)
{
	int i = 0, j = 0;

	cout<<"Matrix:\n";

	for(i = 0; i < rows; i++)
	{
		cout<<"|";
		for(j = 0; j < cols; j++)
		{
			cout<<" "<<a[i*cols+j]<<"|";
		}
		cout<<"\n";
	}

	cout<<"\n";
}

/**
 * Prints the content of a linear matrix of floats.
 *
 * @param[in]	a	the linear matrix
 * @param[in]	rows	number of rows
 * @param[in]	cols	number of cols
 */
void print_linear_matrix_float(float *a, int rows, int cols)
{
	int i = 0, j = 0;

	cout<<"Matrix:\n";

	for(i = 0; i < rows; i++)
	{
		cout<<"|";
		for(j = 0; j < cols; j++)
		{
			cout<<" "<<a[i*cols+j]<<"|";
		}
		cout<<"\n";
	}

	cout<<"\n";
}

/**
 * Prints the content of a linear matrix of doubles.
 *
 * @param[in]	a	the linear matrix
 * @param[in]	rows	number of rows
 * @param[in]	cols	number of cols
 */
void print_linear_matrix_double(double *a, int rows, int cols)
{
	int i = 0, j = 0;

	cout<<"Matrix:\n";

	for(i = 0; i < rows; i++)
	{
		cout<<"|";
		for(j = 0; j < cols; j++)
		{
			cout<<" "<<a[i*cols+j]<<"|";
		}
		cout<<"\n";
	}

	cout<<"\n";
}

/**
 * Prints the content of an array of chars.
 *
 * @param[in]	a	the array
 * @param[in]	size	size of the array
 */
void print_array_char(char *a, int size)
{
	int i = 0;

	cout<<"Array:\n|";

	for(i = 0; i < size; i++)
		cout<<" "<< int(static_cast<unsigned char>(a[i]))<<"|";

	cout<<"\n";
}

/**
 * Prints the content of an array of ints.
 *
 * @param[in]	a	the array
 * @param[in]	size	size of the array
 */
void print_array_int(int *a, int size)
{
	int i = 0;

	cout<<"Array:\n|";

	for(i = 0; i < size; i++)
		cout<<" "<< int(static_cast<unsigned char>(a[i]))<<"|";

	cout<<"\n";
}

/**
 * Prints the content of an array of floats.
 *
 * @param[in]	a	the array
 * @param[in]	size	size of the array
 */
void print_array_float(float *a, int size)
{
	int i = 0;

	cout<<"Array:\n|";

	for(i = 0; i < size; i++)
		cout<<" "<<a[i]<<"|";

	cout<<"\n";
}

/**
 * Prints the content of an array of doubles.
 *
 * @param[in]	a	the array
 * @param[in]	size	size of the array
 */
void print_array_double(double *a, int size)
{
	int i = 0;

	cout<<"Array:\n|";

	for(i = 0; i < size; i++)
		cout<<" "<<a[i]<<"|";

	cout<<"\n";
}


/**
 * Compares two arrays of chars.
 *
 * @param[in]	a	first array
 * @param[in]	b	second array
 * @param[in]	size	size of the arrays
 * @return 	True if arrays are equal, otherwise false.
 */
bool isEqual_array_char(char *a, char *b, int size)
{
	int i = 0;
	bool rv = true;

	for(i = 0; i < size; i++)
		if(a[i] != b[i])
		{
			rv = false;
			break;
		}

	return rv;
}

/**
 * Compares two arrays of ints.
 *
 * @param[in]	a	first array
 * @param[in]	b	second array
 * @param[in]	size	size of the arrays
 * @return 	True if arrays are equal, otherwise false.
 */
bool isEqual_array_int(int *a, int *b, int size)
{
	int i = 0;
	bool rv = true;

	for(i = 0; i < size; i++)
		if(a[i] != b[i])
		{
			rv = false;
			break;
		}

	return rv;
}

/**
 * Compares two arrays of floats.
 *
 * @param[in]	a	first array
 * @param[in]	b	second array
 * @param[in]	size	size of the arrays
 * @return 	True if arrays are equal, otherwise false.
 */
bool isEqual_array_float(float *a, float *b, int size)
{
	int i = 0;
	bool rv = true;

	for(i = 0; i < size; i++)
		if(a[i] != b[i])
		{
			rv = false;
			break;
		}

	return rv;
}

/**
 * Compares two arrays of doubles.
 *
 * @param[in]	a	first array
 * @param[in]	b	second array
 * @param[in]	size	size of the arrays
 * @return 	True if arrays are equal, otherwise false.
 */
bool isEqual_array_double(double *a, double *b, int size)
{
	int i = 0;
	bool rv = true;

	for(i = 0; i < size; i++)
		if(a[i] != b[i])
		{
			rv = false;
			break;
		}

	return rv;
}

/**
 * Compares two matrixes of chars.
 *
 * @param[in]	a	first matrix
 * @param[in]	b	second matrix
 * @param[in]	rows	number of rows
 * @param[in]	cols	number of columns
 * @return 	True if arrays are equal, otherwise false.
 */
bool isEqual_matrix_char(char **a, char **b, int rows, int cols)
{
	int i = 0, j = 0;
	bool rv = true;

	for(i = 0; i < rows; i++)
		for(j = 0; j < cols; j++)
		if(a[i][j] != b[i][j])
		{
			rv = false;
			break;
		}

	return rv;
}

/**
 * Compares two matrixes of ints.
 *
 * @param[in]	a	first matrix
 * @param[in]	b	second matrix
 * @param[in]	rows	number of rows
 * @param[in]	cols	number of columns
 * @return 	True if arrays are equal, otherwise false.
 */
bool isEqual_matrix_int(int **a, int **b, int rows, int cols)
{
	int i = 0, j = 0;
	bool rv = true;

	for(i = 0; i < rows; i++)
		for(j = 0; j < cols; j++)
		if(a[i][j] != b[i][j])
		{
			rv = false;
			break;
		}

	return rv;
}

/**
 * Compares two matrixes of floats.
 *
 * @param[in]	a	first matrix
 * @param[in]	b	second matrix
 * @param[in]	rows	number of rows
 * @param[in]	cols	number of columns
 * @return 	True if arrays are equal, otherwise false.
 */
bool isEqual_matrix_float(float **a, float **b, int rows, int cols)
{
	int i = 0, j = 0;
	bool rv = true;

	for(i = 0; i < rows; i++)
		for(j = 0; j < cols; j++)
		if(a[i][j] != b[i][j])
		{
			rv = false;
			break;
		}

	return rv;
}

/**
 * Compares two matrixes of doubles.
 *
 * @param[in]	a	first matrix
 * @param[in]	b	second matrix
 * @param[in]	rows	number of rows
 * @param[in]	cols	number of columns
 * @return 	True if arrays are equal, otherwise false.
 */
bool isEqual_matrix_double(double **a, double **b, int rows, int cols)
{
	int i = 0, j = 0;
	bool rv = true;

	for(i = 0; i < rows; i++)
	{
		for(j = 0; j < cols; j++)
		{
			if(a[i][j] != b[i][j])
			{
				rv = false;
				break;
			}
		}

		if(!rv)
		{
			break;
		}
	}

	return rv;
}

/**
 * Compares two linear matrixes of chars.
 *
 * @param[in]	a	first matrix
 * @param[in]	b	second matrix
 * @param[in]	rows	number of rows
 * @param[in]	cols	number of columns
 * @return 	True if arrays are equal, otherwise false.
 */
bool isEqual_linear_matrix_char(char *a, char *b, int rows, int cols)
{
	int i = 0;
	int size = rows * cols;
	bool rv = true;

	for(i = 0; i < size; i++)
		if(a[i] != b[i])
		{
			rv = false;
			break;
		}

	return rv;
}

/**
 * Compares two linear matrixes of ints.
 *
 * @param[in]	a	first matrix
 * @param[in]	b	second matrix
 * @param[in]	rows	number of rows
 * @param[in]	cols	number of columns
 * @return 	True if arrays are equal, otherwise false.
 */
bool isEqual_linear_matrix_int(int *a, int *b, int rows, int cols)
{
	int i = 0;
	int size = rows * cols;
	bool rv = true;

	for(i = 0; i < size; i++)
		if(a[i] != b[i])
		{
			rv = false;
			break;
		}

	return rv;
}

/**
 * Compares two linear matrixes of floats.
 *
 * @param[in]	a	first matrix
 * @param[in]	b	second matrix
 * @param[in]	rows	number of rows
 * @param[in]	cols	number of columns
 * @return 	True if arrays are equal, otherwise false.
 */
bool isEqual_linear_matrix_float(float *a, float *b, int rows, int cols)
{
	int i = 0;
	int size = rows * cols;
	bool rv = true;

	for(i = 0; i < size; i++)
		if(a[i] != b[i])
		{
			rv = false;
			break;
		}

	return rv;
}

/**
 * Compares two linear matrixes of doubles.
 *
 * @param[in]	a	first matrix
 * @param[in]	b	second matrix
 * @param[in]	rows	number of rows
 * @param[in]	cols	number of columns
 * @return 	True if arrays are equal, otherwise false.
 */
bool isEqual_linear_matrix_double(double *a, double *b, int rows, int cols)
{
	int i = 0;
	int size = rows * cols;
	bool rv = true;

	for(i = 0; i < size; i++)
		if(a[i] != b[i])
		{
			rv = false;
			break;
		}

	return rv;
}

/**
 *
 *
 */
bool isNearBy_float(float a, float b, float delta)
{
	bool rv = false;
	float dif = fabs(a - b);

	if(dif < delta)
		rv = true;

	return rv;
}

/**
 *
 *
 */
bool isNearBy_double(double a, double b, double delta)
{
	bool rv = false;
	double dif = fabs(a - b);

	if(dif < delta)
		rv = true;

	return rv;
}

/**
 *
 */
bool isNearBy_array_float(float *a, float *b, int size, float delta)
{
	bool rv = true;
	int i = 0;

	for(i = 0; i < size; i++)
	{
		if(!isNearBy_float(a[i], b[i], delta))
		{
			rv = false;
			break;
		}
	}

	return rv;
}

/**
 *
 */
bool isNearBy_array_double(double *a, double *b, int size, double delta)
{
	bool rv = true;
	int i = 0;

	for(i = 0; i < size; i++)
	{
		if(!isNearBy_double(a[i], b[i], delta))
		{
			rv = false;
			break;
		}
	}

	return rv;
}

bool isNearBy_matrix_float(float **a, float **b, float delta, int rows, int cols)
{
	int i = 0, j = 0;
	bool rv = true;

	for(i = 0; i < rows; i++)
	{
		for(j = 0; j < cols; j++)
		{
			if(!isNearBy_float(a[i][j], b[i][j], delta))
			{
				rv = false;
				break;
			}
		}

		if(!rv)
		{
			break;
		}
	}

	return rv;
}

bool isNearBy_matrix_double(double **a, double **b, double delta, int rows, int cols)
{
	int i = 0, j = 0;
	bool rv = true;

	for(i = 0; i < rows; i++)
	{
		for(j = 0; j < cols; j++)
		{
			if(!isNearBy_double(a[i][j], b[i][j], delta))
			{
				rv = false;
				break;
			}
		}

		if(!rv)
		{
			break;
		}
	}

	return rv;
}
