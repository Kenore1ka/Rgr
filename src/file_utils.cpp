#include "common.h"
#include "file_utils.h"

// Вместо exit() выбрасываем исключение
void handle_error(const std::string &message) {
    throw std::runtime_error(message);
}

void validate_password(const std::string &input_password, const std::string &expected_password) {
    if (input_password != expected_password) {
        handle_error("Неверный пароль.");
    }
}

std::string read_file(const std::string &path) {
    std::ifstream file(path, std::ios::binary); // Используем binary для корректного чтения любых данных
    if (!file.is_open()) {
        handle_error("Не удалось открыть файл: " + path);
    }

    std::ostringstream content;
    content << file.rdbuf();
    file.close();
    return content.str();
}

void write_file(const std::string &path, const std::string &content) {
    std::ofstream file(path, std::ios::binary); // Используем binary для корректной записи
    if (!file.is_open()) {
        handle_error("Не удалось открыть файл для записи: " + path);
    }

    file << content;
    file.close();
}