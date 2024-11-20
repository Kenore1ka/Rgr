#include "common.h"

void handle_error(const std::string &message) {
    std::cerr << "Ошибка: " << message << std::endl;
    exit(EXIT_FAILURE);
}

std::string read_file(const std::string &path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        handle_error("Не удалось открыть файл: " + path);
    }

    std::ostringstream content;
    content << file.rdbuf();
    file.close();
    return content.str();
}

void write_file(const std::string &path, const std::string &content) {
    std::ofstream file(path);
    if (!file.is_open()) {
        handle_error("Не удалось открыть файл для записи: " + path);
    }

    file << content;
    file.close();
}
