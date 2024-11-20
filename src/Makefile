# Название исполняемого файла
TARGET = ../build/encryptor

# Компилятор и флаги
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

# Исходные файлы
SRC = main.cpp encrypt.cpp decrypt.cpp file_utils.cpp
OBJ = $(SRC:.cpp=.o)

# Правило сборки
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

# Компиляция отдельных файлов
%.o: %.cpp common.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Очистка
clean:
	rm -f $(OBJ) $(TARGET)
