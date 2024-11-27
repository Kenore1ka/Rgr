#include "common.h"

extern std::string read_file(const std::string &);
extern void validate_password(const std::string &, const std::string &);
extern void write_file(const std::string &, const std::string &);

extern std::string caesar_encrypt(const std::string &, int);
extern std::string caesar_decrypt(const std::string &, int);

extern std::string playfair_encrypt(const std::string &, const std::string &);
extern std::string playfair_decrypt(const std::string &, const std::string &);

extern std::string keyword_encrypt(const std::string &, const std::string &);
extern std::string keyword_decrypt(const std::string &, const std::string &);

void print_usage() {
    std::cout << "Использование:\n";
    std::cout << "  ./encryptor --input <путь к файлу>\n";
    std::cout << "  ./encryptor --encrypt <путь к файлу>\n";
    std::cout << "  ./encryptor --decrypt <путь к файлу>\n";
    std::cout << "  ./encryptor --print <путь к файлу>\n";
}

void input_command(const std::string &file_path) {
    std::cout << "Введите текст. Для завершения ввода нажмите Enter, затем Ctrl+D:\n";
    std::string input_text;
    std::string line;

    while (std::getline(std::cin, line)) {
        input_text += line + "\n";
    }

    write_file(file_path, input_text);
    std::cout << "Текст сохранён в файл: " << file_path << std::endl;
}

void encrypt_command(const std::string &file_path) {
    std::cout << "Выберите метод шифрования:\n"
              << "1 - Шифр Цезаря\n"
              << "2 - Шифр Плейфера\n"
              << "3 - Шифр с кодовым словом\n";
    int method;
    std::cin >> method;

    std::cin.ignore(); // Очистка ввода после считывания числа
    std::string content = read_file(file_path);
    std::string encrypted;

    if (method == 1) {
        std::cout << "Введите сдвиг: ";
        int shift;
        std::cin >> shift;
        encrypted = caesar_encrypt(content, shift);

    } else if (method == 2) {
        std::cout << "Введите ключ для шифра Плейфера: ";
        std::string key;
        std::cin >> key;
        encrypted = playfair_encrypt(content, key);

    } else if (method == 3) {
        std::cout << "Введите кодовое слово: ";
        std::string key;
        std::cin >> key;
        encrypted = keyword_encrypt(content, key);

    } else {
        handle_error("Неверный выбор метода шифрования.");
    }

    write_file(file_path + ENCRYPTED_FILE_SUFFIX, encrypted);
    std::cout << "Файл зашифрован и сохранён как: " << file_path + ENCRYPTED_FILE_SUFFIX << std::endl;
}

void decrypt_command(const std::string &file_path) {
    std::cout << "Выберите метод дешифрования:\n"
              << "1 - Шифр Цезаря\n"
              << "2 - Шифр Плейфера\n"
              << "3 - Шифр с кодовым словом\n";
    int method;
    std::cin >> method;

    std::cin.ignore(); // Очистка ввода после считывания числа
    std::string content = read_file(file_path);
    std::string decrypted;

    if (method == 1) {
        std::cout << "Введите сдвиг: ";
        int shift;
        std::cin >> shift;
        decrypted = caesar_decrypt(content, shift);

    } else if (method == 2) {
        std::cout << "Введите ключ для шифра Плейфера: ";
        std::string key;
        std::cin >> key;
        decrypted = playfair_decrypt(content, key);

    } else if (method == 3) {
        std::cout << "Введите кодовое слово: ";
        std::string key;
        std::cin >> key;
        decrypted = keyword_decrypt(content, key);

    } else {
        handle_error("Неверный выбор метода дешифрования.");
    }

    write_file(file_path + DECRYPTED_FILE_SUFFIX, decrypted);
    std::cout << "Файл расшифрован и сохранён как: " << file_path + DECRYPTED_FILE_SUFFIX << std::endl;
}

void print_command(const std::string &file_path) {
    std::string content = read_file(file_path);
    std::cout << "Содержимое файла:\n" << content << std::endl;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        print_usage();
        return EXIT_FAILURE;
    }
    const std::string headPassword = "aboba";
    std::string password;
    
    std::string command = argv[1];
    std::string file_path = argv[2];

    try {
        if (command == "--input") {
            input_command(file_path);
        } else if (command == "--encrypt") {
            std::cout << "Введите пароль:\n";
            std::cin >> password;
            validate_password(password, headPassword);
            encrypt_command(file_path);
        } else if (command == "--decrypt") {
            std::cout << "Введите пароль:\n";
            std::cin >> password;
            validate_password(password, headPassword);
            decrypt_command(file_path);
        } else if (command == "--print") {
            print_command(file_path);
        } else {
            print_usage();
        }
    } catch (const std::exception &e) {
        handle_error(e.what());
    }

    return 0;
}
