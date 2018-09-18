#include <stdio.h>
#include <string.h>
#include "calc.h"

int main(int argc, const char *argv[])
{
	char input_buffer[256] = { 0 };
	while (1) {
		printf(">>>");
        gets(input_buffer);
		if (strcmp(input_buffer, "exit") == 0) {
			break;
		}
		int input_size = strlen(input_buffer);
		if (calc_input_check(input_buffer, input_size)) {
			printf("%lf\n", calc_compute(input_buffer, input_size));
		} else {
			printf("Input error!\n");
		}
	}

	return 0;
}
