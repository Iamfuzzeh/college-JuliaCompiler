typedef enum{addI, mulI, subI, divI, eqI, difI, ltI, gtI, leI, geI, assI}Instr;
typedef enum{Null, Num, Var, Flo, Bol, Ass}Address_kind;
typedef struct {
	Address_kind kind;
	union{
		int val;
		float flo;
		char *id;
		_Bool boo;
	}value;
}Address;

typedef struct {
	Instr op;
	Address arg1, arg2, arg3;
}Code;

typedef struct Code_list {
	Code	code;
	struct Code_list *next;
} Code_list;

void print_addresses(Code e){

	printf("code:( %d ", e.op);

	if(e.arg1.kind == Num){
		printf("%d ", e.arg1.value.val );
	}

	else if (e.arg1.kind == Flo)
		printf("%f ", e.arg1.value.flo);

	else if (e.arg1.kind == Bol)
		printf(e.arg1.value.boo ? "true " : "false ");

	else printf("%s ", e.arg1.value.id);


	//arg2


	if(e.arg2.kind == Num){
		printf("%d ", e.arg2.value.val );
	}

	else if (e.arg2.kind == Flo)
		printf("%f ", e.arg2.value.flo);

	else if (e.arg2.kind == Bol)
		printf(e.arg2.value.boo ? "true " : "false ");

	else printf("%s ", e.arg2.value.id);


	//arg3


	if(e.arg3.kind == Num){
		printf("%d ", e.arg3.value.val );
	}

	else if (e.arg3.kind == Flo)
		printf("%f ", e.arg3.value.flo);

	else if (e.arg3.kind == Bol)
		printf(e.arg3.value.boo ? "true " : "false ");

	else printf("%s ", e.arg3.value.id);

	printf(")\n");

}
