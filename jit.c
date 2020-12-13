#include "stream.h"
#include "jit.h"
#include "new.h"

void add(double *res, double *a, double *b) {
	*res = *a + *b;
}

void sub(double *res, double *a, double *b) {
	*res = *a - *b;
}

void mul(double *res, double *a, double *b) {
	*res = (*a) * (*b);
}

void div(double *res, double *a, double *b) {
	*res = *a / *b;
}

void set(double *res, double *a, double *b) {
	*res = *a;
}

int ins_count = 0;
Instruction ins_list[8192];

double ra = 0, rb = 0, rc = 0,
       rd = 0, re = 0, rf = 0;

int add_ins(function func, double *res, double *a, double *b) {
	Instruction *ins = &ins_list[ins_count];
	ins->res = res;
	ins->a = a;
	ins->b = b;
	ins->func = func;
	ins_count++;
	return 0;
}

void jit_next_group(Stream *stream) {
	Result r;

	r = Stream_read(stream);

	double *fp = NEW(double); *fp = r.value;
	add_ins(set, &rd, fp, NULL);

	while (1) {
		r = stream->next;
		if (r.value == '*' || r.value == '/') {
			int op = r.value;
			Stream_read(stream);
			r = Stream_read(stream);
			fp = NEW(double); *fp = r.value;
			////////////////////////////////////////////////
			if (op == '*') add_ins(mul, &rd, &rd, fp);
			else add_ins(div, &rd, &rd, fp);
			////////////////////////////////////////////////
		}
		else {
			return;
		}
	}
}

void jit_compile(Stream *stream) {
	int opr;

	Result r = stream->next;
	if (r.type == TYPE_NUM) {
		jit_next_group(stream); //
		add_ins(set, &ra, &rd, NULL);
	}

	while (1) {
		r = Stream_read(stream);
		if (r.type == TYPE_END)
			return;
		opr = r.value;
		jit_next_group(stream); //
		add_ins(set, &rb, &rd, NULL);
		if (opr == '+')
			add_ins(add, &ra, &ra, &rb);
		else
			add_ins(sub, &ra, &ra, &rb);
	}
}

double jit_execute() {
	int i;
	for (i = 0; i < ins_count; i++) {
		Instruction *ins = &ins_list[i];
		ins->func(ins->res, ins->a, ins->b);
	}
	return ra;
}
