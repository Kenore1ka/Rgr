#include "common.h"

std::string caesar_decrypt(const std::string &text, int shift) {
    std::string result;
    for (char ch : text) {
        result += static_cast<char>(ch - shift);
    }
    return result;
}
