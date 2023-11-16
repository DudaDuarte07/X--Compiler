#include "scanner.h"

class Parser{
	private:
		Scanner* scanner;
		Token* lToken;
		void error(int, string);

		void advance();
		
		int match(int);

		void Program();

		void ClassList();

		void ClassListLine();

		void ClassDecl();

		void ClassDeclLine();

		void ClassBody();

		void VarDeclListOpt();

		void VarDeclList();

		void VarDeclListLine();

		void VarDecl();

		void VarDeclLine();

		void VarDeclOpt();

		void Type();

		void ConstructDeclListOpt();

		void ConstructDeclList();

		void ConstructDeclListLine();

		void ConstructDecl();

		void MethodDeclListOpt();

		void MethodDeclList();

		void MethodDeclListLine();

		void MethodDecl();

		void MethodDeclLine();

		void MethodBody();

		void ParamListOpt();

		void ParamList();

		void ParamListLine();

		void Param();

		void ParamLine();

		void StatementsOpt();

		void Statements();

		void StatementsLine();

		void Statement();

		void StatementLine();

		void Expression();

		void Lvalue();

		void ArgListOpt();

	public:
		Parser(string);
		void run();//inicia analise sintática
};

