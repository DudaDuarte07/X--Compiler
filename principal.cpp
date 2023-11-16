#include "parser.cpp"

using namespace std;

int main(int argc, char* argv[]) {

    Parser *parser = new Parser(argv[1]);
    printf("\n");
    parser->run();

    return 0;
}