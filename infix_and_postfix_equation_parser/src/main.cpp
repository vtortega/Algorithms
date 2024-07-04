#include "parser.hpp"

int main(int argc, char* argv[]) {

    if (argc != 2) {
        std::cerr << "Usado: " << argv[0] << " <filename>\n";
        return 1;
    }

    std::string filename = "equations.txt";

    std::ifstream file(argv[1]);
    if (!file) {
        std::cerr << "Erro ao abrir arquivo \"" << argv[1] << "\"\n";
        return 1;
    }

    std::string line, equation;
    bool infixa, posfixa = false;    //algumas funcoes exigem sabermos qual tipo de expressão é;
    std::ifstream inFile(filename);

    if (!inFile) {
        std::cout << "Problema ao abrir o arquivo" << std::endl;
        return 1;
    }

    while (std::getline(inFile, line)) {

        std::stringstream ss(line);


        if(line.find("LER INFIXA") == 0) {

            auto pos = line.find("LER INFIXA");
            equation = line.substr(pos + 12);
            infixa = true;
            posfixa = false;

            try {
                Parser parser(equation);
                parser.parseInfix();
                std::cout << "INFIXA: " << equation << std::endl;
            }
            catch (const std::exception& e) {
                std::cerr << "ERRO: " << equation << " NÃO VÁLIDA" << e.what() << std::endl;
            }

        }

        if(line.find("LER POSFIXA") == 0) {


            auto pos = line.find("LET POSFIXA");
            equation = line.substr(pos + 14);
            posfixa = true;
            infixa = false;

            try {
                Parser parser(equation);
                parser.parsePostfix();
                std::cout << "POSFIXA: " << equation << std::endl;
            }
            catch (const std::exception& e) {
                std::cerr << "ERRO: " << equation << " NÃO VÁLIDA" << e.what() << std::endl;
            }


        }

        if(line.find("INFIXA") == 0) {

            try {
                Parser parser(equation);
                std::cout << "INFIXA: " << parser.toInfix() << std::endl;
            }
            catch (const std::exception& e) {
                std::cerr << "ERRO: " << equation << " NÃO VÁLIDA" << e.what() << std::endl;
            }

        }

                
        if(line.find("POSFIXA") == 0) {

            try {
                Parser parser(equation);
                std::cout << "POSFIXA: " << parser.toPostfix() << std::endl;
            }
            catch (const std::exception& e) {
                std::cerr << "ERRO: " << equation << " NÃO VÁLIDA" << e.what() << std::endl;
            }

        }


        if(line.find("RESOLVE") == 0 && infixa) {

            try {
            Parser parser(equation);
            Node* root = parser.parseInfix();
            std::cout << "POSFIXA: " << std::fixed << std::setprecision(6) << root->evaluate() << std::endl;
            delete root;
            }
            catch (const std::exception& e) {
                std::cerr << "ERRO: " << equation << " NÃO VÁLIDA" << e.what() << std::endl;
            }
        }

        if(line.find("RESOLVE") == 0 && posfixa) {
            try {
            Parser parser(equation);
            Node* root = parser.parsePostfix();
            std::cout << "POSFIXA: " << std::fixed << std::setprecision(6) << root->evaluate() << std::endl;
            delete root;
            }
            catch (const std::exception& e) {
                std::cerr << "ERRO: " << equation << " NÃO VÁLIDA" << e.what() << std::endl;
            }
        }



        std::string token;
        ss >> token;

    }

    inFile.close();
    return 0;
}