#include <map>
#include "stentry.h"

class SymbolTable
{
    private:
        SymbolTable* parent;
        map<string, STEntry*> symbols;

    public:
        SymbolTable();
        SymbolTable(SymbolTable*);

        bool add(STEntry*);
        bool remove(string);
        void clear();
        bool isEmpty();
        STEntry* get(string);
        SymbolTable* getParent();

};