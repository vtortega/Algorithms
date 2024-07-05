#include "utility.hpp"

namespace Huffman {
namespace Utility {

ll get_file_size(const char* filename) {
    FILE* p_file = fopen(filename, "rb");
    fseek(p_file, 0, SEEK_END);
    ll size = ftello(p_file);
    fclose(p_file);
    return size;
}

}
} 
