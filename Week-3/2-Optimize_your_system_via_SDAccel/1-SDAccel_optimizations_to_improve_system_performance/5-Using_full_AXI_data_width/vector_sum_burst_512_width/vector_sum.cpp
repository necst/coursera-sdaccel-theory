#include <string.h>
#include "ap_int.h"
#define N 1024
#define WIDTH 512
#define FLOAT_BITS (sizeof(float) * 8)
#define FLOATS_PER_ELEM (WIDTH / FLOAT_BITS)

typedef union
{
	unsigned int raw_val;
	float float_val;
} raw_float;

inline float get_float(ap_int<WIDTH> ap, int index)
{
	raw_float tmp;
	tmp.raw_val = ap.range((index+1)*FLOAT_BITS - 1, index*FLOAT_BITS);
	return tmp.float_val;
}

inline void store_float(ap_int<WIDTH> &ap, int index, float val)
{
	raw_float tmp;
	tmp.float_val = val;
	ap.range((index+1)*FLOAT_BITS - 1, index*FLOAT_BITS) = tmp.raw_val;
}

void vector_sum(ap_int<WIDTH> *a, ap_int<WIDTH> *b, ap_int<WIDTH> *res)
{
	#pragma HLS INTERFACE depth=1024 m_axi port=a offset=slave bundle=gmem0
	#pragma HLS INTERFACE depth=1024 m_axi port=b offset=slave bundle=gmem0
	#pragma HLS INTERFACE depth=1024 m_axi port=res offset=slave bundle=gmem0

	#pragma HLS INTERFACE s_axilite port=a bundle=control
	#pragma HLS INTERFACE s_axilite port=b bundle=control
	#pragma HLS INTERFACE s_axilite port=res bundle=control
	#pragma HLS INTERFACE s_axilite port=return bundle=control

	ap_int<WIDTH> local_a[N / FLOATS_PER_ELEM];
	ap_int<WIDTH> local_b[N / FLOATS_PER_ELEM];
	ap_int<WIDTH> local_res[N / FLOATS_PER_ELEM];

	// read data from DDR to local memories
	memcpy(local_a, a, sizeof(float) * N);
	memcpy(local_b, b, sizeof(float) * N);

	// do the actual computation
	sum_loop:for(int i = 0; i < N / FLOATS_PER_ELEM; i++) {
		inner_sum_loop:for(int j = 0; j < FLOATS_PER_ELEM; j++) {
			store_float(local_res[i], j, get_float(local_a[i], j) + get_float(local_b[i], j));
		}
	}

	// write data from local memories to the DDR
	memcpy(res, local_res, sizeof(float) * N);
}

