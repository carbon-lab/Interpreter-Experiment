
#define TYPE_END (-1)
#define TYPE_NUM 1
#define TYPE_OPR 2

typedef struct {
	int type;
	int value;
} Result;

typedef struct {
	char *src;
	char *ptr;
	Result next;
} Stream;


Stream *new_Stream(char *src);
Result Stream_next(Stream *stream);
Result Stream_read(Stream *stream);
int Stream_init(Stream *stream);
