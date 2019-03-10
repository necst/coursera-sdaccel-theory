#include<string.h>
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

	float local_a_0[N/4], local_a_1[N/4], local_a_2[N/4], local_a_3[N/4];
	float local_b_0[N/4], local_b_1[N/4], local_b_2[N/4], local_b_3[N/4];
	float local_res_0[N/4], local_res_1[N/4], local_res_2[N/4], local_res_3[N/4];

	int i;

	// read data from DDR to local memories
	copy_a:for(i = 0; i < N; i++) {
		#pragma HLS PIPELINE
		switch (i % 4) {
			case 0: local_a_0[i/4] = a[i]; break;
			case 1: local_a_1[i/4] = a[i]; break;
			case 2: local_a_2[i/4] = a[i]; break;
			case 3: local_a_3[i/4] = a[i]; break;
		}
	}

	copy_b:for(i = 0; i < N; i++) {
		#pragma HLS PIPELINE
		switch (i % 4) {
			case 0: local_b_0[i/4] = a[i]; break;
			case 1: local_b_1[i/4] = a[i]; break;
			case 2: local_b_2[i/4] = a[i]; break;
			case 3: local_b_3[i/4] = a[i]; break;
		}
	}

	// do the actual computation
	sum_loop:for(i = 0; i < N; i+=4) {
		#pragma HLS PIPELINE
		local_res_0[i/4] = local_a_0[i/4] + local_b_0[i/4];
		local_res_1[i/4] = local_a_1[i/4] + local_b_1[i/4];
		local_res_2[i/4] = local_a_2[i/4] + local_b_2[i/4];
		local_res_3[i/4] = local_a_3[i/4] + local_b_3[i/4];
	}

	// write data from local memories to the DDR
	copy_res:for(i = 0; i < N; i++) {
		#pragma HLS PIPELINE
		switch (i % 4) {
			case 0: res[i] = local_res_0[i/4]; break;
			case 1: res[i] = local_res_1[i/4]; break;
			case 2: res[i] = local_res_2[i/4]; break;
			case 3: res[i] = local_res_3[i/4]; break;
		}
	}
}