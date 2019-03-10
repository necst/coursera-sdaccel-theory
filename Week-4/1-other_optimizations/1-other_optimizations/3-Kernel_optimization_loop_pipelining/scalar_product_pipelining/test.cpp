#include <stdio.h>

#define N 1024

void scalar_product(float *a, float *b, float *res);

int main()
{
	float a[N];
	float b[N];
	float res[1];
	float golden_res = 0.0;

	unsigned int i, j, errors = 0;

	for(i = 0; i < N; i++) {
		a[i] = i*1.0;
		b[i] = i*2.0;
		golden_res += a[i]* b[i];
	}

	scalar_product(a, b, res);

	if(res[0] == golden_res) {
		printf("Test succeeded!\n");
		return 0;
	} else {
		printf("Test failed, expected: %f, got: %f \n", golden_res, res[0]);
		return 1;
	}
}