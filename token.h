#include <iostream>
#include <ctype.h>//Funções de caracteres
#include <cstring>
#include <string>

using namespace std;

enum Names{
    //IDENTIFICADORES
    UNDEF,              //0
    ID,                 //1
    IF,                 //2
    ELSE,               //3
    THEN,               //4
    OP,                 //5
    EQ,                 //6 ==
    NE,                 //7 !=
    GT,                 //8 >
    GE,                 //9 >=
    LT,                 //10 <
    LE,                 //11 <=
    //TIPOS
    NUMBER,             //12
    INTEGER_LITERAL,    //13
    STRING_LITERAL,     //14
    ATRIBUTO,
    //OPERADORES
    ADD,                //15 +
    SUB,                //16 -
    MULT,               //17 *
    DIVIDE,             //18 /
    RESTO,              //19 %
    IGUAL,              //20 =
    SEP,                //21
    L_PAREN,            //22 (
    R_PAREN,            //23 )
    L_COLCH,            //24 [
    R_COLCH,            //25 ]
    L_KEY,              //26 {
    R_KEY,              //27 }
    PONTO_VIRGULA,      //28 ;
    PONTO,              //29 .
    COMMA,              //30 ,
    //PALAVRAS RESERVADAS
    CLASS,              // 31
    EXTENDS,            // 32
    INT,                // 33
    STRING,             // 34
    BREAK,              // 35
    PRINT,              // 36
    READ,               // 37
    RETURN,             // 38
    SUPER,              // 39
    FOR,                // 40
    NEW,                // 41
    CONSTRUCTOR,        // 42
    RelOp,              // 43
    END_OF_FILE         // 44
};

class Token 
{
    public: 
        int name;
        int attribute;
        string* lexeme;

        Token(int name)
        {
            this->name = name;
            attribute = UNDEF;
        }

        Token(int name, int attr)
        {
            this->name = name;
            attribute = attr;
        }

        
};