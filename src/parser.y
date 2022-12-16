%code top{
    #include <iostream>
    #include <assert.h>
    #include <map>
    #include <vector>
    #include "parser.h"
    using namespace std;
    extern Ast ast;
    int yylex();
    int yyerror( char const * );

    map<std::string, ExprNode*> idlist;
    map<std::string, int> arraylist;
    std::vector<Type*> paramtypes;
    vector<SymbolEntry*> sesymlist;
    std::vector<std::string> paramsymbols;
    std::vector<ExprNode*> globle_tmp_paramcalls;
    bool isret=false;
    
    bool alarm=false;
    extern int yylineno;
    string curr_func="";

    vector<BreakStmt*> breakList;
    vector<ContinueStmt*> continueList;
}

%code requires {
    #include "Ast.h"
    #include "SymbolTable.h"
    #include "Type.h"
}

%union {
    int itype;
    char* strtype;
    StmtNode* stmttype;
    ExprNode* exprtype;
    Type* type;
}

%start Program
%token <strtype> ID 
%token <itype> INTEGER
%token IF ELSE WHILE
%token INT BOOL VOID
%token LPAREN RPAREN LBRACKET RBRACKET LBRACE RBRACE SEMICOLON COMMA
%token NOT AADD SSUB
%token MUL DIV MOD ADD SUB OR AND LESS MORE EQUAL MORE_E LESS_E NOT_EQUAL ASSIGN
%token RETURN CONST
%token BREAK CONTINUE


%nterm <stmttype> Stmts Stmt AssignStmt BlockStmt IfStmt WhileStmt AssignExpr ReturnStmt DeclStmt ExprStmt BreakStmt ContinueStmt FuncDef
%nterm <exprtype> Cond Exp MulExp AddExp LOrExp PrimaryExp LVal EqlExp RelExp LAndExp preSinExp sufSinExp FuncCall
%nterm <type> Type
%nterm IDList

%precedence THEN
%precedence ELSE
%%
Program
    : Stmts {
        //cout<<"Stmts"<<endl;
        ast.setRoot($1);
        //ast.output();
    }
    ;
Stmts
    : Stmt {$$=$1;}
    | Stmts Stmt{
        //cout<<"Stmts1"<<endl;
        $$ = new SeqNode($1, $2);
        
    }
    ;
Stmt
    : AssignStmt {$$=$1;}
    | BlockStmt {$$=$1;}
    | IfStmt {$$=$1;}
    | WhileStmt {$$=$1;}
    | ReturnStmt {$$=$1;}
    | DeclStmt {$$=$1;}
    | FuncDef {$$=$1;}
    | ExprStmt{$$ = $1;}
    | SEMICOLON {$$ = new EmptyStmt();}
    | BreakStmt{$$=$1;}
    | ContinueStmt{$$=$1;}
    ;

BreakStmt
    :
    BREAK SEMICOLON{
        BreakStmt* bs = new BreakStmt();
        breakList.push_back(bs);
        $$ = bs;
    }
    ;

ContinueStmt
    :
    CONTINUE SEMICOLON{
        ContinueStmt* cs = new ContinueStmt();
        continueList.push_back(cs);
        $$ = cs;
    }
    ;

LVal
    : ID {
        SymbolEntry *se;
        se = identifiers->lookup($1);

        //类型检查：使用前未声明
        if(se == nullptr)
        {
            cout<<"line: "<<yylineno<<endl;
            fprintf(stderr, "identifier \"%s\" is undefined\n", (char*)$1);
            delete [](char*)$1;
            cout<<se->toStr()<<endl;
            assert(se != nullptr);
        }

        if(se->getType()->isArray()){
            //$$ = (ExprNode*)(((IdentifierSymbolEntry*)se)->getParent());
            SymbolEntry *offset_se = new ConstantSymbolEntry(TypeSystem::intType, 0);//offset为常数
            Constant *offset = new Constant(offset_se);
            $$ = new ArrayItem(se, offset, true);
        }
        else{
            $$ = new Id(se);
        }
        delete []$1;
    }
    |
    ID LBRACKET INTEGER RBRACKET {
        SymbolEntry *array_se;
        array_se = identifiers->lookup($1);
        
        SymbolEntry *offset_se = new ConstantSymbolEntry(TypeSystem::intType, $3);//offset为常数
        Constant *offset = new Constant(offset_se);

        if(array_se == nullptr)
        {
            fprintf(stderr, "identifier \"%s\" is undefined\n", (char*)$1);
            delete [](char*)$1;
            assert(array_se != nullptr);
        }
        $$ = new ArrayItem(array_se, offset);
        cout<<"--------------array_se:"<<array_se<<endl;
        ((IdentifierSymbolEntry*)array_se)->setParent($$);
        delete []$1;
    }
    |
    ID LBRACKET ID RBRACKET {
        SymbolEntry *array_se;
        array_se = identifiers->lookup($1);

        SymbolEntry *offset_se=identifiers->lookup($3);
        Id *offset = new Id(offset_se);

        if(array_se == nullptr)
        {
            fprintf(stderr, "identifier \"%s\" is undefined\n", (char*)$1);
            delete [](char*)$1;
            assert(array_se != nullptr);
        }
        $$ = new ArrayItem(array_se, offset);
        ((IdentifierSymbolEntry*)array_se)->setParent($$);
        delete []$1;
    }
    ;
ExprStmt
    :
    Exp SEMICOLON{
        $$ = new ExprStmt($1);
        //std::cout<<"ExprStmt"<<endl;
    }
    ;
AssignStmt
    :
    AssignExpr SEMICOLON {
        $$ = $1;
    }
    ;
AssignExpr
    :
    LVal ASSIGN{alarm=false;} Exp {
        //类型检查：函数返回值为void（空）
        if(alarm){
            // cout<<"error"<<endl;
            cout<<"lineno: "<<yylineno+1<<endl;
            alarm=false;                          
            fprintf(stderr, "assign error: operation's type should not be <void>.\n");
            //assert(alarm);
        }
        SymbolEntry *se = $1->getSymPtr();
        $$ = new AssignStmt($1, $4);
    }
    ;
BlockStmt
    :   LBRACE 
        {identifiers = new SymbolTable(identifiers);} 
        Stmts RBRACE 
        {
            $$ = new CompoundStmt($3);
            SymbolTable *top = identifiers;
            identifiers = identifiers->getPrev();
            delete top;
        }
    |
    LBRACE RBRACE
    {
        $$ = new EmptyStmt();
    }
    ;
IfStmt
    : IF LPAREN Cond RPAREN Stmt %prec THEN {
        $$ = new IfStmt($3, $5);
    }
    | IF LPAREN Cond RPAREN Stmt ELSE Stmt {
        $$ = new IfElseStmt($3, $5, $7);
    }
    ;
WhileStmt
    : 
    WHILE {
        breakList.clear();
        continueList.clear();
    }
    LPAREN Cond RPAREN Stmt{
        $$ = new WhileStmt($4, $6);
        for(int i=0;i<(int)(breakList.size());i++){
            breakList[i]->setParent($$);
        }
        for(int i=0;i<(int)(continueList.size());i++){
            continueList[i]->setParent($$);
        }
    }   
    ;

ReturnStmt
    :
    RETURN SEMICOLON{

        $$ = new ReturnStmt();
    }
    |
    RETURN Exp SEMICOLON{
        isret=true;

        $$ = new ReturnStmt($2);
    }
    ;
Exp
    :
    LOrExp {
        $$ = $1;//std::cout<<"LOrExp"<<endl;
    }
    ;
Cond
    :
    Exp 
    {
        //类型检查：int->bool
        if($1->getSymPtr()->getType()->toStr()=="i32"){
            cout<<"line:"<<yylineno+1<<endl;
            cout<<"cond expr should be bool!"<<endl;
        }

        $$ = $1;
    }
    ;

PrimaryExp
    :
    LVal {
        $$ = $1;
        //std::cout<<"LVal"<<endl;
    }
    |
    INTEGER {
        SymbolEntry *se = new ConstantSymbolEntry(TypeSystem::intType, $1);
        $$ = new Constant(se);
       // std::cout<<"INTEGER"<<$1<<endl;
    }
    |
    LPAREN Exp RPAREN {
        $$ = $2;
    }
    |
    FuncCall {
        //类型检查：返回值是否为void
        SymbolEntry* se = ((FunctionCall*)$1)->getSymPtr();
        if(((FunctionType*)(se->getType()))->getRetType()->isVoid()){
            // cout<<"line:"<<yylineno+1<<endl;
            // cout<<"Exp should not be void!"<<endl;
            alarm=true;
        }

        $$ = $1;
    }
    ;

sufSinExp
    :
    PrimaryExp{
        //类型检查：函数返回值为void（空）
        SymbolEntry* se1=$1->getSymPtr();
        

        if(((se1->getType()))->isFunc()){
            if(((FunctionType*)(se1->getType()))->getRetType()->isVoid())
            {               
                alarm=true; 
                //fprintf(stderr, "error: operation's type should not be <void>.");
                //assert(!((FunctionType*)(se1->getType()))->getRetType()->isVoid());
            }
        }

        $$ = $1;
        //std::cout<<"PrimaryExp"<<endl;
    }
    |
    sufSinExp AADD {
        //类型检查：函数返回值为void（空）
        SymbolEntry* se1=$1->getSymPtr();
        

        if(((se1->getType()))->isFunc()){
            if(((FunctionType*)(se1->getType()))->getRetType()->isVoid())
            {
                
                alarm=true; 
                //fprintf(stderr, "error: operation's type should not be <void>.");
                //assert(!((FunctionType*)(se1->getType()))->getRetType()->isVoid());
            }
        }

        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new sufSingleExpr(se, $1, sufSingleExpr::AADD);
    }
    | 
    sufSinExp SSUB {
        //类型检查：函数返回值为void（空）
        SymbolEntry* se1=$1->getSymPtr();
        

        if(((se1->getType()))->isFunc()){
            if(((FunctionType*)(se1->getType()))->getRetType()->isVoid())
            {
                
                alarm=true; 
                //fprintf(stderr, "error: operation's type should not be <void>.");
                //assert(!((FunctionType*)(se1->getType()))->getRetType()->isVoid());
            }
        }

        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new sufSingleExpr(se, $1, sufSingleExpr::SSUB);
    }
    
    ;
preSinExp
    :
    sufSinExp {
        $$ = $1;
        //std::cout<<"sufSinExp"<<endl;
    }
    |
    AADD preSinExp {
        //类型检查：函数返回值为void（空）
        SymbolEntry* se1=$2->getSymPtr();
        

        if(((se1->getType()))->isFunc()){
            if(((FunctionType*)(se1->getType()))->getRetType()->isVoid())
            {
                
                alarm=true; 
                //fprintf(stderr, "error: operation's type should not be <void>.");
                //assert(!((FunctionType*)(se1->getType()))->getRetType()->isVoid());
            }
        }

        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new preSingleExpr(se, preSingleExpr::AADD, $2);
    }
    | 
    SSUB preSinExp{
        //类型检查：函数返回值为void（空）
        SymbolEntry* se1=$2->getSymPtr();
        

        if(((se1->getType()))->isFunc()){
            if(((FunctionType*)(se1->getType()))->getRetType()->isVoid())
            {
                
                alarm=true; 
                //fprintf(stderr, "error: operation's type should not be <void>.");
                //assert(!((FunctionType*)(se1->getType()))->getRetType()->isVoid());
            }
        }

        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new preSingleExpr(se, preSingleExpr::SSUB, $2);
    }
    |
    NOT preSinExp{
        //是不是应该存布尔？
        //类型检查：int->bool
        if(!$2->getSymPtr()->isTemporary())
            cout<<"wrong int in line:"<<yylineno+1<<endl;

        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        $$ = new preSingleExpr(se, preSingleExpr::NOT, $2);
    }
    |
    ADD preSinExp {
        //+出现不对表达式的值产生影响 直接忽略
        // SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        // $$ = new preSingleExpr(se, preSingleExpr::ADD, $2);
        $$=$2;
    }
    |
    SUB preSinExp{
        if($2->getSymPtr()->isConstant()){
            SymbolEntry *se = new ConstantSymbolEntry(TypeSystem::intType, -1*((ConstantSymbolEntry*)($2->getSymPtr()))->getValue());
            $$ = new Constant(se);
        }
        else{
            SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
            $$ = new preSingleExpr(se, preSingleExpr::SUB, $2);
        }
    }
    ; 
MulExp
    :
    preSinExp {
        //类型检查：函数返回值为void（空）
        SymbolEntry* se1=$1->getSymPtr();
        

        if(((se1->getType()))->isFunc()){
            if(((FunctionType*)(se1->getType()))->getRetType()->isVoid())
            {
                
                alarm=true; 
                //fprintf(stderr, "error: operation's type should not be <void>.");
                //assert(!((FunctionType*)(se1->getType()))->getRetType()->isVoid());
            }
        }

        $$ = $1;
        //std::cout<<"MulExp"<<endl;
        }
    |
    MulExp MUL preSinExp
    {
        //类型检查：函数返回值为void（空）
        SymbolEntry* se1=$3->getSymPtr();
        

        if(((se1->getType()))->isFunc()){
            if(((FunctionType*)(se1->getType()))->getRetType()->isVoid())
            {               
                alarm=true; 
                //fprintf(stderr, "error: operation's type should not be <void>.");
                //assert(!((FunctionType*)(se1->getType()))->getRetType()->isVoid());
            }
        }

        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::MUL, $1, $3);
    }
    |
    MulExp DIV preSinExp
    {
        //类型检查：函数返回值为void（空）
        SymbolEntry* se1=$3->getSymPtr();
        

        if(((se1->getType()))->isFunc()){
            if(((FunctionType*)(se1->getType()))->getRetType()->isVoid())
            {
                
                alarm=true; 
                //fprintf(stderr, "error: operation's type should not be <void>.");
                //assert(!((FunctionType*)(se1->getType()))->getRetType()->isVoid());
            }
        }

        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::DIV, $1, $3);
    }
    |
    MulExp MOD preSinExp
    {
        //类型检查：函数返回值为void（空）
        SymbolEntry* se1=$3->getSymPtr();
        

        if(((se1->getType()))->isFunc()){
            if(((FunctionType*)(se1->getType()))->getRetType()->isVoid())
            {
                
                alarm=true; 
                //fprintf(stderr, "error: operation's type should not be <void>.");
                //assert(!((FunctionType*)(se1->getType()))->getRetType()->isVoid());
            }
        }

        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::MOD, $1, $3);
    }
    ;
AddExp
    :
    MulExp {
        //类型检查：函数返回值为void（空）
        SymbolEntry* se1=$1->getSymPtr();
        

        if(((se1->getType()))->isFunc()){
            if(((FunctionType*)(se1->getType()))->getRetType()->isVoid())
            {
                
                alarm=true; 
                //fprintf(stderr, "error: operation's type should not be <void>.");
                //assert(!((FunctionType*)(se1->getType()))->getRetType()->isVoid());
            }
        }

        $$ = $1;//std::cout<<"add2"<<endl;
    }
    |
    AddExp ADD MulExp
    {
       // std::cout<<"add1"<<endl;
       SymbolEntry* se1=$3->getSymPtr();
        

        if(((se1->getType()))->isFunc()){
            if(((FunctionType*)(se1->getType()))->getRetType()->isVoid())
            {
                
                alarm=true; 
                //fprintf(stderr, "error: operation's type should not be <void>.");
                //assert(!((FunctionType*)(se1->getType()))->getRetType()->isVoid());
            }
        }
        
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::ADD, $1, $3);
    }
    |
    AddExp SUB MulExp
    {
        //类型检查：函数返回值为void（空）
        SymbolEntry* se1=$3->getSymPtr();
        

        if(((se1->getType()))->isFunc()){
            if(((FunctionType*)(se1->getType()))->getRetType()->isVoid())
            {
                
                alarm=true; 
                //fprintf(stderr, "error: operation's type should not be <void>.");
                //assert(!((FunctionType*)(se1->getType()))->getRetType()->isVoid());
            }
        }
        
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::SUB, $1, $3);
    }
    ;
RelExp
    :
    AddExp {
        //类型检查：函数返回值为void（空）
        SymbolEntry* se1=$1->getSymPtr();
        

        if(((se1->getType()))->isFunc()){
            if(((FunctionType*)(se1->getType()))->getRetType()->isVoid())
            {
                
                alarm=true; 
                //fprintf(stderr, "error: operation's type should not be <void>.");
                //assert(!((FunctionType*)(se1->getType()))->getRetType()->isVoid());
            }
        }

        $$ = $1;//std::cout<<"AddExp"<<endl;
    }
    |
    RelExp LESS AddExp
    {
        //类型检查：函数返回值为void（空）
        SymbolEntry* se1=$3->getSymPtr();
        

        if(((se1->getType()))->isFunc()){
            if(((FunctionType*)(se1->getType()))->getRetType()->isVoid())
            {
                
                alarm=true; 
                //fprintf(stderr, "error: operation's type should not be <void>.");
                //assert(!((FunctionType*)(se1->getType()))->getRetType()->isVoid());
            }
        }

        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::LESS, $1, $3);
    }
    |
    RelExp MORE AddExp
    {
        //类型检查：函数返回值为void（空）
        SymbolEntry* se1=$3->getSymPtr();
        

        if(((se1->getType()))->isFunc()){
            if(((FunctionType*)(se1->getType()))->getRetType()->isVoid())
            {
                
                alarm=true; 
                //fprintf(stderr, "error: operation's type should not be <void>.");
                //assert(!((FunctionType*)(se1->getType()))->getRetType()->isVoid());
            }
        }
        
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::MORE, $1, $3);
    }
    |
    RelExp LESS_E AddExp
    {
        //类型检查：函数返回值为void（空）
        SymbolEntry* se1=$3->getSymPtr();
        

        if(((se1->getType()))->isFunc()){
            if(((FunctionType*)(se1->getType()))->getRetType()->isVoid())
            {
                
                alarm=true; 
                //fprintf(stderr, "error: operation's type should not be <void>.");
                //assert(!((FunctionType*)(se1->getType()))->getRetType()->isVoid());
            }
        }
        
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::LESS_E, $1, $3);
    }
    |
    RelExp MORE_E AddExp
    {
        //类型检查：函数返回值为void（空）
        SymbolEntry* se1=$3->getSymPtr();
        

        if(((se1->getType()))->isFunc()){
            if(((FunctionType*)(se1->getType()))->getRetType()->isVoid())
            {
                
                alarm=true; 
                //fprintf(stderr, "error: operation's type should not be <void>.");
                //assert(!((FunctionType*)(se1->getType()))->getRetType()->isVoid());
            }
        }
        
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::MORE_E, $1, $3);
    }
    ;
EqlExp  
    :
    RelExp{
        //类型检查：函数返回值为void（空）
        SymbolEntry* se1=$1->getSymPtr();
        

        if(((se1->getType()))->isFunc()){
            if(((FunctionType*)(se1->getType()))->getRetType()->isVoid())
            {
                
                alarm=true; 
                //fprintf(stderr, "error: operation's type should not be <void>.");
                //assert(!((FunctionType*)(se1->getType()))->getRetType()->isVoid());
            }
        }

        $$ = $1;//std::cout<<"RelExp"<<endl;
    }
    |
    EqlExp EQUAL RelExp{
        //类型检查：函数返回值为void（空）
        SymbolEntry* se1=$3->getSymPtr();
        

        if(((se1->getType()))->isFunc()){
            if(((FunctionType*)(se1->getType()))->getRetType()->isVoid())
            {
                
                alarm=true; 
                //fprintf(stderr, "error: operation's type should not be <void>.");
                //assert(!((FunctionType*)(se1->getType()))->getRetType()->isVoid());
            }
        }
        
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::EQUAL, $1, $3);
    }
    |
    EqlExp NOT_EQUAL RelExp{
        //类型检查：函数返回值为void（空）
        SymbolEntry* se1=$3->getSymPtr();
        

        if(((se1->getType()))->isFunc()){
            if(((FunctionType*)(se1->getType()))->getRetType()->isVoid())
            {
                
                alarm=true; 
                //fprintf(stderr, "error: operation's type should not be <void>.");
                //assert(!((FunctionType*)(se1->getType()))->getRetType()->isVoid());
            }
        }
        
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::NOT_EQUAL, $1, $3);
    }
    ;
LAndExp
    :
    EqlExp {
        //类型检查：函数返回值为void（空）
        SymbolEntry* se1=$1->getSymPtr();
        
        if(((se1->getType()))->isFunc()){
            if(((FunctionType*)(se1->getType()))->getRetType()->isVoid())
            {
                
                alarm=true; 
                //fprintf(stderr, "error: operation's type should not be <void>.");
                //assert(!((FunctionType*)(se1->getType()))->getRetType()->isVoid());
            }
        }

        $$ = $1;//std::cout<<"RelExp"<<endl;
    }
    |
    LAndExp AND EqlExp
    {
        //类型检查：函数返回值为void（空）
        SymbolEntry* se1=$3->getSymPtr();
        
        //类型检查：int->bool
        if($3->getSymPtr()->getType()->toStr()=="i32"){
            cout<<"line:"<<yylineno+2<<endl;
            cout<<"cond expr should be bool!"<<endl;
        }

        if(((se1->getType()))->isFunc()){
            if(((FunctionType*)(se1->getType()))->getRetType()->isVoid())
            {
                
                alarm=true; 
                //fprintf(stderr, "error: operation's type should not be <void>.");
                //assert(!((FunctionType*)(se1->getType()))->getRetType()->isVoid());
            }
        }
        
        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::AND, $1, $3);
    }
    ;
LOrExp
    :
    LAndExp {
        //类型检查：函数返回值为void（空）
        SymbolEntry* se1=$1->getSymPtr();
        
        if(((se1->getType()))->isFunc()){
            if(((FunctionType*)(se1->getType()))->getRetType()->isVoid())
            {
                
                alarm=true; 
                //fprintf(stderr, "error: operation's type should not be <void>.");
                //assert(!((FunctionType*)(se1->getType()))->getRetType()->isVoid());
            }
        }

        $$ = $1;//std::cout<<"LAndExp"<<endl;
    }
    |
    LOrExp OR LAndExp
    {
        cout<<"OR!"<<endl;
        //类型检查：函数返回值为void（空）
        SymbolEntry* se1=$3->getSymPtr();
        
        //类型检查：int->bool
        if($3->getSymPtr()->getType()->toStr()=="i32"){
            cout<<"line:"<<yylineno+2<<endl;
            cout<<"cond expr should be bool!"<<endl;
        }

        if(((se1->getType()))->isFunc()){
            if(((FunctionType*)(se1->getType()))->getRetType()->isVoid())
            {                
                alarm=true; 
                //fprintf(stderr, "error: operation's type should not be <void>.");
                //assert(!((FunctionType*)(se1->getType()))->getRetType()->isVoid());
            }
        }
        

        SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
        $$ = new BinaryExpr(se, BinaryExpr::OR, $1, $3);
    }
    ;
Type
    : INT {
        $$ = TypeSystem::intType;
    }
    |
    BOOL{
        $$ = TypeSystem::boolType;
    }
    | VOID {
        $$ = TypeSystem::voidType;
    }
    | CONST Type {
        // cout<<"ha"<<endl;
        // $$ = new IntType(4, 1);
        $$ = TypeSystem::constType;
    }
    ;
Array
    :
    ID LBRACKET INTEGER RBRACKET
    {
        //cout<<"hi array"<<endl;
        arraylist[$1]=$3;
    }
    ;
IDList
    :
    ID COMMA{
        idlist[$1]=nullptr;
    }
    |
    ID ASSIGN Exp COMMA{
        idlist[$1]=$3;
    }
    |
    Array COMMA{
    }
    |
    IDList ID COMMA{
        idlist[$2]=nullptr;
    }
    |
    IDList ID ASSIGN Exp COMMA{
        idlist[$2]=$4;
    }
    |
    IDList Array COMMA{
        
    }
    |
    IDList ID{
        //结束
        idlist[$2]=nullptr;
    }
    |
    IDList ID ASSIGN Exp{
        //结束
        idlist[$2]=$4;
    }
    |
    IDList Array {
        
    }
    ;
DeclStmt
    :
    Type ID SEMICOLON {
        // cout<<"hhh"<<endl;
        SymbolEntry *se;
        //类型检查：是否重复声明
        se = identifiers->lookup($2);
        if(se != nullptr)
        {
            cout<<"line:"<<yylineno+1<<endl;
            fprintf(stderr, "identifier \"%s\" is redefined\n", (char*)$2);
            assert(se == nullptr);
        }
        //se = 
        se = new IdentifierSymbolEntry($1, $2, identifiers->getLevel());
        identifiers->install($2, se);
        DeclStmt* tmp = new DeclStmt();
        tmp->insert(new Id(se));
        $$ = tmp; 
        delete []$2;
    }
    |
    Type ID ASSIGN Exp SEMICOLON{

        //类型检查：函数返回值为void（空）
        if(alarm){
            // cout<<"error"<<endl;
            cout<<"lineno: "<<yylineno+1<<endl;
            alarm=false;                          
            fprintf(stderr, "assign error: operation's type should not be <void>.\n");
            //assert(alarm);
        }

        //应该加一个value值 在entry里也要加
        SymbolEntry *se;

        //类型检查：是否重复声明
        se = identifiers->lookup($2);
        if(se != nullptr)
        {
            cout<<"line:"<<yylineno+1<<endl;
            fprintf(stderr, "identifier \"%s\" is redefined\n", (char*)$2);
            //assert(se == nullptr);
        }

        se = new IdentifierSymbolEntry($1, $2, identifiers->getLevel());
        identifiers->install($2, se);
        DeclStmt* tmp = new DeclStmt();
        tmp->insert(new Id(se),$4);
        $$ = tmp;       
        delete []$2;
    }
    |
    Type Array SEMICOLON{
        //处理数组声明
        std::map <std::string, int>::iterator it1=arraylist.begin();
        SymbolEntry *se1;
        DeclStmt* tmp = new DeclStmt();
        while(it1!=arraylist.end()){
            // cout<<it->first<<endl;
            Type* arrayType;
            arrayType=new ArrayType($1, it1->second);
            se1 = new IdentifierSymbolEntry(arrayType, it1->first, identifiers->getLevel());
            identifiers->install(it1->first, se1);
            tmp->insert(new Id(se1));
            it1++;
        }
        $$ = tmp;
        arraylist.clear();
    }
    |
    Type IDList SEMICOLON {
        cout<<"hhh"<<endl;
        DeclStmt* tmp = new DeclStmt();

        //处理普通变量声明
        std::map <std::string, ExprNode*>::iterator it=idlist.begin();
        SymbolEntry *se;
        while(it!=idlist.end()){
            // cout<<it->first<<endl;
            se = new IdentifierSymbolEntry($1, it->first, identifiers->getLevel());
            identifiers->install(it->first, se);
            tmp->insert(new Id(se), it->second);
            it++;
        }

        //处理数组声明
        std::map <std::string, int>::iterator it1=arraylist.begin();
        SymbolEntry *se1;
        while(it1!=arraylist.end()){
            // cout<<it->first<<endl;
            Type* arrayType;
            arrayType=new ArrayType($1, it1->second);
            se1 = new IdentifierSymbolEntry(arrayType, it1->first, identifiers->getLevel());
            identifiers->install(it1->first, se1);
            tmp->insert(new Id(se1));
            it1++;
        }

        $$ = tmp;
        idlist.clear();//存完以后清空
        arraylist.clear();
        //delete []$2;
    }
    ;
ParamDefs:
    Type ID{
        // paramtypes.clear();
        // paramsymbols.clear();
        paramtypes.push_back($1);
        paramsymbols.push_back($2);
    }
    |
    Type ID LBRACKET INTEGER RBRACKET{        
        paramtypes.push_back(new ArrayType($1, $4));
        paramsymbols.push_back($2);
    }
    |
    Type ID LBRACKET RBRACKET{        
        paramtypes.push_back(new ArrayType($1));
        paramsymbols.push_back($2);
    }
    |
    ParamDefs COMMA Type ID{
        paramtypes.push_back($3);
        paramsymbols.push_back($4);
    }
    |
    ParamDefs COMMA Type ID LBRACKET INTEGER RBRACKET{
        paramtypes.push_back(new ArrayType($3, $6));
        paramsymbols.push_back($4);
    }
    |
    ParamDefs COMMA Type ID LBRACKET RBRACKET{
        paramtypes.push_back(new ArrayType($3));
        paramsymbols.push_back($4);
    }
    ;
FuncDef
    :
    Type ID 
    LPAREN ParamDefs RPAREN
    {
        isret=false;

        //类型检查：是否重复定义（可能有问题，声明没有处理）
        SymbolEntry *se1=identifiers->lookup($2);
        //cout<<((FunctionType*)(se1->getType()))->num_params()<<endl;
        //cout<<(int)(paramtypes.size())<<endl;
        if(se1){
            if(((FunctionType*)(se1->getType()))->num_params()==(int)(paramtypes.size())){
                cout<<"line: "<<yylineno<<endl;
                fprintf(stderr, "function define error: the function is redefined.\n");
                //assert(se1);
            }
        }

        //类型检查：检查return
        curr_func=$2;


        Type *funcType;
        //std::vector<Type*> params;
        //params.swap(paramtypes);
        funcType = new FunctionType($1,paramtypes);
        SymbolEntry *se = new IdentifierSymbolEntry(funcType, $2, identifiers->getLevel());
        identifiers->install($2, se);
        identifiers = new SymbolTable(identifiers);

        
        for(int i=0;i<int(paramsymbols.size());i++){
            // cout<<paramsymbols[i]<<endl;
            SymbolEntry *sesym = new IdentifierSymbolEntry(paramtypes[i], paramsymbols[i], identifiers->getLevel());
            sesymlist.push_back(sesym);
            identifiers->install(paramsymbols[i], sesym);
        }
    }
    BlockStmt
    {

        //类型检查：检查返回值类型
        if($1->isVoid()&&isret){
            cout<<"line:"<<yylineno<<endl;
            cout<<"function\""<<$2<<"\""<<"should return void!"<<endl;
        }
        else if (!$1->isVoid()&&!isret){
            cout<<"line:"<<yylineno<<endl;
            cout<<"function\""<<$2<<"\""<<"should return an int value!"<<endl;
        }

        SymbolEntry *se;
        se = identifiers->lookup($2);
        assert(se != nullptr);

        //改动
        vector<Id*> paramlist;
        for(int i=0;i<int(paramsymbols.size());i++){
            //SymbolEntry *sesym = new IdentifierSymbolEntry(paramtypes[i], paramsymbols[i], identifiers->getLevel());
            Id *id = new Id(sesymlist[i]);//不能new！！一定要保持符号表表项
            paramlist.push_back(id);
        }
        $$ = new FunctionDef(se, $7, paramlist, paramsymbols);

        SymbolTable *top = identifiers;
        identifiers = identifiers->getPrev();

        std::vector<Type*> params;
        params.swap(paramtypes);
        std::vector<std::string> params1;
        params1.swap(paramsymbols);
        std::vector<SymbolEntry*> sesyms;
        sesymlist.swap(sesyms);

        paramtypes.clear();
        paramsymbols.clear();
        delete top;
        delete []$2;
    }
    |
    Type ID 
    LPAREN RPAREN
    {
        isret=false;

        //类型检查：是否重复定义（可能有问题，声明没有处理）
        SymbolEntry *se1=identifiers->lookup($2);
        //cout<<((FunctionType*)(se1->getType()))->num_params()<<endl;
        //cout<<(int)(paramtypes.size())<<endl;
        if(se1){
            if(((FunctionType*)(se1->getType()))->num_params()==(int)(paramtypes.size())){
                cout<<"line: "<<yylineno<<endl;
                fprintf(stderr, "function define error: the function is redefined.\n");
                //assert(se1);
            }
        }
        //类型检查：检查return
        curr_func=$2;

        Type *funcType;
        std::vector<Type*> params;
        funcType = new FunctionType($1,params);
        SymbolEntry *se = new IdentifierSymbolEntry(funcType, $2, identifiers->getLevel());
        identifiers->install($2, se);
        identifiers = new SymbolTable(identifiers);

        for(int i=0;i<int(paramsymbols.size());i++){
            // cout<<paramsymbols[i]<<endl;
            SymbolEntry *sesym = new IdentifierSymbolEntry(paramtypes[i], paramsymbols[i], identifiers->getLevel());
            identifiers->install(paramsymbols[i], sesym);
        }
    }
    BlockStmt
    {

        //类型检查：检查返回值类型
        if($1->isVoid()&&isret){
            cout<<"line:"<<yylineno<<endl;
            cout<<"function\""<<$2<<"\""<<"should return void!"<<endl;
        }
        else if (!$1->isVoid()&&!isret){
            cout<<"line:"<<yylineno<<endl;
            cout<<"function\""<<$2<<"\""<<"should return an int value!"<<endl;
        }

        SymbolEntry *se;
        se = identifiers->lookup($2);
        assert(se != nullptr);
        //改动
        vector<Id*> paramlist;
        for(int i=0;i<int(paramsymbols.size());i++){
            SymbolEntry *sesym = new IdentifierSymbolEntry(paramtypes[i], paramsymbols[i], identifiers->getLevel());
            Id *id = new Id(sesym);
            paramlist.push_back(id);
        }
        $$ = new FunctionDef(se, $6, paramlist, paramsymbols);
        SymbolTable *top = identifiers;
        identifiers = identifiers->getPrev();

        paramtypes.clear();
        paramsymbols.clear();
        delete top;
        delete []$2;
    }
    ;
Params:
    Exp{
        //全部变成ID了。。。
        //globle_tmp_paramcalls.clear();
        globle_tmp_paramcalls.push_back($1);
    }
    |
    Params COMMA Exp{
        //SymbolEntry *se;
        //se = identifiers->lookup($3);
        //assert(se != nullptr);
        globle_tmp_paramcalls.push_back($3);
    }
    ;
FuncCall
    :
    ID LPAREN Params RPAREN
    {
        std::vector<ExprNode*> params;
        params.swap(globle_tmp_paramcalls);
        
        SymbolEntry *se;
        se = identifiers->lookup($1);
        
        cout<<$1<<endl;
        //类型检查：函数是否声明
        if(!se){
            cout<<"line:"<<yylineno<<endl;
            cout<<"function\""<<$1<<"\" is called without declaration!"<<endl;
        }
        assert(se != nullptr);
        //类型检查：检查参数个数是否正确
        if(int(params.size())!=((FunctionType*)(se->getType()))->num_params()){
            cout<<"line: "<<yylineno<<endl;
            fprintf(stderr, "function call error: please check params.\n");
            //assert();
        }
        $$ = new FunctionCall(se, params);
    }
    |
    ID LPAREN RPAREN
    {
        std::vector<ExprNode*> params;
        params.swap(globle_tmp_paramcalls);
        SymbolEntry *se;
        se = identifiers->lookup($1);
        //assert(se != nullptr);
        $$ = new FunctionCall(se, params);
    }
    ;

%%

int yyerror(char const* message)
{
    std::cerr<<message<<std::endl;
    return -1;
}
