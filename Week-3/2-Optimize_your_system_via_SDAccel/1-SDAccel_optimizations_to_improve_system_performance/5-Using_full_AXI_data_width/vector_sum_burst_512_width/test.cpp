#include <stdio.h>
#include"ap_int.h"

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

void vector_sum(ap_int<512> *a, ap_int<512> *b, ap_int<512> *res);

int main()
{
	ap_int<WIDTH> ap_a[N / FLOATS_PER_ELEM];
	ap_int<WIDTH> ap_b[N / FLOATS_PER_ELEM];
	ap_int<WIDTH> ap_res[N / FLOATS_PER_ELEM];

	float golden_res[N];
	unsigned int i, j, cur_element, errors = 0;

	for(i = 0; i < N / FLOATS_PER_ELEM; i++) {
		for(j = 0; j < FLOATS_PER_ELEM; j++) {
			cur_element = i*FLOATS_PER_ELEM + j;
			float v = cur_element*1.0;
			float v2 = cur_element*2.0;
			store_float(ap_a[i], j, v);
			store_float(ap_b[i], j, v2);
			golden_res[cur_element] = v + v2;
		}
	}

	vector_sum(ap_a, ap_b, ap_res);

	for(i = 0; i < N / FLOATS_PER_ELEM; i++) {
		for(j = 0; j < FLOATS_PER_ELEM; j++) {
			cur_element = i*FLOATS_PER_ELEM + j;
			float res = get_float(ap_res[i], j);
			float expected = golden_res[cur_element];

			if(res != expected) {
				printf("Error, expected: %f, got: %f \n", expected, res);
				errors++;
			}
		}
	}

	if(errors == 0) {
		printf("Test succeeded!\n");
		return 0;
	} else {
		printf("Test failed, %u errors\n", errors);
		return 1;
	}
}
