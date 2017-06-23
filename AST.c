extern int linenum;

typedef struct AST {
	int linenum;
	enum {integer, floater, variable, boolean, assign, binary, print}kind;
	union{
		int integerE;
		float floatE;
		_Bool booleanE;
		char *variableE;
		struct{
			char *op;
			struct AST *left; 
			struct AST *right;		
		}binaryE;
		struct{
			char *name;
			struct AST *exp;
		}assignE;
		struct{
			struct Pair_list *pairs;
		}printE;
	}val;
} AST;

typedef struct AST_list {
	AST	*elem;
	struct AST_list *next;
} AST_list;

typedef struct Pair{
	char *string;
	struct AST_list *exp;
}Pair;

typedef struct Pair_list{
	Pair	*elem;
	struct Pair_list *next;
}Pair_list;

AST *make_integer(int num){
	AST *e;
	e = (AST *) malloc (sizeof(AST));
	e->linenum=linenum;
	e->kind = integer;
	e->val.integerE = num;
	return e;
}

AST *make_float(float flo){
	AST *e;
	e = (AST *) malloc (sizeof(AST));
	e->linenum=linenum;
	e->kind = floater;
	e->val.floatE = flo;
	return e;
}

AST *make_variable(char *name){

	AST *e;
	e = (AST *) malloc (sizeof(AST));
	e->linenum=linenum;
	e->kind = variable;
	e->val.variableE = name;
	return e;
}

AST *make_bool(_Bool boo){

	AST *e;
	e = (AST *) malloc (sizeof(AST));
	e->linenum=linenum;
	e->kind = boolean;
	e->val.booleanE = boo;
	return e;
}

AST *make_logical(char *op, AST *left, AST *right ){

	AST *e;
	e = (AST *) malloc (sizeof(AST));
	e->linenum=linenum;
	e->kind = binary;
	e->val.binaryE.op = op;
	e->val.binaryE.left = left;
	e->val.binaryE.right = right;
	return e;
}

AST *make_assign(char *name, AST *exp){

	AST *e;
	e = (AST *) malloc (sizeof(AST));
	e->linenum=linenum;
	e->kind = assign;
	e->val.assignE.name = name;
	e->val.assignE.exp = exp;
	
	return e;
}

AST *make_print(){

	AST *e;
	e = (AST *) malloc (sizeof(AST));
	e->linenum = linenum;
	e->kind = print;
	e->val.printE.pairs->elem->string ="";
	return e;
}

