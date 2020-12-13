
typedef void (*function)(double *res, double *a, double *b);

typedef struct {
	double *res;
	double *a;
	double *b;
	function func;
} Instruction;

void add(double *res, double *a, double *b);
void sub(double *res, double *a, double *b);
void mul(double *res, double *a, double *b);
void div(double *res, double *a, double *b);
void set(double *res, double *a, double *b);

void jit_compile(Stream *stream);
double jit_execute();
