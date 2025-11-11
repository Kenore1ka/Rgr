#include "common.h"
#include "decrypt.h"
#include <vector>
#include <algorithm>

// --- Шифр Цезаря и Шифр с кодовым словом (остаются без изменений) ---

std::string caesar_decrypt(const std::string &text, int shift) {
    std::string result;
    for (unsigned char ch : text) {
        result += static_cast<char>((ch - shift + 256) % 256);
    }
    return result;
}

std::string keyword_decrypt(const std::string &text, const std::string &key) {
    if (key.empty()) {
        handle_error("Ключ для шифра с кодовым словом не может быть пустым.");
    }
    std::string result;
    int key_index = 0;
    for (char ch : text) {
        result += static_cast<char>(ch ^ key[key_index]);
        key_index = (key_index + 1) % key.length();
    }
    return result;
}


// --- Реализация дешифрования для "Байтового" Плейфера ---

// Подключаем объявления вспомогательных функций, реализованных в encrypt.cpp
// В реальном проекте их стоило бы вынести в отдельный playfair_utils.cpp
struct Point {
    int row, col;
};
void generate_playfair_matrix_16x16(const std::string &key, std::vector<std::vector<unsigned char>> &matrix);
Point find_position_16x16(const std::vector<std::vector<unsigned char>> &matrix, unsigned char byte_val);


std::string playfair_decrypt(const std::string &text, const std::string &key) {
    if (key.empty()) {
         handle_error("Ключ для шифра Плейфера не может быть пустым.");
    }
    if (text.length() % 2 != 0) {
        handle_error("Некорректная длина зашифрованного текста для Плейфера.");
    }
    
    std::vector<std::vector<unsigned char>> matrix;
    generate_playfair_matrix_16x16(key, matrix);
    std::string decrypted_text;

    for (size_t i = 0; i < text.length(); i += 2) {
        unsigned char a = text[i];
        unsigned char b = text[i+1];
        Point pos_a = find_position_16x16(matrix, a);
        Point pos_b = find_position_16x16(matrix, b);

        if (pos_a.row == pos_b.row) { // Та же строка
            decrypted_text += matrix[pos_a.row][(pos_a.col - 1 + 16) % 16];
            decrypted_text += matrix[pos_b.row][(pos_b.col - 1 + 16) % 16];
        } else if (pos_a.col == pos_b.col) { // Тот же столбец
            decrypted_text += matrix[(pos_a.row - 1 + 16) % 16][pos_a.col];
            decrypted_text += matrix[(pos_b.row - 1 + 16) % 16][pos_b.col];
        } else { // Прямоугольник
            decrypted_text += matrix[pos_a.row][pos_b.col];
            decrypted_text += matrix[pos_b.row][pos_a.col];
        }
    }

    // Удаляем нулевой байт в конце, если он был добавлен для выравнивания
    if (!decrypted_text.empty() && decrypted_text.back() == '\0') {
        decrypted_text.pop_back();
    }

    return decrypted_text;
}