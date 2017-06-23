#include <stdio.h>
#include <string.h>
#include "AST.c"

extern Code_list *int_iterator;
int j=0;

void one_or_the_other(AST *e){

	struct Pair_list *holder;
	holder = e->val.printE.pairs;

	while(holder->next != NULL){
		if(holder->elem->string != NULL){
			printf("name\n");
		}
		else printf("nope\n");

	}
}


void printer(AST *e){

	switch (e->kind){

		case integer 	: printf("%d", e->val.integerE);
		break;

		case floater	: printf("%f", e->val.floatE);
		break;

		case variable 	: printf("%s", e->val.variableE);
		break;

		case boolean	: printf(e->val.booleanE ? "true " : "false");
		break;

		case assign	: {
			printf("%s=", e->val.assignE.name);
			printer(e->val.assignE.exp);
			break;
		}

		case print	: {
			one_or_the_other(e);
		}

		case binary	: {
			printf("(");
			printer(e->val.binaryE.left);
			printf("%s", e->val.binaryE.op);
			printer(e->val.binaryE.right);
			printf(")");
			break;
		}
	}
}

void printlist(AST_list *e){

	do{
		printer(e->elem);
		e = e->next;
	} while (e-> next != NULL);

}


Address make_address(AST *holder){

			Address arg;
			
			if(holder->kind == integer){
				arg.kind = Num;
				arg.value.val = holder->val.integerE;
			}

			else if(holder->kind == floater){
				arg.kind = Flo;
				arg.value.flo = holder->val.floatE;
			}

			else if(holder->kind == variable){
				arg.kind = Var;
				arg.value.id = holder->val.variableE;
			}

			else if(holder->kind == boolean){
				arg.kind = Bol;
				arg.value.boo = holder->val.booleanE;
			}

			else if(holder->kind == assign){
				arg.kind = Ass;
				arg.value.id = holder->val.assignE.name;
			}

	return arg;
}


void insert(Code code){
	int_iterator->code = code;
	int_iterator->next = malloc (sizeof(Code_list));
	int_iterator = int_iterator->next;
	int_iterator->next = NULL;
}

AST *convert_address(AST *e){

	switch (e->kind){

		case integer 	:return e;
		break;

		case floater	:return e;
		break;

		case variable 	:return e;
		break;

		case boolean	:return e;
		break;

		case assign	: {

			//resolve expressao

			Code code;

			code.op = assI;
			code.arg1 = make_address(e);

			AST *holder = convert_address(e->val.assignE.exp);
			code.arg2 = make_address(holder);

			code.arg3.kind = Var;
			char *buf = malloc(sizeof(code.arg3.value.id-1));

			sprintf(buf, "t%d", j);
			code.arg3.value.id = buf;
			j++;

			insert(code);
			break;

		}

		case binary	: {


			Code code;

			if (e->val.binaryE.op == "+"){
				code.op = addI;
			}
			else if (e->val.binaryE.op == "-"){
				code.op = subI;
			}
			else if (e->val.binaryE.op == "*"){
				code.op = mulI;
			}
			else if (e->val.binaryE.op == "/"){
				code.op = divI;
			}
			else if (e->val.binaryE.op == "=="){
				code.op = eqI;
			}
			else if (e->val.binaryE.op == "!="){
				code.op = difI;
			}
			else if (e->val.binaryE.op == "<"){
				code.op = ltI;
			}
			else if (e->val.binaryE.op == ">"){
				code.op = gtI;
			}
			else if (e->val.binaryE.op == "<="){
				code.op = leI;
			}
			else if (e->val.binaryE.op == ">="){
				code.op = geI;
			}



			AST *holder = convert_address(e->val.binaryE.left);
			code.arg1 = make_address(holder);

			//work op
			holder = convert_address(e->val.binaryE.right);
			code.arg2 = make_address(holder);

			code.arg3.kind = Var;
			char *buf = malloc(sizeof(code.arg3.value.id-1));

			sprintf(buf, "t%d", j);
			code.arg3.value.id = buf;
			j++;

			insert(code);
			break;
		}
	}
	return e;
}


