# Introduction
The focus of this program is to evaluate mathematical expressions provided via a file, which can be in different formats, and to convert an equation from one format to another. To solve the provided expressions, we first need to define the structure used to store them. The rest of the program's functionalities will be easier to implement with a strong, versatile, and well-controlled base. So... let's use a tree with different types of nodes, some representing operations and one representing a node with only a value. This allows for the addition of more capabilities to the equation reader, such as negation of a number or new operations like factorial or exponential. With this base, all other functionalities become easier to implement, as shown below.

**P.S**: Sorry for the mixed names of variables in Portuguese and English, but i found easier to do that as the input is in Portuguese. 
I ran this on a MacOS Machine, it seems like i got some problems when trying to run it on a Linux machine, but i didn't dwelve into it.

# Method
In summary: A simple mathematical expression parser was implemented using a recursive descent parsing technique. The parser reads the arithmetic expression as a string and converts it into a stream of tokens separated by whitespace. It then parses the tokens to create an abstract syntax tree (AST) representing the structure of the expression.

## Classes
- **Node**: The parent class of all other nodes in the program. Introduces the `evaluate` function, which has no implementation here.
- **BinaryOpNode**: Inherits from `Node` and serves as the parent of all classes representing operations in an expression. Its most important part is that it points to two other `Node`s.
- **ValueNode**: Inherits from `Node` but does not point to any other nodes. It is essential as it represents the numbers in the expression. Here, `evaluate` returns the value the node represents.
- **AddNode, SubtractNode, DivideNode, MultiplyNode**: Inherit from `BinaryOpNode`. Each represents an operation and points to two values to perform this operation, whether these values are numbers or expressions (which will also have a value).
- **Stack**: Implements a stack data structure.
- **Parser**: Combines all classes to build the tree representing the equation and implements functions to convert equations from infix to postfix notation.

## Functions
- **Parser (Constructor)**: Formats the given expression and checks for invalid parentheses.
- **parseInfix and parsePostfix**: Read the expression and construct a tree, returning the head node of this structure. `parsePostfix` builds the tree within the function using loops, while `parseInfix` uses the following functions:
  - **parseExpression, parseTerm, parseFactor, parseNumber**: Parse the components of infix expressions. `parseInfix` calls `parseExpression` on the provided equation. Priority handling for operations is done here, giving precedence to terms involving multiplication and division. Finally, the expression handles addition operations among the terms.
- **toPostfix and toInfix**: Convert an equation from infix to postfix notation or vice versa.
- **evaluate**: Returns the result of the equation. For a `ValueNode`, it returns the node's value. For a subclass of `BinaryOpNode`, it returns the result of the operation, calling `evaluate()` recursively until the final result is obtained.
- **isPostfix**: Determines if the expression is in postfix notation, useful for applying the correct string formatting for the expression.

# Complexity
- **Parser (Constructor)**: O(n), depends on the length of the input string.
- **parseInfix and parsePostfix**: O(n), depends on the length of the input string.
- **parseExpression, parseTerm, parseFactor**: O(n), depends on the length of the input string.
- **parseNumber**: O(1)
- **toPostfix and toInfix**: O(n)
- **evaluate**: O(n) when called on an entire expression, depends on its length. O(1) when called on a `ValueNode`.
- **isPostfix**: O(n)

None of the functions contain nested loops, ensuring that no function exceeds O(n) complexity.

# Robustness Strategies
To make the program more robust, try-catch blocks were used. When an issue is detected while reading or calculating an expression, the operation terminates without crashing the program, moving on to the next task. This technique is applied throughout the code to check for expected actions, providing important feedback on encountered issues. For example, division by zero is tested every time `evaluate()` is called on a division node. This strategy effectively handles issues such as 3 / (3 - 1 * 3), which might not be detected otherwise and cause a lot of trouble.

# Running the program
Execute the program with `make run file=filename`. `filename` should be the name of the file the serves as input, like `equations.in`.

You can execute `make clean` to clean the objects and executable files too.

<img width="682" alt="Screenshot 2024-07-04 at 12 51 43" src="https://github.com/vtortega/Algorithms/assets/112141870/4e03939a-b986-4f4f-ac8b-10ae7fd0c429">

This is the graph showing the number of equations made on the X axis and time(in ms) on the Y axis
