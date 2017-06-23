char *vars[20] = {};
int nvars=0;


typedef struct Var_tup {
	char *id;
	int t;
}Var_tup;

typedef struct Var_list {
	Var_tup tuple;
	struct Var_list *next;

}Var_list;

Var_list *var_list;
Var_list *var_iterator;

void initialize_var_list(){
	var_list = malloc( sizeof(Var_list));
	var_list->tuple.id="";
	var_list->tuple.t=0;
}

int insert_tuple(char *e){

	int t = var_iterator->tuple.t;
	t++;
	var_iterator->next = malloc (sizeof(Var_list));
	var_iterator = var_iterator->next;
	var_iterator->tuple.id = e;
	var_iterator->tuple.t = t;
	var_iterator->next = NULL;

	return t;
}

int search_var(char *e){
	var_iterator = var_list;	

	while(var_iterator->next != NULL){
		if ( strcmp(var_iterator->tuple.id,e) == 0 ) return var_iterator->tuple.t;
		var_iterator = var_iterator->next;
	}

	return insert_tuple(e);
}


void print_code(Code code, FILE *f){

	// 4 tipos
	if (code.op == addI){

		if(code.arg1.kind == Num){
			fprintf(f, "   addi  $%s,$%s,%d\n", code.arg3.value.id, code.arg3.value.id, code.arg1.value.val );
		}

		else if(code.arg1.kind == Flo){
			fprintf(f, "   addi  $%s,$%s,%f\n", code.arg3.value.id, code.arg3.value.id, code.arg1.value.flo );
		}

		else if(code.arg1.kind == Bol){
			fprintf(f, "   addi  $%s,$%s,", code.arg3.value.id, code.arg3.value.id);
			fprintf(f, code.arg1.value.boo ? "true\n" : "false\n");
		}

		else {
			int i = search_var(code.arg1.value.id);
			fprintf(f, "   add   $%s,$%s,$t%d\n", code.arg3.value.id, code.arg3.value.id, i);
		}

		if(code.arg2.kind == Num){
			fprintf(f, "   addi  $%s,$%s,%d\n", code.arg3.value.id, code.arg3.value.id, code.arg2.value.val );
		}

		else if(code.arg2.kind == Flo){
			fprintf(f, "   addi  $%s,$%s,%f\n", code.arg3.value.id, code.arg3.value.id, code.arg1.value.flo );
		}

		else {
			int i = search_var(code.arg2.value.id);
			fprintf(f, "   add   $%s,$%s,$t%d\n", code.arg3.value.id, code.arg3.value.id, i);

		}
		
	}

	else if(code.op == mulI){

		if(code.arg1.kind == Num){
			fprintf(f, "   addi  $%s,$%s,%d\n", code.arg3.value.id, code.arg3.value.id, code.arg1.value.val );
		}

		else if(code.arg1.kind == Flo){
			fprintf(f, "   addi  $%s,$%s,%f\n", code.arg3.value.id, code.arg3.value.id, code.arg1.value.flo );
		}

		else if(code.arg1.kind == Bol){
			fprintf(f, "   addi  $%s,$%s,", code.arg3.value.id, code.arg3.value.id);
			fprintf(f, code.arg1.value.boo ? "true\n" : "false\n");
		}

		else {
			int i = search_var(code.arg1.value.id);
			fprintf(f, "   add  $%s,$%s,$t%d\n", code.arg3.value.id, code.arg3.value.id, i);

		}
		if(code.arg2.kind == Num){
			fprintf(f, "   mult  $%s,$%s,%d\n", code.arg3.value.id, code.arg3.value.id, code.arg2.value.val );
		}

		else if(code.arg2.kind == Flo){
			fprintf(f, "   mult  $%s,$%s,%f\n", code.arg3.value.id, code.arg3.value.id, code.arg2.value.flo );
		}

		else{
			int i = search_var(code.arg2.value.id);
			fprintf(f, "   mult  $%s,$%s,$t%d\n", code.arg3.value.id, code.arg3.value.id,i);
		}
	}
	
	else if(code.op == subI){

		if(code.arg1.kind == Num){
			fprintf(f, "   addi  $%s,$%s,%d\n", code.arg3.value.id, code.arg3.value.id, code.arg1.value.val );
		}

		else if(code.arg1.kind == Flo){
			fprintf(f, "   addi  $%s,$%s,%f\n", code.arg3.value.id, code.arg3.value.id, code.arg1.value.flo );
		}

		else if(code.arg1.kind == Bol){
			fprintf(f, "   addi  $%s,$%s,", code.arg3.value.id, code.arg3.value.id);
			fprintf(f, code.arg1.value.boo ? "true\n" : "false\n");
		}

		else {
			int i = search_var(code.arg1.value.id);
			fprintf(f, "   add  $%s,$%s,$t%d\n", code.arg3.value.id, code.arg3.value.id, i);

		}
		if(code.arg2.kind == Num){
			fprintf(f, "   sub  $%s,$%s,%d\n", code.arg3.value.id, code.arg3.value.id, code.arg2.value.val );
		}

		else if(code.arg2.kind == Flo){
			fprintf(f, "   sub  $%s,$%s,%f\n", code.arg3.value.id, code.arg3.value.id, code.arg2.value.flo );
		}
		else{
			int i = search_var(code.arg2.value.id);
			fprintf(f, "   sub  $%s,$%s,$t%d\n", code.arg3.value.id, code.arg3.value.id,i);
		}
		
	}

	else if(code.op == divI){

		if(code.arg1.kind == Num){
			fprintf(f, "   addi  $%s,$%s,%d\n", code.arg3.value.id, code.arg3.value.id, code.arg1.value.val );
		}

		else if(code.arg1.kind == Flo){
			fprintf(f, "   addi  $%s,$%s,%f\n", code.arg3.value.id, code.arg3.value.id, code.arg1.value.flo );
		}

		else if(code.arg1.kind == Bol){
			fprintf(f, "   addi  $%s,$%s,", code.arg3.value.id, code.arg3.value.id);
			fprintf(f, code.arg1.value.boo ? "true\n" : "false\n");
		}

		else {
			int i = search_var(code.arg1.value.id);
			fprintf(f, "   add  $%s,$%s,$t%d\n", code.arg3.value.id, code.arg3.value.id, i);

		}
		if(code.arg2.kind == Num){
			fprintf(f, "   div  $%s,$%s,%d\n", code.arg3.value.id, code.arg3.value.id, code.arg2.value.val );
		}

		else if(code.arg2.kind == Flo){
			fprintf(f, "   div  $%s,$%s,%f\n", code.arg3.value.id, code.arg3.value.id, code.arg2.value.flo );
		}

		else{
			int i = search_var(code.arg2.value.id);
			fprintf(f, "   div  $%s,$%s,$t%d\n", code.arg3.value.id, code.arg3.value.id,i);
		}
		
	}

	else if(code.op == eqI){

		if(code.arg1.kind == Num){
			fprintf(f, "   addi  $%s,$%s,%d\n", code.arg3.value.id, code.arg3.value.id, code.arg1.value.val );
		}

		else if(code.arg1.kind == Flo){
			fprintf(f, "   addi  $%s,$%s,%f\n", code.arg3.value.id, code.arg3.value.id, code.arg1.value.flo );
		}

		else if(code.arg1.kind == Bol){
			fprintf(f, "   addi  $%s,$%s,", code.arg3.value.id, code.arg3.value.id);
			fprintf(f, code.arg1.value.boo ? "true\n" : "false\n");
		}

		else {
			int i = search_var(code.arg1.value.id);
			fprintf(f, "   seq  $%s,$%s,$t%d\n", code.arg3.value.id, code.arg3.value.id, i);

		}
		if(code.arg2.kind == Num){
			fprintf(f, "   seq  $%s,$%s,%d\n", code.arg3.value.id, code.arg3.value.id, code.arg2.value.val );
		}

		else if(code.arg2.kind == Flo){
			fprintf(f, "   seq  $%s,$%s,%f\n", code.arg3.value.id, code.arg3.value.id, code.arg2.value.flo );
		}

		else{
			int i = search_var(code.arg2.value.id);
			fprintf(f, "   seq  $%s,$%s,$t%d\n", code.arg3.value.id, code.arg3.value.id,i);
		}

	}

	else if(code.op == difI){

		if(code.arg1.kind == Num){
			fprintf(f, "   addi  $%s,$%s,%d\n", code.arg3.value.id, code.arg3.value.id, code.arg1.value.val );
		}

		else if(code.arg1.kind == Flo){
			fprintf(f, "   addi  $%s,$%s,%f\n", code.arg3.value.id, code.arg3.value.id, code.arg1.value.flo );
		}

		else if(code.arg1.kind == Bol){
			fprintf(f, "   addi  $%s,$%s,", code.arg3.value.id, code.arg3.value.id);
			fprintf(f, code.arg1.value.boo ? "true\n" : "false\n");
		}

		else {
			int i = search_var(code.arg1.value.id);
			fprintf(f, "   sne  $%s,$%s,$t%d\n", code.arg3.value.id, code.arg3.value.id, i);

		}
		if(code.arg2.kind == Num){
			fprintf(f, "   sne  $%s,$%s,%d\n", code.arg3.value.id, code.arg3.value.id, code.arg2.value.val );
		}

		else if(code.arg2.kind == Flo){
			fprintf(f, "   sne  $%s,$%s,%f\n", code.arg3.value.id, code.arg3.value.id, code.arg2.value.flo );
		}

		else{
			int i = search_var(code.arg2.value.id);
			fprintf(f, "   sne  $%s,$%s,$t%d\n", code.arg3.value.id, code.arg3.value.id,i);
		}

	}

	else if(code.op == ltI){

		if(code.arg1.kind == Num){
			fprintf(f, "   addi  $%s,$%s,%d\n", code.arg3.value.id, code.arg3.value.id, code.arg1.value.val );
		}

		else if(code.arg1.kind == Flo){
			fprintf(f, "   addi  $%s,$%s,%f\n", code.arg3.value.id, code.arg3.value.id, code.arg1.value.flo );
		}

		else if(code.arg1.kind == Bol){
			fprintf(f, "   addi  $%s,$%s,", code.arg3.value.id, code.arg3.value.id);
			fprintf(f, code.arg1.value.boo ? "true\n" : "false\n");
		}

		else {
			int i = search_var(code.arg1.value.id);
			fprintf(f, "   slt  $%s,$%s,$t%d\n", code.arg3.value.id, code.arg3.value.id, i);

		}
		if(code.arg2.kind == Num){
			fprintf(f, "   slt  $%s,$%s,%d\n", code.arg3.value.id, code.arg3.value.id, code.arg2.value.val );
		}

		else if(code.arg2.kind == Flo){
			fprintf(f, "   slt  $%s,$%s,%f\n", code.arg3.value.id, code.arg3.value.id, code.arg2.value.flo );
		}

		else{
			int i = search_var(code.arg2.value.id);
			fprintf(f, "   slt  $%s,$%s,$t%d\n", code.arg3.value.id, code.arg3.value.id,i);
		}

	}

	else if(code.op == gtI){

		if(code.arg1.kind == Num){
			fprintf(f, "   addi  $%s,$%s,%d\n", code.arg3.value.id, code.arg3.value.id, code.arg1.value.val );
		}

		else if(code.arg1.kind == Flo){
			fprintf(f, "   addi  $%s,$%s,%f\n", code.arg3.value.id, code.arg3.value.id, code.arg1.value.flo );
		}

		else if(code.arg1.kind == Bol){
			fprintf(f, "   addi  $%s,$%s,", code.arg3.value.id, code.arg3.value.id);
			fprintf(f, code.arg1.value.boo ? "true\n" : "false\n");
		}

		else {
			int i = search_var(code.arg1.value.id);
			fprintf(f, "   sgt  $%s,$%s,$t%d\n", code.arg3.value.id, code.arg3.value.id, i);

		}
		if(code.arg2.kind == Num){
			fprintf(f, "   sgt  $%s,$%s,%d\n", code.arg3.value.id, code.arg3.value.id, code.arg2.value.val );
		}

		else if(code.arg2.kind == Flo){
			fprintf(f, "   sgt  $%s,$%s,%f\n", code.arg3.value.id, code.arg3.value.id, code.arg2.value.flo );
		}

		else{
			int i = search_var(code.arg2.value.id);
			fprintf(f, "   sgt  $%s,$%s,$t%d\n", code.arg3.value.id, code.arg3.value.id,i);
		}

	}

	else if(code.op == leI){

		if(code.arg1.kind == Num){
			fprintf(f, "   addi  $%s,$%s,%d\n", code.arg3.value.id, code.arg3.value.id, code.arg1.value.val );
		}

		else if(code.arg1.kind == Flo){
			fprintf(f, "   addi  $%s,$%s,%f\n", code.arg3.value.id, code.arg3.value.id, code.arg1.value.flo );
		}

		else if(code.arg1.kind == Bol){
			fprintf(f, "   addi  $%s,$%s,", code.arg3.value.id, code.arg3.value.id);
			fprintf(f, code.arg1.value.boo ? "true\n" : "false\n");
		}

		else {
			int i = search_var(code.arg1.value.id);
			fprintf(f, "   sle  $%s,$%s,$t%d\n", code.arg3.value.id, code.arg3.value.id, i);

		}
		if(code.arg2.kind == Num){
			fprintf(f, "   sle  $%s,$%s,%d\n", code.arg3.value.id, code.arg3.value.id, code.arg2.value.val );
		}

		else if(code.arg2.kind == Flo){
			fprintf(f, "   sle  $%s,$%s,%f\n", code.arg3.value.id, code.arg3.value.id, code.arg2.value.flo );
		}

		else{
			int i = search_var(code.arg2.value.id);
			fprintf(f, "   sle  $%s,$%s,$t%d\n", code.arg3.value.id, code.arg3.value.id,i);
		}

	}


	else if(code.op == geI){

		if(code.arg1.kind == Num){
			fprintf(f, "   addi  $%s,$%s,%d\n", code.arg3.value.id, code.arg3.value.id, code.arg1.value.val );
		}

		else if(code.arg1.kind == Flo){
			fprintf(f, "   addi  $%s,$%s,%f\n", code.arg3.value.id, code.arg3.value.id, code.arg1.value.flo );
		}

		else if(code.arg1.kind == Bol){
			fprintf(f, "   addi  $%s,$%s,", code.arg3.value.id, code.arg3.value.id);
			fprintf(f, code.arg1.value.boo ? "true\n" : "false\n");
		}

		else {
			int i = search_var(code.arg1.value.id);
			fprintf(f, "   sge  $%s,$%s,$t%d\n", code.arg3.value.id, code.arg3.value.id, i);

		}
		if(code.arg2.kind == Num){
			fprintf(f, "   sge  $%s,$%s,%d\n", code.arg3.value.id, code.arg3.value.id, code.arg2.value.val );
		}

		else if(code.arg2.kind == Flo){
			fprintf(f, "   sge  $%s,$%s,%f\n", code.arg3.value.id, code.arg3.value.id, code.arg2.value.flo );
		}

		else{
			int i = search_var(code.arg2.value.id);
			fprintf(f, "   sge  $%s,$%s,$t%d\n", code.arg3.value.id, code.arg3.value.id,i);
		}

	}


else if(code.op == assI){

		if(code.arg2.kind == Num){
			fprintf(f, "   li  $%s, %d\n", code.arg3.value.id, code.arg2.value.val);
		}		
		else{
			int i = search_var(code.arg2.value.id);
			fprintf(f, "   la  $%s, $t%d\n", code.arg3.value.id, i);
		}

	}

}



void write_shit(Code_list *code_list){

	initialize_var_list();

	FILE *f = fopen("MIPS.txt", "w");
	if (f == NULL){
	    printf("Error opening file!\n");
	    exit(1);
	}

	/* print some text */
	const char *text = "main:\n";
	fprintf(f, "%s", text);
	
	while (code_list->next != NULL){
		print_addresses(code_list->code);
		print_code(code_list->code, f);
		code_list = code_list->next;
	}

	fclose(f);
}
