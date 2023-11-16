#include "scanner.h"

class Parser{
    private:
        Scanner* scanner;
        Token* lToken;

        // Vetor auxiliar 
        string vetor[45] = {"UNDEF",
                            "ID",
                            "IF",
                            "ELSE",
                            "THEN",
                            "OPERADOR",
                            "=",
                            "!=",
                            ">",
                            ">=",
                            "<",
                            "<=",
                            "NUMBER",
                            "INTEGER_LITERAL",
                            "+",
                            "-",
                            "*",
                            "/",
                            "%",
                            "==",
                            "STRING_LITERAL",
                            "SEPARADOR",
                            "(",
                            ")",
                            "{",
                            "}",
                            ";",
                            ".",
                            ",",
                            "class",
                            "int",
                            "string",
                            "break",
                            "print",
                            "read",
                            "return",
                            "super",
                            "for",
                            "new",
                            "constructor", 
                            "relop",
                            "END_OF_FILE"};

    //verificar relop

    /*Por algum motivo, em alguns pontos quando utilizo match(ID)
    tenho um erro de segmentação, mesmo a função match usando exit(),
    para "driblar" isso, usei uma verificação a mais e implementei
    uma função error*/

    /*
    Da produção Statements em diante, utilizei a gramática modificada
    para me auxiliar, a mesma está contida no diretório do trabalho com
    o nome "gramat_altered.txt".
    */

    public:
    Parser(string input){
        scanner = new Scanner(input);
    }

        void error(string mensagem){
            cout << "Erro sintático na linha "<< scanner -> getLine()
            << ": "<< mensagem << endl;
            exit(EXIT_FAILURE);
        }


        void advance(){
            lToken = scanner -> nextToken();
        }


        int match(int t){

            if( (lToken -> name) == t || (lToken -> attribute) == t ){
                advance();
                return 1;
            }
            else{
                cout << "Erro na Linha " << scanner -> getLine() << ": esperado '" <<
                this -> vetor[t - 2] << "'." << endl;

                exit(EXIT_FAILURE);
                return 0;
            }
        }


        void Program(){

            if( !(lToken->name == END_OF_FILE) )
                ClassList();
            else
                 ;
        }


        void ClassList(){

            do{
                ClassDecl();
            } while(lToken -> attribute == CLASS);

        }


        void ClassDecl(){
            match(CLASS);
            if(lToken -> name == ID){
                match(ID);			
            } else {
                error("Espera-se 'ID'.");
            }

            if(lToken->attribute == EXTENDS){
                advance();
                if(lToken->name == ID){
                    match(ID);			
                } else {
                    error("Espera-se 'ID'.");
                }
            }

            ClassBody();
        }


        void run(){
            advance();
            Program();
            printf("Compilação encerrada com sucesso\n");
        }


        void ClassBody(){
            /*printf("ClassBody");*/
            match(L_KEY);
            /*printf("LK\n");*/
            VarDeclListOpt();
            ConstructDeclListOpt();
            MethodDeclListOpt();
            //Statement();
            //VarDeclListOpt TOTALMENT FUNCIONAL
            //Statements();
            //Expression();
            match(R_KEY);
        }


        void VarDeclListOpt(){
            if(isType(lToken)){
                /*printf("Entrei\n");*/
                VarDeclList();
            }
        }


        void VarDeclList(){
            do{
                VarDecl();  
                /*printf("\n, %d %d\n", lToken->name, lToken->attribute);*/
            } while(isType(lToken));
            //problema aqui
        }


        void VarDecl(){

            Type();

            if(lToken -> attribute == L_COLCH){
                advance();
                match(R_COLCH);
            }

            if(lToken -> name == ID){
                match(ID);		
            } else {
                error("Espera-se 'ID'.");
            }

            VarDeclOpt();
            /*printf("\n, %d %d\n", lToken->name, lToken->attribute);*/
            match(PONTO_VIRGULA);

            /*printf("pasei ;\n");*/

        }


        void VarDeclOpt(){

            while(lToken->attribute == COMMA){
                advance();		

                if(lToken->name == ID){
                    match(ID);
                } else {
                    error("Espera-se 'ID'.");
                }

                //após consumir um id, nesse caso
                //ou vem ;, ou , 
            }

        }


        void Type(){
            if(isType(lToken)){
                /*printf("aqui1");*/
                advance();
            } else {
                printf("Erro na linha %d: Não é um tipo válido\n", scanner -> getLine());
                exit(EXIT_FAILURE);
            }
        }


        void ConstructDeclListOpt(){
            /*printf("construtor %d, %d\n", lToken->name, lToken->attribute);*/
            if(lToken -> attribute == CONSTRUCTOR){
                /*printf("Entrei aqui");*/
                ConstructDeclList();
            }
        }


        void ConstructDeclList(){
            do{
                ConstructDecl();
            }while(lToken -> attribute == CONSTRUCTOR);
        }


        void ConstructDecl(){
            match(CONSTRUCTOR);
            MethodBody();
        }


        void MethodDeclListOpt(){
            if(isType(lToken)){
                /*printf("Entrei\n");*/
                MethodDeclList();
            }
        }


        void MethodDeclList(){
            do{
                MethodDecl();  
                /*printf("\n, %d %d\n", lToken->name, lToken->attribute);*/
            }while(isType(lToken));
            //problema aqui
        }


        void MethodDecl(){

            Type();

            if(lToken -> attribute == L_COLCH){
                advance();
                match(R_COLCH);
            }

            if(lToken -> name == ID)
                match(ID);			
            else
                error("Espera-se 'ID'.");

            MethodBody();
            /*printf("\n, %d %d\n", lToken->name, lToken->attribute);*/


            /*printf("pasei ;\n");*/

        }


        void MethodBody(){

            match(L_PAREN);
            ParamListOpt();
            match(R_PAREN);
            match(L_KEY);
            Statements();
            match(R_KEY);
        }


        void ParamListOpt(){
            if(isType(lToken))
                ParamList();
        }


        void ParamList(){
            do{
                Param();
            }while(isType(lToken));
        }


        void Param(){
            Type();


            if(lToken->attribute == L_COLCH){
                advance();
                match(R_COLCH);
            }
            if(lToken->name == ID)
                    match(ID);			
                else
                    error("Espera-se 'ID'.");
            ParamDeclOpt();
        }


        void Statements(){
            do{
                Statement();
            }while(StatementType(lToken));
        }


        void Statement(){
            /*printf("\n, %d %d\n", lToken->name, lToken->attribute);*/
            if(lToken->name == ID){
                advance();
                /*printf("Statement\n");*/
                StatementLine();

                /*printf("SC\n");*/
            }
            else if(isType(lToken)){
                VarDeclList();
            }
            else if(lToken->name == PRINT || lToken->name == RETURN){
                advance();
                Expression();
                match(PONTO_VIRGULA);
            }
            else if(lToken->name == READ){
                advance();
                LValue();
                match(PONTO_VIRGULA);
            }
            else if(lToken->name == SUPER){
                advance();
                match(L_PAREN);
                ArgListOpt();
                match(R_PAREN);
                match(PONTO_VIRGULA);
            }
            //falta if e for
            else if(lToken->name == BREAK){
                advance();
                match(PONTO_VIRGULA);
            }
            else if(lToken->name == IF){
                match(IF);
                match(L_PAREN);//(
                Expression();
                match(R_PAREN);//)
                match(L_KEY);//{
                Statements();
                match(R_KEY);//}
                ifStatLine();//caso tenha else
            }
            else if(lToken->attribute == FOR){
                /*for ( AtribStatOpt ; ExpressionOpt ; AtribStatOpt )
                { Statements }*/
                match(FOR);
                match(L_PAREN);
                AtribStatOpt();
                match(PONTO_VIRGULA);
                ExpressionOpt();
                match(PONTO_VIRGULA);
                AtribStatOpt();
                match(R_PAREN);
                match(L_KEY);
                Statements();
                match(R_KEY);

            }
            else if(lToken->attribute == PONTO_VIRGULA){
                advance();
            }
            //falta for
            //pode ser vazio
            //parece funcional

        }


        void StatementLine(){
            if(lToken->name == ID){
                advance();
                VarDeclOpt();
                match(PONTO_VIRGULA);

                if(isType(lToken))
                    VarDeclList();

            }
            else if(lToken -> attribute == L_COLCH){
                advance();
                if(lToken -> name == ADD || lToken -> name == SUB){
                    Expression();
                    match(R_COLCH);
                    LValueComp();
                    match(EQ);
                    AtribStatLine();
                    match(PONTO_VIRGULA);
                }
                else{
                    match(R_COLCH);
                    if(lToken -> name == ID){
                        match(ID);			
                    }
                    else{
                        error("Espera-se 'ID'.");
                    }
                    VarDeclOpt();
                    match(PONTO_VIRGULA);

                    if(isType(lToken))
                        VarDeclList();
                }
            }
            else if(lToken -> attribute == PONTO){
                advance();
                if(lToken -> name == ID)
                    match(ID);			
                else
                    error("Espera-se 'ID'.");
                LValueCompLine();
                match(EQ);
                AtribStatLine();
                match(PONTO_VIRGULA);
            }
            else if(lToken -> attribute == EQ){
                match(EQ);
                AtribStatLine();
                match(PONTO_VIRGULA);
            }
        }


        void Expression(){
            NumExpression();
            ExpressionLine();
        }


        void LValue(){
            if(lToken -> name == ID)
                match(ID);			
            else
                error("Espera-se 'ID'.");
            LValueLine();
        }


        void ArgListOpt(){
            ArgList();
        }


        void ParamDeclOpt(){
            if(lToken -> attribute == COMMA){
                advance();
                Type();


                if(lToken -> attribute == L_COLCH){
                    advance();
                    match(R_COLCH);
                }
                if(lToken -> name == ID)
                    match(ID);			
                else
                    error("Espera-se 'ID'.");


            }
        }

        int StatementType(Token *t){

            if ((t->name == ID) ||
                (isType(t)) ||
                (t -> name == PRINT ||
                t -> name == RETURN) ||
                (t -> name == READ) ||
                (t -> name == SUPER) ||
                (t -> name == BREAK) || 
                (t -> name == IF) ||
                (t -> attribute == PONTO_VIRGULA)){
                return 1;
            } else {
                return 0;
            }

        }



        void AtribStatOpt(){
            //AtribStatOpt -> ID LValue' = AtribStat' | vazio
            if(lToken -> name == ID){
                if(lToken -> name == ID)
                    match(ID);			
                else
                    error("Espera-se 'ID'.");
                LValueLine();
                match(EQ);
                AtribStatLine();
            }
            else
                ;//vazio
        }

        void ExpressionOpt(){
            if(lToken -> name == ADD || lToken -> name == SUB)
                Expression();
        }

        void ifStatLine(){
            if(lToken -> name == ELSE){
                match(ELSE);
                match(L_KEY);
                Statements();
                match(R_KEY);
            }
            else
                ;//if sem else
        }


        void LValueLine(){
            if(lToken -> attribute == PONTO){
                match(PONTO);
                if(lToken -> name == ID)
                    match(ID);			
                else
                    error("Espera-se 'ID'.");
                LValueCompLine();
            }
            else if(lToken -> attribute == L_COLCH){
                match(L_COLCH);
                Expression();
                match(R_COLCH);
                LValueComp();
            }
            else
                ;//vazio
        }

        void ArgList(){
            Expression();

            while(lToken -> attribute == COMMA){
                advance();
                Expression();
            }

        }

        void AllocExpression(){
            if(isType(lToken)){
                Type();
                match(L_COLCH);
                Expression();
                match(R_COLCH);
            }else if(lToken -> attribute == NEW){
                advance();
                if(lToken -> name == ID)
                    match(ID);			
                else
                    error("Espera-se 'ID'.");
                match(L_PAREN);
                ArgListOpt();
                match(R_PAREN);
            }
        }


        void LValueComp(){
            if(lToken -> attribute == PONTO){
                match(PONTO);
                if(lToken -> name == ID)
                    match(ID);			
                else
                    error("Espera-se 'ID'.");
                LValueCompLine();
            }
            else{
                ;
            }
        }


        void LValueCompLine(){
            if(lToken -> attribute == PONTO){
                match(PONTO);
                if(lToken -> name == ID)
                    match(ID);			
                else
                    error("Espera-se 'ID'.");
                LValueCompLine();
            }
            else if(lToken->attribute == L_COLCH){
                match(L_COLCH);
                Expression();
                match(R_COLCH);
                LValueComp();
            }
            else
                ;
        }

        void AtribStatLine(){
            if(lToken -> attribute == ADD || lToken -> attribute == SUB){
                advance();
                Factor();
                TermLine();
                NumExpressionLine();
                ExpressionLine();
            }
            else if(lToken -> name == NEW || isType(lToken)){
                AllocExpression();
            }
            else{
                error("Esperado um '+', '-' ou 'AllocExpression'");	
            }
        }

        void Factor(){
            if(lToken -> name == STRING_LITERAL ||
                lToken -> name == INTEGER_LITERAL){
                advance();
            }
            else if(lToken -> name == ID){
                LValue();

            }
            else if(lToken -> attribute == L_PAREN){
                match(L_PAREN);
                Expression();
                match(R_PAREN);
            }
            else{
                error("Esperado: 'Fator'.");
            }


        }

        void TermLine(){
            if(lToken  -> attribute == MULT
                || lToken -> attribute == DIVIDE
                || lToken -> attribute == RESTO){
                advance();
                UnaryExpression();
            }
            else
                ;//vazio
        }

        void NumExpressionLine(){
            if(lToken -> attribute == ADD
                || lToken->attribute == SUB){
                advance();
                Term();

            }
            else
                ;
        }

        void UnaryExpression(){
            if(lToken -> attribute == ADD
                || lToken->attribute == SUB){
                advance();
                Factor();
            }
            else{
                error("Espera-se '+' ou '-'.");
            }
        }
        int isRelop(Token *t){
            if (t -> attribute == NE || t -> attribute == LE ||
                t -> attribute == LT || t -> attribute == GE ||
                t -> attribute == GT || t -> attribute == ATRIBUTO){
                return 1;
            }
            else
                return 0;

        }
        void ExpressionLine(){
            if(isRelop(lToken)){
                advance();
                NumExpression();
            }
            else{
                ;//vazio
            }
        }


        void Term(){
            UnaryExpression();
            TermLine();
        }


        void NumExpression(){
            Term();
            NumExpressionLine();
        }

        int isType(Token *t){
            int result = 0;

                if ((t->attribute == INT) ||
                    (t->attribute == STRING)  ||
                    (t->name == ID) ){

                    result = 1;
                }

            return result;
        }

};