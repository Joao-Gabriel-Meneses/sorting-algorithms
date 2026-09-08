# Laboratorio 1 - Algoritmos de Ordenacao
#
#   make            -> compila o programa principal (bin/ordenacao)
#   make run        -> compila e executa o menu
#   make test       -> compila e roda TODOS os testes
#   make test-heap  -> roda apenas os testes do Heap Sort
#   make clean      -> remove os binarios

CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2

SRC_DIR  := src
TEST_DIR := test
BIN_DIR  := bin

# Modulos compartilhados pelo programa principal
FONTES := $(SRC_DIR)/main.cpp \
          $(SRC_DIR)/gerador.cpp \
          $(SRC_DIR)/tabela.cpp \
          $(SRC_DIR)/selection-sort.cpp \
          $(SRC_DIR)/insertion-sort.cpp \
          $(SRC_DIR)/shell-sort.cpp \
          $(SRC_DIR)/quick-sort.cpp \
          $(SRC_DIR)/heap-sort.cpp

ALVO := $(BIN_DIR)/ordenacao

TESTES := gerador selection-sort insertion-sort shell-sort quick-sort heap-sort
BIN_TESTES := $(addprefix $(BIN_DIR)/test-,$(TESTES))

.PHONY: all run test clean $(addprefix test-,$(TESTES))

all: $(ALVO)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(ALVO): $(FONTES) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $(FONTES)

run: $(ALVO)
	./$(ALVO)

# Cada teste vira um executavel proprio, ligado apenas ao que precisa
$(BIN_DIR)/test-gerador: $(TEST_DIR)/gerador-test.cpp $(SRC_DIR)/gerador.cpp | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(BIN_DIR)/test-selection-sort: $(TEST_DIR)/selection-sort-test.cpp $(SRC_DIR)/selection-sort.cpp $(SRC_DIR)/gerador.cpp | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(BIN_DIR)/test-insertion-sort: $(TEST_DIR)/insertion-sort-test.cpp $(SRC_DIR)/insertion-sort.cpp $(SRC_DIR)/gerador.cpp | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(BIN_DIR)/test-shell-sort: $(TEST_DIR)/shell-sort-test.cpp $(SRC_DIR)/shell-sort.cpp $(SRC_DIR)/insertion-sort.cpp $(SRC_DIR)/gerador.cpp | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(BIN_DIR)/test-quick-sort: $(TEST_DIR)/quick-sort-test.cpp $(SRC_DIR)/quick-sort.cpp $(SRC_DIR)/gerador.cpp | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(BIN_DIR)/test-heap-sort: $(TEST_DIR)/heap-sort-test.cpp $(SRC_DIR)/heap-sort.cpp $(SRC_DIR)/gerador.cpp | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

test-%: $(BIN_DIR)/test-%
	@./$<

test: $(BIN_TESTES)
	@for t in $(BIN_TESTES); do ./$$t || exit 1; echo; done
	@echo "======================================"
	@echo " TODOS OS MODULOS PASSARAM NOS TESTES"
	@echo "======================================"

clean:
	rm -rf $(BIN_DIR)
