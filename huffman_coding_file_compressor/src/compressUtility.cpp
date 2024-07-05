#include "compressUtility.hpp"

extern std::string HuffmanValue[256];

namespace Huffman {
namespace CompressUtility {

Node *combine(Node *a, Node *b) {
    Node *parent = new Node((a ? a->count : 0)+(b ? b->count : 0));
    parent->left = b;
    parent->right = a;
    return parent;
}

bool sortbysec(const Node *a, const Node *b) { 
    return (a->count > b->count); 
}

Map<char, ll>parse_file(const char* filename, const ll Filesize) {
    FILE *ptr = fopen(filename, "rb");
    if (ptr == NULL) {
        perror("Erro: arquivo não encontrado:");
        exit(-1);
    }
    unsigned char ch;
    ll size = 0, filesize = Filesize;
    Vector<ll>Store(256, 0);

    while (size != filesize) {
        ch = fgetc(ptr);
        ++Store[ch];
        ++size;
    }

    Map<char, ll>store;
    for (int i = 0; i < 256; ++i) {
        if (Store[i]) {
            store[i] = Store[i];
        }
    }
    fclose(ptr);
    return store;
}

Vector<Node*>sort_by_character_count(const Map<char, ll>&value) {
    Vector<Node*> store;
    for (auto &x: value) {
        store.push_back(new Node(x.first, x.second));
    }
    std::sort(store.begin(), store.end(), sortbysec);
    return store;
}

std::string generate_header(const char padding) {
    std::string header = "";
    unsigned char unique_character = 255;
    
    for (int i = 0; i < 256; ++i) {
        if (HuffmanValue[i].size()) {
            header.push_back(i);
            header.push_back(HuffmanValue[i].size());
            header += HuffmanValue[i];
            ++unique_character;
        }
    }
    char value = unique_character;
    return value+header+(char)padding;
}

ll store_huffman_value(const Node *root, std::string &value) {
    ll temp = 0;  
    if (root) {
        value.push_back('0');
        temp = store_huffman_value(root->left, value);
        value.pop_back();
        if (!root->left && !root->right) {
            HuffmanValue[(unsigned char)root->character] = value;
            temp += value.size() * root->count;
        }
        value.push_back('1');
        temp += store_huffman_value(root->right, value);
        value.pop_back();
    }
    return temp;
}

Node *generate_huffman_tree(const Map <char, ll>&value) {
    Vector<Node*> store = sort_by_character_count(value);
    Node *one, *two, *parent;
    std::sort(store.begin(), store.end(), sortbysec);
    if (store.size() == 1) {
        return combine(store.back(), nullptr);
    }
    while (store.size() > 2) {
        one = *(store.end() - 1); two = *(store.end() - 2);
        parent = combine(one, two);
        store.pop_back(); store.pop_back();
        store.push_back(parent);

        Vector<Node*>::iterator it1 = store.end() - 2;
        while ((*it1)->count < parent->count && it1 != store.begin()) {
            --it1;
        }
        std::sort(it1, store.end(), sortbysec);
    }
    one = *(store.end() - 1); two = *(store.end() - 2);
    return combine(one, two);
}

void compress (const char *filename, const char *filename2, const ll Filesize, const ll PredictedFileSize) {
    const char padding = (8 - ((PredictedFileSize)&(7)))&(7);
    const std::string header = generate_header(padding);
    int header_i = 0;
    const int h_length = header.size();

    FILE *iptr = fopen(filename, "rb"), *optr = fopen(filename2, "wb");

    if(Filesize == 0) {
        std::cout << "Arquivo a ser comprimido está vazio " << std::endl;
        fclose(iptr);
        fclose(optr);
        exit(-1);
    }

    if (!iptr) {
        perror("Erro: arquivo a ser compactado não encontrado: \n");
        exit(-1);
    }

    while (header_i < h_length) {
        fputc(header[header_i], optr);
        ++header_i;
    }

    unsigned char ch, fch = 0;
    char counter = 7;
    ll size = 0, i;
    while(size != Filesize) {
        ch = fgetc(iptr);
        i = 0;
        const std::string &huffmanStr = HuffmanValue[ch];
        while(huffmanStr[i] != '\0') {
            fch = fch | ((huffmanStr[i] - '0') << counter);
            counter = (counter + 7) & 7;
            if(counter == 7) {
                fputc(fch, optr);
                fch ^= fch;
            }
            ++i;
        }
        ++size;
    }
    if(fch) {
        fputc(fch, optr);
    }
    fclose(iptr);
    fclose(optr);
}

};
};