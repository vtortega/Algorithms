#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>

class Node {
    public:
     virtual ~Node() = default;
     virtual double evaluate() const = 0;

};

#endif