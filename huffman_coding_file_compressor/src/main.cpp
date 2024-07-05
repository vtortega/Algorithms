#include "compressUtility.hpp"
#include "decompressUtility.hpp"
#include <cstdio>

std::string HuffmanValue[256] = {""};

using namespace Huffman;

int main(int argc, char *argv[]) {
    if(argc != 4) {
        printf("Como utilizar:\n (./a.out) (-c ArquivoASerComprimido ArquivoOndeSeráfeitaACompressão | -d ArquivoComprimido ArquivoOndeSeráfeitaADescompressão)");
        exit(-1);
    }
    const char *option = argv[1], *filename = argv[2], *filename2 = argv[3];
    
    ll filesize, predfilesize = 0;
    if (std::string(option) == "-c") {
        filesize = Utility::get_file_size(filename);
        auto mapper = CompressUtility::parse_file(filename, filesize);
        Node *const root = CompressUtility::generate_huffman_tree(mapper);
        std::string buf = "";
        predfilesize = CompressUtility::store_huffman_value(root, buf);
    
        CompressUtility::compress(filename, filename2, filesize, predfilesize);
    
    }
    else if (std::string(option) == "-d") {
        filesize = Utility::get_file_size(filename);
        DecompressUtility::decompress(filename, filename2, filesize);
    } 
    else {
        std::cout << "\nErro de entrada\n";
    }
    return 0;
}