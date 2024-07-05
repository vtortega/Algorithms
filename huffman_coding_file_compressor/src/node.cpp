#include "node.hpp"

namespace Huffman {

Node::Node(ll count) {
    this->character = 0;
    this->count = count;
    this->left = this->right = nullptr;
}

Node::Node(char character, ll count) {
    this->character = character;
    this->count = count;
    this->left = this->right = nullptr;
}

}