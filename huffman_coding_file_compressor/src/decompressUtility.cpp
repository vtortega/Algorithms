#include "decompressUtility.hpp"

namespace Huffman {
namespace DecompressUtility {

void generate_huffman_tree(Node * const root, const std::string &codes, const unsigned char ch) {
    Node *traverse = root;
    int i = 0;
    while(codes[i] != '\0') {
        if(codes[i] == '0') {
            if(!traverse->left) {
                traverse->left = new Node(0);
            }
            traverse = traverse->left;
        } else {
            if(!traverse->right) {
                traverse->right = new Node(0);
            }
            traverse = traverse->right;
        }
        ++i;
    }
    traverse->character = ch;
}

Pair<Node*, Pair<unsigned char, int> >decode_header(FILE *iptr) {
    Node *root = new Node(0);
    int charactercount, buffer, total_length = 1;
    char ch, len;
    charactercount = fgetc(iptr);
    std::string codes;
    ++charactercount;
    while(charactercount) {
        ch = fgetc(iptr);
        codes = ""; 
        len = fgetc(iptr);
        buffer = len;

        while((int)buffer > (int)codes.size()) {
            codes.push_back(fgetc(iptr));
        }

        total_length += codes.size()+2;

        generate_huffman_tree(root, codes, ch);
        --charactercount;
    }
    unsigned char padding = fgetc(iptr);
    ++total_length;
    return std::make_pair(root, std::make_pair(padding, total_length));
}

void decompress(const char *filename, const char *filename2, const ll Filesize) {
    const std::string fl = filename;
    FILE *iptr = fopen(fl.c_str(), "rb");
    FILE *optr = fopen(filename2, "wb");
    
    if (iptr == NULL) {
        perror("Erro: arquivo compactado não encontrado \n");
        exit(-1);
    }

    Pair<Node*, Pair<unsigned char, int> >HeaderMetadata = decode_header(iptr);
    Node *const root = HeaderMetadata.first;
    const auto [padding, headersize] = HeaderMetadata.second;

    char ch, counter = 7;
    ll size = 0;
    const ll filesize = Filesize-headersize;
    Node *traverse = root;
    ch = fgetc(iptr);
    while (size != filesize) {
        while (counter >= 0) {
            traverse = ch & (1 << counter) ? traverse->right : traverse->left;
            ch ^= (1 << counter);
            --counter;
            if (!traverse->left && !traverse->right) {
                fputc(traverse->character, optr);
                if(size == filesize - 1 && padding == counter + 1) {
                    break;
                }
                traverse = root;
            }
        }
        ++size;
        counter = 7;
        ch = fgetc(iptr);
    }
    fclose(iptr);
    fclose(optr);
}

}

};