#include <stdio.h>

#define N 1024

void vector_sum(float *a, float *b, float *res);

int main()
{
	float a[N];
	float b[N];
	float res[N];
	float golden_res[N];

	unsigned int i, j, errors = 0;

	for(i = 0; i < N; i++) {
		a[i] = i*1.0;
		b[i] = i*2.0;
		golden_res[i] = a[i] + b[i];
	}

	vector_sum(a, b, res);

	for(i = 0; i < N; i++) {
		if(res[i] != golden_res[i]) {
			printf("Error, expected: %f, got: %f \n", golden_res[i], res[i]);
			errors++;
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

