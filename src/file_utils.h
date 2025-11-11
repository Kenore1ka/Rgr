#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <string>

void validate_password(const std::string &input_password, const std::string &expected_password);
std::string read_file(const std::string &path);
void write_file(const std::string &path, const std::string &content);

#endif