#include <iostream>
#include <cstring>
#include <cstdlib>

#include "libMultimedia.h"
#include "dataStructure.h"

#define SIZE 1000000
#define SIZE2 100
#define COLS 1000
#define ROWS 500
#define COLS2 10
#define ROWS2 10
#define REPEAT 10

using namespace std;

void testSumelem()
{
	clock_t init, end;
	float time1, time2;

	char *array_char = create_array_char(SIZE),
	     result_char1 = 0, 
	     result_char2 = 0,
	     result_char3 = 0;
	int *array_int = create_array_int(SIZE),
	    result_int1 = 0,
	    result_int2 = 0,
	    result_int3 = 0,
	    result_int4 = 0;
	float *array_float = create_array_float(SIZE),
	      result_float1 = 0,
	      result_float2 = 0,
	      result_float3 = 0,
	      result_float4 = 0;
	double *array_double = create_array_double(SIZE),
	       result_double1 = 0,
	       result_double2 = 0,
	       result_double3 = 0,
	       result_double4 = 0;

	fill_array_random_char(array_char, SIZE);
	fill_array_random_int(array_int, SIZE);
	fill_array_random_float(array_float, SIZE);
	fill_array_random_double(array_double, SIZE);

	/*** char ***/

	init = clock();
	for(int i=0; i<REPEAT; i++)
		result_char1 = sumelem_char(array_char, SIZE);
	end = clock();
	time1 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "sumelem_char time: " << time1 << endl;

	init = clock();
	for(int i=0; i<REPEAT; i++)
		result_char2 = sumelem_char_sse2(array_char, SIZE);
	end = clock();
	time2 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "sumelem_char_sse2 time: " << time2 << endl;

	cout << "speedup: " << time1/time2 << endl;

	init = clock();
	for(int i=0; i<REPEAT; i++)
		result_char3 = sumelem_char_unrolled_sse2(array_char, SIZE);
	end = clock();
	time2 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "sumelem_char_unrolled_sse2 time: " << time2 << endl;

	cout << "speedup: " << time1/time2 << endl;

	cout << "Compare Result: ";
	if( result_char1 == result_char2 && result_char2 == result_char3)
		cout << "Equal" << endl;
	else
		cout << "Not Equal!" << endl;

	/*** int ***/

	init = clock();
	for(int i=0; i<REPEAT; i++)
		result_int1 = sumelem_int(array_int, SIZE);
	end = clock();
	time1 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "sumelem_int time: " << time1 << endl;

	init = clock();
	for(int i=0; i<REPEAT; i++)
		result_int2 = sumelem_int_sse2(array_int, SIZE);
	end = clock();
	time2 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "sumelem_int_sse2 time: " << time2 << endl;
	cout << "speedup : " << time1/time2 << endl;

	init = clock();
	for(int i=0; i<REPEAT; i++)
		result_int3 = sumelem_int_sse3(array_int, SIZE);
	end = clock();
	time2 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "sumelem_int_sse3 time: " << time2 << endl;
	cout << "speedup : " << time1/time2 << endl;

	init = clock();
	for(int i=0; i<REPEAT; i++)
		result_int4 = sumelem_int_unrolled_sse2(array_int, SIZE);
	end = clock();
	time2 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "sumelem_int_unrolled_sse2 time: " << time2 << endl;
	cout << "speedup : " << time1/time2 << endl;

	cout << "Compare Result: ";
	if( result_int1 == result_int2 && result_int1 == result_int3 && result_int1 == result_int4)
		cout << "Equal" << endl;
	else
		cout << "Not Equal!" << endl;

	/*** float ***/

	init = clock();
	for(int i=0; i<REPEAT; i++)
		result_float1 = sumelem_float(array_float, SIZE);
	end = clock();
	time1 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "sumelem_float time: " << time1 << endl;

	init = clock();
	for(int i=0; i<REPEAT; i++)
		result_float2 = sumelem_float_sse2(array_float, SIZE);
	end = clock();
	time2 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "sumelem_float_sse2 time: " << time2 << endl;
	cout << "speedup : " << time1/time2 << endl;

	init = clock();
	for(int i=0; i<REPEAT; i++)
		result_float3 = sumelem_float_sse3(array_float, SIZE);
	end = clock();
	time2 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "sumelem_float_sse3 time: " << time2 << endl;
	cout << "speedup : " << time1/time2 << endl;

	init = clock();
	for(int i=0; i<REPEAT; i++)
		result_float4 = sumelem_float_unrolled_sse2(array_float, SIZE);
	end = clock();
	time2 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "sumelem_float_unrolled_sse2 time: " << time2 << endl;
	cout << "speedup : " << time1/time2 << endl;

	cout<<"Results: "<<result_float1<<"; "<<result_float2<<"; "<<result_float3<<"; "<<result_float4<<"; "<<endl;	

	cout << "Compare Result: ";
	if( result_float1 == result_float2 && result_float2 == result_float3 && result_float1 == result_float4)
		cout << "Equal" << endl;
	else
		cout << "Not Equal!" << endl;

	/*** double ***/

	init = clock();
	for(int i=0; i<REPEAT; i++)
		result_double1 = sumelem_double(array_double, SIZE);
	end = clock();
	time1 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "sumelem_double time: " << time1 << endl;

	init = clock();
	for(int i=0; i<REPEAT; i++)
		result_double2 = sumelem_double_sse2(array_double, SIZE);
	end = clock();
	time2 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "sumelem_double_sse2 time: " << time2 << endl;
	cout << "speedup : " << time1/time2 << endl;

	init = clock();
	for(int i=0; i<REPEAT; i++)
		result_double3 = sumelem_double_sse3(array_double, SIZE);
	end = clock();
	time2 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "sumelem_double_sse3 time: " << time2 << endl;
	cout << "speedup : " << time1/time2 << endl;

	init = clock();
	for(int i=0; i<REPEAT; i++)
		result_double4 = sumelem_double_unrolled_sse2(array_double, SIZE);
	end = clock();
	time2 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "sumelem_double_unrolled_sse2 time: " << time2 << endl;
	cout << "speedup : " << time1/time2 << endl;

	cout << "Compare Result: ";
	if( result_double1 == result_double2 && result_double2 == result_double3 && result_double1 == result_double4 )
		cout << "Equal" << endl;
	else
		cout << "Not Equal!" << endl;

	destroy_array_char(&array_char);
	destroy_array_int(&array_int);
	destroy_array_float(&array_float);
	destroy_array_double(&array_double);
}

void testCmp()
{
	int i;
	clock_t init, end;
	float time1, time2, time3;

	char *array_char1 = create_array_char(SIZE),
	     *array_char2 = create_array_char(SIZE),
	     *result_char1 = create_array_char(SIZE), 
	     *result_char2 = create_array_char(SIZE),
	     *result_char3 = create_array_char(SIZE);
	int *array_int1 = create_array_int(SIZE),
	    *array_int2 = create_array_int(SIZE),
	    *result_int1 = create_array_int(SIZE),
	    *result_int2 = create_array_int(SIZE);
	float *array_float1 = create_array_float(SIZE),
	      *array_float2 = create_array_float(SIZE),
	      *result_float1 = create_array_float(SIZE),
	      *result_float2 = create_array_float(SIZE);
	double *array_double1 = create_array_double(SIZE),
	       *array_double2 = create_array_double(SIZE),
	       *result_double1 = create_array_double(SIZE),
	       *result_double2 = create_array_double(SIZE);

	fill_array_random_char(array_char1, SIZE);
	for(int i=0; i<SIZE; i++)
	{
		if( i%10 == 0)
			array_char2[i] = array_char1[i];
		else
			array_char2[i] = i;
	}
	fill_array_random_int(array_int1, SIZE);
	for(int i=0; i<SIZE; i++)
	{
		if( i%10 == 0)
			array_int2[i] = array_int1[i];
		else
			array_int2[i] = i;
	}
	fill_array_random_float(array_float1, SIZE);
	for(int i=0; i<SIZE; i++)
	{
		if( i%10 == 0)
			array_float2[i] = array_float1[i];
		else
			array_float2[i] = i;
	}
	fill_array_random_double(array_double1, SIZE);
	for(int i=0; i<SIZE; i++)
	{
		if( i%10 == 0)
			array_double2[i] = array_double1[i];
		else
			array_double2[i] = i;
	}

	/*** char ***/

	init = clock();
	for(int i=0; i<REPEAT; i++)
		cmp_equal_char(array_char1, array_char2, result_char1, SIZE);
	end = clock();
	time1 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "cmp_equal_char time: " << time1 << endl;

	init = clock();
	for(int i=0; i<REPEAT; i++)
		cmp_equal_char_sse2(array_char1, array_char2, result_char2, SIZE);
	end = clock();
	time2 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "cmp_equal_char_ss2 time: " << time2 << endl;

	cout << "speedup: " << time1/time2 << endl;

	cout << "Compare Result: ";
	for(i=0; i<SIZE && result_char1[i] == result_char2[i]; i++);
	if( i==SIZE )
		cout << "Equal" << endl;
	else
		cout << "Not Equal!" << endl;

	/*** int ***/

	init = clock();
	for(int i=0; i<REPEAT; i++)
		cmp_equal_int(array_int1, array_int2, result_int1, SIZE);
	end = clock();
	time1 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "cmp_equal_int time: " << time1 << endl;

	init = clock();
	for(int i=0; i<REPEAT; i++)
		cmp_equal_int_sse2(array_int1, array_int2, result_int2, SIZE);
	end = clock();
	time2 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "cmp_equal_int_ss2 time: " << time2 << endl;

	cout << "speedup: " << time1/time2 << endl;

	cout << "Compare Result: ";
	for(i=0; i<SIZE && result_int1[i] == result_int2[i]; i++);
	if( i==SIZE )
		cout << "Equal" << endl;
	else
		cout << "Not Equal!" << endl;

	/*** float ***/

	init = clock();
	for(int i=0; i<REPEAT; i++)
		cmp_equal_float(array_float1, array_float2, result_float1, SIZE);
	end = clock();
	time1 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "cmp_equal_float time: " << time1 << endl;

	init = clock();
	for(int i=0; i<REPEAT; i++)
		cmp_equal_float_sse2(array_float1, array_float2, result_float2, SIZE);
	end = clock();
	time2 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "cmp_equal_float_ss2 time: " << time2 << endl;

	cout << "speedup: " << time1/time2 << endl;

	cout << "Compare Result: ";
	for(i=0; i<SIZE && (bool)result_float1[i] == (bool)result_float2[i]; i++);
	if( i==SIZE )
		cout << "Equal" << endl;
	else
		cout << "Not Equal!" << endl;

	/*** double ***/

	init = clock();
	for(int i=0; i<REPEAT; i++)
		cmp_equal_double(array_double1, array_double2, result_double1, SIZE);
	end = clock();
	time1 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "cmp_equal_double time: " << time1 << endl;

	init = clock();
	for(int i=0; i<REPEAT; i++)
		cmp_equal_double_sse2(array_double1, array_double2, result_double2, SIZE);
	end = clock();
	time2 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "cmp_equal_double_ss2 time: " << time2 << endl;

	cout << "speedup: " << time1/time2 << endl;

	cout << "Compare Result: ";
	for(i=0; i<SIZE && (bool)result_double1[i] == (bool)result_double2[i]; i++);
	if( i==SIZE )
		cout << "Equal" << endl;
	else
		cout << "Not Equal!" << endl;

	/*** greater ***/
	fill_array_random_char(array_char1, SIZE);
	fill_array_random_char(array_char2, SIZE);
	fill_array_random_int(array_int1, SIZE);
	fill_array_random_int(array_int2, SIZE);

	for(i=0; i<SIZE; i++)
		array_float1[i]=(float)i;
	for(i=0; i<SIZE; i++)
		if(i%10==0)
			array_float2[i]=i-1;
		else
			array_float2[i]=i+1;
	for(i=0; i<SIZE; i++)
		array_double1[i]=i;
	for(i=0; i<SIZE; i++)
		if(i%10==0)
			array_double2[i]=i-1;
		else
			array_double2[i]=i+1;

	/*** char ***/
	init = clock();
	for(int i=0; i<REPEAT; i++)
		cmp_greater_char(array_char1, array_char2, result_char1, SIZE);
	end = clock();
	time1 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "cmp_greater_char time: " << time1 << endl;

	init = clock();
	for(int i=0; i<REPEAT; i++)
		cmp_greater_char_sse2(array_char1, array_char2, result_char2, SIZE);
	end = clock();
	time2 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "cmp_greater_char_ss2 time: " << time2 << endl;

	cout << "speedup: " << time1/time2 << endl;

	cout << "Compare Result: ";
	for(i=0; i<SIZE && result_char1[i] == result_char2[i]; i++);
	if( i==SIZE )
		cout << "Equal" << endl;
	else
		cout << "Not Equal!" << endl;
	
	init = clock();
	for(int i=0; i<REPEAT; i++)
		cmp_greater_unrolled_char_sse2(array_char1, array_char2, result_char3, SIZE);
	end = clock();
	time3 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "cmp_greater_unrolled_char_ss2 time: " << time3 << endl;

	cout << "speedup: " << time1/time3 << endl;

	cout << "Compare Result: ";
	for(i=0; i<SIZE && result_char1[i] == result_char3[i]; i++);
	if( i==SIZE )
		cout << "Equal" << endl;
	else
		cout << "Not Equal!" << endl;

	/*** int ***/
	init = clock();
	for(int i=0; i<REPEAT; i++)
		cmp_greater_int(array_int1, array_int2, result_int1, SIZE);
	end = clock();
	time1 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "cmp_greater_int time: " << time1 << endl;

	init = clock();
	for(int i=0; i<REPEAT; i++)
		cmp_greater_int_sse2(array_int1, array_int2, result_int2, SIZE);
	end = clock();
	time2 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "cmp_greater_int_ss2 time: " << time2 << endl;

	cout << "speedup: " << time1/time2 << endl;

	cout << "Compare Result: ";
	for(i=0; i<SIZE && result_int1[i] == result_int2[i]; i++);
	if( i==SIZE )
		cout << "Equal" << endl;
	else
		cout << "Not Equal!" << endl;

	/*** float ***/
	init = clock();
	for(int i=0; i<REPEAT; i++)
		cmp_greater_float(array_float1, array_float2, result_float1, SIZE);
	end = clock();
	time1 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "cmp_greater_float time: " << time1 << endl;

	init = clock();
	for(int i=0; i<REPEAT; i++)
		cmp_greater_float_sse2(array_float1, array_float2, result_float2, SIZE);
	end = clock();
	time2 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "cmp_greater_float_ss2 time: " << time2 << endl;

	cout << "speedup: " << time1/time2 << endl;

	cout << "Compare Result: ";
	for(i=0; i<SIZE && (bool)result_float1[i] == (bool)result_float2[i]; i++);
	if( i==SIZE )
		cout << "Equal" << endl;
	else
		cout << "Not Equal!" << endl;

	/*** double ***/
	init = clock();
	for(int i=0; i<REPEAT; i++)
		cmp_greater_double(array_double1, array_double2, result_double1, SIZE);
	end = clock();
	time1 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "cmp_greater_double time: " << time1 << endl;

	init = clock();
	for(int i=0; i<REPEAT; i++)
		cmp_greater_double_sse2(array_double1, array_double2, result_double2, SIZE);
	end = clock();
	time2 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "cmp_greater_double_ss2 time: " << time2 << endl;

	cout << "speedup: " << time1/time2 << endl;

	cout << "Compare Result: ";
	for(i=0; i<SIZE && (bool)result_double1[i] == (bool)result_double2[i]; i++);
	if( i==SIZE )
		cout << "Equal" << endl;
	else
		cout << "Not Equal!" << endl;

	/*** Less ***/

	/*** char ***/
	init = clock();
	for(int i=0; i<REPEAT; i++)
		cmp_less_char(array_char1, array_char2, result_char1, SIZE);
	end = clock();
	time1 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "cmp_less_char time: " << time1 << endl;

	init = clock();
	for(int i=0; i<REPEAT; i++)
		cmp_less_char_sse2(array_char1, array_char2, result_char2, SIZE);
	end = clock();
	time2 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "cmp_less_char_ss2 time: " << time2 << endl;

	cout << "speedup: " << time1/time2 << endl;

	cout << "Compare Result: ";
	for(i=0; i<SIZE && result_char1[i] == result_char2[i]; i++);
	if( i==SIZE )
		cout << "Equal" << endl;
	else
		cout << "Not Equal!" << endl;
	
	init = clock();
	for(int i=0; i<REPEAT; i++)
		cmp_less_unrolled_char_sse2(array_char1, array_char2, result_char3, SIZE);
	end = clock();
	time3 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "cmp_less_unrolled_char_ss2 time: " << time3 << endl;

	cout << "speedup: " << time1/time3 << endl;

	cout << "Compare Result: ";
	for(i=0; i<SIZE && result_char1[i] == result_char3[i]; i++);
	if( i==SIZE )
		cout << "Equal" << endl;
	else
		cout << "Not Equal!" << endl;

	/*** int ***/
	init = clock();
	for(int i=0; i<REPEAT; i++)
		cmp_less_int(array_int1, array_int2, result_int1, SIZE);
	end = clock();
	time1 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "cmp_less_int time: " << time1 << endl;

	init = clock();
	for(int i=0; i<REPEAT; i++)
		cmp_less_int_sse2(array_int1, array_int2, result_int2, SIZE);
	end = clock();
	time2 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "cmp_less_int_ss2 time: " << time2 << endl;

	cout << "speedup: " << time1/time2 << endl;

	cout << "Compare Result: ";
	for(i=0; i<SIZE && result_int1[i] == result_int2[i]; i++);
	if( i==SIZE )
		cout << "Equal" << endl;
	else
		cout << "Not Equal!" << endl;

	/*** float ***/
	init = clock();
	for(int i=0; i<REPEAT; i++)
		cmp_less_float(array_float1, array_float2, result_float1, SIZE);
	end = clock();
	time1 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "cmp_less_float time: " << time1 << endl;

	init = clock();
	for(int i=0; i<REPEAT; i++)
		cmp_less_float_sse2(array_float1, array_float2, result_float2, SIZE);
	end = clock();
	time2 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "cmp_less_float_ss2 time: " << time2 << endl;

	cout << "speedup: " << time1/time2 << endl;

	cout << "Compare Result: ";
	for(i=0; i<SIZE && (bool)result_float1[i] == (bool)result_float2[i]; i++);
	if( i==SIZE )
		cout << "Equal" << endl;
	else
		cout << "Not Equal!" << endl;

	/*** double ***/
	init = clock();
	for(int i=0; i<REPEAT; i++)
		cmp_less_double(array_double1, array_double2, result_double1, SIZE);
	end = clock();
	time1 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "cmp_less_double time: " << time1 << endl;

	init = clock();
	for(int i=0; i<REPEAT; i++)
		cmp_less_double_sse2(array_double1, array_double2, result_double2, SIZE);
	end = clock();
	time2 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "cmp_less_double_ss2 time: " << time2 << endl;

	cout << "speedup: " << time1/time2 << endl;

	cout << "Compare Result: ";
	for(i=0; i<SIZE && (bool)result_double1[i] == (bool)result_double2[i]; i++);
	if( i==SIZE )
		cout << "Equal" << endl;
	else
		cout << "Not Equal!" << endl;

	destroy_array_char(&array_char1);
	destroy_array_char(&array_char2);
	destroy_array_char(&result_char1);
	destroy_array_char(&result_char2);
	destroy_array_int(&array_int1);
	destroy_array_int(&array_int2);
	destroy_array_int(&result_int1);
	destroy_array_int(&result_int2);
	destroy_array_float(&array_float1);
	destroy_array_float(&array_float2);
	destroy_array_float(&result_float1);
	destroy_array_float(&result_float2);
	destroy_array_double(&array_double1);
	destroy_array_double(&array_double2);
	destroy_array_double(&result_double1);
	destroy_array_double(&result_double2);
}

void testSumarray()
{
	clock_t init, end;
	float time1, time2;

	char *array_char1 = create_array_char(SIZE),
	     *array_char2 = create_array_char(SIZE),
	     *result_char1 = create_array_char(SIZE), 
	     *result_char2 = create_array_char(SIZE),
	     *result_char3 = create_array_char(SIZE);
	int *array_int1 = create_array_int(SIZE),
	    *array_int2 = create_array_int(SIZE),
	    *result_int1 = create_array_int(SIZE),
	    *result_int2 = create_array_int(SIZE),
	    *result_int3 = create_array_int(SIZE);
	float *array_float1 = create_array_float(SIZE),
	      *array_float2 = create_array_float(SIZE),
	      *result_float1 = create_array_float(SIZE),
	      *result_float2 = create_array_float(SIZE),
	      *result_float3 = create_array_float(SIZE);
	double *array_double1 = create_array_double(SIZE),
	       *array_double2 = create_array_double(SIZE),
	       *result_double1 = create_array_double(SIZE),
	       *result_double2 = create_array_double(SIZE),
	       *result_double3 = create_array_double(SIZE);

	fill_array_random_char(array_char1, SIZE);
	fill_array_random_char(array_char2, SIZE);
	fill_array_random_int(array_int1, SIZE);
	fill_array_random_int(array_int2, SIZE);
	fill_array_random_float(array_float1, SIZE);
	fill_array_random_float(array_float2, SIZE);
	fill_array_random_double(array_double1, SIZE);
	fill_array_random_double(array_double2, SIZE);

	/*** char ***/
	init = clock();
	for(int i=0; i<REPEAT; i++)
		sumarray_char(array_char1, array_char2, result_char1, SIZE);
	end = clock();
	time1 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "sumarray_char time: " << time1 << endl;

	init = clock();
	for(int i=0; i<REPEAT; i++)
		sumarray_char_sse2(array_char1, array_char2, result_char2, SIZE);
	end = clock();
	time2 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "sumarray_char_sse2 time: " << time2 << endl;

	cout << "speedup: " << time1/time2 << endl;

	init = clock();
	for(int i=0; i<REPEAT; i++)
		sumarray_char_unrolled_sse2(array_char1, array_char2, result_char3, SIZE);
	end = clock();
	time2 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "sumarray_char_unrolled_sse2 time: " << time2 << endl;

	cout << "speedup: " << time1/time2 << endl;

	cout << "Compare Result: ";
	
	if(isEqual_array_char(result_char1, result_char2, SIZE) && isEqual_array_char(result_char1, result_char3, SIZE))
		cout << "Equal" << endl;
	else
		cout << "Not Equal!" << endl;

	/*** int ***/
	init = clock();
	for(int i=0; i<REPEAT; i++)
		sumarray_int(array_int1, array_int2, result_int1, SIZE);
	end = clock();
	time1 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "sumarray_int time: " << time1 << endl;

	init = clock();
	for(int i=0; i<REPEAT; i++)
		sumarray_int_sse2(array_int1, array_int2, result_int2, SIZE);
	end = clock();
	time2 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "sumarray_int_sse2 time: " << time2 << endl;

	cout << "speedup: " << time1/time2 << endl;

	init = clock();
	for(int i=0; i<REPEAT; i++)
		sumarray_int_unrolled_sse2(array_int1, array_int2, result_int3, SIZE);
	end = clock();
	time2 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "sumarray_int_unrolled_sse2 time: " << time2 << endl;

	cout << "speedup: " << time1/time2 << endl;

	cout << "Compare Result: ";
	if(isEqual_array_int(result_int1, result_int2, SIZE) && isEqual_array_int(result_int1, result_int3, SIZE))
		cout << "Equal" << endl;
	else
		cout << "Not Equal!" << endl;

	/*** float ***/
	init = clock();
	for(int i=0; i<REPEAT; i++)
		sumarray_float(array_float1, array_float2, result_float1, SIZE);
	end = clock();
	time1 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "sumarray_float time: " << time1 << endl;

	init = clock();
	for(int i=0; i<REPEAT; i++)
		sumarray_float_sse2(array_float1, array_float2, result_float2, SIZE);
	end = clock();
	time2 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "sumarray_float_sse2 time: " << time2 << endl;

	cout << "speedup: " << time1/time2 << endl;

	init = clock();
	for(int i=0; i<REPEAT; i++)
		sumarray_float_unrolled_sse2(array_float1, array_float2, result_float3, SIZE);
	end = clock();
	time2 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "sumarray_float_unrolled_sse2 time: " << time2 << endl;

	cout << "speedup: " << time1/time2 << endl;

	cout << "Compare Result: ";
	
	if(isEqual_array_float(result_float1, result_float2, SIZE) && isEqual_array_float(result_float1, result_float3, SIZE))
		cout << "Equal" << endl;
	else
		cout << "Not Equal!" << endl;

	/*** double ***/
	init = clock();
	for(int i=0; i<REPEAT; i++)
		sumarray_double(array_double1, array_double2, result_double1, SIZE);
	end = clock();
	time1 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "sumarray_double time: " << time1 << endl;

	init = clock();
	for(int i=0; i<REPEAT; i++)
		sumarray_double_sse2(array_double1, array_double2, result_double2, SIZE);
	end = clock();
	time2 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "sumarray_double_sse2 time: " << time2 << endl;

	cout << "speedup: " << time1/time2 << endl;

	init = clock();
	for(int i=0; i<REPEAT; i++)
		sumarray_double_unrolled_sse2(array_double1, array_double2, result_double3, SIZE);
	end = clock();
	time2 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "sumarray_double_unrolled_sse2 time: " << time2 << endl;

	cout << "speedup: " << time1/time2 << endl;

	cout << "Compare Result: ";
	if(isEqual_array_double(result_double1, result_double2, SIZE) && isEqual_array_double(result_double1, result_double3, SIZE))
		cout << "Equal" << endl;
	else
		cout << "Not Equal!" << endl;

	destroy_array_char(&array_char1);
	destroy_array_char(&array_char2);
	destroy_array_char(&result_char1);
	destroy_array_char(&result_char2);
	destroy_array_char(&result_char3);
	destroy_array_int(&array_int1);
	destroy_array_int(&array_int2);
	destroy_array_int(&result_int1);
	destroy_array_int(&result_int2);
	destroy_array_int(&result_int3);
	destroy_array_float(&array_float1);
	destroy_array_float(&array_float2);
	destroy_array_float(&result_float1);
	destroy_array_float(&result_float2);
	destroy_array_float(&result_float3);
	destroy_array_double(&array_double1);
	destroy_array_double(&array_double2);
	destroy_array_double(&result_double1);
	destroy_array_double(&result_double2);
	destroy_array_double(&result_double3);
}

void testMularray()
{
	clock_t init, end;
	float time1, time2;

	float *array_float1 = create_array_float(SIZE),
	      *array_float2 = create_array_float(SIZE),
	      *result_float1 = create_array_float(SIZE),
	      *result_float2 = create_array_float(SIZE),
	      *result_float3 = create_array_float(SIZE);
	
	double *array_double1 = create_array_double(SIZE),
	       *array_double2 = create_array_double(SIZE),
	       *result_double1 = create_array_double(SIZE),
	       *result_double2 = create_array_double(SIZE),
	       *result_double3 = create_array_double(SIZE);

	fill_array_random_float(array_float1, SIZE);
	fill_array_random_float(array_float2, SIZE);
	fill_array_random_double(array_double1, SIZE);
	fill_array_random_double(array_double2, SIZE);

	/*** float ***/
	init = clock();
	for(int i=0; i<REPEAT; i++)
		mularray_float(array_float1, array_float2, result_float1, SIZE);
	end = clock();
	time1 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "mularray_float time: " << time1 << endl;

	init = clock();
	for(int i=0; i<REPEAT; i++)
		mularray_float_sse2(array_float1, array_float2, result_float2, SIZE);
	end = clock();
	time2 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "mularray_float_sse2 time: " << time2 << endl;

	cout << "speedup: " << time1/time2 << endl;

	init = clock();
	for(int i=0; i<REPEAT; i++)
		mularray_float_unrolled_sse2(array_float1, array_float2, result_float3, SIZE);
	end = clock();
	time2 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "mularray_unrolled_float_sse2 time: " << time2 << endl;

	cout << "speedup: " << time1/time2 << endl;

	cout << "Compare Result: ";
	if(isEqual_array_float(result_float1, result_float2, SIZE) && isEqual_array_float(result_float1, result_float3, SIZE))
		cout << "Equal" << endl;
	else
		cout << "Not Equal!" << endl;

	/*** double ***/
	init = clock();
	for(int i=0; i<REPEAT; i++)
		mularray_double(array_double1, array_double2, result_double1, SIZE);
	end = clock();
	time1 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "mularray_double time: " << time1 << endl;

	init = clock();
	for(int i=0; i<REPEAT; i++)
		mularray_double_sse2(array_double1, array_double2, result_double2, SIZE);
	end = clock();
	time2 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "mularray_double_sse2 time: " << time2 << endl;

	cout << "speedup: " << time1/time2 << endl;

	init = clock();
	for(int i=0; i<REPEAT; i++)
		mularray_double_unrolled_sse2(array_double1, array_double2, result_double3, SIZE);
	end = clock();
	time2 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "mularray_unrolled_double_sse2 time: " << time2 << endl;

	cout << "speedup: " << time1/time2 << endl;

	cout << "Compare Result: ";
	if(isEqual_array_double(result_double1, result_double2, SIZE) && isEqual_array_double(result_double1, result_double3, SIZE))
		cout << "Equal" << endl;
	else
		cout << "Not Equal!" << endl;

	destroy_array_float(&array_float2);
	destroy_array_float(&array_float1);
	destroy_array_float(&result_float1);
	destroy_array_float(&result_float2);
	destroy_array_float(&result_float3);
	destroy_array_double(&array_double2);
	destroy_array_double(&array_double1);
	destroy_array_double(&result_double1);
	destroy_array_double(&result_double2);
	destroy_array_double(&result_double3);
}

void testDotProduct()
{
	clock_t init, end;
	float time1, time2;

	float *array_float1 = create_array_float(SIZE),
	      *array_float2 = create_array_float(SIZE),
	      result_float1 = 0,
	      result_float2 = 0,
	      result_float3 = 0;
	double *array_double1 = create_array_double(SIZE),
	       *array_double2 = create_array_double(SIZE),
	       result_double1 = 0,
	       result_double2 = 0,
	       result_double3 = 0;

	fill_array_random_float(array_float1, SIZE);
	fill_array_random_float(array_float2, SIZE);
	fill_array_random_double(array_double1, SIZE);
	fill_array_random_double(array_double2, SIZE);

	/*** float ***/
	init = clock();
	for(int i=0; i<REPEAT; i++)
		result_float1 = dotProduct_float(array_float1, array_float2, SIZE);
	end = clock();
	time1 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "dotProduct_float time: " << time1 << endl;

	init = clock();
	for(int i=0; i<REPEAT; i++)
		result_float2 = dotProduct_float_sse2(array_float1, array_float2, SIZE);
	end = clock();
	time2 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "dotProduct_float_sse2 time: " << time2 << endl;

	cout << "speedup: " << time1/time2 << endl;

	init = clock();
	for(int i=0; i<REPEAT; i++)
		result_float3 = dotProduct_float_unrolled_sse2(array_float1, array_float2, SIZE);
	end = clock();
	time2 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "dotProduct_float_unrolled_sse2 time: " << time2 << endl;

	cout << "speedup: " << time1/time2 << endl;

	cout<<"Results: "<<result_float1<<"; "<<result_float2<<"; "<<result_float3<<endl;

	cout << "Compare Result: ";
	if(result_float1 == result_float2 && result_float1 == result_float3)
		cout << "Equal" << endl;
	else
		cout << "Not Equal!" << endl;

	/*** double ***/
	init = clock();
	for(int i=0; i<REPEAT; i++)
		result_double1 = dotProduct_double(array_double1, array_double2, SIZE);
	end = clock();
	time1 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "dotProduct_double time: " << time1 << endl;

	init = clock();
	for(int i=0; i<REPEAT; i++)
		result_double2 = dotProduct_double_sse2(array_double1, array_double2, SIZE);
	end = clock();
	time2 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "dotProduct_double_sse2 time: " << time2 << endl;

	cout << "speedup: " << time1/time2 << endl;

	init = clock();
	for(int i=0; i<REPEAT; i++)
		result_double3 = dotProduct_double_unrolled_sse2(array_double1, array_double2, SIZE);
	end = clock();
	time2 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "dotProduct_double_unrolled_sse2 time: " << time2 << endl;

	cout << "speedup: " << time1/time2 << endl;

	cout<<"Results: "<<result_double1<<"; "<<result_double2<<"; "<<result_double3<<endl;

	cout << "Compare Result: ";
	if(result_double1 == result_double2)
		cout << "Equal" << endl;
	else
		cout << "Not Equal!" << endl;

	destroy_array_float(&array_float1);
	destroy_array_float(&array_float2);
	destroy_array_double(&array_double1);
	destroy_array_double(&array_double2);
}

void testSummatrix()
{
	clock_t init, end;
	float time1, time2;

	float **matrix_float1 = create_matrix_float(ROWS, COLS);
	float **matrix_float2 = create_matrix_float(ROWS, COLS);
	float **result_float1 = create_matrix_float(ROWS, COLS);
	float **result_float2 = create_matrix_float(ROWS, COLS);
	double **matrix_double1 = create_matrix_double(ROWS, COLS);
	double **matrix_double2 = create_matrix_double(ROWS, COLS);
	double **result_double1 = create_matrix_double(ROWS, COLS);
	double **result_double2 = create_matrix_double(ROWS, COLS);
	
	fill_matrix_random_float(matrix_float1, ROWS, COLS);
	fill_matrix_random_float(matrix_float2, ROWS, COLS);
	fill_matrix_random_double(matrix_double1, ROWS, COLS);
	fill_matrix_random_double(matrix_double2, ROWS, COLS);

	char **matrix_char1 = create_matrix_char(ROWS, COLS);
	char **matrix_char2 = create_matrix_char(ROWS, COLS);
	char **result_char1 = create_matrix_char(ROWS, COLS);
	char **result_char2 = create_matrix_char(ROWS, COLS);
	char **result_char3 = create_matrix_char(ROWS, COLS);

	fill_matrix_random_char(matrix_char1, ROWS, COLS);
	fill_matrix_random_char(matrix_char2, ROWS, COLS);

	/*** char ***/
	init = clock();
	for(int i=0; i<REPEAT; i++)
		summatrix_char(matrix_char1, matrix_char2, result_char1, ROWS, COLS);
	end = clock();
	time1 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "summatrix_char time: " << time1 << endl;

	init = clock();
	for(int i=0; i<REPEAT; i++)
		summatrix_char_sse2(matrix_char1, matrix_char2, result_char2, ROWS, COLS);
	end = clock();
	time2 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "summatrix_char_sse2 time: " << time2 << endl;

	cout << "speedup: " << time1/time2 << endl;

	init = clock();
	for(int i=0; i<REPEAT; i++)
		summatrix_char_unrolled_sse2(matrix_char1, matrix_char2, result_char3, ROWS, COLS);
	end = clock();
	time2 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "summatrix_char_unrolled_sse2 time: " << time2 << endl;

	cout << "speedup: " << time1/time2 << endl;

	cout << "Compare Result: ";
	if(isEqual_matrix_char(result_char1, result_char2, ROWS, COLS) && isEqual_matrix_char(result_char1, result_char3, ROWS, COLS))
		cout << "Equal" << endl;
	else
		cout << "Not Equal!" << endl;

	destroy_matrix_char(&matrix_char1, ROWS);
	destroy_matrix_char(&matrix_char2, ROWS);
	destroy_matrix_char(&result_char1, ROWS);
	destroy_matrix_char(&result_char2, ROWS);
	destroy_matrix_char(&result_char3, ROWS);

	int **matrix_int1 = create_matrix_int(ROWS, COLS);
	int **matrix_int2 = create_matrix_int(ROWS, COLS);
	int **result_int1 = create_matrix_int(ROWS, COLS);
	int **result_int2 = create_matrix_int(ROWS, COLS);
	int **result_int3 = create_matrix_int(ROWS, COLS);

	fill_matrix_random_int(matrix_int1, ROWS, COLS);
	fill_matrix_random_int(matrix_int2, ROWS, COLS);

	/*** int ***/
	init = clock();
	for(int i=0; i<REPEAT; i++)
		summatrix_int(matrix_int1, matrix_int2, result_int1, ROWS, COLS);
	end = clock();
	time1 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "summatrix_int time: " << time1 << endl;

	init = clock();
	for(int i=0; i<REPEAT; i++)
		summatrix_int_sse2(matrix_int1, matrix_int2, result_int2, ROWS, COLS);
	end = clock();
	time2 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "summatrix_int_sse2 time: " << time2 << endl;

	cout << "speedup: " << time1/time2 << endl;

	init = clock();
	for(int i=0; i<REPEAT; i++)
		summatrix_int_unrolled_sse2(matrix_int1, matrix_int2, result_int3, ROWS, COLS);
	end = clock();
	time2 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "summatrix_int_unrolled_sse2 time: " << time2 << endl;

	cout << "speedup: " << time1/time2 << endl;

	cout << "Compare Result: ";
	if(isEqual_matrix_int(result_int1, result_int2, ROWS, COLS) && isEqual_matrix_int(result_int1, result_int3, ROWS, COLS))
		cout << "Equal" << endl;
	else
		cout << "Not Equal!" << endl;

	destroy_matrix_int(&matrix_int1, ROWS);
	destroy_matrix_int(&matrix_int2, ROWS);
	destroy_matrix_int(&result_int1, ROWS);
	destroy_matrix_int(&result_int2, ROWS);
	destroy_matrix_int(&result_int3, ROWS);

	/*** float***/
	init = clock();
	for(int i=0; i<REPEAT; i++)
		summatrix_float(matrix_float1, matrix_float2, result_float1, ROWS, COLS);
	end = clock();
	time1 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "summatrix_float time: " << time1 << endl;

	init = clock();
	for(int i=0; i<REPEAT; i++)
		summatrix_float_sse2(matrix_float1, matrix_float2, result_float2, ROWS, COLS);
	end = clock();
	time2 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "summatrix_float_sse2 time: " << time2 << endl;

	cout << "speedup: " << time1/time2 << endl;

	cout << "Compare Result: ";
	if(isEqual_matrix_float(result_float1, result_float2, ROWS, COLS))
		cout << "Equal" << endl;
	else
		cout << "Not Equal!" << endl;

	/*** double ***/
	init = clock();
	for(int i=0; i<REPEAT; i++)
		summatrix_double(matrix_double1, matrix_double2, result_double1, ROWS, COLS);
	end = clock();
	time1 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "summatrix_double time: " << time1 << endl;

	init = clock();
	for(int i=0; i<REPEAT; i++)
		summatrix_double_sse2(matrix_double1, matrix_double2, result_double2, ROWS, COLS);
	end = clock();
	time2 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "summatrix_double_sse2 time: " << time2 << endl;

	cout << "speedup: " << time1/time2 << endl;

	cout << "Compare Result: ";
	if(isEqual_matrix_double(result_double1, result_double2, ROWS, COLS))
		cout << "Equal" << endl;
	else
		cout << "Not Equal!" << endl;

	destroy_matrix_float(&matrix_float1, ROWS);
	destroy_matrix_float(&matrix_float2, ROWS);
	destroy_matrix_float(&result_float1, ROWS);
	destroy_matrix_float(&result_float2, ROWS);
	destroy_matrix_double(&matrix_double1, ROWS);
	destroy_matrix_double(&matrix_double2, ROWS);
	destroy_matrix_double(&result_double1, ROWS);
	destroy_matrix_double(&result_double2, ROWS);
}

void testSumLinearMatrix()
{
	clock_t init, end;
	float time1, time2;

	char *matrix_char1 = create_linear_matrix_char(ROWS, COLS);
	char *matrix_char2 = create_linear_matrix_char(ROWS, COLS);
	char *result_char1 = create_linear_matrix_char(ROWS, COLS);
	char *result_char2 = create_linear_matrix_char(ROWS, COLS);
	char *result_char3 = create_linear_matrix_char(ROWS, COLS);
	int *matrix_int1 = create_linear_matrix_int(ROWS, COLS);
	int *matrix_int2 = create_linear_matrix_int(ROWS, COLS);
	int *result_int1 = create_linear_matrix_int(ROWS, COLS);
	int *result_int2 = create_linear_matrix_int(ROWS, COLS);
	int *result_int3 = create_linear_matrix_int(ROWS, COLS);
	float *matrix_float1 = create_linear_matrix_float(ROWS, COLS);
	float *matrix_float2 = create_linear_matrix_float(ROWS, COLS);
	float *result_float1 = create_linear_matrix_float(ROWS, COLS);
	float *result_float2 = create_linear_matrix_float(ROWS, COLS);
	double *matrix_double1 = create_linear_matrix_double(ROWS, COLS);
	double *matrix_double2 = create_linear_matrix_double(ROWS, COLS);
	double *result_double1 = create_linear_matrix_double(ROWS, COLS);
	double *result_double2 = create_linear_matrix_double(ROWS, COLS);

	fill_linear_matrix_random_char(matrix_char1, ROWS, COLS);
	fill_linear_matrix_random_char(matrix_char2, ROWS, COLS);
	fill_linear_matrix_random_int(matrix_int1, ROWS, COLS);
	fill_linear_matrix_random_int(matrix_int2, ROWS, COLS);
	fill_linear_matrix_random_float(matrix_float1, ROWS, COLS);
	fill_linear_matrix_random_float(matrix_float2, ROWS, COLS);
	fill_linear_matrix_random_double(matrix_double1, ROWS, COLS);
	fill_linear_matrix_random_double(matrix_double2, ROWS, COLS);

	/*** char ***/
	init = clock();
	for(int i=0; i<REPEAT; i++)
		sum_linear_matrix_char(matrix_char1, matrix_char2, result_char1, ROWS, COLS);
	end = clock();
	time1 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "sum_linear_matrix_char time: " << time1 << endl;

	init = clock();
	for(int i=0; i<REPEAT; i++)
		sum_linear_matrix_char_sse2(matrix_char1, matrix_char2, result_char2, ROWS, COLS);
	end = clock();
	time2 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "sum_linear_matrix_char_sse2 time: " << time2 << endl;

	cout << "speedup: " << time1/time2 << endl;

	init = clock();
	for(int i=0; i<REPEAT; i++)
		sum_linear_matrix_char_unrolled_sse2(matrix_char1, matrix_char2, result_char3, ROWS, COLS);
	end = clock();
	time2 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "sum_linear_matrix_char_unrolled_sse2 time: " << time2 << endl;

	cout << "speedup: " << time1/time2 << endl;

	cout << "Compare Result: ";
	if(isEqual_linear_matrix_char(result_char1, result_char2, ROWS, COLS) && isEqual_linear_matrix_char(result_char1, result_char3, ROWS, COLS))
		cout << "Equal" << endl;
	else
		cout << "Not Equal!" << endl;

	/*** int ***/
	init = clock();
	for(int i=0; i<REPEAT; i++)
		sum_linear_matrix_int(matrix_int1, matrix_int2, result_int1, ROWS, COLS);
	end = clock();
	time1 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "sum_linear_matrix_int time: " << time1 << endl;

	init = clock();
	for(int i=0; i<REPEAT; i++)
		sum_linear_matrix_int_sse2(matrix_int1, matrix_int2, result_int2, ROWS, COLS);
	end = clock();
	time2 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "sum_linear_matrix_int_sse2 time: " << time2 << endl;

	cout << "speedup: " << time1/time2 << endl;

	init = clock();
	for(int i=0; i<REPEAT; i++)
		sum_linear_matrix_int_unrolled_sse2(matrix_int1, matrix_int2, result_int3, ROWS, COLS);
	end = clock();
	time2 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "sum_linear_matrix_int_unrolled_sse2 time: " << time2 << endl;

	cout << "speedup: " << time1/time2 << endl;

	cout << "Compare Result: ";
	if(isEqual_linear_matrix_int(result_int1, result_int2, ROWS, COLS) && isEqual_linear_matrix_int(result_int1, result_int3, ROWS, COLS))
		cout << "Equal" << endl;
	else
		cout << "Not Equal!" << endl;

	/*** float ***/
	init = clock();
	for(int i=0; i<REPEAT; i++)
		sum_linear_matrix_float(matrix_float1, matrix_float2, result_float1, ROWS, COLS);
	end = clock();
	time1 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "sum_float_matrix_float time: " << time1 << endl;

	init = clock();
	for(int i=0; i<REPEAT; i++)
		sum_linear_matrix_float_sse2(matrix_float1, matrix_float2, result_float2, ROWS, COLS);
	end = clock();
	time2 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "sum_float_matrix_float_sse2 time: " << time2 << endl;

	cout << "speedup: " << time1/time2 << endl;

	cout << "Compare Result: ";
	if(isEqual_linear_matrix_float(result_float1, result_float2, ROWS, COLS))
		cout << "Equal" << endl;
	else
		cout << "Not Equal!" << endl;

	/*** double ***/
	init = clock();
	for(int i=0; i<REPEAT; i++)
		sum_linear_matrix_double(matrix_double1, matrix_double2, result_double1, ROWS, COLS);
	end = clock();
	time1 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "sum_linear_matrix_double time: " << time1 << endl;

	init = clock();
	for(int i=0; i<REPEAT; i++)
		sum_linear_matrix_double_sse2(matrix_double1, matrix_double2, result_double2, ROWS, COLS);
	end = clock();
	time2 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "sum_linear_matrix_double_sse2 time: " << time2 << endl;

	cout << "speedup: " << time1/time2 << endl;

	cout << "Compare Result: ";
	if(isEqual_linear_matrix_double(result_double1, result_double2, ROWS, COLS))
		cout << "Equal" << endl;
	else
		cout << "Not Equal!" << endl;

	destroy_linear_matrix_char(&matrix_char1);
	destroy_linear_matrix_char(&matrix_char2);
	destroy_linear_matrix_char(&result_char1);
	destroy_linear_matrix_char(&result_char2);
	destroy_linear_matrix_char(&result_char3);
	destroy_linear_matrix_int(&matrix_int1);
	destroy_linear_matrix_int(&matrix_int2);
	destroy_linear_matrix_int(&result_int1);
	destroy_linear_matrix_int(&result_int2);
	destroy_linear_matrix_int(&result_int3);
	destroy_linear_matrix_float(&matrix_float1);
	destroy_linear_matrix_float(&matrix_float2);
	destroy_linear_matrix_float(&result_float1);
	destroy_linear_matrix_float(&result_float2);
	destroy_linear_matrix_double(&matrix_double1);
	destroy_linear_matrix_double(&matrix_double2);
	destroy_linear_matrix_double(&result_double1);
	destroy_linear_matrix_double(&result_double2);
}

void testMulmatrix()
{
	clock_t init, end;
	float time1, time2;

	float **matrix_float1 = create_matrix_float(ROWS, COLS);
	float **matrix_float2 = create_matrix_float(COLS, ROWS);
	float **result_float1 = create_matrix_float(ROWS, ROWS);
	float **result_float2 = create_matrix_float(ROWS, ROWS);
	double **matrix_double1 = create_matrix_double(ROWS, COLS);
	double **matrix_double2 = create_matrix_double(COLS, ROWS);
	double **result_double1 = create_matrix_double(ROWS, ROWS);
	double **result_double2 = create_matrix_double(ROWS, ROWS);

	fill_matrix_random_float(matrix_float1, ROWS, COLS);
	fill_matrix_random_float(matrix_float2, COLS, ROWS);
	fill_matrix_random_double(matrix_double1, ROWS, COLS);
	fill_matrix_random_double(matrix_double2, COLS, ROWS);

	/*** float ***/
	init = clock();
	for(int i=0; i<REPEAT; i++)
		mulmatrix_float(matrix_float1, matrix_float2, result_float1, ROWS, COLS, ROWS);
	end = clock();
	time1 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "mulmatrix_float time: " << time1 << endl;

	init = clock();
	for(int i=0; i<REPEAT; i++)
		mulmatrix_float_sse2(matrix_float1, matrix_float2, result_float2, ROWS, COLS, ROWS);
	end = clock();
	time2 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "mulmatrix_float_sse2 time: " << time2 << endl;

	cout << "speedup: " << time1/time2 << endl;

	cout << "Compare Result: ";
	if(isEqual_matrix_float(result_float1, result_float2, ROWS, COLS))
		cout << "Equal" << endl;
	else
		cout << "Not Equal!" << endl;

	//print_matrix_float(result_float1, ROWS, COLS);
	//print_matrix_float(result_float2, ROWS, COLS);

	/*** double ***/
	init = clock();
	for(int i=0; i<REPEAT; i++)
		mulmatrix_double(matrix_double1, matrix_double2, result_double1, ROWS, COLS, ROWS);
	end = clock();
	time1 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "mulmatrix_double time: " << time1 << endl;

	init = clock();
	for(int i=0; i<REPEAT; i++)
		mulmatrix_double_sse2(matrix_double1, matrix_double2, result_double2, ROWS, COLS, ROWS);
	end = clock();
	time2 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "mulmatrix_double_sse2 time: " << time2 << endl;

	cout << "speedup: " << time1/time2 << endl;

	cout << "Compare Result: ";
	if(isEqual_matrix_double(result_double1, result_double2, ROWS, COLS))
		cout << "Equal" << endl;
	else
		cout << "Not Equal!" << endl;

	//print_matrix_double(result_double1, ROWS, COLS);
	//print_matrix_double(result_double2, ROWS, COLS);

	destroy_matrix_float(&matrix_float1, ROWS);
	destroy_matrix_float(&matrix_float2, COLS);
	destroy_matrix_float(&result_float1, ROWS);
	destroy_matrix_float(&result_float2, ROWS);
	destroy_matrix_double(&matrix_double1, ROWS);
	destroy_matrix_double(&matrix_double2, COLS);
	destroy_matrix_double(&result_double1, ROWS);
	destroy_matrix_double(&result_double2, ROWS);
}

void testMax()
{
	clock_t init, end;
	float time1, time2;

	float *array_float = create_array_float(SIZE),
	      result_float1 = 0,
	      result_float2 = 0;
	double *array_double = create_array_double(SIZE),
	       result_double1 = 0,
	       result_double2 = 0;

	fill_array_random_float(array_float, SIZE);
	fill_array_random_double(array_double, SIZE);

	/*** float ***/
	init = clock();
	for(int i=0; i<REPEAT; i++)
		result_float1 = maxelem_float(array_float, SIZE);
	end = clock();
	time1 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "maxelem_float time: " << time1 << endl;

	init = clock();
	for(int i=0; i<REPEAT; i++)
		result_float2 = maxelem_float_sse2(array_float, SIZE);
	end = clock();
	time2 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "maxelem_float_sse2 time: " << time2 << endl;

	cout << "speedup: " << time1/time2 << endl;

	cout << "Compare Result: ";
	if( result_float1 == result_float2 )
		cout << "Equal" << endl;
	else
		cout << "Not Equal!" << endl;

	/*** double ***/
	init = clock();
	for(int i=0; i<REPEAT; i++)
		result_double1 = maxelem_double(array_double, SIZE);
	end = clock();
	time1 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "maxelem_double time: " << time1 << endl;

	init = clock();
	for(int i=0; i<REPEAT; i++)
		result_double2 = maxelem_double_sse2(array_double, SIZE);
	end = clock();
	time2 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "maxelem_double_sse2 time: " << time2 << endl;

	cout << "speedup: " << time1/time2 << endl;

	cout << "Compare Result: ";
	if( result_double1 == result_double2 )
		cout << "Equal" << endl;
	else
		cout << "Not Equal!" << endl;

	destroy_array_float(&array_float);
	destroy_array_double(&array_double);
}

void testMin()
{
	clock_t init, end;
	float time1, time2;

	float *array_float = create_array_float(SIZE),
	      result_float1 = 0,
	      result_float2 = 0;
	double *array_double = create_array_double(SIZE),
	       result_double1 = 0,
	       result_double2 = 0;

	fill_array_random_float(array_float, SIZE);
	fill_array_random_double(array_double, SIZE);

	/*** float ***/
	init = clock();
	for(int i=0; i<REPEAT; i++)
		result_float1 = minelem_float(array_float, SIZE);
	end = clock();
	time1 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "minelem_float time: " << time1 << endl;

	init = clock();
	for(int i=0; i<REPEAT; i++)
		result_float2 = minelem_float_sse2(array_float, SIZE);
	end = clock();
	time2 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "minelem_float_sse2 time: " << time2 << endl;

	cout << "speedup: " << time1/time2 << endl;

	cout << "Compare Result: ";
	if( result_float1 == result_float2 )
		cout << "Equal" << endl;
	else
		cout << "Not Equal!" << endl;

	/*** double ***/
	init = clock();
	for(int i=0; i<REPEAT; i++)
		result_double1 = minelem_double(array_double, SIZE);
	end = clock();
	time1 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "minelem_double time: " << time1 << endl;

	init = clock();
	for(int i=0; i<REPEAT; i++)
		result_double2 = minelem_double_sse2(array_double, SIZE);
	end = clock();
	time2 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "minelem_double_sse2 time: " << time2 << endl;

	cout << "speedup: " << time1/time2 << endl;

	cout << "Compare Result: ";
	if( result_double1 == result_double2 )
		cout << "Equal" << endl;
	else
		cout << "Not Equal!" << endl;

	destroy_array_float(&array_float);
	destroy_array_double(&array_double);
}

void testMemCpy()
{
	clock_t init, end;
	float time1, time2;

	char *array_char = create_array_char(SIZE),
	     *result_char1 = create_array_char(SIZE),
	     *result_char2 = create_array_char(SIZE),
	     *result_char3 = create_array_char(SIZE);

	fill_array_random_char(array_char, SIZE);
	
	init = clock();
	for(int i=0; i<REPEAT; i++)
		memcpy(result_char1, array_char, SIZE*sizeof(char));
	end = clock();
	time1 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "memcpy time: " << time1 << endl;

	init = clock();
	for(int i=0; i<REPEAT; i++)
		memcpy_sse2(result_char2, array_char, SIZE*sizeof(char));
	end = clock();
	time2 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "memcpy_sse2 time: " << time2 << endl;

	cout << "speedup: " << time1/time2 << endl;

	init = clock();
	for(int i=0; i<REPEAT; i++)
		memcpy_unrolled_sse2(result_char3, array_char, SIZE*sizeof(char));
	end = clock();
	time2 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "memcpy_unrolled_sse2 time: " << time2 << endl;

	cout << "speedup: " << time1/time2 << endl;

	cout << "Compare Result: ";
	if( isEqual_array_char(result_char1, result_char2, SIZE) && isEqual_array_char(result_char2, result_char3, SIZE))
		cout << "Equal" << endl;
	else
		cout << "Not Equal!" << endl;

	destroy_array_char(&array_char);
	destroy_array_char(&result_char1);
	destroy_array_char(&result_char2);
	destroy_array_char(&result_char3);
}

void testConvolutionLinear()
{
	clock_t init, end;
	float time1, time2;

	float array_float1[SIZE] __attribute__ ((aligned(16)));
	float array_float2[SIZE2] __attribute__ ((aligned(16)));
	float result_float1[SIZE] __attribute__ ((aligned(16)));
	float result_float2[SIZE] __attribute__ ((aligned(16)));
	double array_double1[SIZE] __attribute__ ((aligned(16)));
	double array_double2[SIZE2] __attribute__ ((aligned(16)));
	double result_double1[SIZE] __attribute__ ((aligned(16)));
	double result_double2[SIZE] __attribute__ ((aligned(16)));

	fill_array_random_float(array_float1, SIZE);
	fill_array_random_float(array_float2, SIZE2);
	fill_array_random_double(array_double1, SIZE);
	fill_array_random_double(array_double2, SIZE2);

	/*** float ***/
	init = clock();
	for(int i=0; i<REPEAT; i++)
		convolution_linear_float(array_float1, array_float2, result_float1, SIZE, SIZE2);
	end = clock();
	time1 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "convolution_linear_float time: " << time1 << endl;

	init = clock();
	for(int i=0; i<REPEAT; i++)
		convolution_linear_float_sse2(array_float1, array_float2, result_float2, SIZE, SIZE2);
	end = clock();
	time2 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "convolution_linear_float_sse2 time: " << time2 << endl;

	cout << "speedup: " << time1/time2 << endl;

	cout << "Compare Result: ";
	if( isEqual_array_float(result_float1, result_float2, SIZE))
		cout << "Equal" << endl;
	else
		cout << "Not Equal!" << endl;

	/*** double ***/
	init = clock();
	for(int i=0; i<REPEAT; i++)
		convolution_linear_double(array_double1, array_double2, result_double1, SIZE, SIZE2);
	end = clock();
	time1 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "convolution_linear_double time: " << time1 << endl;

	init = clock();
	for(int i=0; i<REPEAT; i++)
		convolution_linear_double_sse2(array_double1, array_double2, result_double2, SIZE, SIZE2);
	end = clock();
	time2 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "convolution_linear_double_sse2 time: " << time2 << endl;

	cout << "speedup: " << time1/time2 << endl;

	cout << "Compare Result: ";
	if( isEqual_array_double(result_double1, result_double2, SIZE))
		cout << "Equal" << endl;
	else
		cout << "Not Equal!" << endl;

	/*print_array_float(result_float1, SIZE);
	print_array_float(result_float2, SIZE);*/
}

void testTransposeMatrix()
{
	clock_t init, end;
	float time1, time2;

	float **matrix_float = create_matrix_float(ROWS, COLS);
	float **result_float1 = create_matrix_float(COLS, ROWS);
	float **result_float2 = create_matrix_float(COLS, ROWS);

	double **matrix_double = create_matrix_double(ROWS, COLS);
	double **result_double1 = create_matrix_double(COLS, ROWS);
	double **result_double2 = create_matrix_double(COLS, ROWS);

	fill_matrix_random_float(matrix_float, ROWS, COLS);
	fill_matrix_random_double(matrix_double, ROWS, COLS);

	/*** float ***/
	init = clock();
	for(int i=0; i<REPEAT; i++)
		transpose_matrix_float(matrix_float, result_float1, ROWS, COLS);
	end = clock();
	time1 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "transpose_matrix_float time: " << time1 << endl;

	init = clock();
	for(int i=0; i<REPEAT; i++)
		transpose_matrix_float(matrix_float, result_float2, ROWS, COLS);
	end = clock();
	time2 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "transpose_matrix_float_sse2 time: " << time2 << endl;

	cout << "speedup: " << time1/time2 << endl;

	cout << "Compare Result: ";
	if(isEqual_matrix_float(result_float1, result_float2, COLS, ROWS))
		cout << "Equal" << endl;
	else
		cout << "Not Equal!" << endl;

	destroy_matrix_float(&matrix_float, ROWS);
	destroy_matrix_float(&result_float1, COLS);
	destroy_matrix_float(&result_float2, COLS);

	/*** double ***/
	init = clock();
	for(int i = 0; i < REPEAT; i++)
		transpose_matrix_double(matrix_double, result_double1, ROWS, COLS);
	end = clock();
	time1 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "transpose_matrix_double time: " << time1 << endl;

	init = clock();
	for(int i=0; i<REPEAT; i++)
		transpose_matrix_double_sse2(matrix_double, result_double2, ROWS, COLS);
	end = clock();
	time2 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "transpose_matrix_double_sse2 time: " << time2 << endl;

	cout << "speedup: " << time1/time2 << endl;

	cout << "Compare Result: ";
	if(isEqual_matrix_double(result_double1, result_double2, COLS, ROWS))
		cout << "Equal" << endl;
	else
		cout << "Not Equal!" << endl;

	destroy_matrix_double(&matrix_double, ROWS);
	destroy_matrix_double(&result_double1, COLS);
	destroy_matrix_double(&result_double2, COLS);
}

void testConvolutionMatrix()
{
	clock_t init, end;
	float time1, time2;

	float **matrix_float1 = create_matrix_float(ROWS, COLS);
	float **matrix_float2 = create_matrix_float(ROWS2, COLS2);
	float **result_float1 = create_matrix_float(ROWS, COLS);
	float **result_float2 = create_matrix_float(ROWS, COLS);
	double **matrix_double1 = create_matrix_double(ROWS, COLS);
	double **matrix_double2 = create_matrix_double(ROWS2, COLS2);
	double **result_double1 = create_matrix_double(ROWS, COLS);
	double **result_double2 = create_matrix_double(ROWS, COLS);

	fill_matrix_random_float(matrix_float1, ROWS, COLS);
	fill_matrix_random_float(matrix_float2, ROWS2, COLS2);
	fill_matrix_random_double(matrix_double1, ROWS, COLS);
	fill_matrix_random_double(matrix_double2, ROWS2, COLS2);

	/*** float ***/
	init = clock();
	for(int i=0; i<REPEAT; i++)
		convolution_matrix_float(matrix_float1, matrix_float2, result_float1, ROWS, COLS, ROWS2, COLS2);
	end = clock();
	time1 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "convolution_matrix_float time: " << time1 << endl;

	init = clock();
	for(int i=0; i<REPEAT; i++)
		convolution_matrix_float_sse2(matrix_float1, matrix_float2, result_float2, ROWS, COLS, ROWS2, COLS2);
	end = clock();
	time2 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "convolution_matrix_float_sse2 time: " << time2 << endl;

	cout << "speedup: " << time1/time2 << endl;

	cout << "Compare Result: ";
	if(isEqual_matrix_float(result_float1, result_float2, ROWS, COLS))
		cout << "Equal" << endl;
	else
		cout << "Not Equal!" << endl;

	//print_matrix_float(result_float1, ROWS, COLS);
	//print_matrix_float(result_float2, ROWS, COLS);
	//print_matrix_float(result_float3, ROWS, COLS);

	/*** double ***/
	init = clock();
	for(int i=0; i<REPEAT; i++)
		convolution_matrix_double(matrix_double1, matrix_double2, result_double1, ROWS, COLS, ROWS2, COLS2);
	end = clock();
	time1 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "convolution_matrix_double time: " << time1 << endl;

	init = clock();
	for(int i=0; i<REPEAT; i++)
		convolution_matrix_double_sse2(matrix_double1, matrix_double2, result_double2, ROWS, COLS, ROWS2, COLS2);
	end = clock();
	time2 = (end-init)/(CLOCKS_PER_SEC*1.0);

	cout << "convolution_matrix_double_sse2 time: " << time2 << endl;

	cout << "speedup: " << time1/time2 << endl;

	cout << "Compare Result: ";
	if(isEqual_matrix_double(result_double1, result_double2, ROWS, COLS))
		cout << "Equal" << endl;
	else
		cout << "Not Equal!" << endl;

	//print_matrix_double(result_double1, ROWS, COLS);
	//print_matrix_double(result_double2, ROWS, COLS);
	//print_matrix_double(result_double3, ROWS, COLS);
	
	destroy_matrix_float(&matrix_float1, ROWS);
	destroy_matrix_float(&matrix_float2, ROWS2);
	destroy_matrix_float(&result_float1, ROWS);
	destroy_matrix_float(&result_float2, ROWS);
	destroy_matrix_double(&matrix_double1, ROWS);
	destroy_matrix_double(&matrix_double2, ROWS2);
	destroy_matrix_double(&result_double1, ROWS);
	destroy_matrix_double(&result_double2, ROWS);
}

int main (void)
{	
	srandom(time(NULL));

	//testSumelem();
	//testSumarray();
	//testMularray();
	//testDotProduct();
	//testSummatrix();
	//testSumLinearMatrix();
	testTransposeMatrix();
	testMulmatrix();
	//testMax();
	//testMin();
	//testMemCpy();
	//testConvolutionLinear();
	//testConvolutionMatrix();
	//testCmp();
	
	return 0;
}
