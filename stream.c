
#include <malloc.h>
#include "stream.h"

Stream *new_Stream(char *src) {
	Stream *R = ((Stream*)malloc(sizeof(Stream)));
	R->src = R->ptr = src;
	R->next = Stream_next(R);
	return R;
}

int Stream_init(Stream *stream) {
	stream->ptr = stream->src;
	stream->next = Stream_next(stream);
	return 0;
}

Result Stream_next(Stream *stream) {
	Result result;
	int ch;

	L_START:
	ch = stream->ptr[0];
	if (ch >= '0' && ch <= '9') {
		result.type = TYPE_NUM;
		result.value = ch - '0';
		stream->ptr++;
		ch = stream->ptr[0];
		while (ch >= '0' && ch <= '9') {
			result.value = result.value * 10 + (ch - '0');
			stream->ptr++;
			ch = stream->ptr[0];
		}
		return result;
	}
	else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' ) {
		result.type = TYPE_OPR;
		result.value = ch;
		stream->ptr++;
		return result;
	}
	else if (ch == '\0') {
		result.type = TYPE_END;
		result.value = 0;
		return result;
	}
	else {
		stream->ptr++;
		goto L_START;
	}
}

Result Stream_read(Stream *obj) {
	Result r = obj->next;
	obj->next = Stream_next(obj);
	return r;
}
