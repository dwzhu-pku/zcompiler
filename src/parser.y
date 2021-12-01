%{
    #include<stdio.h>
    #include"ast.hpp"
    extern int yylex();
    extern int yylineno;
    extern FILE * yyin;
    extern FILE * yyout;
    void yyerror(BaseAst**, const char *);
%}

%union{
    Token* kToken;
    BaseAst* kPtrAst;
};
%parse-param {BaseAst* *root}

%token <kToken> INT VOID CONST // 类型关键字
%token <kToken> IF ELSE WHILE BREAK CONTINUE RETURN // 控制流关键字
%token <kToken> ADD SUB MUL DIV MOD NOT// 运算符关键字(+, -, *, /, %, !)
%token <kToken> LT GT LE GE EQ NE // 关系运算符(<, >, <=, >=, ==, !=)
%token <kToken> LAND LOR // 逻辑运算符(&&, || )
%token <kToken> IDENT ASSIGN // 标识符 赋值运算
%token <kToken> VAL_CONST // 常量值
%token <kToken> SEMI COMMA LKHX RKHX LKHZ RKHZ LKHD RKHD  // 标点符号(; , ( ) [ ] { })

%type <kPtrAst> CompUnit Decl FuncDef ConstDecl VarDecl VarDef VarDefArr InitVal ConstInitVal
%type <kPtrAst> ConstDef ConstDefArr ConstExp AddExp MulExp UnaryExp Exp
%type <kPtrAst> PrimaryExp LVal Block BlockItem BlockItems Stmt
%type <kPtrAst> Cond LOrExp LAndExp EqExp RelExp FuncFParams FuncRParams FuncFParam
%type <kPtrAst> ConstExpArr ConstInitValArr InitValArr

%%
CompUnit        : CompUnit Decl
                    {
                        if(Debug_Parser)    printf("Trace: CompUnit\n");
                        dynamic_cast<BlockAst*>($1)->append_stmt($2);
                        $$=$1;
                    }
                | CompUnit FuncDef
                    {
                        if(Debug_Parser)    printf("Trace: CompUnit\n");
                        dynamic_cast<BlockAst*>($1)->append_stmt($2);
                        $$=$1;
                    }
                | Decl
                    {
                        if(Debug_Parser)    printf("Trace: CompUnit\n");
                        BlockAst* ptr = new BlockAst();
                        ptr->append_stmt($1);
                        *root = ptr;
		                $$ = ptr;
                    }
                | FuncDef
                    {
                        if(Debug_Parser)    printf("Trace: CompUnit\n");
                        BlockAst* ptr = new BlockAst();
                        ptr->append_stmt($1);
                        *root = ptr;
		                $$ = ptr;
                    }
                ;

Decl            : ConstDecl
                    {
                        $$=$1;
                    }
                | VarDecl
                    {
                        $$=$1;
                    }
                ;
ConstDecl       : CONST INT ConstDefArr SEMI
                    {
                        ($3)->is_const = 1;
                        $$=$3;
                    }
                ;

VarDecl         : INT VarDefArr SEMI
                    {
                        $$ = $2;
                    }
                ;

VarDefArr       : VarDefArr COMMA VarDef
                    {
                        dynamic_cast<ArrayAst*>($1)->append_item($3);
                        $$=$1;
                    }
                | VarDef
                    {
                        ArrayAst* ptr = new ArrayAst();
                        ptr->append_item($1);
                        $$=ptr;
                    }

VarDef          : IDENT
                    {
                        DeclAst* ptr = new DeclAst(1, $1->ident_name);
                        $$=ptr;
                    }
                | IDENT ASSIGN InitVal
                    {
                        if(Debug_Parser)    printf("Trace: VarDef\n");
                        DeclAst* ptr = new DeclAst(1, $1->ident_name, $3);
                        $$=ptr;
                    }
                | IDENT ConstExpArr
                    {
                        if(Debug_Parser)    printf("Trace: VarDef\n");
                        ListAst* ptr = new ListAst(($1)->ident_name, dynamic_cast<ArrayAst*>($2)->array_list);
                        $$ = ptr;
                    }
                | IDENT ConstExpArr ASSIGN InitVal
                    {
                        if(Debug_Parser)    printf("Trace: VarDef\n");
                        ListAst* ptr = new ListAst(($1)->ident_name, dynamic_cast<ArrayAst*>($2)->array_list, 
                                                    dynamic_cast<ArrayAst*>($4)->array_list);
                        $$ = ptr;
                    }
                ;

InitVal         : Exp
                    {
                        $$=$1;
                    }
                | LKHD RKHD
                    {
                        ArrayAst* ptr = new ArrayAst();
                        $$=ptr;
                    }
                | LKHD InitValArr RKHD
                    {
                        ArrayAst* ptr = new ArrayAst(dynamic_cast<ArrayAst*>($2)->array_list);
                        $$=ptr;
                    }
                ;
InitValArr      : InitValArr COMMA InitVal
                    {
                        dynamic_cast<ArrayAst*>($1)->append_item($3);
                        $$=$1;
                    }
                | InitVal
                    {
                        ArrayAst* ptr = new ArrayAst();
                        ptr->append_item($1);
                        $$=ptr;
                    }
                ;
ConstDefArr     : ConstDefArr COMMA ConstDef
                    {
                        dynamic_cast<ArrayAst*>($1)->append_item($3);
                        $$=$1;
                    }
                | ConstDef
                    {
                        ArrayAst* ptr = new ArrayAst();
                        ptr->append_item($1);
                        $$=ptr;
                    }
                ;
ConstDef        : IDENT ASSIGN ConstInitVal
                    {
                        DeclAst* ptr = new DeclAst(1, $1->ident_name, $3);
                        $$=ptr;
                    }
                | IDENT ConstExpArr ASSIGN ConstInitVal
                    {
                        if(Debug_Parser)    printf("Trace: ConstDef\n");
                        ListAst* ptr = new ListAst(($1)->ident_name, dynamic_cast<ArrayAst*>($2)->array_list, 
                                                    dynamic_cast<ArrayAst*>($4)->array_list);
                        $$ = ptr;
                    }
                ;
ConstExpArr     : ConstExpArr LKHZ ConstExp RKHZ
                    {
                        if(Debug_Parser)    printf("Trace: ConstExpArr\n");
                        dynamic_cast<ArrayAst*>($1)->append_item($3);
                        $$=$1;
                    }
                | LKHZ ConstExp RKHZ
                    {
                        if(Debug_Parser)    printf("Trace: ConstExpArr\n");
                        ArrayAst* ptr = new ArrayAst();
                        ptr->append_item($2);
                        $$=ptr;
                    }
                ;
ConstInitVal    : ConstExp
                    {
                        $$=$1;
                    }
                | LKHD RKHD
                    {
                        ArrayAst* ptr = new ArrayAst();
                        $$=ptr;
                    }
                | LKHD ConstInitValArr RKHD
                    {
                        ArrayAst* ptr = new ArrayAst(dynamic_cast<ArrayAst*>($2)->array_list);
                        $$=ptr;
                    }
                ;
ConstInitValArr : ConstInitValArr COMMA ConstInitVal
                    {
                        dynamic_cast<ArrayAst*>($1)->append_item($3);
                        $$=$1;
                    }
                | ConstInitVal
                    {
                        ArrayAst* ptr = new ArrayAst();
                        ptr->append_item($1);
                        $$=ptr;
                    }
                ;
ConstExp        : AddExp
                    {
                        $$=$1;
                    }
                ;
AddExp          : MulExp
                    {
                        $$=$1;
                    }
                | AddExp ADD MulExp
                    {
                        BinaryOpAst* ptr = new BinaryOpAst($1, $3, "+", 0, 0);
                        $$ = ptr;
                    }
                | AddExp SUB MulExp
                    {
                        BinaryOpAst* ptr = new BinaryOpAst($1, $3, "-", 0, 0);
                        $$ = ptr;
                    }
                ;
MulExp          : UnaryExp
                    {
                        $$=$1;
                    }
                | MulExp MUL UnaryExp
                    {
                        BinaryOpAst* ptr = new BinaryOpAst($1, $3, "*", 0, 0);
                        $$ = ptr;
                    }
                | MulExp DIV UnaryExp
                    {
                        BinaryOpAst* ptr = new BinaryOpAst($1, $3, "/", 0, 0);
                        $$ = ptr;
                    }
                | MulExp MOD UnaryExp
                    {
                        BinaryOpAst* ptr = new BinaryOpAst($1, $3, "%", 0, 0);
                        $$ = ptr;
                    }
                ;

UnaryExp        : PrimaryExp
                    {
                        $$=$1;
                    }
                | IDENT LKHX RKHX
                    {
                        FunCallAst* ptr = new FunCallAst(($1)->ident_name);
                        $$ = ptr;
                    }
                | IDENT LKHX FuncRParams RKHX
                    {
                        FunCallAst* ptr = new FunCallAst(($1)->ident_name, dynamic_cast<ArrayAst*>($3)->array_list);
                        $$ = ptr;
                    }
                | ADD UnaryExp
                    {
                        UnaryOpAst* ptr = new UnaryOpAst($2, "+");
                        $$ = ptr;
                    }
                | SUB UnaryExp
                    {
                        UnaryOpAst* ptr = new UnaryOpAst($2, "-");
                        $$ = ptr;
                    }
                | NOT UnaryExp
                    {
                        UnaryOpAst* ptr = new UnaryOpAst($2, "!");
                        $$ = ptr;
                    }
                
                ;
            
PrimaryExp      : LKHX Exp RKHX
                    {
                        $$=$2;
                    }
                |  LVal
                    {
                        dynamic_cast<LvalAst*>($1)->is_left_val = 0;
                        $$=$1;
                    }
                | VAL_CONST
                    {
                        if(Debug_Parser)    printf("Trace: PrimaryExp\n");
                        BinaryOpAst* ptr = new BinaryOpAst(nullptr, nullptr, "", ($1)->val, 1);
                        $$ = ptr;
                    }
                ;
FuncRParams     : FuncRParams COMMA Exp
                    {
                        dynamic_cast<ArrayAst*>($1)->append_item($3);
                        $$=$1;
                    }
                | Exp
                    {
                        ArrayAst* ptr = new ArrayAst();
                        ptr->append_item($1);
                        $$=ptr;
                    }
                ;

Exp             : AddExp
                    {
                        $$=$1;
                    }
                ;
LVal            : IDENT
                    {
                        LvalAst* ptr = new LvalAst(($1)->ident_name);
                        $$ = ptr;
                    }
                | IDENT ConstExpArr
                    {
                        if(Debug_Parser)    printf("Trace: LVal\n");
                        LvalAst* ptr = new LvalAst(($1)->ident_name, dynamic_cast<ArrayAst*>($2)->array_list);
                        $$ = ptr;
                    }
                ;

FuncDef         : VOID IDENT LKHX RKHX Block
                    {
                        BlockAst* tmp_ptr = dynamic_cast<BlockAst*>($5);
                        int flag = 0;
                        for (auto i: tmp_ptr->list_stmts){
                            if (i->node_type == AstType::kReturn){
                                flag = 1; break;
                            } 
                        }
                        if (flag == 0){
                            tmp_ptr->append_stmt(new ReturnAst(nullptr, nullptr));
                        }
                        FunDefAst* ptr = new FunDefAst(0, ($2)->ident_name, tmp_ptr);
                        $$ = ptr;
                    }
                | INT IDENT LKHX RKHX Block
                    {
                        FunDefAst* ptr = new FunDefAst(1, ($2)->ident_name, $5);
                        $$ = ptr;
                    }
                | VOID IDENT LKHX FuncFParams RKHX Block
                    {
                        if(Debug_Parser)    printf("Trace: FuncDef\n");

                        BlockAst* tmp_ptr = dynamic_cast<BlockAst*>($6);
                        int flag = 0;
                        for (auto i: tmp_ptr->list_stmts){
                            if (i->node_type == AstType::kReturn){
                                flag = 1; break;
                            } 
                        }
                        if (flag == 0){
                            tmp_ptr->append_stmt(new ReturnAst(nullptr, nullptr));
                        }

                        FunDefAst* ptr = new FunDefAst(0, ($2)->ident_name, tmp_ptr, dynamic_cast<ArrayAst*>($4)->array_list);
                        $$ = ptr;
                    }
                | INT IDENT LKHX FuncFParams RKHX Block
                    {
                        if(Debug_Parser)    printf("Trace: FuncDef\n");
                        FunDefAst* ptr = new FunDefAst(1, ($2)->ident_name, $6, dynamic_cast<ArrayAst*>($4)->array_list);
                        $$ = ptr;
                    }
                ;

FuncFParams     : FuncFParams COMMA FuncFParam
                    {
                        dynamic_cast<ArrayAst*>($1)->append_item($3);
                        $$ = $1;
                    }
                | FuncFParam
                    {
                        ArrayAst* ptr = new ArrayAst();
                        ptr->append_item($1);
                        $$ = ptr;
                    }
                ;

FuncFParam      : INT IDENT
                    {
                        if(Debug_Parser)    printf("Trace: FuncFParam\n");
                        DeclAst* ptr = new DeclAst(1, ($2)->ident_name);
                        $$ = ptr;
                    }
                | INT IDENT LKHZ RKHZ 
                    {
                        if(Debug_Parser)    printf("Trace: FuncFParam\n");
                        ArrayAst* tmp_ptr = new ArrayAst();
                        tmp_ptr->append_item(new BinaryOpAst(nullptr, nullptr, "", 1, 1));
                        ListAst* ptr = new ListAst(($2)->ident_name, tmp_ptr->array_list);
                        $$ = ptr;
                    }
                | INT IDENT LKHZ RKHZ ConstExpArr
                    {
                        if(Debug_Parser)    printf("Trace: FuncFParam\n");
                        ArrayAst* tmp_ptr = dynamic_cast<ArrayAst*>($5);
                        tmp_ptr->array_list.insert(tmp_ptr->array_list.begin(), new BinaryOpAst(nullptr, nullptr, "", 1, 1));
                        ListAst* ptr = new ListAst(($2)->ident_name, tmp_ptr->array_list);
                        $$ = ptr;
                    }
                ;


Block           : LKHD RKHD 
                    {
                        BlockAst* ptr = new BlockAst();
                        $$=ptr;
                    }
                | LKHD BlockItems RKHD 
                    {
                        BlockAst* ptr = new BlockAst(dynamic_cast<BlockAst*>($2)->list_stmts);
                        $$=ptr;
                    }
                ;

BlockItems      : BlockItems BlockItem
                    {
                        dynamic_cast<BlockAst*>($1)->append_stmt($2);
                        $$=$1;
                    }
                | BlockItem
                    {
                        BlockAst* ptr = new BlockAst;
                        ptr->append_stmt($1);
		                $$ = ptr;
                    }
                ;

BlockItem       : Decl
                    {
                        $$ = $1;
                    }
                | Stmt
                    {
                        $$ = $1;
                    }
                ;

Stmt            : LVal ASSIGN Exp SEMI
                    {
                        if(Debug_Parser)    printf("Trace: Stmt\n");
                        dynamic_cast<LvalAst*>($1)->is_left_val = 1;
                        AssignAst* ptr = new AssignAst($1, $3);
                        $$ = ptr;
                    }
                | SEMI
                    {
                        ;
                    }
                | Exp SEMI
                    {
                        $$=$1;
                    }
                | Block
                    {
                        $$=$1;
                    }
                | IF LKHX Cond RKHX Stmt
                    {
                        IfAst* ptr = new IfAst($3, $5, nullptr);
                        $$ = ptr;
                    }
                | IF LKHX Cond RKHX Stmt ELSE Stmt
                    {
                        IfAst* ptr = new IfAst($3, $5, $7);
                        $$ = ptr;
                    }
                | WHILE LKHX Cond RKHX Stmt
                    {
                        WhileAst* ptr = new WhileAst($3, $5);
                        $$ = ptr;
                    }
                | BREAK SEMI
                    {
                        BreakAst* ptr = new BreakAst();
                        $$ = ptr;
                    }
                | CONTINUE SEMI
                    {
                        ContinueAst* ptr = new ContinueAst();
                        $$ = ptr;
                    }
                | RETURN SEMI
                    {
                        ReturnAst* ptr = new ReturnAst(nullptr, nullptr);
                        $$ = ptr;
                    }
                | RETURN Exp SEMI
                    {
                        ReturnAst* ptr = new ReturnAst(nullptr, $2);
                        $$ = ptr;
                    }
                ;

Cond            : LOrExp
                    {
                        $$=$1;
                    }
                ;

LOrExp          : LAndExp
                    {
                        $$=$1;
                    }
                | LOrExp LOR LAndExp
                    {
                        BinaryOpAst* ptr = new BinaryOpAst($1, $3, "||", 0, 0);
                        $$ = ptr; 
                    }
                ;
LAndExp         : EqExp
                    {
                        $$ = $1;
                    }
                | LAndExp LAND EqExp
                    {
                        BinaryOpAst* ptr = new BinaryOpAst($1, $3, "&&", 0, 0);
                        $$ = ptr;
                    }
                ;

EqExp           : RelExp
                    {
                        $$ = $1;
                    }
                | EqExp EQ RelExp
                    {
                        BinaryOpAst* ptr = new BinaryOpAst($1, $3, "==", 0, 0);
                        $$ = ptr;
                    }
                | EqExp NE RelExp
                    {
                        BinaryOpAst* ptr = new BinaryOpAst($1, $3, "!=", 0, 0);
                        $$ = ptr;
                    }
                ;

RelExp          : AddExp 
                    {
                        $$ = $1;
                    }
                | RelExp LT AddExp
                    {
                        BinaryOpAst* ptr = new BinaryOpAst($1, $3, "<", 0, 0);
                        $$ = ptr;
                    }
                | RelExp GT AddExp
                    {
                        BinaryOpAst* ptr = new BinaryOpAst($1, $3, ">", 0, 0);
                        $$ = ptr;
                    }
                | RelExp LE AddExp
                    {
                        BinaryOpAst* ptr = new BinaryOpAst($1, $3, "<=", 0, 0);
                        $$ = ptr;
                    }
                | RelExp GE AddExp
                    {
                        BinaryOpAst* ptr = new BinaryOpAst($1, $3, ">=", 0, 0);
                        $$ = ptr;
                    }
                ;

%%

void yyerror(BaseAst**, const char *){
    printf("Syntax error at line %d. \n", yylineno);
};

int yywrap(void){
    return 1;
}