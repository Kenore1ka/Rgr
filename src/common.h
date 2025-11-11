#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <sstream>
#include <limits> // Для защиты от некорректного ввода

// Общие константы
const std::string ENCRYPTED_FILE_SUFFIX = ".enc";
const std::string DECRYPTED_FILE_SUFFIX = ".dec";

// Общие функции
void handle_error(const std::string &message);

#endif