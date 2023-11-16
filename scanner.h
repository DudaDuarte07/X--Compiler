#include "token.h"

class Scanner 
{
    private: 
        string input;//Armazena o texto de entrada
        int pos;//Posição atual
        int line; // 
    
    public:
    //Construtor
        Scanner(string);

        //seta atributo input
        void setInput(string input);

        void printInformations(string input);

        //retorna o numero da posição
        int getPos();
    
        //Método que retorna o próximo token da entrada
        Token* nextToken();        
    
        //Método para manipular erros
        void ErroLexico(string);

        int getLine();
};
