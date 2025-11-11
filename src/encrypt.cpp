#include "common.h"
#include "encrypt.h"
#include <vector>
#include <algorithm>

// Цезарь
std::string caesar_encrypt(const std::string &text, int shift) {
    std::string result;
    for (unsigned char ch : text) {
        result += static_cast<char>((ch + shift) % 256);
    }
    return result;
}

// Кодовое слово
std::string keyword_encrypt(const std::string &text, const std::string &key) {
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

// Плейфер

// Вспомогательная структура для координат в матрице 16x16
struct Point {
    int row, col;
};

// Генерация матрицы 16x16 для всех возможных байтов
void generate_playfair_matrix_16x16(const std::string &key, std::vector<std::vector<unsigned char>> &matrix) {
    matrix.assign(16, std::vector<unsigned char>(16));
    std::vector<bool> used(256, false);
    std::string temp_key;

    // Добавляем уникальные байты из ключа
    for (unsigned char ch : key) {
        if (!used[ch]) {
            temp_key += ch;
            used[ch] = true;
        }
    }

    // Добавляем все остальные байты (от 0 до 255)
    for (int i = 0; i < 256; ++i) {
        if (!used[i]) {
            temp_key += static_cast<unsigned char>(i);
        }
    }

    // Заполняем матрицу 16x16
    int k = 0;
    for (int i = 0; i < 16; ++i) {
        for (int j = 0; j < 16; ++j) {
            matrix[i][j] = temp_key[k++];
        }
    }
}

// Поиск позиции байта в матрице
Point find_position_16x16(const std::vector<std::vector<unsigned char>> &matrix, unsigned char byte_val) {
    for (int i = 0; i < 16; ++i) {
        for (int j = 0; j < 16; ++j) {
            if (matrix[i][j] == byte_val) {
                return {i, j};
            }
        }
    }
    return {-1, -1};
}

std::string playfair_encrypt(const std::string &text, const std::string &key) {
    if (key.empty()) {
         handle_error("Ключ для шифра Плейфера не может быть пустым.");
    }
    std::vector<std::vector<unsigned char>> matrix;
    generate_playfair_matrix_16x16(key, matrix);
    
    std::string prepared_text = text;
    // Если длина текста нечетная, добавляем нулевой байт для создания последней пары
    if (prepared_text.length() % 2 != 0) {
        prepared_text += '\0';
    }

    std::string encrypted_text;
    for (size_t i = 0; i < prepared_text.length(); i += 2) {
        unsigned char a = prepared_text[i];
        unsigned char b = prepared_text[i+1];

        // Вставка байта-заполнителя, если байты в паре одинаковы
        if (a == b) {
            b = '\0'; // Используем нулевой байт как заполнитель
        }

        Point pos_a = find_position_16x16(matrix, a);
        Point pos_b = find_position_16x16(matrix, b);

        if (pos_a.row == pos_b.row) { // Та же строка
            encrypted_text += matrix[pos_a.row][(pos_a.col + 1) % 16];
            encrypted_text += matrix[pos_b.row][(pos_b.col + 1) % 16];
        } else if (pos_a.col == pos_b.col) { // Тот же столбец
            encrypted_text += matrix[(pos_a.row + 1) % 16][pos_a.col];
            encrypted_text += matrix[(pos_b.row + 1) % 16][pos_b.col];
        } else { // Прямоугольник
            encrypted_text += matrix[pos_a.row][pos_b.col];
            encrypted_text += matrix[pos_b.row][pos_a.col];
        }
    }
    return encrypted_text;
}