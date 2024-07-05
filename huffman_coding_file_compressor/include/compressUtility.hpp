#ifndef COMPRESS_UTILIITY_HPP
#define COMPRESS_UTILIITY_HPP

#include "utility.hpp"
#include <fstream>
#include <algorithm>

namespace Huffman {
namespace CompressUtility {

Node *combine(Node *a, Node *b);

bool sortbysec(const Node *a, const Node *b);

Map<char, ll>parse_file(const char* filename, const ll Filesize);

Vector<Node*>sort_by_character_count(const Map<char, ll>&value); 

std::string generate_header(const char padding); 

ll store_huffman_value(const Node *root, std::string &value);

Node *generate_huffman_tree(const Map <char, ll>&value);  

void compress (const char *filename, const char *filename2, const ll Filesize, const ll PredictedFileSize); //comprime o arquivo

};
};

#endif