#ifndef NODE_HPP
#define NODE_HPP
#define ll unsigned long long int

#include <iostream>
#include <string>

#include "myMap.hpp"


namespace Huffman {

struct Node {
    char character;
    ll count;
    Node* left;
    Node* right;

    Node(char character, ll count);
    Node(ll count);

};

} 

#endif
