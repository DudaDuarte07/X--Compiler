#include "scanner.h" 
#include <fstream>   
#include <string.h>

 //rever

/* 
Palavras reservadas x++: class,
                         extends,
                         int,
                         string,
                         break,
                         print,
                         read,
                         return, 
                         super,
                         if,
                         else,
                         for,
                         new,
                         constructor

*/ 

Scanner::Scanner(string input){
        pos = 0;
        line = 1;

        ifstream inputFile(input, ios::in);
        string line;

        if(inputFile.is_open()){

            while(getline(inputFile, line)){
                this->input.append(line + '\n');
            }

            // Elimina o \n da ultima string
            this->input.pop_back();
            inputFile.close();
        } else
            cout << "Arquivo não encontrado!\n";

        /*Se não quier imprimir o conteudo do arquivo lido comente essa parte*/
        printf("Conteudo lido: \n");
        cout << this->input;

}

Token* Scanner::nextToken(){
    Token* tok ;

    if(input[pos] == '\n'){
        line++;
        pos++;

        while(input[pos] == '\n'){
            line++;
            pos++;
        }

    }
    // Comentario com */
    if(input[pos] == '/' && input[pos + 1] == '*'){

        pos = pos + 2;

        while(input[pos + 1] != '*' && input[pos + 2] != '/'){

            if(input[pos] == '\n'){
                line++;
            }

            pos++;
        }
        pos = pos + 3;

        while(input[pos] == '\n'){
            line++;
            pos++;
        }
    }
    // Comentário em linha
    if(input[pos] == '/' && input[pos + 1] == '/'){


        pos = pos + 2;

        while(input[pos] != '\n' && input[pos] != '\0'){
            pos = pos + 1;
        }

        while(input[pos] == '\n'){
            line++;
            pos++;
        }


    }
    if(isspace(input[pos]) || input[pos] == '\n'){

        if(input[pos] == '\n'){
            line++; 
        }

        pos++;
        while(isspace(input[pos]) || input[pos] == '\n'){
            if(input[pos] == '\n'){
                line++; 
            }
            pos++;
        }
    }



    // String
    if(input[pos] == '"'){
        pos++;

        while(input[pos] != '"'){

            // String aberta
            if(input[pos] == '\0'){
                ErroLexico("Token nao pertence a linguagem\n");
            }
            pos++;
        }

        pos++;
        tok = new Token(STRING_LITERAL);


    }
    else if(isalpha(input[pos]) || input[pos] == '_'){
        /* 
        Palavras reservadas x++:
        class, extends, int, string, break, print, read, return, 
        super, if, else, for, new, constructor
        São reconhecidas como ID, mas inseridas como tokens, com o 
        nome e atributo pertencente ao seu próprio tipo
        */ 

        if(input.compare(pos, 5, "class") == 0){
            pos = pos + 5;
            tok = new Token(CLASS, CLASS);
        }

        else if(input.compare(pos, 7, "extends") == 0){
            pos+=7;
            tok = new Token(EXTENDS, EXTENDS);
        }

        else if(input.compare(pos, 3, "int") == 0){
            pos = pos + 3;
            tok = new Token(INT, INT);
        }

        else if(input.compare(pos, 6, "string") == 0){
            pos = pos + 6;
            tok = new Token(STRING, STRING);
        }

        else if(input.compare(pos, 5, "break") == 0){
            pos = pos + 5;
            tok = new Token(BREAK, BREAK);
        }

        else if(input.compare(pos, 5, "print") == 0){
            pos = pos + 5;
            tok = new Token(PRINT, PRINT);
        }

        else if(input.compare(pos, 4, "read") == 0){
            pos = pos + 4;
            tok = new Token(READ, READ);
        }

        else if(input.compare(pos, 6, "return") == 0){
            pos = pos + 6;
            tok = new Token(RETURN, RETURN);
        }

        else if(input.compare(pos, 5, "super") == 0){
            pos = pos + 5;
            tok = new Token(SUPER, SUPER);
        }

        else if(input.compare(pos, 3, "for") == 0){
            pos = pos + 3;
            tok = new Token(FOR, FOR);
        }

        else if(input.compare(pos, 2, "if") == 0){
            pos = pos + 2;
            tok = new Token(IF, IF);
        }

        else if(input.compare(pos, 4, "else") == 0){
            pos = pos + 4;
            tok = new Token(ELSE, ELSE);
        }

        else if(input.compare(pos, 3, "new") == 0){
            pos = pos + 3;
            tok = new Token(NEW, NEW);
        }

        else if(input.compare(pos, 11, "constructor") == 0){
            pos = pos + 11;
            tok = new Token(CONSTRUCTOR, CONSTRUCTOR);
        }

        else{

            while(isalnum(input[pos]) || input[pos] == '_')
                pos++;
            tok = new Token(ID);
        }

    } else if(input[pos] == '\0'){
        tok = new Token(END_OF_FILE);

    } else if(input[pos] == '<'){
        pos++;
        if(input[pos] == '='){
            pos++;

            tok = new Token(OP, LE);

        } else
            tok = new Token(OP, LT);

    } else if(input[pos] == '>'){
        pos++;

        if(input[pos] == '='){
            pos++;

            tok = new Token(OP, GE);

        } else
            tok = new Token(OP, GT);
    }

    else if(input[pos] == '='){

        pos++;

        if(input[pos] == '='){
            pos++;

            tok = new Token(OP, ATRIBUTO);

        } else
            tok = new Token(OP, EQ);

    } else if(input[pos] == '!'){
        pos++;
        if(input[pos] == '='){
            pos++;

            tok = new Token(OP, NE);

        } else{
            ErroLexico("Esperado '!='");
        }

    } else if(input[pos] == '+'){
        pos++;
        tok = new Token(OP, ADD);
    }

    else if(input[pos] == '-'){
        pos++;
        tok = new Token(OP, SUB);
    }

    else if(input[pos] == '*'){
        pos++;
        tok = new Token(OP, MULT);
    }

    else if(input[pos] == '/'){
        pos++;
        tok = new Token(OP, DIVIDE);
    }

    else if(input[pos] == '%'){
        pos++;
        tok = new Token(OP, RESTO);
    }
    else if(input[pos] == '('){
        pos++;
        tok = new Token(SEP, L_PAREN);
    }

    else if(input[pos] == ')'){
        pos++;
        tok = new Token(SEP, R_PAREN);
    }

    else if(input[pos] == '['){
        pos++;
        tok = new Token(SEP, L_COLCH);
    }

    else if(input[pos] == ']'){
        pos++;
        tok = new Token(SEP, R_COLCH);
    }

    else if(input[pos] == '{'){
        pos++;
        tok = new Token(SEP, L_KEY);
    }

    else if(input[pos] == '}'){
        pos++;
        tok = new Token(SEP, R_KEY);
    }

    else if(input[pos] == ';'){
        pos++;
        tok = new Token(SEP, PONTO_VIRGULA);
    }

    else if(input[pos] == '.'){
        pos++;
        tok = new Token(SEP, PONTO);
    }

    else if(input[pos] == ','){
        pos++;
        tok = new Token(SEP, COMMA);
    }

    else if(isdigit(input[pos])){
        pos++;
        while(isdigit(input[pos]))
            pos++;
        tok = new Token(INTEGER_LITERAL);
    }

    else {
        ErroLexico("Token nao pertence a linguagem\n");
    }

    return tok;
}

void Scanner::ErroLexico(string msg_erro){
   cout << "\nErro lexico na linha "<< this -> getLine()
    << ": "<< msg_erro << endl;
    exit(EXIT_FAILURE);
}


int Scanner::getLine(){
    return this -> line;
}
