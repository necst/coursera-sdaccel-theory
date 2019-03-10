#include <string.h>
#define N 1024

void vector_sum(float *a, float *b, float *res)
{
	#pragma HLS INTERFACE m_axi depth=1024 port=a offset=slave bundle=gmem0
	#pragma HLS INTERFACE m_axi depth=1024 port=b offset=slave bundle=gmem0
	#pragma HLS INTERFACE m_axi depth=1024 port=res offset=slave bundle=gmem0

	#pragma HLS INTERFACE s_axilite port=a bundle=control
	#pragma HLS INTERFACE s_axilite port=b bundle=control
	#pragma HLS INTERFACE s_axilite port=res bundle=control
	#pragma HLS INTERFACE s_axilite port=return bundle=control

	float local_a[N];
	float local_b[N];
	float local_res[N];

	// read data from DDR to local memories
	memcpy(local_a, a, sizeof(float) * N);
	memcpy(local_b, b, sizeof(float) * N);

	// do the actual computation
	sum_loop:for(int i = 0; i < N; i++) {
		local_res[i] = local_a[i] + local_b[i];
	}

	// write data from local memories to the DDR
	memcpy(res, local_res, sizeof(float) * N);
}