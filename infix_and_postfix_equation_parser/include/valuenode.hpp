#ifndef VALUENODE_HPP
#define VALUENODE_HPP
#include "node.hpp"

class ValueNode : public Node {
    public:
     ValueNode(double value);
     ~ValueNode() = default;

     double evaluate() const override;

    private:
     double m_value;
     
};

#endif