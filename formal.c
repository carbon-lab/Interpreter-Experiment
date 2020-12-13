
#include "stream.h"

double next_group(Stream *stream) {
	double result = 0;

	Result r;

	r = Stream_read(stream);
	result = r.value;
	while (1) {
		r = stream->next;
		if (r.value == '*' || r.value == '/') {
			int op = r.value;
			Stream_read(stream);
			r = Stream_read(stream);
			if (op == '*') result *= r.value;
			else result /= r.value;
		}
		else {
			return result;
		}
	}
}

double formal_execute(Stream *stream) {
	int opr;
	double result = 0, num;

	Result r = stream->next;
	if (r.type == TYPE_NUM) {
		result = next_group(stream);
	}

	while (1) {
		r = Stream_read(stream);
		if (r.type == TYPE_END)
			return result;
		opr = r.value;
		num = next_group(stream);
		if (opr == '+')
			result += num;
		else
			result -= num;
	}
}
