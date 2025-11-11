#ifndef ENCRYPT_H
#define ENCRYPT_H

#include <string>

std::string caesar_encrypt(const std::string &text, int shift);
std::string playfair_encrypt(const std::string &text, const std::string &key);
std::string keyword_encrypt(const std::string &text, const std::string &key);

#endif