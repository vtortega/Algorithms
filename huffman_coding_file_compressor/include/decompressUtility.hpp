#ifndef DECOMPRESS_UTILITY_HPP
#define DECOMPRESS_UTILITY_HPP

#include "utility.hpp"

namespace Huffman {

namespace DecompressUtility {

void generate_huffman_tree(Node * const root, const std::string &codes, const unsigned char ch);

Pair<Node*, Pair<unsigned char, int> >decode_header(FILE *iptr);

void decompress(const char*filename, const char*filename2, const ll Filesize); 

}

};


#endif