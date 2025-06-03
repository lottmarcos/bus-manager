CXX = g++
CXXFLAGS = -std=c++14 -Wall -I./include -I./include/models -I./include/services -g
LDFLAGS = -lgtest -lgtest_main -pthread -lsqlite3 --coverage

CXXFLAGS += --coverage

SRC_DIR = src
BUILD_DIR = build
UNIT_TEST_DIR = tests/unit
INTEGRATION_TEST_DIR = tests/integration

# Fontes organizados por subdiretórios
SRC_MODELS = $(wildcard $(SRC_DIR)/models/*.cpp)
SRC_SERVICES = $(wildcard $(SRC_DIR)/services/*.cpp)
SRC_MAIN = $(SRC_DIR)/main.cpp
SRC = $(SRC_MODELS) $(SRC_SERVICES) $(filter-out $(SRC_DIR)/main.cpp, $(SRC_MAIN))

OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Encontrar todos os arquivos de teste
UNIT_TEST_SOURCES = $(wildcard $(UNIT_TEST_DIR)/*.cpp)
INTEGRATION_TEST_SOURCES = $(wildcard $(INTEGRATION_TEST_DIR)/*.cpp)

# Gerar objetos para os testes
UNIT_TEST_OBJ = $(UNIT_TEST_SOURCES:$(UNIT_TEST_DIR)/%.cpp=$(BUILD_DIR)/unit/%.o)
INTEGRATION_TEST_OBJ = $(INTEGRATION_TEST_SOURCES:$(INTEGRATION_TEST_DIR)/%.cpp=$(BUILD_DIR)/integration/%.o)

# Executáveis para os testes e a main
UNIT_TEST_EXEC = $(BUILD_DIR)/unit_tests_executavel
INTEGRATION_TEST_EXEC = $(BUILD_DIR)/integration_tests_executavel
MAIN_EXEC = $(BUILD_DIR)/main_executavel

# Criar diretório de build
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Criar diretórios para os objetos de testes
$(BUILD_DIR)/unit:
	mkdir -p $(BUILD_DIR)/unit

$(BUILD_DIR)/integration:
	mkdir -p $(BUILD_DIR)/integration

# Compilação dos arquivos fonte
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compilação dos arquivos de teste (unitários e de integração)
$(BUILD_DIR)/unit/%.o: $(UNIT_TEST_DIR)/%.cpp $(BUILD_DIR)/unit
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/integration/%.o: $(INTEGRATION_TEST_DIR)/%.cpp $(BUILD_DIR)/integration
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compilação do executável de testes de unidade
$(UNIT_TEST_EXEC): $(OBJ) $(UNIT_TEST_OBJ)
	$(CXX) $(OBJ) $(UNIT_TEST_OBJ) $(LDFLAGS) -o $(UNIT_TEST_EXEC)

# Compilação do executável de testes de integração
$(INTEGRATION_TEST_EXEC): $(OBJ) $(INTEGRATION_TEST_OBJ)
	$(CXX) $(OBJ) $(INTEGRATION_TEST_OBJ) $(LDFLAGS) -o $(INTEGRATION_TEST_EXEC)

# Compilação do executável da main
$(MAIN_EXEC): $(OBJ) $(SRC_MAIN)
	$(CXX) $(OBJ) $(SRC_MAIN) $(CXXFLAGS) $(LDFLAGS) -o $(MAIN_EXEC)

# Rodar os testes unitários
run_unit_tests: $(UNIT_TEST_EXEC)
	./$(UNIT_TEST_EXEC)

# Rodar os testes de integração
run_integration_tests: $(INTEGRATION_TEST_EXEC)
	./$(INTEGRATION_TEST_EXEC)

# Rodar o executável principal
run_main: $(MAIN_EXEC)
	clear
	./$(MAIN_EXEC)

# Limpeza dos arquivos gerados
clean:
	rm -rf $(BUILD_DIR)

# Alvo padrão
all: run_unit_tests run_integration_tests
