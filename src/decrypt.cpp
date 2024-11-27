#include "common.h"

// Caesar Cipher (уже реализован)
std::string caesar_decrypt(const std::string &text, int shift) {
    std::string result;
    for (char ch : text) {
        result += static_cast<char>(ch - shift);
    }
    return result;
}

// Playfair Cipher
std::string playfair_decrypt(const std::string &text, const std::string &key) {
    std::string result;
    for (char ch : text) {
        result += static_cast<char>((ch - key.length() + 256) % 256);
    }
    return result;
}

// Keyword-based Cipher
std::string keyword_decrypt(const std::string &text, const std::string &key) {
    std::string result;
    int key_index = 0;
    for (char ch : text) {
        result += static_cast<char>(ch ^ key[key_index]);
        key_index = (key_index + 1) % key.length();
    }
    return result;
}
