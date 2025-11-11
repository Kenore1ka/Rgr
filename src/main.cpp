#include "common.h"
#include "encrypt.h"
#include "decrypt.h"
#include "file_utils.h"

void print_usage() {
    std::cout << "Использование:\n";
    std::cout << "  ./encryptor --input <путь к файлу>       - Ввод текста в файл\n";
    std::cout << "  ./encryptor --encrypt <путь к файлу>     - Зашифровать файл\n";
    std::cout << "  ./encryptor --decrypt <путь к файлу>     - Расшифровать файл\n";
    std::cout << "  ./encryptor --print <путь к файлу>       - Показать содержимое файла\n";
}

void input_command(const std::string &file_path) {
    std::cout << "Введите текст.\n";

    std::stringstream buffer;
    buffer << std::cin.rdbuf();
    std::string input_text = buffer.str();

    if (!input_text.empty() && input_text.back() == 26) {
        input_text.pop_back();
    }

    write_file(file_path, input_text);
    std::cout << "Текст сохранён в файл: " << file_path << std::endl;
}

// Вспомогательная функция для надежного ввода числа
int get_menu_choice(int min, int max) {
    int choice;
    while (!(std::cin >> choice) || choice < min || choice > max) {
        std::cout << "Некорректный ввод. Пожалуйста, введите число от " << min << " до " << max << ": ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очистка буфера для следующего ввода
    return choice;
}

void encrypt_command(const std::string &file_path) {
    std::cout << "Выберите метод шифрования:\n"
              << "1 - Шифр Цезаря\n"
              << "2 - Шифр Плейфера\n"
              << "3 - Шифр с кодовым словом\n"
              << "Ваш выбор: ";
    int method = get_menu_choice(1, 3);
    
    std::string content = read_file(file_path);
    std::string encrypted;

    if (method == 1) {
        std::cout << "Введите сдвиг (целое число): ";
        int shift;
        while (!(std::cin >> shift)) {
             std::cout << "Некорректный ввод. Пожалуйста, введите целое число: ";
             std::cin.clear();
             std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        encrypted = caesar_encrypt(content, shift);

    } else if (method == 2) {
        std::cout << "Введите ключ для шифра Плейфера (латинские буквы): ";
        std::string key;
        std::getline(std::cin, key);
        encrypted = playfair_encrypt(content, key);

    } else if (method == 3) {
        std::cout << "Введите кодовое слово: ";
        std::string key;
        std::getline(std::cin, key);
        encrypted = keyword_encrypt(content, key);
    }

    write_file(file_path + ENCRYPTED_FILE_SUFFIX, encrypted);
    std::cout << "Файл зашифрован и сохранён как: " << file_path + ENCRYPTED_FILE_SUFFIX << std::endl;
}

void decrypt_command(const std::string &file_path) {
    std::cout << "Выберите метод дешифрования:\n"
              << "1 - Шифр Цезаря\n"
              << "2 - Шифр Плейфера\n"
              << "3 - Шифр с кодовым словом\n"
              << "Ваш выбор: ";
    int method = get_menu_choice(1, 3);

    std::string content = read_file(file_path);
    std::string decrypted;

    if (method == 1) {
        std::cout << "Введите сдвиг, использованный при шифровании: ";
        int shift;
        while (!(std::cin >> shift)) {
             std::cout << "Некорректный ввод. Пожалуйста, введите целое число: ";
             std::cin.clear();
             std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        decrypted = caesar_decrypt(content, shift);

    } else if (method == 2) {
        std::cout << "Введите ключ для шифра Плейфера: ";
        std::string key;
        std::getline(std::cin, key);
        decrypted = playfair_decrypt(content, key);

    } else if (method == 3) {
        std::cout << "Введите кодовое слово: ";
        std::string key;
        std::getline(std::cin, key);
        decrypted = keyword_decrypt(content, key);
    }

    std::string output_path = file_path;
    // Убираем суффикс .enc, если он есть
    if(output_path.size() > 4 && output_path.substr(output_path.size() - 4) == ENCRYPTED_FILE_SUFFIX) {
        output_path = output_path.substr(0, output_path.size() - 4);
    }
    
    write_file(output_path + DECRYPTED_FILE_SUFFIX, decrypted);
    std::cout << "Файл расшифрован и сохранён как: " << output_path + DECRYPTED_FILE_SUFFIX << std::endl;
}

void print_command(const std::string &file_path) {
    std::string content = read_file(file_path);
    std::cout << "--- Содержимое файла: " << file_path << " ---\n" << content << "\n--- Конец файла ---\n";
}

int main(int argc, char *argv[]) {
    // Для корректного отображения кириллицы в консоли Windows
    #ifdef _WIN32
        setlocale(LC_ALL, "Russian");
    #endif

    if (argc < 3) {
        print_usage();
        return 1;
    }
    
    const std::string headPassword = "aboba";
    std::string command = argv[1];
    std::string file_path = argv[2];

    try {
        if (command == "--input") {
            input_command(file_path);
        } else if (command == "--encrypt" || command == "--decrypt") {
            std::cout << "Введите пароль: ";
            std::string password;
            std::getline(std::cin, password);
            validate_password(password, headPassword);
            
            if(command == "--encrypt") {
                encrypt_command(file_path);
            } else {
                decrypt_command(file_path);
            }
        } else if (command == "--print") {
            print_command(file_path);
        } else {
            std::cerr << "Неизвестная команда: " << command << std::endl;
            print_usage();
            return 1;
        }
    } catch (const std::exception &e) {
        std::cerr << "Произошла ошибка: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}