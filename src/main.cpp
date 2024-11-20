#include "common.h"

extern std::string read_file(const std::string &);
extern void write_file(const std::string &, const std::string &);
extern std::string caesar_encrypt(const std::string &, int);
extern std::string caesar_decrypt(const std::string &, int);

void print_usage() {
    std::cout << "Использование:\n";
    std::cout << "  ./encryptor --input <путь к файлу>\n";
    std::cout << "  ./encryptor --encrypt <путь к файлу>\n";
    std::cout << "  ./encryptor --decrypt <путь к файлу>\n";
    std::cout << "  ./encryptor --print <путь к файлу>\n";
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        print_usage();
        return EXIT_FAILURE;
    }

    std::string command = argv[1];
    std::string file_path = argv[2];

    try {
        if (command == "--input") {
            std::cout << "Введите текст. Для завершения ввода нажмите Enter, затем Ctrl+D:\n";
            std::string input_text;
            std::string line;

            while (std::getline(std::cin, line)) {
                input_text += line + "\n";
            }

            write_file(file_path, input_text);
            std::cout << "Текст сохранён в файл: " << file_path << std::endl;

        } else if (command == "--encrypt") {
            std::cout << "Введите сдвиг для шифра Цезаря: ";
            int shift;
            std::cin >> shift;

            std::string content = read_file(file_path);
            std::string encrypted = caesar_encrypt(content, shift);

            write_file(file_path + ENCRYPTED_FILE_SUFFIX, encrypted);
            std::cout << "Файл зашифрован и сохранён как: " << file_path + ENCRYPTED_FILE_SUFFIX << std::endl;

        } else if (command == "--decrypt") {
            std::cout << "Введите сдвиг для шифра Цезаря: ";
            int shift;
            std::cin >> shift;

            std::string content = read_file(file_path);
            std::string decrypted = caesar_decrypt(content, shift);

            write_file(file_path + DECRYPTED_FILE_SUFFIX, decrypted);
            std::cout << "Файл расшифрован и сохранён как: " << file_path + DECRYPTED_FILE_SUFFIX << std::endl;

        } else if (command == "--print") {
            std::string content = read_file(file_path);
            std::cout << "Содержимое файла:\n" << content << std::endl;

        } else {
            print_usage();
        }

    } catch (const std::exception &e) {
        handle_error(e.what());
    }

    return 0;
}
