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

	sum_loop:for(int i = 0; i < N; i++) {
		res[i] = a[i] + b[i];
	}
}