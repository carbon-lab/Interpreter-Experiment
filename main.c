#include "pch.h"
#include <sys/time.h>

unsigned long long getTime() {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

char buffer[65536];

int read_file(FILE *file, char *buf) {
	int ch;
	char *p = buf;

	ch = fgetc(file);
	while (ch != EOF) {
		*p = ch;
		p++;
		ch = fgetc(file);
	}

	*p = '\0';
	return 0;
}

#define N 1000000

int main() {
	FILE *input = fopen("../formula.txt", "r");
	read_file(input, buffer);
	fclose(input);

	int i;
	unsigned long long start, end;
	double result;

	start = getTime();
	Stream *stream = new_Stream(buffer);
	for (i = 0; i < N; i++) {
		result = formal_execute(stream);
		Stream_init(stream);
	}
	end = getTime();

	printf("Formal execute time: %d ms, result = %lf\n", end - start, result);

	Stream *stream2 = new_Stream(buffer);
	start = getTime();
	jit_compile(stream2);
	for (i = 0; i < N; i++) {
		result = jit_execute();
	}
	end = getTime();
	printf("JIT execute time: %d ms, result = %lf\n", end - start, result);

	return 0;
}
