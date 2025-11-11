#ifndef DECRYPT_H
#define DECRYPT_H

#include <string>

std::string caesar_decrypt(const std::string &text, int shift);
std::string playfair_decrypt(const std::string &text, const std::string &key);
std::string keyword_decrypt(const std::string &text, const std::string &key);

#endif