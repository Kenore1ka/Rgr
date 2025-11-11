# Название исполняемого файла
TARGET = ../build/encryptor

# Компилятор и флаги
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

# Директории
BUILD_DIR = ../build
SRC_DIR = .

# Автоматически находим все .cpp файлы
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)

# Генерируем имена объектных файлов, которые будут лежать в build
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SOURCES))

# Правило по умолчанию
all: $(TARGET)

# Правило сборки исполняемого файла
$(TARGET): $(OBJECTS)
	@echo "Linking..."
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)
	@echo "Build finished: $(TARGET)"

# Правило для компиляции .cpp файлов в .o файлы в директории build
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(wildcard $(SRC_DIR)/*.h)
	@mkdir -p $(BUILD_DIR)
	@echo "Compiling $<..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Очистка
clean:
	@echo "Cleaning build files..."
	rm -rf $(BUILD_DIR)

.PHONY: all clean