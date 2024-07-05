# Introduction
This documentation addresses the problem of file compression and decompression using the Huffman algorithm. Besides ensuring the functionality of the program in various scenarios, it should also be fast.

Dividing the program into parts facilitates its implementation. Therefore, it was first necessary to understand how to write the file in actual binary, so that 0s and 1s are written as bits and not bytes(as we will learn, we can only write a group of bits at the same time, not bits alone). After that, we applied the Huffman algorithm, constructed the tree with characters and their frequencies, and merged two nodes of the tree.

Interpreting the binary file is also not trivial; it must have a header to indicate what each binary sequence means.

# Method

## Data Structure
The primary data structure of the project is the Huffman tree. It is made up of nodes that point to other nodes. Each node contains the character it represents and its frequency (the number of times it appears).

To construct this tree, more common data structures were needed, which required less attention but still needed to be implemented. These include a vector, a pair, and a map.

## Classes
Several classes were used in the project:

- **Basic Structures (Pair, Vector, and Map)**: Replacements for STL libraries.
- **Utilities (utility, compressUtility, and decompressUtility)**: Not classes but namespaces containing functions for file compression and decompression.
- **Node**: Defines the node of the Huffman tree. Each new node created is of this type.

## Functions
The code contains several important functions, often interconnected.

### Utility
- **get_file_size (const char* filename)**: Gets the size of the given file.

### CompressUtility
- **Node *combine(Node *a, Node *b)**: Combines two nodes into a new parent node. Creates a new node with the sum of the counters of the provided nodes and sets the provided nodes as left and right children of the new node. The new parent node is returned.
- **bool sortbysec(const Node *a, const Node *b)**: Sorting criterion for nodes based on their counters. Returns true if node `a`'s counter is greater than node `b`'s counter.
- **Map<char, ll> parse_file(const char* filename, const ll Filesize)**: Reads a file and returns a map that relates each character present in the file with the number of occurrences of that character.
- **Vector<Node*> sort_by_character_count(const Map<char, ll>& value)**: Sorts the nodes in descending order of character frequency.
- **std::string generate_header(const char padding)**: Generates the header for the compressed file.
- **ll store_huffman_value(const Node *root, std::string &value)**: Traverses the Huffman tree and stores the Huffman codes of each character, returning the total size of the stored codes.
- **Node *generate_huffman_tree(const Map<char, ll>& value)**: Generates the Huffman tree based on the frequency of each character.
- **void compress(const char *filename, const ll Filesize, const ll PredictedFileSize)**: Compresses the file, generates the header with `generate_header`, and reads the file byte by byte while generating the codes and storing them in the compressed file after storing the header.

### DecompressUtility
- **void generate_huffman_tree(Node * const root, const std::string &codes, const unsigned char ch)**: Generates the Huffman tree based on the codes and corresponding characters. Traverses the tree to find the correct position for each code, creating new nodes as necessary.
- **Pair<Node*, Pair<unsigned char, int> > decode_header(FILE *iptr)**: Decodes the header of the compressed file. Reads the header information from the binary, such as the number of characters, the corresponding Huffman codes, and the total header size. Then, calls `generate_huffman_tree` to create the Huffman tree based on the header information.
- **void decompress(const char *filename, const char *filename2, const ll Filesize)**: Opens the compressed file in binary read mode and the output file in binary write mode. Calls `decode_header` to obtain the Huffman tree and header information. Traverses the compressed file bit by bit, using the Huffman tree to decode the characters and write them to the output file.

# Complexity Analysis

### Utility
- **get_file_size**: The function's complexity is O(1) because it only involves moving the file pointer and getting its position. The space complexity is also O(1) because it uses only local variables.

### Compression
- **parse_file**: The function scans the entire file to count occurrences of each character, resulting in a time complexity of O(Filesize), where Filesize is the file size. The space complexity is O(1) as it uses a map to store character counts.
- **sort_by_character_count**: The function creates nodes for each character and their counters, then sorts the nodes by counters. Node creation has a complexity of O(n), where n is the number of distinct characters. Sorting has a worst-case complexity of O(n log n) due to `std::sort`. The space complexity is O(n) for storing nodes in the vector.
- **generate_header**: Iterates over all characters and their Huffman codes. Given a constant number of characters (256), the time complexity depends on the total size of Huffman codes. The worst-case time complexity is O(256 * MaxCodeLength), where MaxCodeLength is the maximum length of a Huffman code. The space complexity is O(1) for the header string.
- **store_huffman_value**: Traverses the Huffman tree and stores Huffman codes. The time complexity is O(n), where n is the number of distinct characters. The space complexity is O(1) as it modifies the external HuffmanValue array.
- **generate_huffman_tree**: Combines nodes with the lowest counts until only one node remains. The time complexity is O(n log n) in the worst case. The space complexity is O(n) for storing nodes in the vector.
- **compress**: Reads the input file and writes the compressed file. The time complexity is O(Filesize). Generating the header and encoding characters follows the complexities described above. The space complexity is O(1) for temporary variables.

### Decompression (simpler than compression)
- **decode_header**: The time complexity depends on the header size, proportional to the number of distinct characters. Thus, the time complexity is O(n). The space complexity is O(1) for temporary variables and nodes.
- **decompress**: Reads the compressed file and writes the decompressed file. The time complexity is O(Filesize). Decoding characters using the Huffman tree has a worst-case time complexity of O(Filesize). The space complexity is O(1) for temporary variables.

In summary, Huffman compression and decompression have an asymptotic time complexity of O(n log n) and space complexity of O(n), where n is the number of distinct characters.

# Robustness Strategies

- **Null Pointer Checks**: The code checks for null pointers before performing operations. For example, in `combine()`, it checks if `a` and `b` are null before accessing their properties. This prevents invalid memory access when pointers are null.
- **Valid File Checks**: In `parse_file()`, it checks if the specified file opened correctly (`ptr == NULL`). If the file is not found, an error message is displayed, and the program exits. This prevents manipulating an invalid file.
- **Vector Size Handling**: The code uses containers like Vector and Map with dynamic sizes. Before accessing elements, it checks if the index is within valid bounds. For instance, in `generate_header()`, it checks if `HuffmanValue[i]` has a value before accessing its size. This prevents out-of-bounds access.
- **File Opening Error Handling**: When opening a file for reading (iptr) or writing (optr), it checks if the file opened correctly. If not, an error message is displayed, and the program exits, handling I/O failures gracefully.
- **Vector Size Verification**: Before accessing elements in vectors, such as in `sort_by_character_count()`, it checks if the vector `store` has at least two elements to combine (`store.size() > 2`). This prevents errors during Huffman tree creation.
- **File Size Verification**: Before starting decompression, it checks if the file size (Filesize) is consistent with the expected size. This prevents errors if the file size is incorrect.
- **End-of-File Checks**: During decompression, it checks if `size` matches the expected filesize before reading the next byte. This prevents reading beyond the file end.
- **Argument Number Verification**: The program checks if the number of command-line arguments is 4. If not, it displays an error message and exits, preventing errors from incorrect argument counts (-c or -d and the required 2 files).
- **Option Validation**: The program verifies if the command-line option is "-c" (compression) or "-d" (decompression). If invalid, an error message is displayed, and the program exits, ensuring valid options are used.
- **File Opening Error Handling**: The program attempts to open input and output files using `fopen`. If an error occurs, it displays an error message and exits, handling I/O failures gracefully. An empty file also has special handling to prevent related issues.