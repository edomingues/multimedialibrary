/**
 * @file libMultimedia.cpp
 *
 * @brief Library that uses multimedia instruction to speedup array processing
 *
 * @author Edgar Domingues (39026)
 * @author Mario Antunes   (39372)
 *
 * @version 1.0
 *
 */

#include <cstring>
#include "dataStructure.h"
#include "libMultimedia.h"

/**
 * Calculate the sum of all elements in a array of bytes.
 * Classic algorithm.
 *
 * Example:
 \verbatim
       A
  | 1| 2| 3| => 6
 \endverbatim
 *
 * @param[in]	a array with the elements to sum
 * @param[in]	size size of the array
 * @return sum of the elements in the array	
 *
 */
char sumelem_char(char *a, int size)
{
	int i = 0;
	char rv = 0;

	for(i = 0; i < size; i++)
		rv = rv + a[i];

	return rv;
}

/**
 * Calculate the sum of all elements in a array of bytes.
 * Algorithm uses SSE2 instructions.
 *
 * Example:
 \verbatim
       A
  | 1| 2| 3| => 6
 \endverbatim
 *
 * @param[in]	a array with the elements to sum
 * @param[in]	size size of the array
 * @return sum of the elements in the array	
 *
 */
char sumelem_char_sse2(char *a, int size)
{
	char __attribute__ ((aligned(16))) b[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int i = 0, length = (size / 16) * 16;
	char rv = 0;
	
	__asm__ volatile
        ("movdqa %0,%%xmm0" : :"m" (b[0]));

	for (i = 0; i < length; i += 16)
	{
		__asm__ volatile
                ("paddb %0,%%xmm0": :"m" (a[i]));
	}

	__asm__ volatile
        ("movdqa %%xmm0,%0 " :"=m" (b[0]):);
	
	rv = b[0]+b[1]+b[2]+b[3]+b[4]+b[5]+b[6]+b[7]+b[8]+b[9]+b[10]+b[11]+b[12]+b[13]+b[14]+b[15];
	
	for(i = length; i < size; i++)
		rv = rv + a[i];
	
	return rv;
}

/**
 * Calculate the sum of all elements in a array of bytes.
 * Algorithm uses SSE2 instructions.
 *
 * Example:
 \verbatim
       A
  | 1| 2| 3| => 6
 \endverbatim
 *
 * @param[in]	a array with the elements to sum
 * @param[in]	size size of the array
 * @return sum of the elements in the array	
 *
 */
char sumelem_char_unrolled_sse2(char *a, int size)
{
	char __attribute__ ((aligned(16))) b[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int i = 0,
	    length6 = (size/96)*96,
	    length3 = (size/48)*48,
	    length = (size/16)*16;
	char rv = 0;

	__asm__ volatile
        ("\n\tmovdqa %0,%%xmm0\t#"
	 "\n\tmovdqa %0,%%xmm1\t#" : :"m" (b[0]));

	for (; i < length6; i += 96)
	{
		__asm__ volatile
		(// instruction		 comment
		 "\n\t movdqa %0,%%xmm2 \t#"
		 "\n\t movdqa %1,%%xmm3 \t#"
		 "\n\t movdqa %2,%%xmm4 \t#"
		 "\n\t movdqa %3,%%xmm5 \t#"
		 "\n\t movdqa %4,%%xmm6 \t#"
		 "\n\t movdqa %5,%%xmm7 \t#"
		 "\n\t paddb %%xmm2,%%xmm0 \t#"
		 "\n\t paddb %%xmm5,%%xmm1 \t#"
		 "\n\t paddb %%xmm3,%%xmm0 \t#"
		 "\n\t paddb %%xmm6,%%xmm1 \t#"
		 "\n\t paddb %%xmm4,%%xmm0 \t#"
		 "\n\t paddb %%xmm7,%%xmm1 \t#"
		 :
		 :"m"  (a[i]),       // %0
		  "m"  (a[i+16]),    // %1
		  "m"  (a[i+32]),    // %2
		  "m"  (a[i+48]),    // %3
		  "m"  (a[i+64]),    // %4
		  "m"  (a[i+80])     // %5
		);
	}

	for (; i < length3; i += 48)
	{
		__asm__ volatile
		(// instruction             comment
		 "\n\t movdqa %0,%%xmm2 \t#"
		 "\n\t movdqa %1,%%xmm3 \t#"
		 "\n\t movdqa %2,%%xmm4 \t#"
		 "\n\t paddb %%xmm2,%%xmm0 \t#"
		 "\n\t paddb %%xmm4,%%xmm1 \t#"
		 "\n\t paddb %%xmm3,%%xmm0 \t#"
		 :
		 :"m"  (a[i]),       // %0
		  "m"  (a[i+16]),    // %1
		  "m"  (a[i+32])     // %2
		);
	}

	for (; i < length; i += 16)
	{
		__asm__ volatile
                (
		 "\n\t paddb %0,%%xmm0 \t#" : :"m" (a[i]));
	}

	__asm__ volatile
        ("\n\t paddb %%xmm1,%%xmm0 \t#"
	 "\n\t movdqa %%xmm0,%0 \t#" :"=m" (b[0]): );
	
	rv = b[0]+b[1]+b[2]+b[3]+b[4]+b[5]+b[6]+b[7]+b[8]+b[9]+b[10]+b[11]+b[12]+b[13]+b[14]+b[15];
	
	for(; i < size; i++)
	{
		rv = rv + a[i];
	}
	
	return rv;
}

/**
 * Calculate the sum of all elements in a array of integers.
 * Classic algorithm.
 *
 * @param[in]	a array with the elements to sum
 * @param[in]	size size of the array
 * @return sum of the elements in the array	
 *
 */
int sumelem_int(int *a, int size)
{
	int i = 0, rv = 0;

	for(i = 0; i < size; i++)
		rv = rv + a[i];

	return rv;
}

/**
 * Calculate the sum of all elements in a array of integers.
 * Algorithm uses SSE2 instructions.
 *
 * Example:
 \verbatim
       A
  | 1| 2| 3| => 6
 \endverbatim
 *
 * @param[in]	a array with the elements to sum
 * @param[in]	size size of the array
 * @return sum of the elements in the array	
 *
 */
int sumelem_int_sse2(int *a, int size)
{
	int __attribute__ ((aligned(16))) b[4] = {0, 0, 0, 0};
	int i = 0, length = (size / 4) * 4, rv = 0;

	__asm__ volatile
        ("movdqa %0,%%xmm0" : :"m" (b[0]));
		
	for (i = 0; i < length; i += 4)
	{
		__asm__ volatile
                ("paddd %0,%%xmm0": :"m" (a[i]));

	}
	
	__asm__ volatile
        ("movdqa %%xmm0,%0 " :"=m" (b[0]):);
	
	rv = b[0] + b[1] + b[2] + b[3];
	
	for(i = length; i < size; i++)
		rv = rv + a[i];
	
	return rv;
}

/**
 * Calculate the sum of all elements in a array of integers.
 * Algorithm uses SSE2 instructions.
 *
 * Example:
 \verbatim
       A
  | 1| 2| 3| => 6
 \endverbatim
 *
 * @param[in]	a array with the elements to sum
 * @param[in]	size size of the array
 * @return sum of the elements in the array	
 *
 */
int sumelem_int_unrolled_sse2(int *a, int size)
{
	int __attribute__ ((aligned(16))) b[4] = {0, 0, 0, 0};
	int i = 0,
	    length6 = (size/24)*24,
	    length3 = (size/12)*12,
	    length = (size/4)*4;
	int rv = 0;

	__asm__ volatile
        ("\n\tmovdqa %0,%%xmm0\t#"
	 "\n\tmovdqa %0,%%xmm1\t#" : :"m" (b[0]));

	for (; i < length6; i += 24)
	{
		__asm__ volatile
		(// instruction		 comment
		 "\n\t movdqa %0,%%xmm2 \t#"
		 "\n\t movdqa %1,%%xmm3 \t#"
		 "\n\t movdqa %2,%%xmm4 \t#"
		 "\n\t movdqa %3,%%xmm5 \t#"
		 "\n\t movdqa %4,%%xmm6 \t#"
		 "\n\t movdqa %5,%%xmm7 \t#"
		 "\n\t paddd %%xmm2,%%xmm0 \t#"
		 "\n\t paddd %%xmm5,%%xmm1 \t#"
		 "\n\t paddd %%xmm3,%%xmm0 \t#"
		 "\n\t paddd %%xmm6,%%xmm1 \t#"
		 "\n\t paddd %%xmm4,%%xmm0 \t#"
		 "\n\t paddd %%xmm7,%%xmm1 \t#"
		 :
		 :"m"  (a[i]),       // %0
		  "m"  (a[i+4]),     // %1
		  "m"  (a[i+8]),     // %2
		  "m"  (a[i+12]),    // %3
		  "m"  (a[i+16]),    // %4
		  "m"  (a[i+20])     // %5
		);
	}

	for (; i < length3; i += 12)
	{
		__asm__ volatile
		(// instruction             comment
		 "\n\t movdqa %0,%%xmm2 \t#"
		 "\n\t movdqa %1,%%xmm3 \t#"
		 "\n\t movdqa %2,%%xmm4 \t#"
		 "\n\t paddd %%xmm2,%%xmm0 \t#"
		 "\n\t paddd %%xmm4,%%xmm1 \t#"
		 "\n\t paddd %%xmm3,%%xmm0 \t#"
		 :
		 :"m"  (a[i]),       // %0
		  "m"  (a[i+4]),     // %1
		  "m"  (a[i+8])      // %2
		);
	}

	for (; i < length; i += 4)
	{
		__asm__ volatile
                ("paddd %0,%%xmm0" : :"m" (a[i]));
	}

	__asm__ volatile
        ("\n\t paddd %%xmm1,%%xmm0 \t#"
	 "\n\t movdqa %%xmm0,%0    \t#" :"=m" (b[0]): );
	
	rv = b[0]+b[1]+b[2]+b[3];
	
	for(; i < size; i++)
	{
		rv = rv + a[i];
	}
	
	return rv;
}

/**
 * Calculate the sum of all elements in a array of integers.
 * Algorithm uses SSE3 instructions.
 *
 * Example:
 \verbatim
       A
  | 1| 2| 3| => 6
 \endverbatim
 *
 * @param[in]	a array with the elements to sum
 * @param[in]	size size of the array
 * @return sum of the elements in the array	
 *
 */
int sumelem_int_sse3(int *a, int size)
{
	int __attribute__ ((aligned(16))) b[size];
	int i = 0, j = 0, rv = 0;

	int maxLength, length;

	if(size > 12)
	{
		maxLength = (size / 4) * 4;
		length = maxLength;
	}
	else
	{
		maxLength = (size / 8) * 8;
		length = maxLength;
	}

	for (i = 0, j = 0; i < (length/8) * 8; i+=8, j+=4)
	{

			__asm__ volatile
                	( // instruction             comment
                	"\n\t movdqa     %1,%%xmm0         \t#"
                	"\n\t movdqa     %2,%%xmm1         \t#"
                	"\n\t phaddd      %%xmm0,%%xmm1     \t#"
                	"\n\t movdqa     %%xmm1,%0         \t#"
			: "=m" (b[j])      // %0
			: "m"  (a[i+4]),   // %1
		  	  "m"  (a[i])      // %2
			);

		}

		if(length % 8 != 0)
		{
			b[j] = a[length - 4];
			b[j+1] = a[length - 3];
			b[j+2] = a[length - 2];
			b[j+3] = a[length - 1];

			length = (length / 8) * 4 + 4;
		}
		else
			length = length / 2;

	while(length > 4)
	{
		for (i = 0, j = 0; i < (length/8) * 8; i+=8, j+=4)
		{
			__asm__ volatile
                	( // instruction             comment
                	"\n\t movdqa     %1,%%xmm0         \t#"
                	"\n\t movdqa     %2,%%xmm1         \t#"
                	"\n\t phaddd      %%xmm0,%%xmm1     \t#"
                	"\n\t movdqa     %%xmm1,%0         \t#"
			: "=m" (b[j])      // %0
			: "m"  (b[i+4]),   // %1
		  	  "m"  (b[i])      // %2
			);
		}

		if((length > 8) && (length % 8 != 0))
		{
			b[j] = b[length - 4];
			b[j+1] = b[length - 3];
			b[j+2] = b[length - 2];
			b[j+3] = b[length - 1];

			length = (length / 8) * 4 + 4;
		}
		else
			length = length / 2;
	}

	rv = b[0] + b[1] + b[2] + b[3];

	for(i = maxLength; i < size; i++)
		rv = rv + a[i];

	return rv;
}

/**
 * Calculate the sum of all elements in a array of floats.
 * Classic algorithm.
 *
 * Example:
 \verbatim
       A
  | 1| 2| 3| => 6
 \endverbatim
 *
 * @param[in]	a array with the elements to sum
 * @param[in]	size size of the array
 * @return sum of the elements in the array	
 *
 */
float sumelem_float(float *a, int size)
{
	int i = 0;
	float rv = 0.0;

	for(i = 0; i < size; i++)
		rv = rv + a[i];	

	return rv;
}

/**
 * Calculate the sum of all elements in a array of floats.
 * Algorithm uses SSE2 instructions.
 *
 * Example:
 \verbatim
       A
  | 1| 2| 3| => 6
 \endverbatim
 *
 * @param[in]	a array with the elements to sum
 * @param[in]	size size of the array
 * @return sum of the elements in the array	
 *
 */
float sumelem_float_sse2(float *a, int size)
{
	float __attribute__ ((aligned(16))) b[4] = { 0.0, 0.0, 0.0, 0.0};
	int i = 0, length = (size / 4) * 4;
	float rv = 0;
	
	__asm__ volatile
        ("movdqa     %0,%%xmm0" : :"m" (b[0]));

	for (i = 0; i < length; i += 4)
	{
		__asm__ volatile
                ("addps %0,%%xmm0": : "m" (a[i]));
	}

	__asm__ volatile
        ("movdqa %%xmm0,%0 " :"=m" (b[0]):);
	
	rv = b[0] + b[1] + b[2] + b[3];
	
	for(i = length; i < size; i++)
		rv = rv + a[i];
	
	return rv;
}

/**
 * Calculate the sum of all elements in a array of floats.
 * Algorithm uses SSE2 instructions.
 *
 * Example:
 \verbatim
       A
  | 1| 2| 3| => 6
 \endverbatim
 *
 * @param[in]	a array with the elements to sum
 * @param[in]	size size of the array
 * @return sum of the elements in the array	
 *
 */
float sumelem_float_unrolled_sse2(float *a, int size)
{
	float __attribute__ ((aligned(16))) b[4] = {0.0, 0.0, 0.0, 0.0};
	int i = 0,
	    length6 = (size/24)*24,
	    length3 = (size/12)*12,
	    length = (size/4)*4;
	float rv = 0.0;

	__asm__ volatile
        ("\n\tmovdqa %0,%%xmm0\t#"
	 "\n\tmovdqa %0,%%xmm1\t#" : :"m" (b[0]));

	float *paux=a;

	for (; i < length6; i += 24)
	{
		__asm__ volatile
		(// instruction		 comment
		 "\n\t movdqa %0,%%xmm2    \t#"
		 "\n\t movdqa %1,%%xmm3    \t#"
		 "\n\t movdqa %2,%%xmm4    \t#"
		 "\n\t movdqa %3,%%xmm5    \t#"
		 "\n\t movdqa %4,%%xmm6    \t#"
		 "\n\t movdqa %5,%%xmm7    \t#"
		 "\n\t addps %%xmm2,%%xmm0 \t#"
		 "\n\t addps %%xmm5,%%xmm1 \t#"
		 "\n\t addps %%xmm3,%%xmm0 \t#"
		 "\n\t addps %%xmm6,%%xmm1 \t#"
		 "\n\t addps %%xmm4,%%xmm0 \t#"
		 "\n\t addps %%xmm7,%%xmm1 \t#"
		 :
		 :"m"  (*(paux)),       // %0
		  "m"  (*(paux+4)),     // %1
		  "m"  (*(paux+8)),     // %2
		  "m"  (*(paux+12)),    // %3
		  "m"  (*(paux+16)),    // %4
		  "m"  (*(paux+20))     // %5
		);

		paux = paux + 24;
	}

	for (; i < length3; i += 12)
	{
		__asm__ volatile
		(// instruction             comment
		 "\n\t movdqa %0,%%xmm2    \t#"
		 "\n\t movdqa %1,%%xmm3    \t#"
		 "\n\t movdqa %2,%%xmm4    \t#"
		 "\n\t addps %%xmm2,%%xmm0 \t#"
		 "\n\t addps %%xmm4,%%xmm1 \t#"
		 "\n\t addps %%xmm3,%%xmm0 \t#"
		 :
		 :"m"  (*(paux)),       // %0
		  "m"  (*(paux+4)),     // %1
		  "m"  (*(paux+8))      // %2
		);

		paux = paux +12;
	}

	for (; i < length; i += 4)
	{
		__asm__ volatile
		("addps %0,%%xmm0" : :"m" (*paux));
		
		paux = paux + 4; 
	}

	__asm__ volatile
        ("\n\t addps %%xmm1,%%xmm0 \t#"
	 "\n\t movdqa %%xmm0,%0    \t#" :"=m" (b[0]): );
	
	rv = b[0]+b[1]+b[2]+b[3];
	
	for(; i < size; i++)
	{
		rv = rv + a[i];
	}
	
	return rv;
}

/**
 * Calculate the sum of all elements in a array of floats.
 * Algorithm uses SSE3 instructions.
 *
 * Example:
 \verbatim
       A
  | 1| 2| 3| => 6
 \endverbatim
 *
 * @param[in]	a array with the elements to sum
 * @param[in]	size size of the array
 * @return sum of the elements in the array	
 *
 */
float sumelem_float_sse3(float *a, int size)
{
	float __attribute__ ((aligned(16))) b[size];
	int i = 0, j = 0;
	float rv = 0;

	int maxLength, length;

	if(size >= 12)
	{
		maxLength = (size / 4) * 4;
		length = maxLength;
	}
	else
	{
		maxLength = (size / 8) * 8;
		length = maxLength;
	}

	for (i = 0, j = 0; i < (length/8) * 8; i+=8, j+=4)
	{
		__asm__ volatile
                ( // instruction             comment
                "\n\t movdqa     %1,%%xmm0         \t#"
                "\n\t movdqa     %2,%%xmm1         \t#"
                "\n\t haddps     %%xmm0,%%xmm1     \t#"
                "\n\t movdqa     %%xmm1,%0         \t#"
		: "=m" (b[j])      // %0
		: "m"  (a[i+4]),   // %1
		  "m"  (a[i])      // %2
		);
	}

	if(length % 8 != 0)
	{
		b[j] = a[length - 4];
		b[j+1] = a[length - 3];
		b[j+2] = a[length - 2];
		b[j+3] = a[length - 1];

		length = (length / 8) * 4 + 4;
	}
	else
		length = length / 2;

	while(length > 4)
	{
		for (i = 0, j = 0; i < (length/8) * 8; i+=8, j+=4)
		{
			__asm__ volatile
                	( // instruction             comment
                	"\n\t movdqa     %1,%%xmm0         \t#"
                	"\n\t movdqa     %2,%%xmm1         \t#"
                	"\n\t haddps     %%xmm0,%%xmm1     \t#"
                	"\n\t movdqa     %%xmm1,%0         \t#"
			: "=m" (b[j])      // %0
			: "m"  (b[i+4]),   // %1
		  	  "m"  (b[i])      // %2
			);
		}

		if((length > 8) && (length % 8 != 0))
		{
			b[j] = b[length - 4];
			b[j+1] = b[length - 3];
			b[j+2] = b[length - 2];
			b[j+3] = b[length - 1];

			length = (length / 8) * 4 + 4;
		}
		else
			length = length / 2;
	}

	rv = b[0] + b[1] + b[2] + b[3];

	for(i = maxLength; i < size; i++)
		rv = rv + a[i];

	return rv;
}

/**
 * Calculate the sum of all elements in a array of doubles.
 * Classic algorithm.
 *
 * Example:
 \verbatim
       A
  | 1| 2| 3| => 6
 \endverbatim
 *
 * @param[in]	a array with the elements to sum
 * @param[in]	size size of the array
 * @return sum of the elements in the array	
 *
 */
double sumelem_double(double *a, int size)
{
	int i = 0;
	double rv = 0.0;

	for(i = 0; i < size; i++)
		rv = rv + a[i];	

	return rv;
}

/**
 * Calculate the sum of all elements in a array of doubles.
 * Algorithm uses SSE2 instructions.
 *
 * Example:
 \verbatim
       A
  | 1| 2| 3| => 6
 \endverbatim
 *
 * @param[in]	a array with the elements to sum
 * @param[in]	size size of the array
 * @return sum of the elements in the array	
 *
 */
double sumelem_double_sse2(double *a, int size)
{
	double __attribute__ ((aligned(16))) b[2] = {0.0, 0.0,};
	int i = 0, length = (size / 2) * 2;
	double rv = 0;
	
	__asm__ volatile
        ("movdqa     %0,%%xmm0" : :"m" (b[0]));

	for (i = 0; i < length; i += 2)
	{
		__asm__ volatile
                ("addpd      %0,%%xmm0": :"m"  (a[i]));
	}

	__asm__ volatile
        ("movdqa %%xmm0,%0 " :"=m" (b[0]):);
	
	rv = b[0] + b[1];
	
	for(i = length; i < size; i++)
		rv = rv + a[i];
	
	return rv;
}

/**
 * Calculate the sum of all elements in a array of floats.
 * Algorithm uses SSE2 instructions.
 *
 * Example:
 \verbatim
       A
  | 1| 2| 3| => 6
 \endverbatim
 *
 * @param[in]	a array with the elements to sum
 * @param[in]	size size of the array
 * @return sum of the elements in the array	
 *
 */
double sumelem_double_unrolled_sse2(double *a, int size)
{
	double __attribute__ ((aligned(16))) b[2] = {0.0, 0.0};
	int i = 0,
	    length6 = (size/12)*12,
	    length3 = (size/6)*6,
	    length = (size/2)*2;
	double rv = 0.0;

	__asm__ volatile
        ("\n\tmovdqa %0,%%xmm0\t#"
	 "\n\tmovdqa %0,%%xmm1\t#" : :"m" (b[0]));

	for (; i < length6; i += 12)
	{
		__asm__ volatile
		(// instruction		 comment
		 "\n\t movdqa %0,%%xmm2    \t#"
		 "\n\t movdqa %1,%%xmm3    \t#"
		 "\n\t movdqa %2,%%xmm4    \t#"
		 "\n\t movdqa %3,%%xmm5    \t#"
		 "\n\t movdqa %4,%%xmm6    \t#"
		 "\n\t movdqa %5,%%xmm7    \t#"
		 "\n\t addpd %%xmm2,%%xmm0 \t#"
		 "\n\t addpd %%xmm5,%%xmm1 \t#"
		 "\n\t addpd %%xmm3,%%xmm0 \t#"
		 "\n\t addpd %%xmm6,%%xmm1 \t#"
		 "\n\t addpd %%xmm4,%%xmm0 \t#"
		 "\n\t addpd %%xmm7,%%xmm1 \t#"
		 :
		 :"m"  (a[i]),       // %0
		  "m"  (a[i+2]),     // %1
		  "m"  (a[i+4]),     // %2
		  "m"  (a[i+6]),     // %3
		  "m"  (a[i+8]),     // %4
		  "m"  (a[i+10])     // %5
		);
	}

	for (; i < length3; i += 6)
	{
		__asm__ volatile
		(// instruction             comment
		 "\n\t movdqa %0,%%xmm2    \t#"
		 "\n\t movdqa %1,%%xmm3    \t#"
		 "\n\t movdqa %2,%%xmm4    \t#"
		 "\n\t addpd %%xmm2,%%xmm0 \t#"
		 "\n\t addpd %%xmm4,%%xmm1 \t#"
		 "\n\t addpd %%xmm3,%%xmm0 \t#"
		 :
		 :"m"  (a[i]),       // %0
		  "m"  (a[i+2]),     // %1
		  "m"  (a[i+4])      // %2
		);
	}

	for (; i < length; i += 2)
	{
		__asm__ volatile
                ("addpd %0,%%xmm0" : :"m" (a[i]));
	}

	__asm__ volatile
        ("\n\t addpd %%xmm1,%%xmm0 \t#"
	 "\n\t movdqa %%xmm0,%0    \t#" :"=m" (b[0]): );
	
	rv = b[0]+b[1];
	
	for(; i < size; i++)
	{
		rv = rv + a[i];
	}
	
	return rv;
}

/**
 * Calculate the sum of all elements in a array of doubles.
 * Algorithm uses SSE3 instructions.
 *
 * Example:
 \verbatim
       A
  | 1| 2| 3| => 6
 \endverbatim
 *
 * @param[in]	a array with the elements to sum
 * @param[in]	size size of the array
 * @return sum of the elements in the array	
 *
 */
double sumelem_double_sse3(double *a, int size)
{
	double __attribute__ ((aligned(16))) b[size];
	int i = 0, j = 0;
	double rv = 0;

	int maxLength, length;

	if(size >= 6)
	{
		maxLength = (size / 2) * 2;
		length = maxLength;
	}
	else
	{
		maxLength = (size / 4) * 4;
		length = maxLength;
	}

	for (i = 0, j = 0; i < (length/4)*4; i+=4, j+=2)
	{
		__asm__ volatile
                ( // instruction             comment
                "\n\t movdqa     %1,%%xmm0         \t#"
                "\n\t movdqa     %2,%%xmm1         \t#"
                "\n\t haddpd     %%xmm0,%%xmm1     \t#"
                "\n\t movdqa     %%xmm1,%0         \t#"
		: "=m" (b[j])      // %0
		: "m"  (a[i+2]),   // %1
		  "m"  (a[i])      // %2
		);
	}

	if(length % 4 != 0)
	{
		b[j] = a[length - 2];
		b[j+1] = a[length - 1];

		length = (length / 4) * 2 + 2;
	}
	else
		length = length / 2;

	while(length > 2)
	{
		for (i = 0, j = 0; i < (length/4)*4; i+=4, j+=2)
		{
			__asm__ volatile
                	( // instruction             comment
                	"\n\t movdqa     %1,%%xmm0         \t#"
                	"\n\t movdqa     %2,%%xmm1         \t#"
                	"\n\t haddpd     %%xmm0,%%xmm1     \t#"
                	"\n\t movdqa     %%xmm1,%0         \t#"
			: "=m" (b[j])      // %0
			: "m"  (b[i+2]),   // %1
		  	  "m"  (b[i])      // %2
			);
		}

		if(length % 4 != 0)
		{
			b[j] = b[length - 2];
			b[j+1] = b[length - 1];

			length = (length / 4) * 2 + 2;
		}
		else
			length = length / 2;
	}

	rv = b[0] + b[1];

	for(i = maxLength; i < size; i++)
		rv = rv + a[i];

	return rv;
}

/**
 * Calculate the sum of two arrays of chars.
 * Classic algorithm.
 *
 * Expression:
 \verbatim
  c[i] = a[i] + b[i]
 \endverbatim
 *
 * @param[in]	a array with elements to sum
 * @param[in]	b array with elements to sum
 * @param[in]	size size of the arrays
 * @param[out]	c array with the result of the sum	
 *
 */
void sumarray_char(char *a, char *b, char *c, int size)
{
	int i = 0;

	for (i = 0; i < size; i++)
		c[i]=a[i]+b[i];
}

/**
 * Calculate the sum of two arrays of chars.
 * Algorithm uses SSE2 instructions.
 *
 * Expression:
 \verbatim
  c[i] = a[i] + b[i]
 \endverbatim
 *
 * @param[in]	a array with elements to sum
 * @param[in]	b array with elements to sum
 * @param[in]	size size of the arrays
 * @param[out]	c array with the result of the sum	
 *
 */
void sumarray_char_sse2(char *a, char *b, char *c, int size)
{
	int i = 0;
	int length = (size / 16) * 16;

	for (i = 0; i < length; i += 16)
	{
		__asm__ volatile
                ( // instruction             comment                  
                "\n\t movdqa     %1,%%xmm0         \t#"
                "\n\t movdqa     %2,%%xmm1         \t#"
                "\n\t paddb      %%xmm0,%%xmm1     \t#"
                "\n\t movdqa     %%xmm1,%0         \t#"
		: "=m" (c[i])      // %0
		: "m"  (a[i]),     // %1 
		  "m"  (b[i])      // %2
		);
	}

	for(i = length; i < size; i++)
		c[i] = a[i] + b[i];
}

/**
 * Calculate the sum of two arrays of chars.
 * Algorithm uses SSE2 instructions.
 *
 * Expression:
 \verbatim
  c[i] = a[i] + b[i]
 \endverbatim
 *
 * @param[in]	a array with elements to sum
 * @param[in]	b array with elements to sum
 * @param[in]	size size of the arrays
 * @param[out]	c array with the result of the sum	
 *
 */
void sumarray_char_unrolled_sse2(char *a, char *b, char *c, int size)
{
	int i = 0,
	    length = (size/16)*16,
	    length2 = (size/32)*32,
	    length4 = (size/64)*64;

	for(i = 0; i < length4; i+=64)
	{
		__asm__ volatile
                ( // instruction             comment
                "\n\t movdqa     %4,%%xmm0         \t#"
		"\n\t movdqa     %5,%%xmm1         \t#"
		"\n\t movdqa     %6,%%xmm2         \t#"
		"\n\t movdqa     %7,%%xmm3         \t#"
		"\n\t movdqa     %8,%%xmm4         \t#"
		"\n\t movdqa     %9,%%xmm5         \t#"
		"\n\t movdqa     %10,%%xmm6        \t#"
		"\n\t movdqa     %11,%%xmm7        \t#"
		"\n\t paddb      %%xmm0,%%xmm1     \t#"
		"\n\t paddb      %%xmm2,%%xmm3     \t#"
		"\n\t paddb      %%xmm4,%%xmm5     \t#"
		"\n\t paddb      %%xmm6,%%xmm7     \t#"
	        "\n\t movdqa     %%xmm1,%0         \t#"
		"\n\t movdqa     %%xmm3,%1         \t#"
		"\n\t movdqa     %%xmm5,%2         \t#"
		"\n\t movdqa     %%xmm7,%3         \t#"
		: "=m" (c[i]),     // %0
		  "=m" (c[i+16]),  // %1
		  "=m" (c[i+32]),  // %2
		  "=m" (c[i+48])   // %3
		: "m"  (a[i]),     // %4
		  "m"  (b[i]),     // %5
		  "m"  (a[i+16]),  // %6
		  "m"  (b[i+16]),  // %7
		  "m"  (a[i+32]),  // %8
		  "m"  (b[i+32]),  // %9
		  "m"  (a[i+48]),  // %10
		  "m"  (b[i+48])   // %11
		);
	}
	
	for(; i < length2; i+=32)
	{
		__asm__ volatile
                ( // instruction             comment
                "\n\t movdqa     %2,%%xmm0         \t#"
		"\n\t movdqa     %3,%%xmm1         \t#"
		"\n\t movdqa     %4,%%xmm2         \t#"
		"\n\t movdqa     %5,%%xmm3         \t#"
		"\n\t paddb      %%xmm0,%%xmm1     \t#"
		"\n\t paddb      %%xmm2,%%xmm3     \t#"
	        "\n\t movdqa     %%xmm1,%0         \t#"
		"\n\t movdqa     %%xmm3,%1         \t#"
		: "=m" (c[i]),     // %0
		  "=m" (c[i+16])   // %1
		: "m"  (a[i]),     // %2
		  "m"  (b[i]),     // %3
		  "m"  (a[i+16]),  // %4
		  "m"  (b[i+16])   // %5
		);
	}

	for(; i < length; i+=16)
	{
		__asm__ volatile
                ( // instruction             comment
                "\n\t movdqa     %1,%%xmm0         \t#"
		"\n\t movdqa     %2,%%xmm1         \t#"
		"\n\t paddb      %%xmm0,%%xmm1     \t#"
	        "\n\t movdqa     %%xmm1,%0         \t#"
		: "=m" (c[i])      // %0
		: "m"  (a[i]),     // %1
		  "m"  (b[i])      // %2
		);
	}

	for(; i < size; i++)
		c[i] = a[i] + b[i];
}

/**
 * Calculate the sum of two arrays of integers.
 * Classic algorithm.
 *
 * Expression:
 \verbatim
  c[i] = a[i] + b[i]
 \endverbatim
 *
 * @param[in]	a array with elements to sum
 * @param[in]	b array with elements to sum
 * @param[in]	size size of the arrays
 * @param[out]	c array with the result of the sum	
 *
 */
void sumarray_int(int *a, int *b, int *c, int size)
{
	int i = 0;

	for (i = 0; i < size; i++)
		c[i] = a[i] + b[i];
}

/**
 * Calculate the sum of two arrays of integers.
 * Algorithm uses SSE2 instructions.
 *
 * Expression:
 \verbatim
  c[i] = a[i] + b[i]
 \endverbatim
 *
 * @param[in]	a array with elements to sum
 * @param[in]	b array with elements to sum
 * @param[in]	size size of the arrays
 * @param[out]	c array with the result of the sum	
 *
 */
void sumarray_int_sse2(int *a, int *b, int *c, int size)
{
	int i = 0;
	
	for (i = 0; i < (size/4)*4; i += 4)
	{
		__asm__ volatile
                ( // instruction             comment                  
                "\n\t movdqa     %1,%%xmm0         \t#"
                "\n\t movdqa     %2,%%xmm1         \t#"
                "\n\t paddd      %%xmm0,%%xmm1     \t#"
                "\n\t movdqa     %%xmm1,%0         \t#"
		: "=m" (c[i])      // %0
		: "m"  (a[i]),     // %1 
		  "m"  (b[i])      // %2
		);
	}

	for(i = (size/4)*4; i < size; i++)
		c[i] = a[i] + b[i];
}

/**
 * Calculate the sum of two arrays of integers.
 * Algorithm uses SSE2 instructions.
 *
 * Expression:
 \verbatim
  c[i] = a[i] + b[i]
 \endverbatim
 *
 * @param[in]	a array with elements to sum
 * @param[in]	b array with elements to sum
 * @param[in]	size size of the arrays
 * @param[out]	c array with the result of the sum	
 *
 */
void sumarray_int_unrolled_sse2(int *a, int *b, int *c, int size)
{
	int i = 0,
	    length = (size/4)*4,
	    length2 = (size/8)*8,
	    length4 = (size/16)*16;

	for(i = 0; i < length4; i+=16)
	{
		__asm__ volatile
                ( // instruction             comment
                "\n\t movdqa     %4,%%xmm0         \t#"
		"\n\t movdqa     %5,%%xmm1         \t#"
		"\n\t movdqa     %6,%%xmm2         \t#"
		"\n\t movdqa     %7,%%xmm3         \t#"
		"\n\t movdqa     %8,%%xmm4         \t#"
		"\n\t movdqa     %9,%%xmm5         \t#"
		"\n\t movdqa     %10,%%xmm6        \t#"
		"\n\t movdqa     %11,%%xmm7        \t#"
		"\n\t paddd      %%xmm0,%%xmm1     \t#"
		"\n\t paddd      %%xmm2,%%xmm3     \t#"
		"\n\t paddd      %%xmm4,%%xmm5     \t#"
		"\n\t paddd      %%xmm6,%%xmm7     \t#"
	        "\n\t movdqa     %%xmm1,%0         \t#"
		"\n\t movdqa     %%xmm3,%1         \t#"
		"\n\t movdqa     %%xmm5,%2         \t#"
		"\n\t movdqa     %%xmm7,%3         \t#"
		: "=m" (c[i]),     // %0
		  "=m" (c[i+4]),   // %1
		  "=m" (c[i+8]),   // %2
		  "=m" (c[i+12])   // %3
		: "m"  (a[i]),     // %4
		  "m"  (b[i]),     // %5
		  "m"  (a[i+4]),   // %6
		  "m"  (b[i+4]),   // %7
		  "m"  (a[i+8]),   // %8
		  "m"  (b[i+8]),   // %9
		  "m"  (a[i+12]),  // %10
		  "m"  (b[i+12])   // %11
		);
	}
	
	for(; i < length2; i+=8)
	{
		__asm__ volatile
                ( // instruction             comment
                "\n\t movdqa     %2,%%xmm0         \t#"
		"\n\t movdqa     %3,%%xmm1         \t#"
		"\n\t movdqa     %4,%%xmm2         \t#"
		"\n\t movdqa     %5,%%xmm3         \t#"
		"\n\t paddd      %%xmm0,%%xmm1     \t#"
		"\n\t paddd      %%xmm2,%%xmm3     \t#"
	        "\n\t movdqa     %%xmm1,%0         \t#"
		"\n\t movdqa     %%xmm3,%1         \t#"
		: "=m" (c[i]),     // %0
		  "=m" (c[i+4])    // %1
		: "m"  (a[i]),     // %2
		  "m"  (b[i]),     // %3
		  "m"  (a[i+4]),   // %4
		  "m"  (b[i+4])    // %5
		);
	}

	for(; i < length; i+=4)
	{
		__asm__ volatile
                ( // instruction             comment
                "\n\t movdqa     %1,%%xmm0         \t#"
		"\n\t movdqa     %2,%%xmm1         \t#"
		"\n\t paddd      %%xmm0,%%xmm1     \t#"
	        "\n\t movdqa     %%xmm1,%0         \t#"
		: "=m" (c[i])      // %0
		: "m"  (a[i]),     // %1
		  "m"  (b[i])      // %2
		);
	}

	for(; i < size; i++)
		c[i] = a[i] + b[i];
}

/**
 * Calculate the sum of two arrays of floats.
 * Classic algorithm.
 *
 * Expression:
 \verbatim
  c[i] = a[i] + b[i]
 \endverbatim
 *
 * @param[in]	a array with elements to sum
 * @param[in]	b array with elements to sum
 * @param[out]	c array with the result of the sum	
 * @param[in]	size size of the arrays
 *
 */
void sumarray_float(float *a, float *b, float *c, int size)
{
	int i = 0;

	for (i = 0; i < size; i++)
		c[i]=a[i]+b[i];
}

/**
 * Calculate the sum of two arrays of floats.
 * Algorithm uses SSE2 instructions.
 *
 * Expression:
 \verbatim
  c[i] = a[i] + b[i]
 \endverbatim
 *
 * @param[in]	a array with elements to sum
 * @param[in]	b array with elements to sum
 * @param[out]	c array with the result of the sum	
 * @param[in]	size size of the arrays
 *
 */
void sumarray_float_sse2(float *a, float *b, float *c, int size)
{
	int i = 0;
	int length = (size / 4) * 4;

	for (i = 0; i < length; i += 4)
	{
		__asm__ volatile
                ( // instruction             comment                  
                "\n\t movdqa     %1,%%xmm0         \t#"
                "\n\t movdqa     %2,%%xmm1         \t#"
                "\n\t addps      %%xmm0,%%xmm1     \t#"
                "\n\t movdqa     %%xmm1,%0         \t#"
		: "=m" (c[i])      // %0
		: "m"  (a[i]),     // %1 
		  "m"  (b[i])      // %2
		);
	}

	for(i = length; i < size; i++)
		c[i] = a[i] + b[i];
}

/**
 * Calculate the sum of two arrays of floats.
 * Algorithm uses SSE2 instructions.
 *
 * Expression:
 \verbatim
  c[i] = a[i] + b[i]
 \endverbatim
 *
 * @param[in]	a array with elements to sum
 * @param[in]	b array with elements to sum
 * @param[out]	c array with the result of the sum	
 * @param[in]	size size of the arrays
 *
 */
void sumarray_float_unrolled_sse2(float *a, float *b, float *c, int size)
{
	int i = 0,
	    length = (size/4)*4,
	    length2 = (size/8)*8,
	    length4 = (size/16)*16;

	for(; i < length4; i+=16)
	{
		__asm__ volatile
                ( // instruction             comment
                "\n\t movdqa     %4,%%xmm0         \t#"
		"\n\t movdqa     %5,%%xmm1         \t#"
		"\n\t movdqa     %6,%%xmm2         \t#"
		"\n\t movdqa     %7,%%xmm3         \t#"
		"\n\t movdqa     %8,%%xmm4         \t#"
		"\n\t movdqa     %9,%%xmm5         \t#"
		"\n\t movdqa     %10,%%xmm6        \t#"
		"\n\t movdqa     %11,%%xmm7        \t#"
		"\n\t addps      %%xmm0,%%xmm1     \t#"
		"\n\t addps      %%xmm2,%%xmm3     \t#"
		"\n\t addps      %%xmm4,%%xmm5     \t#"
		"\n\t addps      %%xmm6,%%xmm7     \t#"
	        "\n\t movdqa     %%xmm1,%0         \t#"
		"\n\t movdqa     %%xmm3,%1         \t#"
		"\n\t movdqa     %%xmm5,%2         \t#"
		"\n\t movdqa     %%xmm7,%3         \t#"
		: "=m" (c[i]),     // %0
		  "=m" (c[i+4]),   // %1
		  "=m" (c[i+8]),   // %2
		  "=m" (c[i+12])   // %3
		: "m"  (a[i]),     // %4
		  "m"  (b[i]),     // %5
		  "m"  (a[i+4]),   // %6
		  "m"  (b[i+4]),   // %7
		  "m"  (a[i+8]),   // %8
		  "m"  (b[i+8]),   // %9
		  "m"  (a[i+12]),  // %10
		  "m"  (b[i+12])   // %11
		);
	}
	
	for(; i < length2; i+=8)
	{
		__asm__ volatile
                ( // instruction             comment
                "\n\t movdqa     %2,%%xmm0         \t#"
		"\n\t movdqa     %3,%%xmm1         \t#"
		"\n\t movdqa     %4,%%xmm2         \t#"
		"\n\t movdqa     %5,%%xmm3         \t#"
		"\n\t addps      %%xmm0,%%xmm1     \t#"
		"\n\t addps      %%xmm2,%%xmm3     \t#"
	        "\n\t movdqa     %%xmm1,%0         \t#"
		"\n\t movdqa     %%xmm3,%1         \t#"
		: "=m" (c[i]),     // %0
		  "=m" (c[i+4])    // %1
		: "m"  (a[i]),     // %2
		  "m"  (b[i]),     // %3
		  "m"  (a[i+4]),   // %4
		  "m"  (b[i+4])    // %5
		);
	}

	for(; i < length; i+=4)
	{
		__asm__ volatile
                ( // instruction             comment
                "\n\t movdqa     %1,%%xmm0         \t#"
		"\n\t movdqa     %2,%%xmm1         \t#"
		"\n\t addps      %%xmm0,%%xmm1     \t#"
	        "\n\t movdqa     %%xmm1,%0         \t#"
		: "=m" (c[i])      // %0
		: "m"  (a[i]),     // %1
		  "m"  (b[i])      // %2
		);
	}

	for(; i < size; i++)
		c[i] = a[i] + b[i];
}

/**
 * Calculate the sum of two arrays of doubles.
 * Classic algorithm.
 *
 * Expression:
 \verbatim
  c[i] = a[i] + b[i]
 \endverbatim
 *
 * @param[in]	a array with elements to sum
 * @param[in]	b array with elements to sum
 * @param[in]	size size of the arrays
 * @param[out]	c array with the result of the sum	
 *
 */
void sumarray_double(double *a, double *b, double *c, int size)
{
	int i = 0;

	for (i = 0; i < size; i++)
		c[i]=a[i]+b[i];
}

/**
 * Calculate the sum of two arrays of doubles.
 * Algorithm uses SSE2 instructions.
 *
 * Expression:
 \verbatim
  c[i] = a[i] + b[i]
 \endverbatim
 *
 * @param[in]	a array with elements to sum
 * @param[in]	b array with elements to sum
 * @param[in]	size size of the arrays
 * @param[out]	c array with the result of the sum	
 *
 */
void sumarray_double_sse2(double *a, double *b, double *c, int size)
{
	int i = 0;
	int length = (size / 2) * 2;

	for (i = 0; i < length; i += 2)
	{
		__asm__ volatile
                ( // instruction             comment                  
                "\n\t movdqa     %1,%%xmm0         \t#"
                "\n\t movdqa     %2,%%xmm1         \t#"
                "\n\t addpd      %%xmm0,%%xmm1     \t#"
                "\n\t movdqa     %%xmm1,%0         \t#"
		: "=m" (c[i])      // %0
		: "m"  (a[i]),     // %1 
		  "m"  (b[i])      // %2
		);
	}

	for(i = length; i < size; i++)
		c[i] = a[i] + b[i];
}

/**
 * Calculate the sum of two arrays of doubles.
 * Algorithm uses SSE2 instructions.
 *
 * Expression:
 \verbatim
  c[i] = a[i] + b[i]
 \endverbatim
 *
 * @param[in]	a array with elements to sum
 * @param[in]	b array with elements to sum
 * @param[in]	size size of the arrays
 * @param[out]	c array with the result of the sum	
 *
 */
void sumarray_double_unrolled_sse2(double *a, double *b, double *c, int size)
{
	int i = 0,
	    length = (size/2)*2,
	    length2 = (size/4)*4,
	    length4 = (size/8)*8;

	for(i = 0; i < length4; i+=8)
	{
		__asm__ volatile
                ( // instruction             comment
                "\n\t movdqa     %4,%%xmm0         \t#"
		"\n\t movdqa     %5,%%xmm1         \t#"
		"\n\t movdqa     %6,%%xmm2         \t#"
		"\n\t movdqa     %7,%%xmm3         \t#"
		"\n\t movdqa     %8,%%xmm4         \t#"
		"\n\t movdqa     %9,%%xmm5         \t#"
		"\n\t movdqa     %10,%%xmm6        \t#"
		"\n\t movdqa     %11,%%xmm7        \t#"
		"\n\t addpd      %%xmm0,%%xmm1     \t#"
		"\n\t addpd      %%xmm2,%%xmm3     \t#"
		"\n\t addpd      %%xmm4,%%xmm5     \t#"
		"\n\t addpd      %%xmm6,%%xmm7     \t#"
	        "\n\t movdqa     %%xmm1,%0         \t#"
		"\n\t movdqa     %%xmm3,%1         \t#"
		"\n\t movdqa     %%xmm5,%2         \t#"
		"\n\t movdqa     %%xmm7,%3         \t#"
		: "=m" (c[i]),     // %0
		  "=m" (c[i+2]),   // %1
		  "=m" (c[i+4]),   // %2
		  "=m" (c[i+6])    // %3
		: "m"  (a[i]),     // %4
		  "m"  (b[i]),     // %5
		  "m"  (a[i+2]),   // %6
		  "m"  (b[i+2]),   // %7
		  "m"  (a[i+4]),   // %8
		  "m"  (b[i+4]),   // %9
		  "m"  (a[i+6]),   // %10
		  "m"  (b[i+6])    // %11
		);
	}
	
	for(; i < length2; i+=4)
	{
		__asm__ volatile
                ( // instruction             comment
                "\n\t movdqa     %2,%%xmm0         \t#"
		"\n\t movdqa     %3,%%xmm1         \t#"
		"\n\t movdqa     %4,%%xmm2         \t#"
		"\n\t movdqa     %5,%%xmm3         \t#"
		"\n\t addpd      %%xmm0,%%xmm1     \t#"
		"\n\t addpd      %%xmm2,%%xmm3     \t#"
	        "\n\t movdqa     %%xmm1,%0         \t#"
		"\n\t movdqa     %%xmm3,%1         \t#"
		: "=m" (c[i]),     // %0
		  "=m" (c[i+2])    // %1
		: "m"  (a[i]),     // %2
		  "m"  (b[i]),     // %3
		  "m"  (a[i+2]),   // %4
		  "m"  (b[i+2])    // %5
		);
	}

	for(; i < length; i+=2)
	{
		__asm__ volatile
                ( // instruction             comment
                "\n\t movdqa     %1,%%xmm0         \t#"
		"\n\t movdqa     %2,%%xmm1         \t#"
		"\n\t addpd      %%xmm0,%%xmm1     \t#"
	        "\n\t movdqa     %%xmm1,%0         \t#"
		: "=m" (c[i])      // %0
		: "m"  (a[i]),     // %1
		  "m"  (b[i])      // %2
		);
	}

	for(; i < size; i++)
		c[i] = a[i] + b[i];
}


/**
 * Calculate the sum of two matrix of bytes.
 * Classic algorithm.
 *
 * Expression:
 \verbatim
  c[row][col] = a[row][col] + b[row][col]
 \endverbatim
 *
 * @param[in]	a matrix with elements to sum
 * @param[in]	b matrix with elements to sum
 * @param[out]	c matrix with the result of the sum	
 * @param[in]	rows number of rows of the matrixes
 * @param[in]	cols number of cols of the matrixes
 *
 */
void summatrix_char(char **a, char **b, char **c, int rows, int cols)
{
	for(int i = 0; i < rows; i++)
		for(int j=0; j<cols; j++)
			c[i][j] = a[i][j] + b[i][j];
}

/**
 * Calculate the sum of two matrix of integers.
 * Algorithm uses SSE2 instructions.
 *
 * Expression:
 \verbatim
  c[row][col] = a[row][col] + b[row][col]
 \endverbatim
 *
 * @param[in]	a matrix with elements to sum
 * @param[in]	b matrix with elements to sum
 * @param[out]	c matrix with the result of the sum	
 * @param[in]	rows number of rows of the matrixes
 * @param[in]	cols number of cols of the matrixes
 *
 */
void summatrix_char_sse2(char **a, char **b, char **c, int rows, int cols)
{
	int i = 0;

	for( i = 0; i < rows; i++)
		sumarray_char_sse2(a[i], b[i], c[i], cols);
}

/**
 * Calculate the sum of two matrix of integers.
 * Algorithm uses SSE2 instructions.
 *
 * Expression:
 \verbatim
  c[row][col] = a[row][col] + b[row][col]
 \endverbatim
 *
 * @param[in]	a matrix with elements to sum
 * @param[in]	b matrix with elements to sum
 * @param[out]	c matrix with the result of the sum	
 * @param[in]	rows number of rows of the matrixes
 * @param[in]	cols number of cols of the matrixes
 *
 */
void summatrix_char_unrolled_sse2(char **a, char **b, char **c, int rows, int cols)
{
	int i = 0;

	for( i = 0; i < rows; i++)
		sumarray_char_unrolled_sse2(a[i], b[i], c[i], cols);
}

/**
 * Calculate the sum of two linear matrix of bytes.
 * Classic algorithm.
 *
 * Expression:
 \verbatim
  c[row][col] = a[row][col] + b[row][col]
 \endverbatim
 *
 * @param[in]	a matrix with elements to sum
 * @param[in]	b matrix with elements to sum
 * @param[out]	c matrix with the result of the sum	
 * @param[in]	rows number of rows of the matrixes
 * @param[in]	cols number of cols of the matrixes
 *
 */
void sum_linear_matrix_char(char *a, char *b, char *c, int rows, int cols)
{
	int size = rows * cols;
	int i = 0;

	for(i = 0; i < size; i++)
		c[i] = a[i] + b[i];
}

/**
 * Calculate the sum of two linear matrix of bytes.
 * Algorithm uses SSE2 instructions.
 *
 * Expression:
 \verbatim
  c[row][col] = a[row][col] + b[row][col]
 \endverbatim
 *
 * @param[in]	a matrix with elements to sum
 * @param[in]	b matrix with elements to sum
 * @param[out]	c matrix with the result of the sum	
 * @param[in]	rows number of rows of the matrixes
 * @param[in]	cols number of cols of the matrixes
 *
 */
void sum_linear_matrix_char_sse2(char *a, char *b, char *c, int rows, int cols)
{	
	sumarray_char_sse2(a, b, c, rows*cols);
}

/**
 * Calculate the sum of two linear matrix of bytes.
 * Algorithm uses SSE2 instructions.
 *
 * Expression:
 \verbatim
  c[row][col] = a[row][col] + b[row][col]
 \endverbatim
 *
 * @param[in]	a matrix with elements to sum
 * @param[in]	b matrix with elements to sum
 * @param[out]	c matrix with the result of the sum	
 * @param[in]	rows number of rows of the matrixes
 * @param[in]	cols number of cols of the matrixes
 *
 */
void sum_linear_matrix_char_unrolled_sse2(char *a, char *b, char *c, int rows, int cols)
{	
	sumarray_char_unrolled_sse2(a, b, c, rows*cols);
}

/**
 * Calculate the sum of two matrix of integers.
 * Classic algorithm.
 *
 * Expression:
 \verbatim
  c[row][col] = a[row][col] + b[row][col]
 \endverbatim
 *
 * @param[in]	a matrix with elements to sum
 * @param[in]	b matrix with elements to sum
 * @param[out]	c matrix with the result of the sum	
 * @param[in]	rows number of rows of the matrixes
 * @param[in]	cols number of cols of the matrixes
 *
 */
void summatrix_int(int **a, int **b, int **c, int rows, int cols)
{
	for(int i = 0; i < rows; i++)
		for(int j=0; j<cols; j++)
			c[i][j] = a[i][j] + b[i][j];
}

/**
 * Calculate the sum of two matrix of integers.
 * Algorithm uses SSE2 instructions.
 *
 * Expression:
 \verbatim
  c[row][col] = a[row][col] + b[row][col]
 \endverbatim
 *
 * @param[in]	a matrix with elements to sum
 * @param[in]	b matrix with elements to sum
 * @param[out]	c matrix with the result of the sum	
 * @param[in]	rows number of rows of the matrixes
 * @param[in]	cols number of cols of the matrixes
 *
 */
void summatrix_int_sse2(int **a, int **b, int **c, int rows, int cols)
{
	int i = 0;

	for( i = 0; i < rows; i++)
		sumarray_int_sse2(a[i], b[i], c[i], cols);
}

/**
 * Calculate the sum of two matrix of integers.
 * Algorithm uses SSE2 instructions.
 *
 * Expression:
 \verbatim
  c[row][col] = a[row][col] + b[row][col]
 \endverbatim
 *
 * @param[in]	a matrix with elements to sum
 * @param[in]	b matrix with elements to sum
 * @param[out]	c matrix with the result of the sum	
 * @param[in]	rows number of rows of the matrixes
 * @param[in]	cols number of cols of the matrixes
 *
 */
void summatrix_int_unrolled_sse2(int **a, int **b, int **c, int rows, int cols)
{
	int i = 0;

	for( i = 0; i < rows; i++)
		sumarray_int_unrolled_sse2(a[i], b[i], c[i], cols);
}

/**
 * Calculate the sum of two linear matrix of integers.
 * Classic algorithm.
 *
 * Expression:
 \verbatim
  c[row][col] = a[row][col] + b[row][col]
 \endverbatim
 *
 * @param[in]	a matrix with elements to sum
 * @param[in]	b matrix with elements to sum
 * @param[out]	c matrix with the result of the sum	
 * @param[in]	rows number of rows of the matrixes
 * @param[in]	cols number of cols of the matrixes
 *
 */
void sum_linear_matrix_int(int *a, int *b, int *c, int rows, int cols)
{
	int size = rows * cols;
	int i = 0;

	for(i = 0; i < size; i++)
		c[i] = a[i] + b[i];
}

/**
 * Calculate the sum of two linear matrix of integers.
 * Algorithm uses SSE2 instructions.
 *
 * Expression:
 \verbatim
  c[row][col] = a[row][col] + b[row][col]
 \endverbatim
 *
 * @param[in]	a matrix with elements to sum
 * @param[in]	b matrix with elements to sum
 * @param[out]	c matrix with the result of the sum	
 * @param[in]	rows number of rows of the matrixes
 * @param[in]	cols number of cols of the matrixes
 *
 */
void sum_linear_matrix_int_sse2(int *a, int *b, int *c, int rows, int cols)
{
	sumarray_int_sse2(a, b, c, rows*cols);
}

/**
 * Calculate the sum of two linear matrix of integers.
 * Algorithm uses SSE2 instructions.
 *
 * Expression:
 \verbatim
  c[row][col] = a[row][col] + b[row][col]
 \endverbatim
 *
 * @param[in]	a matrix with elements to sum
 * @param[in]	b matrix with elements to sum
 * @param[out]	c matrix with the result of the sum	
 * @param[in]	rows number of rows of the matrixes
 * @param[in]	cols number of cols of the matrixes
 *
 */
void sum_linear_matrix_int_unrolled_sse2(int *a, int *b, int *c, int rows, int cols)
{
	sumarray_int_unrolled_sse2(a, b, c, rows*cols);
}

/**
 * Calculate the sum of two matrix of floats.
 * Classic algorithm.
 *
 * Expression:
 \verbatim
  c[row][col] = a[row][col] + b[row][col]
 \endverbatim
 *
 * @param[in]	a matrix with elements to sum
 * @param[in]	b matrix with elements to sum
 * @param[out]	c matrix with the result of the sum	
 * @param[in]	rows number of rows of the matrixes
 * @param[in]	cols number of cols of the matrixes
 *
 */
void summatrix_float(float **a, float **b, float **c, int rows, int cols)
{
	for(int i = 0; i < rows; i++)
		for(int j=0; j<cols; j++)
			c[i][j] = a[i][j] + b[i][j];
}

/**
 * Calculate the sum of two matrix of integers.
 * Algorithm uses SSE2 instructions.
 *
 * Expression:
 \verbatim
  c[row][col] = a[row][col] + b[row][col]
 \endverbatim
 *
 * @param[in]	a matrix with elements to sum
 * @param[in]	b matrix with elements to sum
 * @param[out]	c matrix with the result of the sum	
 * @param[in]	rows number of rows of the matrixes
 * @param[in]	cols number of cols of the matrixes
 *
 */
void summatrix_float_sse2(float **a, float **b, float **c, int rows, int cols)
{
	int i = 0;

	for( i = 0; i < rows; i++)
		sumarray_float_sse2(a[i], b[i], c[i], cols);
}

/**
 * Calculate the sum of two matrix of integers.
 * Algorithm uses SSE2 instructions.
 *
 * Expression:
 \verbatim
  c[row][col] = a[row][col] + b[row][col]
 \endverbatim
 *
 * @param[in]	a matrix with elements to sum
 * @param[in]	b matrix with elements to sum
 * @param[out]	c matrix with the result of the sum	
 * @param[in]	rows number of rows of the matrixes
 * @param[in]	cols number of cols of the matrixes
 *
 */
void summatrix_float_unrolled_sse2(float **a, float **b, float **c, int rows, int cols)
{
	int i = 0;

	for( i = 0; i < rows; i++)
		sumarray_float_unrolled_sse2(a[i], b[i], c[i], cols);
}

/**
 * Calculate the sum of two linear matrix of floats.
 * Classic algorithm.
 *
 * Expression:
 \verbatim
  c[row][col] = a[row][col] + b[row][col]
 \endverbatim
 *
 * @param[in]	a matrix with elements to sum
 * @param[in]	b matrix with elements to sum
 * @param[out]	c matrix with the result of the sum	
 * @param[in]	rows number of rows of the matrixes
 * @param[in]	cols number of cols of the matrixes
 *
 */
void sum_linear_matrix_float(float *a, float *b, float *c, int rows, int cols)
{
	int size = rows * cols;
	int i = 0;

	for(i = 0; i < size; i++)
		c[i] = a[i] + b[i];
}

/**
 * Calculate the sum of two linear matrix of floats.
 * Algorithm uses SSE2 instructions.
 *
 * Expression:
 \verbatim
  c[row][col] = a[row][col] + b[row][col]
 \endverbatim
 *
 * @param[in]	a matrix with elements to sum
 * @param[in]	b matrix with elements to sum
 * @param[out]	c matrix with the result of the sum	
 * @param[in]	rows number of rows of the matrixes
 * @param[in]	cols number of cols of the matrixes
 *
 */
void sum_linear_matrix_float_sse2(float *a, float *b, float *c, int rows, int cols)
{
	int i = 0;
	int size = rows * cols;
	int length = (size / 4) * 4;

	for (i = 0; i < length; i += 4)
	{
		__asm__ volatile
                ( // instruction             comment                  
                "\n\t movdqa     %1,%%xmm0         \t#"
                "\n\t movdqa     %2,%%xmm1         \t#"
                "\n\t addps      %%xmm0,%%xmm1     \t#"
                "\n\t movdqa     %%xmm1,%0         \t#"
		: "=m" (c[i])      // %0
		: "m"  (a[i]),     // %1 
		  "m"  (b[i])      // %2
		);
	}

	for(i = length; i < size; i++)
		c[i] = a[i] + b[i];
}

/**
 * Calculate the sum of two matrix of doubles.
 * Classic algorithm.
 *
 * Expression:
 \verbatim
  c[row][col] = a[row][col] + b[row][col]
 \endverbatim
 *
 * @param[in]	a matrix with elements to sum
 * @param[in]	b matrix with elements to sum
 * @param[out]	c matrix with the result of the sum	
 * @param[in]	rows number of rows of the matrixes
 * @param[in]	cols number of cols of the matrixes
 *
 */
void summatrix_double(double **a, double **b, double **c, int rows, int cols)
{
	for(int i = 0; i < rows; i++)
		for(int j=0; j<cols; j++)
			c[i][j] = a[i][j] + b[i][j];
}

/**
 * Calculate the sum of two matrix of integers.
 * Algorithm uses SSE2 instructions.
 *
 * Expression:
 \verbatim
  c[row][col] = a[row][col] + b[row][col]
 \endverbatim
 *
 * @param[in]	a matrix with elements to sum
 * @param[in]	b matrix with elements to sum
 * @param[out]	c matrix with the result of the sum	
 * @param[in]	rows number of rows of the matrixes
 * @param[in]	cols number of cols of the matrixes
 *
 */
void summatrix_double_sse2(double **a, double **b, double **c, int rows, int cols)
{
	int i = 0;

	for( i = 0; i < rows; i++)
		sumarray_double_sse2(a[i], b[i], c[i], cols);
}

/**
 * Calculate the sum of two linear matrix of floats.
 * Classic algorithm.
 *
 * Expression:
 \verbatim
  c[row][col] = a[row][col] + b[row][col]
 \endverbatim
 *
 * @param[in]	a matrix with elements to sum
 * @param[in]	b matrix with elements to sum
 * @param[out]	c matrix with the result of the sum	
 * @param[in]	rows number of rows of the matrixes
 * @param[in]	cols number of cols of the matrixes
 *
 */
void sum_linear_matrix_double(double *a, double *b, double *c, int rows, int cols)
{
	int size = rows * cols;
	int i = 0;

	for(i = 0; i < size; i++)
		c[i] = a[i] + b[i];
}

/**
 * Calculate the sum of two linear matrix of doubles.
 * Algorithm uses SSE2 instructions.
 *
 * Expression:
 \verbatim
  c[row][col] = a[row][col] + b[row][col]
 \endverbatim
 *
 * @param[in]	a matrix with elements to sum
 * @param[in]	b matrix with elements to sum
 * @param[out]	c matrix with the result of the sum	
 * @param[in]	rows number of rows of the matrixes
 * @param[in]	cols number of cols of the matrixes
 *
 */
void sum_linear_matrix_double_sse2(double *a, double *b, double *c, int rows, int cols)
{
	int i = 0;
	int size = rows * cols;
	int length = (size / 2) * 2;

	for (i = 0; i < length; i += 2)
	{
		__asm__ volatile
                ( // instruction             comment                  
                "\n\t movdqa     %1,%%xmm0         \t#"
                "\n\t movdqa     %2,%%xmm1         \t#"
                "\n\t addpd      %%xmm0,%%xmm1     \t#"
                "\n\t movdqa     %%xmm1,%0         \t#"
		: "=m" (c[i])      // %0
		: "m"  (a[i]),     // %1 
		  "m"  (b[i])      // %2
		);
	}

	for(i = length; i < size; i++)
		c[i] = a[i] + b[i];
}

/**
 * Calculate the mul of two arrays of floats.
 * Classic algorithm.
 *
 * Expression:
 \verbatim
  c[i] = a[i] * b[i]
 \endverbatim
 *
 * @param[in]	a array with elements to mul
 * @param[in]	b array with elements to mul
 * @param[in]	size size of the arrays
 * @param[out]	c array with the result of the sum	
 *
 */
void mularray_float(float *a, float *b, float *c, int size)
{
	int i = 0;
	
	for(i = 0; i < size; i++)
		c[i] = a[i] * b[i];
}

/**
 * Calculate the mul of two arrays of floats.
 * Algorithm uses SSE2 instructions.
 *
 * Expression:
 \verbatim
  c[i] = a[i] * b[i]
 \endverbatim
 *
 * @param[in]	a array with elements to mul
 * @param[in]	b array with elements to mul
 * @param[in]	size size of the arrays
 * @param[out]	c array with the result of the sum	
 *
 */
void mularray_float_sse2(float *a, float *b, float *c, int size)
{
	int i = 0, length = (size / 4) * 4;
	
	for (i = 0; i < length; i += 4)
	{
		__asm__ volatile
                ( // instruction             comment                  
                "\n\t movdqa     %1,%%xmm0         \t#"
                "\n\t movdqa     %2,%%xmm1         \t#"
                "\n\t mulps      %%xmm0,%%xmm1     \t#"
                "\n\t movdqa     %%xmm1,%0         \t#"
		: "=m" (c[i])      // %0
		: "m"  (a[i]),     // %1 
		  "m"  (b[i])      // %2
		);
	}
	
	for(i = length; i < size; i++)
		c[i] = a[i] * b[i];
}

/**
 * Calculate the mul of two arrays of floats.
 * Algorithm uses SSE2 instructions.
 *
 * Expression:
 \verbatim
  c[i] = a[i] * b[i]
 \endverbatim
 *
 * @param[in]	a array with elements to mul
 * @param[in]	b array with elements to mul
 * @param[in]	size size of the arrays
 * @param[out]	c array with the result of the sum	
 *
 */
void mularray_float_unrolled_sse2(float *a, float *b, float *c, int size)
{
	int i = 0,
	length = (size/4)*4,
	length2 = (size/8)*8,
	length4 = (size/16)*16;

	for(i = 0; i < length4; i+=16)
	{
		__asm__ volatile
                ( // instruction             comment
                "\n\t movdqa     %4,%%xmm0         \t#"
		"\n\t movdqa     %5,%%xmm1         \t#"
		"\n\t movdqa     %6,%%xmm2        \t#"
		"\n\t movdqa     %7,%%xmm3        \t#"
		"\n\t movdqa     %8,%%xmm4        \t#"
		"\n\t movdqa     %9,%%xmm5        \t#"
		"\n\t movdqa     %10,%%xmm6        \t#"
		"\n\t movdqa     %11,%%xmm7        \t#"
		"\n\t mulps      %%xmm0,%%xmm1     \t#"
		"\n\t mulps      %%xmm2,%%xmm3     \t#"
		"\n\t mulps      %%xmm4,%%xmm5     \t#"
		"\n\t mulps      %%xmm6,%%xmm7     \t#"
                "\n\t movdqa     %%xmm1,%0         \t#"
		"\n\t movdqa     %%xmm3,%1         \t#"
		"\n\t movdqa     %%xmm5,%2         \t#"
		"\n\t movdqa     %%xmm7,%3         \t#"
		: "=m" (c[i]),     // %0
		  "=m" (c[i+4]),   // %1
		  "=m" (c[i+8]),   // %2
		  "=m" (c[i+12])   // %3
		: "m"  (a[i]),     // %4
		  "m"  (b[i]),     // %5
		  "m"  (a[i+4]),   // %6
		  "m"  (b[i+4]),   // %7
		  "m"  (a[i+8]),   // %8
		  "m"  (b[i+8]),   // %9
		  "m"  (a[i+12]),  // %10
		  "m"  (b[i+12])   // %11
		);
	}

	for(i = length4; i < length2; i+=8)
	{
		__asm__ volatile
                ( // instruction             comment
                "\n\t movdqa     %2,%%xmm0         \t#"
		"\n\t movdqa     %3,%%xmm1         \t#"
		"\n\t movdqa     %4,%%xmm2         \t#"
		"\n\t movdqa     %5,%%xmm3         \t#"
		"\n\t mulps      %%xmm0,%%xmm1     \t#"
		"\n\t mulps      %%xmm2,%%xmm3     \t#"
	        "\n\t movdqa     %%xmm1,%0         \t#"
		"\n\t movdqa     %%xmm3,%1         \t#"
		: "=m" (c[i]),     // %0
		  "=m" (c[i+4])    // %1
		: "m"  (a[i]),     // %2
		  "m"  (b[i]),     // %3
		  "m"  (a[i+4]),   // %4
		  "m"  (b[i+4])    // %5
		);
	}
		
	for (i = length2; i < length; i += 4)
	{
		__asm__ volatile
                ( // instruction             comment                  
                "\n\t movdqa     %1,%%xmm0         \t#"
                "\n\t movdqa     %2,%%xmm1         \t#"
                "\n\t mulps      %%xmm0,%%xmm1     \t#"
                "\n\t movdqa     %%xmm1,%0         \t#"
		: "=m" (c[i])      // %0
		: "m"  (a[i]),     // %1 
		  "m"  (b[i])      // %2
		);
	}
	
	for(i = length; i < size; i++)
		c[i] = a[i] * b[i];
}

/**
 * Calculate the mul of two arrays of float.
 * Algorithm uses SSE2 instructions.
 *
 * Expression:
 \verbatim
  c[i] = a[i] * b[i]
 \endverbatim
 *
 * @param[in]	a array with elements to mul
 * @param[in]	b array with elements to mul
 * @param[in]	size size of the arrays
 * @param[out]	c array with the result of the sum	
 *
 */
void mularray_float_unaligned_sse2(float *a, float *b, float *c, int size)
{
	int i = 0, length = (size / 4) * 4;
	
	for (i = 0; i < length; i += 4)
	{
		__asm__ volatile
                ( // instruction             comment                  
                "\n\t movdqu     %1,%%xmm0         \t#"
                "\n\t movdqa     %2,%%xmm1         \t#"
                "\n\t mulps      %%xmm0,%%xmm1     \t#"
                "\n\t movdqa     %%xmm1,%0         \t#"
		: "=m" (c[i])      // %0
		: "m"  (a[i]),     // %1 
		  "m"  (b[i])      // %2
		);
	}
	
	for(i = length; i < size; i++)
		c[i] = a[i] * b[i];
}

/**
 * Calculate the mul of two arrays of floats.
 * Algorithm uses SSE2 instructions.
 *
 * Expression:
 \verbatim
  c[i] = a[i] * b[i]
 \endverbatim
 *
 * @param[in]	a array with elements to mul
 * @param[in]	b array with elements to mul
 * @param[in]	size size of the arrays
 * @param[out]	c array with the result of the sum	
 *
 */
void mularray_float_unrolled_unaligned_sse2(float *a, float *b, float *c, int size)
{
	int i = 0,
	length = (size/4)*4,
	length2 = (size/8)*8,
	length4 = (size/16)*16;

	for(i = 0; i < length4; i+=16)
	{
		__asm__ volatile
                ( // instruction             comment
                "\n\t movdqu     %4,%%xmm0         \t#"
		"\n\t movdqa     %5,%%xmm1         \t#"
		"\n\t movdqu     %6,%%xmm2        \t#"
		"\n\t movdqa     %7,%%xmm3        \t#"
		"\n\t movdqu     %8,%%xmm4        \t#"
		"\n\t movdqa     %9,%%xmm5        \t#"
		"\n\t movdqu     %10,%%xmm6        \t#"
		"\n\t movdqa     %11,%%xmm7        \t#"
		"\n\t mulps      %%xmm0,%%xmm1     \t#"
		"\n\t mulps      %%xmm2,%%xmm3     \t#"
		"\n\t mulps      %%xmm4,%%xmm5     \t#"
		"\n\t mulps      %%xmm6,%%xmm7     \t#"
                "\n\t movdqa     %%xmm1,%0         \t#"
		"\n\t movdqa     %%xmm3,%1         \t#"
		"\n\t movdqa     %%xmm5,%2         \t#"
		"\n\t movdqa     %%xmm7,%3         \t#"
		: "=m" (c[i]),     // %0
		  "=m" (c[i+4]),   // %1
		  "=m" (c[i+8]),   // %2
		  "=m" (c[i+12])   // %3
		: "m"  (a[i]),     // %4
		  "m"  (b[i]),     // %5
		  "m"  (a[i+4]),   // %6
		  "m"  (b[i+4]),   // %7
		  "m"  (a[i+8]),   // %8
		  "m"  (b[i+8]),   // %9
		  "m"  (a[i+12]),  // %10
		  "m"  (b[i+12])   // %11
		);
	}

	for(i = length4; i < length2; i+=8)
	{
		__asm__ volatile
                ( // instruction             comment
                "\n\t movdqu     %2,%%xmm0         \t#"
		"\n\t movdqa     %3,%%xmm1         \t#"
		"\n\t movdqu     %4,%%xmm2         \t#"
		"\n\t movdqa     %5,%%xmm3         \t#"
		"\n\t mulps      %%xmm0,%%xmm1     \t#"
		"\n\t mulps      %%xmm2,%%xmm3     \t#"
	        "\n\t movdqa     %%xmm1,%0         \t#"
		"\n\t movdqa     %%xmm3,%1         \t#"
		: "=m" (c[i]),     // %0
		  "=m" (c[i+4])    // %1
		: "m"  (a[i]),     // %2
		  "m"  (b[i]),     // %3
		  "m"  (a[i+4]),   // %4
		  "m"  (b[i+4])    // %5
		);
	}
		
	for (i = length2; i < length; i += 4)
	{
		__asm__ volatile
                ( // instruction             comment                  
                "\n\t movdqu     %1,%%xmm0         \t#"
                "\n\t movdqa     %2,%%xmm1         \t#"
                "\n\t mulps      %%xmm0,%%xmm1     \t#"
                "\n\t movdqa     %%xmm1,%0         \t#"
		: "=m" (c[i])      // %0
		: "m"  (a[i]),     // %1 
		  "m"  (b[i])      // %2
		);
	}
	
	for(i = length; i < size; i++)
		c[i] = a[i] * b[i];
}

/**
 * Calculate the mul of two arrays of doubles.
 * Classic algorithm.
 *
 * Expression:
 \verbatim
  c[i] = a[i] * b[i]
 \endverbatim
 *
 * @param[in]	a array with elements to mul
 * @param[in]	b array with elements to mul
 * @param[in]	size size of the arrays
 * @param[out]	c array with the result of the sum	
 *
 */
void mularray_double(double *a, double *b, double *c, int size)
{
	int i = 0;

	for(i = 0; i < size; i++)
		c[i] = a[i] * b[i];
}

/**
 * Calculate the mul of two arrays of doubles.
 * Algorithm uses SSE2 instructions.
 *
 * Expression:
 \verbatim
  c[i] = a[i] * b[i]
 \endverbatim
 *
 * @param[in]	a array with elements to mul
 * @param[in]	b array with elements to mul
 * @param[in]	size size of the arrays
 * @param[out]	c array with the result of the sum	
 *
 */
void mularray_double_sse2(double *a, double *b, double *c, int size)
{
	int i = 0, length = (size / 2) * 2;
	
	for (i = 0; i < length; i += 2)
	{
		__asm__ volatile
                ( // instruction             comment                  
                "\n\t movdqa     %1,%%xmm0         \t#"
                "\n\t movdqa     %2,%%xmm1         \t#"
                "\n\t mulpd      %%xmm0,%%xmm1     \t#"
                "\n\t movdqa     %%xmm1,%0         \t#"
		: "=m" (c[i])      // %0
		: "m"  (a[i]),     // %1 
		  "m"  (b[i])      // %2
		);
	}
	
	for(i = length; i < size; i++)
		c[i] = a[i] * b[i];
}

/**
 * Calculate the mul of two arrays of floats.
 * Algorithm uses SSE2 instructions.
 *
 * Expression:
 \verbatim
  c[i] = a[i] * b[i]
 \endverbatim
 *
 * @param[in]	a array with elements to mul
 * @param[in]	b array with elements to mul
 * @param[in]	size size of the arrays
 * @param[out]	c array with the result of the sum	
 *
 */
void mularray_double_unrolled_sse2(double *a, double *b, double *c, int size)
{
	int i = 0,
	length = (size/2)*2,
	length2 = (size/4)*4,
	length4 = (size/8)*8;

	for(i = 0; i < length4; i+=8)
	{
		__asm__ volatile
                ( // instruction             comment
                "\n\t movdqa     %4,%%xmm0         \t#"
		"\n\t movdqa     %5,%%xmm1         \t#"
		"\n\t movdqa     %6,%%xmm2        \t#"
		"\n\t movdqa     %7,%%xmm3        \t#"
		"\n\t movdqa     %8,%%xmm4        \t#"
		"\n\t movdqa     %9,%%xmm5        \t#"
		"\n\t movdqa     %10,%%xmm6        \t#"
		"\n\t movdqa     %11,%%xmm7        \t#"
		"\n\t mulpd      %%xmm0,%%xmm1     \t#"
		"\n\t mulpd      %%xmm2,%%xmm3     \t#"
		"\n\t mulpd      %%xmm4,%%xmm5     \t#"
		"\n\t mulpd      %%xmm6,%%xmm7     \t#"
                "\n\t movdqa     %%xmm1,%0         \t#"
		"\n\t movdqa     %%xmm3,%1         \t#"
		"\n\t movdqa     %%xmm5,%2         \t#"
		"\n\t movdqa     %%xmm7,%3         \t#"
		: "=m" (c[i]),     // %0
		  "=m" (c[i+2]),   // %1
		  "=m" (c[i+4]),   // %2
		  "=m" (c[i+6])    // %3
		: "m"  (a[i]),     // %4
		  "m"  (b[i]),     // %5
		  "m"  (a[i+2]),   // %6
		  "m"  (b[i+2]),   // %7
		  "m"  (a[i+4]),   // %8
		  "m"  (b[i+4]),   // %9
		  "m"  (a[i+6]),   // %10
		  "m"  (b[i+6])    // %11
		);
	}

	for(i = length4; i < length2; i+=4)
	{
		__asm__ volatile
                ( // instruction             comment
                "\n\t movdqa     %2,%%xmm0         \t#"
		"\n\t movdqa     %3,%%xmm1         \t#"
		"\n\t movdqa     %4,%%xmm2         \t#"
		"\n\t movdqa     %5,%%xmm3         \t#"
		"\n\t mulpd      %%xmm0,%%xmm1     \t#"
		"\n\t mulpd      %%xmm2,%%xmm3     \t#"
	        "\n\t movdqa     %%xmm1,%0         \t#"
		"\n\t movdqa     %%xmm3,%1         \t#"
		: "=m" (c[i]),     // %0
		  "=m" (c[i+2])    // %1
		: "m"  (a[i]),     // %2
		  "m"  (b[i]),     // %3
		  "m"  (a[i+2]),   // %4
		  "m"  (b[i+2])    // %5
		);
	}
		
	for (i = length2; i < length; i += 2)
	{
		__asm__ volatile
                ( // instruction             comment                  
                "\n\t movdqa     %1,%%xmm0         \t#"
                "\n\t movdqa     %2,%%xmm1         \t#"
                "\n\t mulpd      %%xmm0,%%xmm1     \t#"
                "\n\t movdqa     %%xmm1,%0         \t#"
		: "=m" (c[i])      // %0
		: "m"  (a[i]),     // %1 
		  "m"  (b[i])      // %2
		);
	}
	
	for(i = length; i < size; i++)
		c[i] = a[i] * b[i];
}

/**
 * Calculate the mul of two arrays of doubles.
 * The second array must be aligned.
 * Useful for calculate convulations.
 * Algorithm uses SSE2 instructions.
 *
 * Expression:
 \verbatim
  c[i] = a[i] * b[i]
 \endverbatim
 *
 * @param[in]	a array with elements to mul
 * @param[in]	b array with elements to mul
 * @param[in]	size size of the arrays
 * @param[out]	c array with the result of the sum	
 *
 */
void mularray_double_unaligned_sse2(double *a, double *b, double *c, int size)
{
	int i = 0,
	length = (size/2)*2;
		
	for (i = 0; i < length; i += 2)
	{
		__asm__ volatile
                ( // instruction             comment                  
                "\n\t movdqu     %1,%%xmm0         \t#"
                "\n\t movdqa     %2,%%xmm1         \t#"
                "\n\t mulpd      %%xmm0,%%xmm1     \t#"
                "\n\t movdqa     %%xmm1,%0         \t#"
		: "=m" (c[i])      // %0
		: "m"  (a[i]),     // %1 
		  "m"  (b[i])      // %2
		);
	}
	
	for(i = length; i < size; i++)
		c[i] = a[i] * b[i];
}

/**
 * Calculate the mul of two arrays of doubles.
 * The second array must be aligned.
 * Useful for calculate convulations.
 * Algorithm uses SSE2 instructions.
 * Unrolled version of the algorithm.
 *
 * Expression:
 \verbatim
  c[i] = a[i] * b[i]
 \endverbatim
 *
 * @param[in]	a array with elements to mul
 * @param[in]	b array with elements to mul
 * @param[in]	size size of the arrays
 * @param[out]	c array with the result of the sum	
 *
 */
void mularray_double_unrolled_unaligned_sse2(double *a, double *b, double *c, int size)
{
	int i = 0,
	length = (size/2)*2,
	length2 = (size/4)*4,
	length4 = (size/8)*8;

	for(i = 0; i < length4; i+=8)
	{
		__asm__ volatile
                ( // instruction             comment
                "\n\t movdqu     %4,%%xmm0         \t#"
		"\n\t movdqa     %5,%%xmm1         \t#"
		"\n\t movdqu     %6,%%xmm2         \t#"
		"\n\t movdqa     %7,%%xmm3         \t#"
		"\n\t movdqu     %8,%%xmm4         \t#"
		"\n\t movdqa     %9,%%xmm5         \t#"
		"\n\t movdqu     %10,%%xmm6        \t#"
		"\n\t movdqa     %11,%%xmm7        \t#"
		"\n\t mulpd      %%xmm0,%%xmm1     \t#"
		"\n\t mulpd      %%xmm2,%%xmm3     \t#"
		"\n\t mulpd      %%xmm4,%%xmm5     \t#"
		"\n\t mulpd      %%xmm6,%%xmm7     \t#"
                "\n\t movdqa     %%xmm1,%0         \t#"
		"\n\t movdqa     %%xmm3,%1         \t#"
		"\n\t movdqa     %%xmm5,%2         \t#"
		"\n\t movdqa     %%xmm7,%3         \t#"
		: "=m" (c[i]),     // %0
		  "=m" (c[i+2]),   // %1
		  "=m" (c[i+4]),   // %2
		  "=m" (c[i+6])    // %3
		: "m"  (a[i]),     // %4
		  "m"  (b[i]),     // %5
		  "m"  (a[i+2]),   // %6
		  "m"  (b[i+2]),   // %7
		  "m"  (a[i+4]),   // %8
		  "m"  (b[i+4]),   // %9
		  "m"  (a[i+6]),   // %10
		  "m"  (b[i+6])    // %11
		);
	}

	for(i = length4; i < length2; i+=4)
	{
		__asm__ volatile
                ( // instruction             comment
                "\n\t movdqu     %2,%%xmm0         \t#"
		"\n\t movdqa     %3,%%xmm1         \t#"
		"\n\t movdqu     %4,%%xmm2         \t#"
		"\n\t movdqa     %5,%%xmm3         \t#"
		"\n\t mulpd      %%xmm0,%%xmm1     \t#"
		"\n\t mulpd      %%xmm2,%%xmm3     \t#"
	        "\n\t movdqa     %%xmm1,%0         \t#"
		"\n\t movdqa     %%xmm3,%1         \t#"
		: "=m" (c[i]),     // %0
		  "=m" (c[i+2])    // %1
		: "m"  (a[i]),     // %2
		  "m"  (b[i]),     // %3
		  "m"  (a[i+2]),   // %4
		  "m"  (b[i+2])    // %5
		);
	}
		
	for (i = length2; i < length; i += 2)
	{
		__asm__ volatile
                ( // instruction             comment                  
                "\n\t movdqu     %1,%%xmm0         \t#"
                "\n\t movdqa     %2,%%xmm1         \t#"
                "\n\t mulpd      %%xmm0,%%xmm1     \t#"
                "\n\t movdqa     %%xmm1,%0         \t#"
		: "=m" (c[i])      // %0
		: "m"  (a[i]),     // %1 
		  "m"  (b[i])      // %2
		);
	}
	
	for(i = length; i < size; i++)
		c[i] = a[i] * b[i];
}

/**
 * Calculate the dot product of two arrays of float.
 * Classic algorithm.
 *
 * Expression:
 \verbatim
  rv = a[0]*b[0] + a[1]*b[1] + ... + a[size]*b[size]
 \endverbatim
 *
 * @param[in]	a array to calculate dot product
 * @param[in]	b array to calculate dot product
 * @param[in]	size size of the arrays
 * @return	the dot product	
 *
 */
float dotProduct_float(float *a, float *b, int size)
{
	float sum = 0;

	for(int i=0; i<size; i++)
		sum += a[i] * b[i];
		
	return sum;
}

/**
 * Calculate the dot product of two arrays of float.
 * Algorithm uses SSE2 instructions.
 *
 * Expression:
 \verbatim
  rv = a[0]*b[0] + a[1]*b[1] + ... + a[size]*b[size]
 \endverbatim
 *
 * @param[in]	a array to calculate dot product
 * @param[in]	b array to calculate dot product
 * @param[in]	size size of the arrays
 * @return	the dot product	
 *
 */
float dotProduct_float_sse2(float *a, float *b, int size)
{
	float __attribute__ ((aligned(16))) c[] = {0.0, 0.0, 0.0, 0.0};
	int i = 0,
	    length  = (size/4)*4;
	float rv = 0.0;

	__asm__ volatile
        ("\n\tmovdqa %0,%%xmm0\t#" : :"m" (c[0]));

	for(; i < length; i += 4)
	{
		__asm__ volatile
		(// instruction		 comment
		 "\n\t movdqa %0,%%xmm2    \t#"
		 "\n\t movdqa %1,%%xmm3    \t#"
		 "\n\t mulps %%xmm3,%%xmm2 \t#"
		 "\n\t addps %%xmm2,%%xmm0 \t#"
		 :
		 :"m"  (a[i]),
		  "m"  (b[i])
		);
	}

	__asm__ volatile
        ("\n\t movdqa %%xmm0,%0    \t#" :"=m" (c[0]): );
	
	rv = c[0]+c[1]+c[2]+c[3];

	for(; i < size; i++)
	{
		rv += (a[i] * b[i]); 
	}

	return rv;
}

/**
 * Calculate the dot product of two arrays of float.
 * Algorithm uses SSE2 instructions.
 *
 * Expression:
 \verbatim
  rv = a[0]*b[0] + a[1]*b[1] + ... + a[size]*b[size]
 \endverbatim
 *
 * @param[in]	a array to calculate dot product
 * @param[in]	b array to calculate dot product
 * @param[in]	size size of the arrays
 * @return	the dot product	
 *
 */
float dotProduct_float_unrolled_sse2(float *a, float *b, int size)
{
	float __attribute__ ((aligned(16))) c[] = {0.0, 0.0, 0.0, 0.0};
	int i = 0,
	    length3 = (size/12)*12,
	    length2 = (size/8)*8,
	    length  = (size/4)*4;
	float rv = 0.0;

	__asm__ volatile
        ("\n\tmovdqa %0,%%xmm0\t#"
	 "\n\tmovdqa %0,%%xmm1\t#" : :"m" (c[0]));

	for(; i < length3; i += 12)
	{
		__asm__ volatile
		(// instruction		 comment
		 "\n\t movdqa %0,%%xmm2 \t#"
		 "\n\t movdqa %1,%%xmm3 \t#"
		 "\n\t movdqa %2,%%xmm4 \t#"
		 "\n\t movdqa %3,%%xmm5 \t#"
		 "\n\t movdqa %4,%%xmm6 \t#"
		 "\n\t movdqa %5,%%xmm7 \t#"
		 "\n\t mulps %%xmm3,%%xmm2 \t#"
		 "\n\t mulps %%xmm5,%%xmm4 \t#"
		 "\n\t mulps %%xmm7,%%xmm6 \t#"
		 "\n\t addps %%xmm2,%%xmm0 \t#"
		 "\n\t addps %%xmm4,%%xmm1 \t#"
		 "\n\t addps %%xmm6,%%xmm0 \t#"
		 :
		 :"m"  (a[i]),
		  "m"  (b[i]),
		  "m"  (a[i+4]),
		  "m"  (b[i+4]),
		  "m"  (a[i+8]),
		  "m"  (b[i+8]) 
		);
	}

	for(; i < length2; i += 8)
	{
		__asm__ volatile
		(// instruction		 comment
		 "\n\t movdqa %0,%%xmm2 \t#"
		 "\n\t movdqa %1,%%xmm3 \t#"
		 "\n\t movdqa %2,%%xmm4 \t#"
		 "\n\t movdqa %3,%%xmm5 \t#"
		 "\n\t mulps %%xmm3,%%xmm2 \t#"
		 "\n\t mulps %%xmm5,%%xmm4 \t#"
		 "\n\t addps %%xmm2,%%xmm0 \t#"
		 "\n\t addps %%xmm4,%%xmm1 \t#"
		 :
		 :"m"  (a[i]),
		  "m"  (b[i]),
		  "m"  (a[i+4]),
		  "m"  (b[i+4])
		);
	}

	for(; i < length; i += 4)
	{
		__asm__ volatile
		(// instruction		 comment
		 "\n\t movdqa %0,%%xmm2    \t#"
		 "\n\t movdqa %1,%%xmm3    \t#"
		 "\n\t mulps %%xmm3,%%xmm2 \t#"
		 "\n\t addps %%xmm2,%%xmm0 \t#"
		 :
		 :"m"  (a[i]),
		  "m"  (b[i])
		);
	}

	__asm__ volatile
        ("\n\t addps %%xmm1,%%xmm0 \t#"
	 "\n\t movdqa %%xmm0,%0    \t#" :"=m" (c[0]): );
	
	rv = c[0]+c[1]+c[2]+c[3];

	for(; i < size; i++)
	{
		rv += (a[i] * b[i]); 
	}

	return rv;
}

/**
 * Calculate the dot product of two arrays of doubles.
 * Classic algorithm.
 *
 * Expression:
 \verbatim
  rv = a[0]*b[0] + a[1]*b[1] + ... + a[size]*b[size]
 \endverbatim
 *
 * @param[in]	a array to calculate dot product
 * @param[in]	b array to calculate dot product
 * @param[in]	size size of the arrays
 * @return	the dot product	
 *
 */
float dotProduct_double(double *a, double *b, int size)
{
	float sum = 0;

	for(int i=0; i<size; i++)
		sum += a[i] * b[i];
		
	return sum;
}

/**
 * Calculate the dot product of two arrays of doubles.
 * Algorithm uses SSE2 instructions.
 *
 * Expression:
 \verbatim
  rv = a[0]*b[0] + a[1]*b[1] + ... + a[size]*b[size]
 \endverbatim
 *
 * @param[in]	a array to calculate dot product
 * @param[in]	b array to calculate dot product
 * @param[in]	size size of the arrays
 * @return	the dot product	
 *
 */
float dotProduct_double_sse2(double *a, double *b, int size)
{
	double __attribute__ ((aligned(16))) c[] = {0.0, 0.0};
	double rv = 0.0;
	int i = 0,
	    length = (size / 2) * 2;

	__asm__ volatile
        ("\n\tmovdqa %0,%%xmm0\t#": :"m" (c[0]));

	for(; i < length; i += 2)
	{
		__asm__ volatile
		(// instruction		 comment
		 "\n\t movdqa %0,%%xmm2    \t#"
		 "\n\t movdqa %1,%%xmm3    \t#"
		 "\n\t mulpd %%xmm3,%%xmm2 \t#"
		 "\n\t addpd %%xmm2,%%xmm0 \t#"
		 :
		 :"m"  (a[i]),
		  "m"  (b[i])
		);
	}

	__asm__ volatile
        ("\n\t movdqa %%xmm0,%0    \t#" :"=m" (c[0]): );
	
	rv = c[0] + c[1];

	for(; i < size; i++)
	{
		rv += (a[i] * b[i]); 
	}

	return rv;
}

/**
 * Calculate the dot product of two arrays of doubles.
 * Algorithm uses SSE2 instructions.
 *
 * Expression:
 \verbatim
  rv = a[0]*b[0] + a[1]*b[1] + ... + a[size]*b[size]
 \endverbatim
 *
 * @param[in]	a array to calculate dot product
 * @param[in]	b array to calculate dot product
 * @param[in]	size size of the arrays
 * @return	the dot product	
 *
 */
double dotProduct_double_unrolled_sse2(double *a, double *b, int size)
{
	double __attribute__ ((aligned(16))) c[] = {0.0, 0.0};
	int i = 0,
	    length3 = (size/6)*6,
	    length2 = (size/4)*4,
	    length  = (size/2)*2;
	double rv = 0.0;

	__asm__ volatile
        ("\n\tmovdqa %0,%%xmm0\t#"
	 "\n\tmovdqa %0,%%xmm1\t#" : :"m" (c[0]));

	for(; i < length3; i += 6)
	{
		__asm__ volatile
		(// instruction		 comment
		 "\n\t movdqa %0,%%xmm2 \t#"
		 "\n\t movdqa %1,%%xmm3 \t#"
		 "\n\t movdqa %2,%%xmm4 \t#"
		 "\n\t movdqa %3,%%xmm5 \t#"
		 "\n\t movdqa %4,%%xmm6 \t#"
		 "\n\t movdqa %5,%%xmm7 \t#"
		 "\n\t mulpd %%xmm3,%%xmm2 \t#"
		 "\n\t mulpd %%xmm5,%%xmm4 \t#"
		 "\n\t mulpd %%xmm7,%%xmm6 \t#"
		 "\n\t addpd %%xmm2,%%xmm0 \t#"
		 "\n\t addpd %%xmm4,%%xmm1 \t#"
		 "\n\t addpd %%xmm6,%%xmm0 \t#"
		 :
		 :"m"  (a[i]),
		  "m"  (b[i]),
		  "m"  (a[i+2]),
		  "m"  (b[i+2]),
		  "m"  (a[i+4]),
		  "m"  (b[i+4]) 
		);
	}

	for(; i < length2; i += 4)
	{
		__asm__ volatile
		(// instruction		 comment
		 "\n\t movdqa %0,%%xmm2 \t#"
		 "\n\t movdqa %1,%%xmm3 \t#"
		 "\n\t movdqa %2,%%xmm4 \t#"
		 "\n\t movdqa %3,%%xmm5 \t#"
		 "\n\t mulpd %%xmm3,%%xmm2 \t#"
		 "\n\t mulpd %%xmm5,%%xmm4 \t#"
		 "\n\t addpd %%xmm2,%%xmm0 \t#"
		 "\n\t addpd %%xmm4,%%xmm1 \t#"
		 :
		 :"m"  (a[i]),
		  "m"  (b[i]),
		  "m"  (a[i+2]),
		  "m"  (b[i+2])
		);
	}

	for(; i < length; i += 2)
	{
		__asm__ volatile
		(// instruction		 comment
		 "\n\t movdqa %0,%%xmm2    \t#"
		 "\n\t movdqa %1,%%xmm3    \t#"
		 "\n\t mulpd %%xmm3,%%xmm2 \t#"
		 "\n\t addpd %%xmm2,%%xmm0 \t#"
		 :
		 :"m"  (a[i]),
		  "m"  (b[i])
		);
	}

	__asm__ volatile
        ("\n\t addpd %%xmm1,%%xmm0 \t#"
	 "\n\t movdqa %%xmm0,%0    \t#" :"=m" (c[0]): );
	
	rv = c[0] + c[1];

	for(; i < size; i++)
	{
		rv += (a[i] * b[i]); 
	}

	return rv;
}



/**
 * Calculates the transpose of matrix A and store it in matrix B.
 * Classic Algorithm.
 *
 * Example:
 \verbatim
        A	         B	
  | 1| 2| 3| 4|    | 1| 5| 9|13|
  | 5| 6| 7| 8| => | 2| 6|10|14|
  | 9|10|11|12|    | 3| 7|11|15|
  |13|14|15|16|    | 4| 8|12|16|
 \endverbatim
 *
 * @param[in]	a source matrix
 * @param[out]	b destination array
 * @param[in]	rows number of rows of matrix A and number of columns of matrix B
 * @param[in]	cols number of columns of matrix A and number of rows of matrix A
 *
 */

void transpose_matrix_float(float **a, float **b, int rows, int cols)
{
	int i = 0, j = 0;

	for(i = 0; i < rows; i++)
		for(j = 0; j < cols; j++)
			b[j][i] = a[i][j]; 
}

/**
 * Calculates the transpose of matrix A and store it in matrix B.
 * Algorithm uses SSE2.
 *
 * Example:
 \verbatim
        A	         B	
  | 1| 2| 3| 4|    | 1| 5| 9|13|
  | 5| 6| 7| 8| => | 2| 6|10|14|
  | 9|10|11|12|    | 3| 7|11|15|
  |13|14|15|16|    | 4| 8|12|16|
 \endverbatim
 *
 * @param[in]	a source matrix
 * @param[out]	b destination array
 * @param[in]	rows number of rows of matrix A and number of columns of matrix B
 * @param[in]	cols number of columns of matrix A and number of rows of matrix A
 *
 */

void transpose_matrix_float_sse2(float **a, float **b, int rows, int cols)
{
	int i = 0, j = 0, lengthRows = (rows / 4) * 4, lengthCols = (cols / 4) * 4;
	float *a0 = NULL, *a1 = NULL, *a2 = NULL, *a3 = NULL,
	      *b0 = NULL, *b1 = NULL, *b2 = NULL, *b3 = NULL;

	for(j = 0; j < lengthCols; j += 4)
	{
		for(i = 0; i < lengthRows; i += 4)
		{
			a0 = &(a[i][j]);
			a1 = &(a[i+1][j]);
			a2 = &(a[i+2][j]);
		       	a3 = &(a[i+3][j]);
			b0 = &(b[j][i]);
			b1 = &(b[j+1][i]);
			b2 = &(b[j+2][i]);
			b3 = &(b[j+3][i]);

			__asm__ volatile
			( // instruction             comment
			"\n\t movdqa	%4,%%xmm0	\t#"
			"\n\t movdqa	%5,%%xmm1	\t#"
			"\n\t movdqa	%6,%%xmm2	\t#"
			"\n\t movdqa	%7,%%xmm3	\t#"
			"\n\t movdqa	%4,%%xmm4	\t#"
			"\n\t movdqa	%5,%%xmm5	\t#"
			"\n\t movdqa	%6,%%xmm6	\t#"
			"\n\t movdqa	%7,%%xmm7	\t#"
			"\n\t unpcklps  %%xmm2,%%xmm0	\t#"
			"\n\t unpcklps	%%xmm3,%%xmm1	\t#"	
			"\n\t unpcklps  %%xmm6,%%xmm4	\t#"
			"\n\t unpcklps	%%xmm7,%%xmm5	\t#"
			"\n\t unpcklps	%%xmm1,%%xmm0	\t#"
			"\n\t unpckhps	%%xmm5,%%xmm4	\t#"
			"\n\t movdqa    %%xmm0,%0	\t#"
			"\n\t movdqa    %%xmm4,%1	\t#"
			"\n\t movdqa	%4,%%xmm0	\t#"
			"\n\t movdqa	%5,%%xmm1	\t#"
			"\n\t movdqa	%4,%%xmm4	\t#"
			"\n\t movdqa	%5,%%xmm5	\t#"
			"\n\t unpckhps  %%xmm2,%%xmm0	\t#"
			"\n\t unpckhps	%%xmm3,%%xmm1	\t#"
			"\n\t unpckhps  %%xmm6,%%xmm4	\t#"
			"\n\t unpckhps	%%xmm7,%%xmm5	\t#"
			"\n\t unpcklps	%%xmm1,%%xmm0	\t#"
			"\n\t unpckhps	%%xmm5,%%xmm4	\t#"
			"\n\t movdqa     %%xmm0,%2	\t#"
			"\n\t movdqa     %%xmm4,%3	\t#"
			: "=m" (*b0),    // %0
			  "=m" (*b1),    // %1
			  "=m" (*b2),    // %2
			  "=m" (*b3)     // %3
			: "m"  (*a0),    // %4
			  "m"  (*a1),    // %5
			  "m"  (*a2),    // %6
			  "m"  (*a3)     // %7
			);
		}
	}

	for(i = 0; i < rows; i++)
		for(j = lengthCols; j < cols; j++)
			b[j][i] = a[i][j];

	for(i = lengthRows; i < rows; i++)
		for(j = 0; j < lengthCols; j++)
			b[j][i] = a[i][j];
}


/*
void transpose_matrix_float_sse2(float **a, float **b, int rows, int cols)
{
	int i = 0, j = 0, lengthRows = (rows / 4) * 4, lengthCols = (cols / 4) * 4;	
	
	for(j = 0; j < lengthCols; j += 4)
	{
		for(i = 0; i < lengthRows; i += 4)
		{
                        float *a0=&(a[i][j]), *a1=&(a[i+1][j]), *a2=&(a[i+2][j]), *a3=&(a[i+3][j]);

			__asm__ volatile
			( // instruction             comment
			"\n\t movdqa	%2,%%xmm0	\t#"
			"\n\t movdqa	%3,%%xmm1	\t#"
			"\n\t movdqa	%4,%%xmm2	\t#"
			"\n\t movdqa	%5,%%xmm3	\t#"
			"\n\t movdqa	%2,%%xmm4	\t#"
			"\n\t movdqa	%3,%%xmm5	\t#"
			"\n\t movdqa	%4,%%xmm6	\t#"
			"\n\t movdqa	%5,%%xmm7	\t#"
			"\n\t unpcklps  %%xmm2,%%xmm0	\t#"
			"\n\t unpcklps	%%xmm3,%%xmm1	\t#"	
			"\n\t unpcklps  %%xmm6,%%xmm4	\t#"
			"\n\t unpcklps	%%xmm7,%%xmm5	\t#"
			"\n\t unpcklps	%%xmm1,%%xmm0	\t#"
			"\n\t unpckhps	%%xmm5,%%xmm4	\t#"
			"\n\t movdqa    %%xmm0,%0	\t#"
			"\n\t movdqa    %%xmm4,%1	\t#"
			"\n\t movdqa	%2,%%xmm0	\t#"
			"\n\t movdqa	%3,%%xmm1	\t#"
			"\n\t movdqa	%2,%%xmm4	\t#"
			"\n\t movdqa	%3,%%xmm5	\t#"
			"\n\t unpckhps  %%xmm2,%%xmm0	\t#"
			"\n\t unpckhps	%%xmm3,%%xmm1	\t#"
			"\n\t unpckhps  %%xmm6,%%xmm4	\t#"
			"\n\t unpckhps	%%xmm7,%%xmm5	\t#"
			"\n\t unpcklps	%%xmm1,%%xmm0	\t#"
			"\n\t unpckhps	%%xmm5,%%xmm4	\t#"
			: "=m" (b[j][i]),      // %0
			  "=m" (b[j+1][i])    // %1
			: "m"  (a0),      // %2
			  "m"  (a1),    // %3
			  "m"  (a2),    // %4
			  "m"  (a3)     // %5
			);


			__asm__ volatile
			( // instruction             comment
			"\n\t movdqa     %%xmm0,%0	\t#"
			"\n\t movdqa     %%xmm4,%1	\t#"
			: "=m" (b[j+2][i]),    // %0
			  "=m" (b[j+3][i])     // %1
                        :
			);

		}
	}

	for(i = 0; i < rows; i++)
		for(j = lengthCols; j < cols; j++)
			b[j][i] = a[i][j];

	for(i = lengthRows; i < rows; i++)
		for(j = 0; j < lengthCols; j++)
			b[j][i] = a[i][j];
}
*/

/**
 * Calculates the transpose of matrix A and store it in matrix B.
 * Classic Algorithm.
 *
 * Example:
 \verbatim
        A	         B	
  | 1| 2| 3| 4|    | 1| 5| 9|13|
  | 5| 6| 7| 8| => | 2| 6|10|14|
  | 9|10|11|12|    | 3| 7|11|15|
  |13|14|15|16|    | 4| 8|12|16|
 \endverbatim
 *
 * @param[in]	a source matrix
 * @param[out]	b destination array
 * @param[in]	rows number of rows of matrix A and number of columns of matrix B
 * @param[in]	cols number of columns of matrix A and number of rows of matrix A
 *
 */
void transpose_matrix_double(double **a, double **b, int rows, int cols)
{
	int i = 0, j = 0;

	for(i = 0; i < rows; i++)
		for(j = 0; j < cols; j++)
			b[j][i] = a[i][j]; 
}

/**
 * Calculates the transpose of matrix A and store it in matrix B.
 * Algorithm uses SSE2.
 *
 * Example:
 \verbatim
        A	         B	
  | 1| 2| 3| 4|    | 1| 5| 9|13|
  | 5| 6| 7| 8| => | 2| 6|10|14|
  | 9|10|11|12|    | 3| 7|11|15|
  |13|14|15|16|    | 4| 8|12|16|
 \endverbatim
 *
 * @param[in]	a source matrix
 * @param[out]	b destination array
 * @param[in]	rows number of rows of matrix A and number of columns of matrix B
 * @param[in]	cols number of columns of matrix A and number of rows of matrix A
 *
 */
void transpose_matrix_double_sse2(double **a, double **b, int rows, int cols)
{
	int i = 0, j = 0, lengthRows = (rows / 2) * 2, lengthCols = (cols / 2) * 2;	
	
	for(j = 0; j < lengthCols; j += 2)
	{
		for(i = 0; i < lengthRows; i += 2)
		{
			__asm__ volatile
			( // instruction             comment
               		"\n\t movdqa	%2,%%xmm0	\t#"
                	"\n\t movdqa	%3,%%xmm1	\t#"
			"\n\t movdqa	%2,%%xmm2	\t#"
                	"\n\t movdqa	%3,%%xmm3	\t#"
                	"\n\t unpcklpd  %%xmm1,%%xmm0	\t#"
			"\n\t unpckhpd  %%xmm3,%%xmm2	\t#"
                	"\n\t movdqa     %%xmm0,%0	\t#"
			"\n\t movdqa     %%xmm2,%1	\t#"
			: "=m" (b[j][i]),    // %0
			  "=m" (b[j+1][i])   // %1
			: "m"  (a[i][j]),    // %2
			  "m"  (a[i+1][j])   // %3
			);
		}
	}

	for(i = 0; i < rows; i++)
		for(j = lengthCols; j < cols; j++)
			b[j][i] = a[i][j];

	for(i = lengthRows; i < rows; i++)
		for(j = 0; j < lengthCols; j++)
			b[j][i] = a[i][j];
}

/**
 * Calculate the mul of two matrixes of floats.
 * Classic algorithm.
 *
 * Expression:
 \verbatim
  c[i][k] = (a[i][0] * b[0][k]) + (a[i][1] * b[1][k]) + ... + (a[i][j] * b[j][k])
 \endverbatim
 *
 * Example:
 \verbatim
  A            B         C
  | 1| 2| 3| * | 1| 4| = |14|32|
  | 4| 5| 6|   | 2| 5|   |32|77|
               | 3| 6|
 \endverbatim
 *
 * @param[in]	a matrix with elements to mul
 * @param[in]	b matrix with elements to mul
 * @param[out]	c result matrix
 * @param[in]	i number of rows of matrix a
 * @param[in]	j number of cols of matrix a and number of rows of matrix b
 * @param[in]	k number of cols of the result matrix
 *
 */
void mulmatrix_float(float **a, float **b, float **c, int i, int j, int k)
{
	int row = 0, col = 0, n = 0;
	float sum = 0.0;

	for(row = 0; row < i; row++)
	{
		for(col = 0; col < k; col++)
		{
			sum = 0.0;
			for(n = 0; n < j; n++)
			{
				sum += a[row][n] * b[n][col];
			}
			c[row][col] = sum;
		}
	}
}

/**
 * Calculate the mul of two matrices of floats.
 * Algorithm uses SSE2 instructions.
 *
 * Expression:
 \verbatim
  c[i][k] = (a[i][0] * b[0][k]) + (a[i][1] * b[1][k]) + ... + (a[i][j] * b[j][k])
 \endverbatim
 *
 * Example:
 \verbatim
 A            B         C
 | 1| 2| 3| * | 1| 4| = |14|32|
 | 4| 5| 6|   | 2| 5|   |32|77|
              | 3| 6|
 \endverbatim
 *
 * @param[in]	a matrix with elements to mul
 * @param[in]	b matrix with elements to mul
 * @param[out]	c result matrix
 * @param[in]	i number of rows of matrix a
 * @param[in]	j number of cols of matrix a and number of rows of matrix b
 * @param[in]	k number of cols of the result matrix
 *
 */
void mulmatrix_float_sse2(float **a, float **b, float **c, int i, int j, int k)
{
	int row = 0, col = 0;
	float **t = create_matrix_float(k, j);

	transpose_matrix_float_sse2(b, t, j, k);

	for(row = 0; row < i; row++)
	{
		for(col = 0; col < k; col++)
		{
			c[row][col] = dotProduct_float_unrolled_sse2(a[row], t[col], j);
		}
	}

	destroy_matrix_float(&t, k);
}

/**
 * Calculate the mul of two matrices of doubles.
 * Classic algorithm.
 *
 * Expression:
 \verbatim
  c[i][k] = (a[i][0] * b[0][k]) + (a[i][1] * b[1][k]) + ... + (a[i][j] * b[j][k])
 \endverbatim
 *
 * Example:
 \verbatim
  A            B         C
  | 1| 2| 3| * | 1| 4| = |14|32|
  | 4| 5| 6|   | 2| 5|   |32|77|
               | 3| 6|
 \endverbatim
 *
 * @param[in]	a matrix with elements to mul
 * @param[in]	b matrix with elements to mul
 * @param[out]	c result matrix
 * @param[in]	i number of rows of the result matrix
 * @param[in]	j number of cols of matrix a and number of rows of matrix b
 * @param[in]	k number of cols of the result matrix
 *
 */
void mulmatrix_double(double **a, double **b, double **c, int i, int j, int k)
{
	int row = 0, col = 0, n = 0;
	double sum = 0.0;

	for(row = 0; row < i; row++)
	{
		for(col = 0; col < k; col++)
		{
			sum = 0.0;
			for(n = 0; n < j; n++)
			{
				sum += a[row][n] * b[n][col];
			}
			c[row][col] = sum;
		}
	}
}

/**
 * Calculate the mul of two matrices of doubles.
 * Algorithm uses SSE2 instructions.
 *
 * Expression:
 \verbatim
  c[i][k] = (a[i][0] * b[0][k]) + (a[i][1] * b[1][k]) + ... + (a[i][j] * b[j][k])
 \endverbatim
 *
 * Example:
 \verbatim
  A            B         C
  | 1| 2| 3| * | 1| 4| = |14|32|
  | 4| 5| 6|   | 2| 5|   |32|77|
               | 3| 6|
 \endverbatim
 *
 * @param[in]	a matrix with elements to mul
 * @param[in]	b matrix with elements to mul
 * @param[out]	c result matrix
 * @param[in]	i number of rows of the result matrix
 * @param[in]	j number of cols of matrix a and number of rows of matrix b
 * @param[in]	k number of cols of the result matrix
 *
 */
void mulmatrix_double_sse2(double **a, double **b, double **c, int i, int j, int k)
{
	int row = 0, col = 0;
	double **t = create_matrix_double(k, j);

	transpose_matrix_double_sse2(b, t, j, k);

	for(row = 0; row < i; row++)
	{
		for(col = 0; col < k; col++)
		{
			c[row][col] = dotProduct_double_unrolled_sse2(a[row], t[col], j);
		}
	}

	destroy_matrix_double(&t, k);
}

/**
 * Returns the max element in the array of floats
 * Classic algorithm.
 *
 * Expression:
 \verbatim
  rv = max(a)
 \endverbatim
 *
 * Example:
 \verbatim
  A                      RV
  | 1| 2| 3| 4| 5| 6| => 6
 \endverbatim
 *
 * @param[in]	a matrix with elements to compare
 * @param[in]	size size of the array
 * @return	max element in the array
 *
 */
float maxelem_float(float *a, int size)
{
	float rv = a[0];

	for(int i=0; i<size; i++)
		if( a[i] > rv )
			rv = a[i];

	return rv;
}

/**
 * Returns the max element in the array of floats
 * Algorithm uses SSE2 instructions.
 *
 * Expression:
 \verbatim
  rv = max(a)
 \endverbatim
 *
 * Example:
 \verbatim
  A                      RV
  | 1| 2| 3| 4| 5| 6| => 6
 \endverbatim
 *
 * @param[in]	a matrix with elements to compare
 * @param[in]	size size of the array
 * @return	max element in the array
 *
 */
float maxelem_float_sse2(float *a, int size)
{
	int i = 0;
	float rv = 0.0;
	int length = (size / 4) * 4;
       
	if(size > 7)
	{
		float __attribute__ ((aligned(16))) b[4] = {a[0], a[1], a[2], a[3]};

		__asm__ volatile
		("movdqa %0,%%xmm0" : :"m" (b[0]));

		for(i = 4; i < length; i+=4)
		{
			__asm__ volatile
                	("maxps %0,%%xmm0" : :"m" (a[i]));
             	}
		
		__asm__ volatile
        	("movdqa %%xmm0,%0 " :"=m" (b[0]):);

		rv = b[0];

		if(rv < b[1])
			rv = b[1];

		if(rv < b[2])
			rv = b[2];

		if(rv < b[3])
			rv = b[3];
	}
	else
	{
		rv = a[0];
		length = 1;
	}

	for(i = length; i < size; i++)
	{
		if(rv < a[i])
			rv = a[i];
	}

	return rv;
}

/**
 * Returns the max element in the array of doubles
 * Classic algorithm.
 *
 * Expression:
 \verbatim
  rv = max(a)
 \endverbatim
 *
 * Example:
 \verbatim
  A                      RV
  | 1| 2| 3| 4| 5| 6| => 6
 \endverbatim
 *
 * @param[in]	a matrix with elements to compare
 * @param[in]	size size of the array
 * @return	max element in the array
 *
 */
double maxelem_double(double *a, int size)
{
	double rv = a[0];

	for(int i=0; i<size; i++)
		if( a[i] > rv )
			rv = a[i];

	return rv;
}

/**
 * Returns the max element in the array of doubles
 * Algorithm uses SSE2 instructions.
 *
 * Expression:
 \verbatim
  rv = max(a)
 \endverbatim
 *
 * Example:
 \verbatim
  A                      RV
  | 1| 2| 3| 4| 5| 6| => 6
 \endverbatim
 *
 * @param[in]	a matrix with elements to compare
 * @param[in]	size size of the array
 * @return	max element in the array
 *
 */
double maxelem_double_sse2(double *a, int size)
{
	int i = 0;
	double rv = 0.0;
	int length = (size / 4) * 4;
       
	if(size > 3)
	{
		double __attribute__ ((aligned(16))) b[2] = {a[0], a[1]};

		__asm__ volatile
		("movdqa %0,%%xmm0" : :"m" (b[0]));

		for(i = 2; i < length; i+=2)
		{
			__asm__ volatile
                	("maxpd %0,%%xmm0" : :"m" (a[i]));
             	}
		
		__asm__ volatile
        	("movdqa %%xmm0,%0 " :"=m" (b[0]):);

		rv = b[0];

		if(rv < b[1])
			rv = b[1];
	}
	else
	{
		rv = a[0];
		length = 1;
	}

	for(i = length; i < size; i++)
	{
		if(rv < a[i])
			rv = a[i];
	}

	return rv;
}

/**
 * Returns the min element in the array of floats
 * Classic algorithm.
 *
 * Expression:
 \verbatim
  rv = min(a)
 \endverbatim
 *
 * Example:
 \verbatim
  A                      RV
  | 1| 2| 3| 4| 5| 6| => 1
 \endverbatim
 *
 * @param[in]	a matrix with elements to compare
 * @param[in]	size size of the array
 * @return	min element in the array
 *
 */
float minelem_float(float *a, int size)
{
	float rv = a[0];

	for(int i=0; i<size; i++)
		if( a[i] < rv )
			rv = a[i];

	return rv;
}

/**
 * Returns the min element in the array of floats
 * Algorithm uses SSE2 instructions.
 *
 * Expression:
 \verbatim
  rv = min(a)
 \endverbatim
 *
 * Example:
 \verbatim
  A                      RV
  | 1| 2| 3| 4| 5| 6| => 1
 \endverbatim
 *
 * @param[in]	a matrix with elements to compare
 * @param[in]	size size of the array
 * @return	min element in the array
 *
 */
float minelem_float_sse2(float *a, int size)
{
	int i = 0;
	float rv = 0.0;
	int length = (size / 4) * 4;
       
	if(size > 7)
	{
		float __attribute__ ((aligned(16))) b[4] = {a[0], a[1], a[2], a[3]};

		__asm__ volatile
		("movdqa %0,%%xmm0" : :"m" (b[0]));

		for(i = 4; i < length; i+=4)
		{
			__asm__ volatile
                	("minps      %0,%%xmm0" : :"m" (a[i]));
             	}
		
		__asm__ volatile
        	("movdqa %%xmm0,%0 " :"=m" (b[0]):);

		rv = b[0];

		if(rv > b[1])
			rv = b[1];

		if(rv > b[2])
			rv = b[2];

		if(rv > b[3])
			rv = b[3];
	}
	else
	{
		rv = a[0];
		length = 1;
	}

	for(i = length; i < size; i++)
	{
		if(rv > a[i])
			rv = a[i];
	}

	return rv;
}

/**
 * Returns the min element in the array of doubles
 * Classic algorithm.
 *
 * Expression:
 \verbatim
  rv = min(a)
 \endverbatim
 *
 * Example:
 \verbatim
  A                      RV
  | 1| 2| 3| 4| 5| 6| => 1
 \endverbatim 
 *
 * @param[in]	a matrix with elements to compare
 * @param[in]	size size of the array
 * @return	min element in the array
 *
 */

double minelem_double(double *a, int size)
{
	double rv = a[0];

	for(int i=0; i<size; i++)
		if( a[i] < rv )
			rv = a[i];

	return rv;
}

/**
 * Returns the min element in the array of doubles
 * Algorithm uses SSE2 instructions.
 *
 * Expression:
 \verbatim
  rv = min(a)
 \endverbatim
 *
 * Example:
 \verbatim
  A                      RV
  | 1| 2| 3| 4| 5| 6| => 1
 \endverbatim
 *
 * @param[in]	a matrix with elements to compare
 * @param[in]	size size of the array
 * @return	min element in the array
 *
 */
double minelem_double_sse2(double *a, int size)
{
	int i = 0;
	float rv = 0.0;
	int length = (size / 2) * 2;
       
	if(size > 3)
	{
		double __attribute__ ((aligned(16))) b[4] = {a[0], a[1]};

		__asm__ volatile
		("movdqa %0,%%xmm0" : :"m" (b[0]));

		for(i = 2; i < length; i+=2)
		{
			__asm__ volatile
                	("minpd      %0,%%xmm0" : :"m" (a[i]));
             	}
		
		__asm__ volatile
        	("movdqa %%xmm0,%0 " :"=m" (b[0]):);

		rv = b[0];

		if(rv > b[1])
			rv = b[1];
	}
	else
	{
		rv = a[0];
		length = 1;
	}

	for(i = length; i < size; i++)
	{
		if(rv > a[i])
			rv = a[i];
	}

	return rv;
}

/**
 * Compares two arrays of chars, using classic algorithm.
 * This function compares two arrays of chars
 * and returns an array with the result for each two chars.
 * If the two compared chars are different then the result
 * is 0x00, otherwise is 0xff.
 *
 * Example:
 \verbatim
  A                     B		  RV
  | 1| 2| 3| 4| 5| ? | 1| 4| 3| 2| 6| => | 0xff| 0x00| 0xff| 0x00| 0x00|
 \endverbatim
 *
 * @param[in]	a first array
 * @param[in]	b second array
 * @param[out]  c result array
 * @param[in]  size size of the arrays
 *
 */
void cmp_equal_char(char *a, char *b, char *c, int size)
{
	for(int i=0; i<size; i++)
		if( a[i] == b[i] )
			c[i] = 0xff;
		else
			c[i] = 0x00;
}

/**
 * Compares two arrays of chars, using sse2 algorithm.
 * This function compares two arrays of chars
 * and returns an array with the result for each two chars.
 * If the two compared chars are different then the result
 * is 0x00, otherwise is 0xff.
 *
 * Example:
 \verbatim
  A                     B		  RV
  | 1| 2| 3| 4| 5| ? | 1| 4| 3| 2| 6| => | 0xff| 0x00| 0xff| 0x00| 0x00|
 \endverbatim
 *
 * @param[in]	a first array
 * @param[in]	b second array
 * @param[out]  c result array
 * @param[in]  size size of the arrays
 *
 */
void cmp_equal_char_sse2(char *a, char *b, char *c, int size)
{
	int i = 0;

	for (i = 0; i < (size/16)*16; i += 16)
	{
		__asm__ volatile
                ( // instruction             comment                  
                "\n\t movdqa     %1,%%xmm0         \t#"
                "\n\t movdqa     %2,%%xmm1         \t#"
                "\n\t pcmpeqb    %%xmm0,%%xmm1     \t#"
                "\n\t movdqa     %%xmm1,%0         \t#"
		: "=m" (c[i])      // %0
		: "m"  (a[i]),     // %1 
		  "m"  (b[i])      // %2
		);
		
	}
		
	for(i = (size/16)*16; i < size; i++)
		c[i] = ( a[i] == b[i] )?0xff:0x00;

}

/**
 * Compares two arrays of ints, using classic algorithm.
 * This function compares two arrays of ints
 * and returns an array with the result for each two ints.
 * If the two compared ints are different then the result
 * is 0x00, otherwise is 0xff.
 *
 * Example:
 \verbatim
  A                     B		  RV
  | 1| 2| 3| 4| 5| ? | 1| 4| 3| 2| 6| => | 0xff| 0x00| 0xff| 0x00| 0x00|
 \endverbatim
 *
 * @param[in]	a first array
 * @param[in]	b second array
 * @param[out]  c result array
 * @param[in]  size size of the arrays
 *
 */
void cmp_equal_int(int *a, int *b, int *c, int size)
{
	for(int i=0; i<size; i++)
		if( a[i] == b[i] )
			c[i] = 0xffffffff;
		else
			c[i] = 0x00000000;
}

/**
 * Compares two arrays of ints, using sse2 algorithm.
 * This function compares two arrays of ints
 * and returns an array with the result for each two ints.
 * If the two compared ints are different then the result
 * is 0x00, otherwise is 0xff.
 *
 * Example:
 \verbatim
  A                     B		  RV
  | 1| 2| 3| 4| 5| ? | 1| 4| 3| 2| 6| => | 0xff| 0x00| 0xff| 0x00| 0x00|
 \endverbatim
 *
 * @param[in]	a first array
 * @param[in]	b second array
 * @param[out]  c result array
 * @param[in]  size size of the arrays
 *
 */
void cmp_equal_int_sse2(int *a, int *b, int *c, int size)
{
	int i = 0;

	for (i = 0; i < (size/4)*4; i += 4)
	{
		__asm__ volatile
                ( // instruction             comment                  
                "\n\t movdqa     %1,%%xmm0         \t#"
                "\n\t movdqa     %2,%%xmm1         \t#"
                "\n\t pcmpeqd      %%xmm0,%%xmm1     \t#"
                "\n\t movdqa     %%xmm1,%0         \t#"
		: "=m" (c[i])      // %0
		: "m"  (a[i]),     // %1 
		  "m"  (b[i])      // %2
		);
		
	}
		
	for(i = (size/4)*4; i < size; i++)
		c[i] = ( a[i] == b[i] )?0xffffffff:0x00000000;

}

/**
 * Compares two arrays of floats, using classic algorithm.
 * This function compares two arrays of floats
 * and returns an array with the result for each two floats.
 * If the two compared floats are different then the result
 * is 0x00, otherwise is 0xff.
 *
 * Example:
 \verbatim
  A                     B		  RV
  | 1| 2| 3| 4| 5| ? | 1| 4| 3| 2| 6| => | 0xff| 0x00| 0xff| 0x00| 0x00|
 \endverbatim
 *
 * @param[in]	a first array
 * @param[in]	b second array
 * @param[out]  c result array
 * @param[in]  size size of the arrays
 *
 */
void cmp_equal_float(float *a, float *b, float *c, int size)
{
	for(int i=0; i<size; i++)
		if( a[i] == b[i] )
			*(unsigned int*)&c[i] = 0xffffffff;
		else
			c[i] = 0;
}

/**
 * Compares two arrays of floats, using sse2 algorithm.
 * This function compares two arrays of floats
 * and returns an array with the result for each two floats.
 * If the two compared floats are different then the result
 * is 0x00, otherwise is 0xff.
 *
 * Example:
 \verbatim
  A                     B		  RV
  | 1| 2| 3| 4| 5| ? | 1| 4| 3| 2| 6| => | 0xff| 0x00| 0xff| 0x00| 0x00|
 \endverbatim
 *
 * @param[in]	a first array
 * @param[in]	b second array
 * @param[out]  c result array
 * @param[in]  size size of the arrays
 *
 */
void cmp_equal_float_sse2(float *a, float *b, float *c, int size)
{
	int i = 0;

	for (i = 0; i < (size/4)*4; i += 4)
	{
		__asm__ volatile
                ( // instruction             comment                  
                "\n\t movdqa     %1,%%xmm0         \t#"
                "\n\t movdqa     %2,%%xmm1         \t#"
                "\n\t cmpeqps      %%xmm0,%%xmm1   \t#"
                "\n\t movdqa     %%xmm1,%0         \t#"
		: "=m" (c[i])      // %0
		: "m"  (a[i]),     // %1 
		  "m"  (b[i])      // %2
		);
		
	}
		
	for(i = (size/4)*4; i < size; i++)
		*(unsigned int*)&c[i] = ( a[i] == b[i] )?0xffffffff:0x00000000;

}

/**
 * Compares two arrays of doubles, using classic algorithm.
 * This function compares two arrays of doubles
 * and returns an array with the result for each two doubles.
 * If the two compared doubles are different then the result
 * is 0x00, otherwise is 0xff.
 *
 * Example:
 \verbatim
  A                     B		  RV
  | 1| 2| 3| 4| 5| ? | 1| 4| 3| 2| 6| => | 0xff| 0x00| 0xff| 0x00| 0x00|
 \endverbatim
 *
 * @param[in]	a first array
 * @param[in]	b second array
 * @param[out]  c result array
 * @param[in]  size size of the arrays
 *
 */
void cmp_equal_double(double *a, double *b, double *c, int size)
{
	for(int i=0; i<size; i++)
		if( a[i] == b[i] )
			*(unsigned long long*)&c[i] = ~0x0ULL;
		else
			c[i] = 0x00;
}

/**
 * Compares two arrays of doubles, using sse2 algorithm.
 * This function compares two arrays of doubles
 * and returns an array with the result for each two doubles.
 * If the two compared doubles are different then the result
 * is 0x00, otherwise is 0xff.
 *
 * Example:
 \verbatim
  A                     B		  RV
  | 1| 2| 3| 4| 5| ? | 1| 4| 3| 2| 6| => | 0xff| 0x00| 0xff| 0x00| 0x00|
 \endverbatim
 *
 * @param[in]	a first array
 * @param[in]	b second array
 * @param[out]  c result array
 * @param[in]  size size of the arrays
 *
 */
void cmp_equal_double_sse2(double *a, double *b, double *c, int size)
{
	int i = 0;

	for (i = 0; i < (size/2)*2; i += 2)
	{
		__asm__ volatile
                ( // instruction             comment                  
                "\n\t movdqa     %1,%%xmm0         \t#"
                "\n\t movdqa     %2,%%xmm1         \t#"
                "\n\t cmpeqpd      %%xmm0,%%xmm1   \t#"
                "\n\t movdqa     %%xmm1,%0         \t#"
		: "=m" (c[i])      // %0
		: "m"  (a[i]),     // %1 
		  "m"  (b[i])      // %2
		);
		
	}
		
	for(i = (size/2)*2; i < size; i++)
		*(unsigned long long*)&c[i] = ( a[i] == b[i] )?~0ULL:0x00;

}

/**
 * Compares two arrays of chars, using classic algorithm.
 * This function compares two arrays of chars
 * and returns an array with the result for each two chars.
 * For each element, if the first is greater than the second returns
 * 0xff, otherwise 0x00.
 *
 * Example:
 \verbatim
  A                     B		  RV
  | 2| 1| 3| 4| 6| > | 1| 4| 3| 2| 5| => | 0xff| 0x00| 0x00| 0x00| 0xff|
 \endverbatim
 *
 * @param[in]	a first array
 * @param[in]	b second array
 * @param[out]  c result array
 * @param[in]  size size of the arrays
 *
 */
void cmp_greater_char(char *a, char *b, char *c, int size)
{
	for(int i=0; i<size; i++)
		if( a[i] > b[i] )
			c[i] = 0xff;
		else
			c[i] = 0x00;
}

/**
 * Compares two arrays of chars, using sse2 algorithm.
 * This function compares two arrays of chars
 * and returns an array with the result for each two chars.
 * For each element, if the first is greater than the second returns
 * 0xff, otherwise 0x00.
 *
 * Example:
 \verbatim
  A                     B		  RV
  | 2| 1| 3| 4| 6| > | 1| 4| 3| 2| 5| => | 0xff| 0x00| 0x00| 0x00| 0xff|
 \endverbatim
 *
 * @param[in]	a first array
 * @param[in]	b second array
 * @param[out]  c result array
 * @param[in]  size size of the arrays
 *
 */
void cmp_greater_char_sse2(char *a, char *b, char *c, int size)
{
	int i = 0;

	for (i = 0; i < (size/16)*16; i += 16)
	{
		__asm__ volatile
                ( // instruction             comment                  
                "\n\t movdqa     %1,%%xmm0         \t#"
                "\n\t movdqa     %2,%%xmm1         \t#"
                "\n\t pcmpgtb    %%xmm1,%%xmm0     \t#"
                "\n\t movdqa     %%xmm0,%0         \t#"
		: "=m" (c[i])      // %0
		: "m"  (a[i]),     // %1 
		  "m"  (b[i])      // %2
		);
		
	}
		
	for(i = (size/16)*16; i < size; i++)
		c[i] = ( a[i] > b[i] )?0xff:0x00;

}

/**
 * Compares two arrays of ints, using classic algorithm.
 * This function compares two arrays of ints
 * and returns an array with the result for each two ints.
 * For each element, if the first is greater than the second returns
 * 0xff, otherwise 0x00.
 *
 * Example:
 \verbatim
  A                     B		  RV
  | 2| 1| 3| 4| 6| > | 1| 4| 3| 2| 5| => | 0xff| 0x00| 0x00| 0x00| 0xff|
 \endverbatim
 *
 * @param[in]	a first array
 * @param[in]	b second array
 * @param[out]  c result array
 * @param[in]  size size of the arrays
 *
 */
void cmp_greater_int(int *a, int *b, int *c, int size)
{
	for(int i=0; i<size; i++)
		if( a[i] > b[i] )
			c[i] = 0xffffffff;
		else
			c[i] = 0x00000000;
}

/**
 * Compares two arrays of ints, using sse2 algorithm.
 * This function compares two arrays of ints
 * and returns an array with the result for each two ints.
 * For each element, if the first is greater than the second returns
 * 0xff, otherwise 0x00.
 *
 * Example:
 \verbatim
  A                     B		  RV
  | 2| 1| 3| 4| 6| > | 1| 4| 3| 2| 5| => | 0xff| 0x00| 0x00| 0x00| 0xff|
 \endverbatim
 *
 * @param[in]	a first array
 * @param[in]	b second array
 * @param[out]  c result array
 * @param[in]  size size of the arrays
 *
 */
void cmp_greater_int_sse2(int *a, int *b, int *c, int size)
{
	int i = 0;

	for (i = 0; i < (size/4)*4; i += 4)
	{
		__asm__ volatile
                ( // instruction             comment                  
                "\n\t movdqa     %1,%%xmm0         \t#"
                "\n\t movdqa     %2,%%xmm1         \t#"
                "\n\t pcmpgtd      %%xmm1,%%xmm0     \t#"
                "\n\t movdqa     %%xmm0,%0         \t#"
		: "=m" (c[i])      // %0
		: "m"  (a[i]),     // %1 
		  "m"  (b[i])      // %2
		);
		
	}
		
	for(i = (size/4)*4; i < size; i++)
		c[i] = ( a[i] > b[i] )?0xffffffff:0x00000000;

}

/**
 * Compares two arrays of floats, using classic algorithm.
 * This function compares two arrays of floats
 * and returns an array with the result for each two floats.
 * For each element, if the first is greater than the second returns
 * 0xff, otherwise 0x00.
 *
 * Example:
 \verbatim
  A                     B		  RV
  | 2| 1| 3| 4| 6| > | 1| 4| 3| 2| 5| => | 0xff| 0x00| 0x00| 0x00| 0xff|
 \endverbatim
 *
 * @param[in]	a first array
 * @param[in]	b second array
 * @param[out]  c result array
 * @param[in]  size size of the arrays
 *
 */
void cmp_greater_float(float *a, float *b, float *c, int size)
{
	for(int i=0; i<size; i++)
		if( a[i] > b[i] )
			*(unsigned int*)&c[i] = 0xffffffff;
		else
			c[i] = 0;
}

/**
 * Compares two arrays of floats, using sse2 algorithm.
 * This function compares two arrays of floats
 * and returns an array with the result for each two floats.
 * For each element, if the first is greater than the second returns
 * 0xff, otherwise 0x00.
 *
 * Example:
 \verbatim
  A                     B		  RV
  | 2| 1| 3| 4| 6| > | 1| 4| 3| 2| 5| => | 0xff| 0x00| 0x00| 0x00| 0xff|
 \endverbatim
 *
 * @param[in]	a first array
 * @param[in]	b second array
 * @param[out]  c result array
 * @param[in]  size size of the arrays
 *
 */
void cmp_greater_float_sse2(float *a, float *b, float *c, int size)
{
	int i = 0;

	for (i = 0; i < (size/4)*4; i += 4)
	{
		__asm__ volatile
                ( // instruction             comment                  
                "\n\t movdqa     %1,%%xmm0         \t#"
                "\n\t movdqa     %2,%%xmm1         \t#"
                "\n\t cmpltps      %%xmm0,%%xmm1   \t#"
                "\n\t movdqa     %%xmm1,%0         \t#"
		: "=m" (c[i])      // %0
		: "m"  (a[i]),     // %1 
		  "m"  (b[i])      // %2
		);
		
	}
		
	for(i = (size/4)*4; i < size; i++)
		*(unsigned int*)&c[i] = ( a[i] > b[i] )?0xffffffff:0x00000000;

}

/**
 * Compares two arrays of doubles, using classic algorithm.
 * This function compares two arrays of doubles
 * and returns an array with the result for each two doubles.
 * For each element, if the first is greater than the second returns
 * 0xff, otherwise 0x00.
 *
 * Example:
 \verbatim
  A                     B		  RV
  | 2| 1| 3| 4| 6| > | 1| 4| 3| 2| 5| => | 0xff| 0x00| 0x00| 0x00| 0xff|
 \endverbatim
 *
 * @param[in]	a first array
 * @param[in]	b second array
 * @param[out]  c result array
 * @param[in]  size size of the arrays
 *
 */
void cmp_greater_double(double *a, double *b, double *c, int size)
{
	for(int i=0; i<size; i++)
		if( a[i] > b[i] )
			*(unsigned long long*)&c[i] = ~0x0ULL;
		else
			c[i] = 0x00;
}

/**
 * Compares two arrays of doubles, using sse2 algorithm.
 * This function compares two arrays of doubles
 * and returns an array with the result for each two doubles.
 * For each element, if the first is greater than the second returns
 * 0xff, otherwise 0x00.
 *
 * Example:
 \verbatim
  A                     B		  RV
  | 2| 1| 3| 4| 6| > | 1| 4| 3| 2| 5| => | 0xff| 0x00| 0x00| 0x00| 0xff|
 \endverbatim
 *
 * @param[in]	a first array
 * @param[in]	b second array
 * @param[out]  c result array
 * @param[in]  size size of the arrays
 *
 */
void cmp_greater_double_sse2(double *a, double *b, double *c, int size)
{
	int i = 0;

	for (i = 0; i < (size/2)*2; i += 2)
	{
		__asm__ volatile
                ( // instruction             comment                  
                "\n\t movdqa     %1,%%xmm0         \t#"
                "\n\t movdqa     %2,%%xmm1         \t#"
                "\n\t cmpltpd      %%xmm0,%%xmm1   \t#"
                "\n\t movdqa     %%xmm1,%0         \t#"
		: "=m" (c[i])      // %0
		: "m"  (a[i]),     // %1 
		  "m"  (b[i])      // %2
		);
		
	}
		
	for(i = (size/2)*2; i < size; i++)
		*(unsigned long long*)&c[i] = ( a[i] > b[i] )?~0ULL:0x00;

}

/**
 * Compares two arrays of chars, using sse2 unrolled algorithm.
 * This function compares two arrays of chars
 * and returns an array with the result for each two chars.
 * For each element, if the first is greater than the second returns
 * 0xff, otherwise 0x00.
 *
 * Example:
 \verbatim
  A                     B		  RV
  | 2| 1| 3| 4| 6| > | 1| 4| 3| 2| 5| => | 0xff| 0x00| 0x00| 0x00| 0xff|
 \endverbatim
 *
 * @param[in]	a first array
 * @param[in]	b second array
 * @param[out]  c result array
 * @param[in]  size size of the arrays
 *
 */
void cmp_greater_unrolled_char_sse2(char *a, char *b, char *c, int size)
{
	int i = 0,
            length = (size/16)*16,
	    length2 = (size/32)*32,
	    length4 = (size/64)*64;

	for(; i < length4; i+=64)
	{
		__asm__ volatile
                ( // instruction             comment
                "\n\t movdqa     %4,%%xmm0         \t#"
		"\n\t movdqa     %5,%%xmm1         \t#"
		"\n\t movdqa     %6,%%xmm2        \t#"
		"\n\t movdqa     %7,%%xmm3        \t#"
		"\n\t movdqa     %8,%%xmm4        \t#"
		"\n\t movdqa     %9,%%xmm5        \t#"
		"\n\t movdqa     %10,%%xmm6        \t#"
		"\n\t movdqa     %11,%%xmm7        \t#"
                "\n\t pcmpgtb    %%xmm1,%%xmm0     \t#"
                "\n\t pcmpgtb    %%xmm3,%%xmm2     \t#"
                "\n\t pcmpgtb    %%xmm5,%%xmm4     \t#"
                "\n\t pcmpgtb    %%xmm7,%%xmm6     \t#"
                "\n\t movdqa     %%xmm0,%0         \t#"
		"\n\t movdqa     %%xmm2,%1         \t#"
		"\n\t movdqa     %%xmm4,%2         \t#"
		"\n\t movdqa     %%xmm6,%3         \t#"
		: "=m" (c[i]),     // %0
		  "=m" (c[i+16]),  // %1
		  "=m" (c[i+32]),  // %2
		  "=m" (c[i+48])  // %3
		: "m"  (a[i]),     // %4
		  "m"  (b[i]),     // %5
		  "m"  (a[i+16]),  // %6
		  "m"  (b[i+16]),  // %7
		  "m"  (a[i+32]),  // %8
		  "m"  (b[i+32]),  // %9
		  "m"  (a[i+48]),  // %10
		  "m"  (b[i+48])  // %11
		);
	}

	for(; i < length2; i+=32)
	{
		__asm__ volatile
                ( // instruction             comment
                "\n\t movdqa     %2,%%xmm0         \t#"
		"\n\t movdqa     %3,%%xmm1         \t#"
		"\n\t movdqa     %4,%%xmm2         \t#"
		"\n\t movdqa     %5,%%xmm3         \t#"
                "\n\t pcmpgtb    %%xmm1,%%xmm0     \t#"
                "\n\t pcmpgtb    %%xmm3,%%xmm2     \t#"
	        "\n\t movdqa     %%xmm0,%0         \t#"
		"\n\t movdqa     %%xmm2,%1         \t#"
		: "=m" (c[i]),     // %0
		  "=m" (c[i+16])  // %1
		: "m"  (a[i]),     // %2
		  "m"  (b[i]),     // %3
		  "m"  (a[i+16]),  // %4
		  "m"  (b[i+16])   // %5
		);
	}


	for(; i < length; i+=16)
	{
		__asm__ volatile
                ( // instruction             comment
                "\n\t movdqa     %1,%%xmm0         \t#"
		"\n\t movdqa     %2,%%xmm1         \t#"
                "\n\t pcmpgtb    %%xmm1,%%xmm0     \t#"
                "\n\t movdqa     %%xmm0,%0         \t#"
		: "=m" (c[i])     // %0
		: "m"  (a[i]),     // %1
		  "m"  (b[i])      // %2
		);
	}

	for(; i < size; i++)
		c[i] = ( a[i] > b[i] )?0xff:0x00;
}

/**
 * Compares two arrays of chars, using classic algorithm.
 * This function compares two arrays of chars
 * and returns an array with the result for each two chars.
 * For each element, if the first is less than the second returns
 * 0xff, otherwise 0x00.
 *
 * Example:
 \verbatim
  A                     B		  RV
  | 2| 1| 3| 4| 6| < | 1| 4| 3| 2| 5| => | 0xff| 0x00| 0x00| 0x00| 0xff|
 \endverbatim
 *
 * @param[in]	a first array
 * @param[in]	b second array
 * @param[out]  c result array
 * @param[in]  size size of the arrays
 *
 */
void cmp_less_char(char *a, char *b, char *c, int size)
{
	for(int i=0; i<size; i++)
		if( a[i] < b[i] )
			c[i] = 0xff;
		else
			c[i] = 0x00;
}

/**
 * Compares two arrays of chars, using sse2 algorithm.
 * This function compares two arrays of chars
 * and returns an array with the result for each two chars.
 * For each element, if the first is less than the second returns
 * 0xff, otherwise 0x00.
 *
 * Example:
 \verbatim
  A                     B		  RV
  | 2| 1| 3| 4| 6| < | 1| 4| 3| 2| 5| => | 0xff| 0x00| 0x00| 0x00| 0xff|
 \endverbatim
 *
 * @param[in]	a first array
 * @param[in]	b second array
 * @param[out]  c result array
 * @param[in]  size size of the arrays
 *
 */
void cmp_less_char_sse2(char *a, char *b, char *c, int size)
{
	int i = 0;

	for (i = 0; i < (size/16)*16; i += 16)
	{
		__asm__ volatile
                ( // instruction             comment                  
                "\n\t movdqa     %1,%%xmm0         \t#"
                "\n\t movdqa     %2,%%xmm1         \t#"
                "\n\t pcmpgtb    %%xmm1,%%xmm0     \t#"
                "\n\t movdqa     %%xmm0,%0         \t#"
		: "=m" (c[i])      // %0
		: "m"  (b[i]),     // %1 
		  "m"  (a[i])      // %2
		);
		
	}
		
	for(i = (size/16)*16; i < size; i++)
		c[i] = ( a[i] < b[i] )?0xff:0x00;

}

/**
 * Compares two arrays of ints, using classic algorithm.
 * This function compares two arrays of ints
 * and returns an array with the result for each two ints.
 * For each element, if the first is less than the second returns
 * 0xff, otherwise 0x00.
 *
 * Example:
 \verbatim
  A                     B		  RV
  | 2| 1| 3| 4| 6| < | 1| 4| 3| 2| 5| => | 0xff| 0x00| 0x00| 0x00| 0xff|
 \endverbatim
 *
 * @param[in]	a first array
 * @param[in]	b second array
 * @param[out]  c result array
 * @param[in]  size size of the arrays
 *
 */
void cmp_less_int(int *a, int *b, int *c, int size)
{
	for(int i=0; i<size; i++)
		if( a[i] < b[i] )
			c[i] = 0xffffffff;
		else
			c[i] = 0x00000000;
}

/**
 * Compares two arrays of ints, using sse2 algorithm.
 * This function compares two arrays of ints
 * and returns an array with the result for each two ints.
 * For each element, if the first is less than the second returns
 * 0xff, otherwise 0x00.
 *
 * Example:
 \verbatim
  A                     B		  RV
  | 2| 1| 3| 4| 6| < | 1| 4| 3| 2| 5| => | 0xff| 0x00| 0x00| 0x00| 0xff|
 \endverbatim
 *
 * @param[in]	a first array
 * @param[in]	b second array
 * @param[out]  c result array
 * @param[in]  size size of the arrays
 *
 */
void cmp_less_int_sse2(int *a, int *b, int *c, int size)
{
	int i = 0;

	for (i = 0; i < (size/4)*4; i += 4)
	{
		__asm__ volatile
                ( // instruction             comment                  
                "\n\t movdqa     %1,%%xmm0         \t#"
                "\n\t movdqa     %2,%%xmm1         \t#"
                "\n\t pcmpgtd      %%xmm1,%%xmm0     \t#"
                "\n\t movdqa     %%xmm0,%0         \t#"
		: "=m" (c[i])      // %0
		: "m"  (b[i]),     // %1 
		  "m"  (a[i])      // %2
		);
		
	}
		
	for(i = (size/4)*4; i < size; i++)
		c[i] = ( a[i] < b[i] )?0xffffffff:0x00000000;

}

/**
 * Compares two arrays of floats, using classic algorithm.
 * This function compares two arrays of floats
 * and returns an array with the result for each two floats.
 * For each element, if the first is less than the second returns
 * 0xff, otherwise 0x00.
 *
 * Example:
 \verbatim
  A                     B		  RV
  | 2| 1| 3| 4| 6| < | 1| 4| 3| 2| 5| => | 0xff| 0x00| 0x00| 0x00| 0xff|
 \endverbatim
 *
 * @param[in]	a first array
 * @param[in]	b second array
 * @param[out]  c result array
 * @param[in]  size size of the arrays
 *
 */
void cmp_less_float(float *a, float *b, float *c, int size)
{
	for(int i=0; i<size; i++)
		if( a[i] < b[i] )
			*(unsigned int*)&c[i] = 0xffffffff;
		else
			c[i] = 0;
}

/**
 * Compares two arrays of floats, using sse2 algorithm.
 * This function compares two arrays of floats
 * and returns an array with the result for each two floats.
 * For each element, if the first is less than the second returns
 * 0xff, otherwise 0x00.
 *
 * Example:
 \verbatim
  A                     B		  RV
  | 2| 1| 3| 4| 6| < | 1| 4| 3| 2| 5| => | 0xff| 0x00| 0x00| 0x00| 0xff|
 \endverbatim
 *
 * @param[in]	a first array
 * @param[in]	b second array
 * @param[out]  c result array
 * @param[in]  size size of the arrays
 *
 */
void cmp_less_float_sse2(float *a, float *b, float *c, int size)
{
	int i = 0;

	for (i = 0; i < (size/4)*4; i += 4)
	{
		__asm__ volatile
                ( // instruction             comment                  
                "\n\t movdqa     %1,%%xmm0         \t#"
                "\n\t movdqa     %2,%%xmm1         \t#"
                "\n\t cmpltps      %%xmm0,%%xmm1   \t#"
                "\n\t movdqa     %%xmm1,%0         \t#"
		: "=m" (c[i])      // %0
		: "m"  (b[i]),     // %1 
		  "m"  (a[i])      // %2
		);
		
	}
		
	for(i = (size/4)*4; i < size; i++)
		*(unsigned int*)&c[i] = ( a[i] < b[i] )?0xffffffff:0x00000000;

}

/**
 * Compares two arrays of doubles, using classic algorithm.
 * This function compares two arrays of doubles
 * and returns an array with the result for each two doubles.
 * For each element, if the first is less than the second returns
 * 0xff, otherwise 0x00.
 *
 * Example:
 \verbatim
  A                     B		  RV
  | 2| 1| 3| 4| 6| < | 1| 4| 3| 2| 5| => | 0xff| 0x00| 0x00| 0x00| 0xff|
 \endverbatim
 *
 * @param[in]	a first array
 * @param[in]	b second array
 * @param[out]  c result array
 * @param[in]  size size of the arrays
 *
 */
void cmp_less_double(double *a, double *b, double *c, int size)
{
	for(int i=0; i<size; i++)
		if( a[i] < b[i] )
			*(unsigned long long*)&c[i] = ~0x0ULL;
		else
			c[i] = 0x00;
}

/**
 * Compares two arrays of doubles, using sse2 algorithm.
 * This function compares two arrays of doubles
 * and returns an array with the result for each two doubles.
 * For each element, if the first is less than the second returns
 * 0xff, otherwise 0x00.
 *
 * Example:
 \verbatim
  A                     B		  RV
  | 2| 1| 3| 4| 6| < | 1| 4| 3| 2| 5| => | 0xff| 0x00| 0x00| 0x00| 0xff|
 \endverbatim
 *
 * @param[in]	a first array
 * @param[in]	b second array
 * @param[out]  c result array
 * @param[in]  size size of the arrays
 *
 */
void cmp_less_double_sse2(double *a, double *b, double *c, int size)
{
	int i = 0;

	for (i = 0; i < (size/2)*2; i += 2)
	{
		__asm__ volatile
                ( // instruction             comment                  
                "\n\t movdqa     %1,%%xmm0         \t#"
                "\n\t movdqa     %2,%%xmm1         \t#"
                "\n\t cmpltpd      %%xmm0,%%xmm1   \t#"
                "\n\t movdqa     %%xmm1,%0         \t#"
		: "=m" (c[i])      // %0
		: "m"  (b[i]),     // %1 
		  "m"  (a[i])      // %2
		);
		
	}
		
	for(i = (size/2)*2; i < size; i++)
		*(unsigned long long*)&c[i] = ( a[i] < b[i] )?~0ULL:0x00;

}

/**
 * Compares two arrays of chars, using sse2 unrolled algorithm.
 * This function compares two arrays of chars
 * and returns an array with the result for each two chars.
 * For each element, if the first is less than the second returns
 * 0xff, otherwise 0x00.
 *
 * Example:
 \verbatim
  A                     B		  RV
  | 2| 1| 3| 4| 6| < | 1| 4| 3| 2| 5| => | 0xff| 0x00| 0x00| 0x00| 0xff|
 \endverbatim
 *
 * @param[in]	a first array
 * @param[in]	b second array
 * @param[out]  c result array
 * @param[in]  size size of the arrays
 *
 */
void cmp_less_unrolled_char_sse2(char *a, char *b, char *c, int size)
{
	int i = 0,
            length = (size/16)*16,
	    length2 = (size/32)*32,
	    length4 = (size/64)*64;

	for(; i < length4; i+=64)
	{
		__asm__ volatile
                ( // instruction             comment
                "\n\t movdqa     %4,%%xmm0         \t#"
		"\n\t movdqa     %5,%%xmm1         \t#"
		"\n\t movdqa     %6,%%xmm2        \t#"
		"\n\t movdqa     %7,%%xmm3        \t#"
		"\n\t movdqa     %8,%%xmm4        \t#"
		"\n\t movdqa     %9,%%xmm5        \t#"
		"\n\t movdqa     %10,%%xmm6        \t#"
		"\n\t movdqa     %11,%%xmm7        \t#"
                "\n\t pcmpgtb    %%xmm1,%%xmm0     \t#"
                "\n\t pcmpgtb    %%xmm3,%%xmm2     \t#"
                "\n\t pcmpgtb    %%xmm5,%%xmm4     \t#"
                "\n\t pcmpgtb    %%xmm7,%%xmm6     \t#"
                "\n\t movdqa     %%xmm0,%0         \t#"
		"\n\t movdqa     %%xmm2,%1         \t#"
		"\n\t movdqa     %%xmm4,%2         \t#"
		"\n\t movdqa     %%xmm6,%3         \t#"
		: "=m" (c[i]),     // %0
		  "=m" (c[i+16]),  // %1
		  "=m" (c[i+32]),  // %2
		  "=m" (c[i+48])  // %3
		: "m"  (b[i]),     // %4
		  "m"  (a[i]),     // %5
		  "m"  (b[i+16]),  // %6
		  "m"  (a[i+16]),  // %7
		  "m"  (b[i+32]),  // %8
		  "m"  (a[i+32]),  // %9
		  "m"  (b[i+48]),  // %10
		  "m"  (a[i+48])  // %11
		);
	}

	for(; i < length2; i+=32)
	{
		__asm__ volatile
                ( // instruction             comment
                "\n\t movdqa     %2,%%xmm0         \t#"
		"\n\t movdqa     %3,%%xmm1         \t#"
		"\n\t movdqa     %4,%%xmm2         \t#"
		"\n\t movdqa     %5,%%xmm3         \t#"
                "\n\t pcmpgtb    %%xmm1,%%xmm0     \t#"
                "\n\t pcmpgtb    %%xmm3,%%xmm2     \t#"
	        "\n\t movdqa     %%xmm0,%0         \t#"
		"\n\t movdqa     %%xmm2,%1         \t#"
		: "=m" (c[i]),     // %0
		  "=m" (c[i+16])  // %1
		: "m"  (b[i]),     // %2
		  "m"  (a[i]),     // %3
		  "m"  (b[i+16]),  // %4
		  "m"  (a[i+16])   // %5
		);
	}


	for(; i < length; i+=16)
	{
		__asm__ volatile
                ( // instruction             comment
                "\n\t movdqa     %1,%%xmm0         \t#"
		"\n\t movdqa     %2,%%xmm1         \t#"
                "\n\t pcmpgtb    %%xmm1,%%xmm0     \t#"
                "\n\t movdqa     %%xmm0,%0         \t#"
		: "=m" (c[i])     // %0
		: "m"  (b[i]),     // %1
		  "m"  (a[i])      // %2
		);
	}

	for(; i < size; i++)
		c[i] = ( a[i] < b[i] )?0xff:0x00;
}

/**
 * Copy size bytes of memory from one pointer to another.
 * Only works with aligned pointers.
 * Algorithm uses SSE2 instructions.
 *
 * Expression:
 *
 \verbatim
  a[i] = b[i]
 \endverbatim
 *
 * Example:
 \verbatim
  A                      B
  | 1| 2| 3| 4| 5| 6| => | 1| 2| 3| 4| 5| 6|
 \endverbatim
 *
 * @param[in]	src source pointer
 * @param[out]	dst destination pointer
 * @param[in]	size size in bytes
 *
 */
void memcpy_sse2(void *dst, void *src, int size)
{
	int i = 0;

	char *a = (char *)src;
	char *b = (char *)dst;

	for(i = 0; i < (size/16)*16; i+=16)
	{
		__asm__ volatile
                ( // instruction             comment
                "\n\t movdqa     %1,%%xmm0         \t#"
                "\n\t movdqa     %%xmm0,%0         \t#"
		: "=m" (b[i])      // %0
		: "m"  (a[i])      // %1
		);
	}

	for(i = (size/16)*16; i < size; i++)
		b[i] = a[i];
}

/**
 * Copy size bytes of memory from one pointer to another.
 * Only works with aligned pointers.
 * Algorithm uses SSE2 instructions.
 *
 * Expression:
 *
 \verbatim
  a[i] = b[i]
 \endverbatim
 *
 * Example:
 \verbatim
  A                      B
  | 1| 2| 3| 4| 5| 6| => | 1| 2| 3| 4| 5| 6|
 \endverbatim
 *
 * @param[in]	src source pointer
 * @param[out]	dst destination pointer
 * @param[in]	size size in bytes
 *
 */
void memcpy_unrolled_sse2(void *dst, void *src, int size)
{
	int i = 0,
	    length = (size/16)*16,
	    length2 = (size/32)*32,
	    length4 = (size/64)*64,
	    length8 = (size/128)*128;

	char *a = (char *)src;
	char *b = (char *)dst;

	for(i = 0; i < length8; i+=128)
	{
		__asm__ volatile
                ( // instruction             comment
                "\n\t movdqa     %8,%%xmm0         \t#"
		"\n\t movdqa     %9,%%xmm1         \t#"
		"\n\t movdqa     %10,%%xmm2        \t#"
		"\n\t movdqa     %11,%%xmm3        \t#"
		"\n\t movdqa     %12,%%xmm4        \t#"
		"\n\t movdqa     %13,%%xmm5        \t#"
		"\n\t movdqa     %14,%%xmm6        \t#"
		"\n\t movdqa     %15,%%xmm7        \t#"
                "\n\t movdqa     %%xmm0,%0         \t#"
		"\n\t movdqa     %%xmm1,%1         \t#"
		"\n\t movdqa     %%xmm2,%2         \t#"
		"\n\t movdqa     %%xmm3,%3         \t#"
		"\n\t movdqa     %%xmm4,%4         \t#"
		"\n\t movdqa     %%xmm5,%5         \t#"
		"\n\t movdqa     %%xmm6,%6         \t#"
		"\n\t movdqa     %%xmm7,%7         \t#"
		: "=m" (b[i]),     // %0
		  "=m" (b[i+16]),  // %1
		  "=m" (b[i+32]),  // %2
		  "=m" (b[i+48]),  // %3
		  "=m" (b[i+64]),  // %4
		  "=m" (b[i+80]),  // %5
		  "=m" (b[i+96]),  // %6
		  "=m" (b[i+112])  // %7
		: "m"  (a[i]),     // %8
		  "m"  (a[i+16]),  // %9
		  "m"  (a[i+32]),  // %10
		  "m"  (a[i+48]),  // %11
		  "m"  (a[i+64]),  // %12
		  "m"  (a[i+80]),  // %13
		  "m"  (a[i+96]),  // %14
		  "m"  (a[i+112])  // %15
		);
	}

	for(i = length8; i < length4; i+=64)
	{
		__asm__ volatile
                ( // instruction             comment
                "\n\t movdqa     %4,%%xmm0         \t#"
		"\n\t movdqa     %5,%%xmm1         \t#"
		"\n\t movdqa     %6,%%xmm2         \t#"
		"\n\t movdqa     %7,%%xmm3         \t#"
	        "\n\t movdqa     %%xmm0,%0         \t#"
		"\n\t movdqa     %%xmm1,%1         \t#"
		"\n\t movdqa     %%xmm2,%2         \t#"
		"\n\t movdqa     %%xmm3,%3         \t#"
		: "=m" (b[i]),     // %0
		  "=m" (b[i+16]),  // %1
		  "=m" (b[i+32]),  // %2
		  "=m" (b[i+48])   // %3
		: "m"  (a[i]),     // %4
		  "m"  (a[i+16]),  // %5
		  "m"  (a[i+32]),  // %6
		  "m"  (a[i+48])   // %7
		);
	}
	
	for(i = length4; i < length2; i+=32)
	{
		__asm__ volatile
                ( // instruction             comment
                "\n\t movdqa     %2,%%xmm0         \t#"
		"\n\t movdqa     %3,%%xmm1         \t#"
                "\n\t movdqa     %%xmm0,%0         \t#"
		"\n\t movdqa     %%xmm1,%1         \t#"
		: "=m" (b[i]),     // %0
		  "=m" (b[i+16])   // %1
		: "m"  (a[i]),     // %2
		  "m"  (a[i+16])   // %3
		);
	}

	for(i = length2; i < length; i+=16)
	{
		__asm__ volatile
                ( // instruction             comment
                "\n\t movdqa     %1,%%xmm0         \t#"
                "\n\t movdqa     %%xmm0,%0         \t#"
		: "=m" (b[i])      // %0
		: "m"  (a[i])      // %1
		);
	}


	for(i = length; i < size; i++)
		b[i] = a[i];
}

/**
 * Computes a linear convolution form the arrays and b and stores the result in c.
 * Classic algorithm.
 *
 * Expression:
 *
 \verbatim
  c[i] = a[i] * b[0] + a[i+1] * b[1] + ... + a[i + size_b - 1] * b[size_b -1]
 \endverbatim
 *
 * Example:
 \verbatim
  A                B         C
  | 1| 2| 3| 4|    | 1| 2| = | 1| 5| 8| 4|
 \endverbatim
 *
 * @param[in]	a source array
 * @param[in]	b source array
 * @param[out]	c destination array
 * @param[in]	size_a size of array a
 * @param[in]	size_b size of array b
 *
 */
void convolution_linear_float(float *a, float *b, float *c, int size_a, int size_b)
{
	int i = 0, j = 0;
	float aux[size_b];

	for(i = 0; i < size_a; i++)
	{
		if((i >= size_b / 2) && (i < (size_a -(size_b / 2))))
		{
			for(j = 0; j < size_b; j++)
				aux[j] = a[i+j-(size_b/2)] * b[j];

			c[i] = aux[0];

			for(j = 1; j < size_b; j++)
				c[i] += aux[j];
		}
		else
		{
			c[i] = a[i];
		}
	}
}

/**
 * Computes a linear convolution form the arrays and b and stores the result in c.
 * Algorithm uses SSE2.
 *
 * Expression:
 *
 \verbatim
  c[i] = a[i] * b[0] + a[i+1] * b[1] + ... + a[i + size_b - 1] * b[size_b -1]
 \endverbatim
 *
 * Example:
 \verbatim
  A                B         C
  | 1| 2| 3| 4|    | 1| 2| = | 1| 5| 8| 4|
 \endverbatim
 *
 * @param[in]	a source array
 * @param[in]	b source array
 * @param[out]	c destination array
 * @param[in]	size_a size of array a
 * @param[in]	size_b size of array b
 *
 */
void convolution_linear_float_sse2(float *a, float *b, float *c, int size_a, int size_b)
{
	int i = 0;
	long pointer = 0;
	float aux[size_b];

	for(i = 0; i < size_a; i++)
	{
		if((i >= size_b / 2) && (i < (size_a -(size_b / 2))))
		{	
			pointer = (long) &a[i - (size_b/2)];
			
			if(pointer % 16 == 0)
				mularray_float_sse2(&a[i - (size_b/2)], b, aux, size_b);
			else
				mularray_float_unaligned_sse2(&a[i - (size_b/2)], b, aux, size_b);

			c[i] = sumelem_float_sse2(aux, size_b);
		}
		else
		{
			c[i] = a[i];
		}
	}
}

/**
 * Computes a linear convolution form the arrays and b and stores the result in c.
 * Classic algorithm.
 *
 * Expression:
 *
 \verbatim
  c[i] = a[i] * b[0] + a[i+1] * b[1] + ... + a[i + size_b - 1] * b[size_b -1]
 \endverbatim
 *
 * Example:
 \verbatim
  A                B         C
  | 1| 2| 3| 4|    | 1| 2| = | 1| 5| 8| 4|
 \endverbatim
 *
 * @param[in]	a source array
 * @param[in]	b source array
 * @param[out]	c destination array
 * @param[in]	size_a size of array a
 * @param[in]	size_b size of array b
 *
 */
void convolution_linear_double(double *a, double *b, double *c, int size_a, int size_b)
{
	int i = 0, j = 0;
	double aux[size_b];

	for(i = 0; i < size_a; i++)
	{
		if((i >= size_b / 2) && (i < (size_a -(size_b / 2))))
		{
			for(j = 0; j < size_b; j++)
				aux[j] = a[i+j-(size_b/2)] * b[j];

			c[i] = aux[0];

			for(j = 1; j < size_b; j++)
				c[i] += aux[j];
		}
		else
		{
			c[i] = a[i];
		}
	}
}

/**
 * Computes a linear convolution form the arrays and b and stores the result in c.
 * Algorithm uses SSE2.
 *
 * Expression:
 *
 \verbatim
  c[i] = a[i] * b[0] + a[i+1] * b[1] + ... + a[i + size_b - 1] * b[size_b -1]
 \endverbatim
 *
 * Example:
 \verbatim
  A                B         C
  | 1| 2| 3| 4|    | 1| 2| = | 1| 5| 8| 4|
 \endverbatim
 *
 * @param[in]	a source array
 * @param[in]	b source array
 * @param[out]	c destination array
 * @param[in]	size_a size of array a
 * @param[in]	size_b size of array b
 *
 */
void convolution_linear_double_sse2(double *a, double *b, double *c, int size_a, int size_b)
{
	int i = 0;
	long pointer = 0;
	double aux[size_b];

	for(i = 0; i < size_a; i++)
	{
		if((i >= size_b / 2) && (i < (size_a -(size_b / 2))))
		{
			pointer = (long) &a[i - (size_b/2)];
			
			if(pointer % 16 == 0)
				mularray_double_sse2(&a[i - (size_b/2)], b, aux, size_b);
			else
				mularray_double_unaligned_sse2(&a[i - (size_b/2)], b, aux, size_b);

			c[i] = sumelem_double_sse2(aux, size_b);
		}
		else
		{
			c[i] = a[i];
		}
	}
}

/**
 * Converts a sub-matrix of A to a array B.
 * The sub-matrix if defined by a point and a size.
 * Algorithm uses SSE2.
 *
 * Expression:
 *
 \verbatim
  b[(rows * cols) - 1] = a[rows-1][cols-1]
 \endverbatim
 *
 * Example:
 \verbatim
  A                B
  | 1| 2| 3| 4| => | 1| 2| 3| 4| 2| 3| 4| 5| 3| 4| 5| 6|
  | 2| 3| 4| 5|
  | 3| 4| 5| 6|
 \endverbatim
 *
 * @param[in]	a source array
 * @param[out]	b destination array
 * @param[in]	row start point of the sub-matrix A
 * @param[in]	col start point of the sub-matrix A
 * @param[in]	rows number of rows of sub-matrix A
 * @param[in]	cols number of columns of sub-matrix A
 *
 */
void sub_matrix2array_float_sse2(float **a, float *b, int row, int col, int rows, int cols)
{
	int i = 0;

	for(i = 0; i < rows; i++)
	{
		long pointer1 = (long)(&b[i*cols]);
		long pointer2 = (long)(&a[row+i][col]);

		if((pointer1 % 16 != 0) || (pointer2 % 16 != 0))
			memcpy(&b[i * cols], &a[row+i][col], cols*sizeof(float));
		else
			memcpy_unrolled_sse2(&b[i *cols], &a[row+i][col], cols*sizeof(float));
	}

}

/**
 * Converts a sub-matrix of A to a array B.
 * The sub-matrix if defined by a point and a size.
 * Algorithm uses SSE2.
 *
 * Expression:
 *
 \verbatim
  b[(rows * cols) - 1] = a[rows-1][cols-1]
 \endverbatim
 *
 * Example:
 \verbatim
  A                B
  | 1| 2| 3| 4| => | 1| 2| 3| 4| 2| 3| 4| 5| 3| 4| 5| 6|
  | 2| 3| 4| 5|
  | 3| 4| 5| 6|
 \endverbatim
 *
 * @param[in]	a source array
 * @param[out]	b destination array
 * @param[in]	row start point of the sub-matrix A
 * @param[in]	col start point of the sub-matrix A
 * @param[in]	rows number of rows of sub-matrix A
 * @param[in]	cols number of columns of sub-matrix A
 *
 */
void sub_matrix2array_double_sse2(double **a, double *b, int row, int col, int rows, int cols)
{
	int i = 0;

	for(i = 0; i < rows; i++)
	{
		long pointer1 = (long)(&b[i*cols]);
		long pointer2 = (long)(&a[row+i][col]);

		if((pointer1 % 16 != 0) || (pointer2 % 16 != 0))
			memcpy(&b[i * cols], &a[row+i][col], cols*sizeof(double));
		else
			memcpy_unrolled_sse2(&b[i *cols], &a[row+i][col], cols*sizeof(double));
	}
}

/**
 * Convert a matrix A to a linear matrix B.
 * Algorithm uses SSE2.
 *
 * Example:
 \verbatim
        A	               B	
  | 1| 5| 9|13| => | 1| 2| 3| 4| 5| 6| 7| 8|
  | 2| 6|10|14|
 \endverbatim
 *
 * @param[in]	a source matrix
 * @param[out]	b destination array
 * @param[in]	rows number of rows of matrix A and number of columns of matrix B
 * @param[in]	cols number of columns of matrix A and number of rows of matrix A
 *
 */
void matrix2linear_matrix_float_sse2(float **a, float *b, int rows, int cols)
{
	sub_matrix2array_float_sse2(a, b, 0, 0, rows, cols);	
}

/**
 * Convert a matrix A to a linear matrix B.
 * Algorithm uses SSE2.
 *
 * Example:
 \verbatim
    A	               B	
  | 1| 5| 9|13| => | 1| 2| 3| 4| 5| 6| 7| 8|
  | 2| 6|10|14|
 \endverbatim
 *
 * @param[in]	a source matrix
 * @param[out]	b destination array
 * @param[in]	rows number of rows of matrix A and number of columns of matrix B
 * @param[in]	cols number of columns of matrix A and number of rows of matrix A
 *
 */
void matrix2linear_matrix_double_sse2(double **a, double *b, int rows, int cols)
{
	sub_matrix2array_double_sse2(a, b, 0, 0, rows, cols);	
}

/**
 * Convert a linear matrix A to a matrix B.
 * Algorithm uses SSE2.
 *
 * Example:
 \verbatim
        A	                     B	
  | 1| 2| 3| 4| 5| 6| 7| 8| => | 1| 5| 9|13|
                               | 2| 6|10|14|
 \endverbatim
 *
 * @param[in]	a source matrix
 * @param[out]	b destination array
 * @param[in]	rows number of rows of matrix A and number of columns of matrix B
 * @param[in]	cols number of columns of matrix A and number of rows of matrix A
 *
 */
void linear_matrix2matrix_float_sse2(float *a, float **b, int rows, int cols)
{
	int i = 0;

	for(i = 0; i < rows; i++)
	{
		long pointer1 = (long)(&b[i][0]);
		long pointer2 = (long)(&a[i*cols]);

		if((pointer1 % 16 != 0) || (pointer2 % 16 != 0))
			memcpy(&b[i][0], &a[i *cols], cols*sizeof(float));
		else
			memcpy_unrolled_sse2(&b[i][0], &a[i *cols], cols*sizeof(float));
	}
}

/**
 * Convert a linear matrix A to a matrix B.
 * Algorithm uses SSE2.
 *
 * Example:
 \verbatim
        A	                     B	
  | 1| 2| 3| 4| 5| 6| 7| 8| => | 1| 5| 9|13|
                               | 2| 6|10|14|
 \endverbatim
 *
 * @param[in]	a source matrix
 * @param[out]	b destination array
 * @param[in]	rows number of rows of matrix A and number of columns of matrix B
 * @param[in]	cols number of columns of matrix A and number of rows of matrix A
 *
 */
void linear_matrix2matrix_double_sse2(double *a, double **b, int rows, int cols)
{
	int i = 0;

	for(i = 0; i < rows; i++)
	{
		long pointer1 = (long)(&b[i][0]);
		long pointer2 = (long)(&a[i*cols]);

		if((pointer1 % 16 != 0) || (pointer2 % 16 != 0))
			memcpy(&b[i][0], &a[i *cols], cols*sizeof(double));
		else
			memcpy_unrolled_sse2(&b[i][0], &a[i *cols], cols*sizeof(double));
	}
}

/**
 * Computes a matrix convolution.
 * Classic algorithm.
 *
 * Example:
 \verbatim
  A                B
  | 1| 2| 3| 4|    | 1| 2| = | 1| 2| 3| 4|
  | 2| 3| 4| 5|    | 2| 3|   | 2|18|25| 5|
  | 3| 4| 5| 6|              | 3| 4| 5| 6|
 \endverbatim
 *
 * @param[in]	a source matrix
 * @param[in]	b source matrix
 * @param[out]	c destination matrix
 * @param[in]	rows_a number of rows of matrix A
 * @param[in]	cols_a number of columns of matrix A
 * @param[in]	rows_b number of rows of matrix B
 * @param[in]	cols_b number of columns of matrix B
 *
 */
void convolution_matrix_float(float **a, float **b, float **c, int rows_a, int cols_a, int rows_b, int cols_b)
{
	int i = 0, j = 0;

	for(i = 0; i < rows_a; i++)
	{
		for(j = 0; j < cols_a; j++)
		{
			if((i >= (rows_b/2)) && (i < (rows_a - (rows_b / 2))) && (j >= (cols_b / 2)) && (j < (cols_a - (cols_b/2))))
			{
				float __attribute__ ((aligned(16))) tmp[cols_b];
				float acc = 0.0;

				for(int tt = 0; tt < rows_b; tt++)
				{
					mularray_float(&a[i+tt-rows_b/2][j-cols_b/2], b[tt], tmp, cols_b);
					acc += sumelem_float(tmp, cols_b);
				}

				c[i][j] = acc;
			}
			else
				c[i][j] = a[i][j];
		}
	}
}

/**
 * Computes a matrix convolution.
 * Algorithm uses SSE2.
 *
 * Example:
 \verbatim
  A                B
  | 1| 2| 3| 4|    | 1| 2| = | 1| 2| 3| 4|
  | 2| 3| 4| 5|    | 2| 3|   | 2|18|25| 5|
  | 3| 4| 5| 6|              | 3| 4| 5| 6|
 \endverbatim
 *
 * @param[in]	a source matrix
 * @param[in]	b source matrix
 * @param[out]	c destination matrix
 * @param[in]	rows_a number of rows of matrix A
 * @param[in]	cols_a number of columns of matrix A
 * @param[in]	rows_b number of rows of matrix B
 * @param[in]	cols_b number of columns of matrix B
 *
 */
void convolution_matrix_float_sse2(float **a, float **b, float **c, int rows_a, int cols_a, int rows_b, int cols_b)
{
	int i = 0, j = 0;

	for(i = 0; i < rows_a; i++)
	{
		for(j = 0; j < cols_a; j++)
		{
			if((i >= (rows_b/2)) && (i < (rows_a - (rows_b / 2))) && (j >= (cols_b / 2)) && (j < (cols_a - (cols_b/2))))
			{
				float __attribute__ ((aligned(16))) tmp[cols_b];
				float acc = 0.0;

				for(int tt = 0; tt < rows_b; tt++)
				{
					mularray_float_unaligned_sse2(&a[i+tt-rows_b/2][j-cols_b/2], b[tt], tmp, cols_b);
					acc += sumelem_float_sse2(tmp, cols_b);
				}

				c[i][j] = acc;
			}
			else
				c[i][j] = a[i][j];
		}
	}
}

/**
 * Computes a matrix convolution.
 * Classic algorithm.
 *
 * Example:
 \verbatim
  A                B
  | 1| 2| 3| 4|    | 1| 2| = | 1| 2| 3| 4|
  | 2| 3| 4| 5|    | 2| 3|   | 2|18|25| 5|
  | 3| 4| 5| 6|              | 3| 4| 5| 6|
 \endverbatim
 *
 * @param[in]	a source matrix
 * @param[in]	b source matrix
 * @param[out]	c destination matrix
 * @param[in]	rows_a number of rows of matrix A
 * @param[in]	cols_a number of columns of matrix A
 * @param[in]	rows_b number of rows of matrix B
 * @param[in]	cols_b number of columns of matrix B
 *
 */
void convolution_matrix_double(double **a, double **b, double **c, int rows_a, int cols_a, int rows_b, int cols_b)
{
	int i = 0, j = 0;
	double __attribute__ ((aligned(16))) tmp[cols_b];
	double acc = 0.0;

	for(i = 0; i < rows_a; i++)
	{
		for(j = 0; j < cols_a; j++)
		{
			if((i >= (rows_b/2)) && (i < (rows_a - (rows_b / 2))) && (j >= (cols_b / 2)) && (j < (cols_a - (cols_b/2))))
			{
				acc = 0.0;

				for(int tt = 0; tt < rows_b; tt++)
				{
					mularray_double(&a[i+tt-rows_b/2][j-cols_b/2], b[tt], tmp, cols_b);
					acc += sumelem_double(tmp, cols_b);
				}

				c[i][j] = acc;
			}
			else
				c[i][j] = a[i][j];
		}
	}
}

/**
 * Computes a matrix convolution.
 * Algorithm uses SSE2.
 *
 * Example:
 \verbatim
  A                B
  | 1| 2| 3| 4|    | 1| 2| = | 1| 2| 3| 4|
  | 2| 3| 4| 5|    | 2| 3|   | 2|18|25| 5|
  | 3| 4| 5| 6|              | 3| 4| 5| 6|
 \endverbatim
 *
 * @param[in]	a source matrix
 * @param[in]	b source matrix
 * @param[out]	c destination matrix
 * @param[in]	rows_a number of rows of matrix A
 * @param[in]	cols_a number of columns of matrix A
 * @param[in]	rows_b number of rows of matrix B
 * @param[in]	cols_b number of columns of matrix B
 *
 */
void convolution_matrix_double_sse2(double **a, double **b, double **c, int rows_a, int cols_a, int rows_b, int cols_b)
{
	int i = 0, j = 0;
	long pointer = 0;
	double __attribute__ ((aligned(16))) tmp[cols_b];
	double acc = 0.0;

	for(i = 0; i < rows_a; i++)
	{
		for(j = 0; j < cols_a; j++)
		{
			if((i >= (rows_b/2)) && (i < (rows_a - (rows_b / 2))) && (j >= (cols_b / 2)) && (j < (cols_a - (cols_b/2))))
			{
				acc = 0.0;

				for(int tt = 0; tt < rows_b; tt++)
				{
					pointer = (long) &a[i+tt-rows_b/2][j-cols_b/2];
					
					if(pointer % 16 == 0)
						mularray_double_sse2(&a[i+tt-rows_b/2][j-cols_b/2], b[tt], tmp, cols_b);
					else
						mularray_double_unaligned_sse2(&a[i+tt-rows_b/2][j-cols_b/2], b[tt], tmp, cols_b);

					acc += sumelem_double_sse2(tmp, cols_b);
				}

				c[i][j] = acc;
			}
			else
				c[i][j] = a[i][j];
		}
	}
}
