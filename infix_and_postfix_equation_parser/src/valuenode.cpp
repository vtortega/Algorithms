#include "valuenode.hpp"

ValueNode::ValueNode(double value) : m_value(value) {}

double ValueNode::evaluate() const {
    return m_value;
}

