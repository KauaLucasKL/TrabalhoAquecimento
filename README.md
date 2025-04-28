# 🔥 Simulação de Propagação de Incêndio em Floresta com Animal em Fuga

## 📋 Descrição do Problema

O objetivo deste projeto é simular a propagação de um incêndio em uma floresta, representada como uma matriz 2D de células, enquanto um animal tenta sobreviver movendo-se por áreas seguras.  
A simulação deve considerar diferentes estratégias de propagação do fogo, tanto com quanto sem influência do vento, e registrar o caminho percorrido pelo animal até a sua sobrevivência ou morte.

Os requisitos principais incluem:

- O fogo se propaga ortogonalmente (cima, baixo, esquerda, direita).
- Com influência do vento, a propagação é restrita a direções configuradas.
- O animal se move para áreas seguras buscando sobreviver.
- A posição do animal é rastreada externamente à matriz.
- A configuração da simulação é feita via arquivo de cabeçalho `config.hpp`.
- Ao final, o caminho percorrido pelo animal é registrado.

---

## 💡 Solução Proposta

Foi desenvolvida uma aplicação em C++ estruturada da seguinte forma:

- **`config.hpp`**: Define variáveis globais, como estratégia de propagação, número máximo de iterações e direções de vento.
- **`Floresta.hpp` / `Floresta.cpp`**: Implementam a classe `Floresta`, que gerencia o estado da matriz, a propagação do fogo e o movimento do animal.
- **`main.cpp`**: Controla a sequência da simulação e a interação entre os componentes.
- **Arquivos de entrada e saída** (`input.dat` e `output.dat`) para representar o mapa inicial da floresta e registrar os resultados.

A aplicação é altamente configurável e modular, permitindo alterar estratégias sem necessidade de reescrever o código principal.

---


## 📚 Estruturas de Dados Utilizadas

| Estrutura         | Utilização                                              | Justificativa                                         |
|-------------------|----------------------------------------------------------|-------------------------------------------------------|
| `std::vector<std::vector<int>>` | Representação da matriz da floresta.               | Flexível e eficiente para manipular matrizes 2D em C++. |
| `std::pair<int, int>`           | Representação da posição do animal na floresta.    | Facilita o controle de coordenadas (linha, coluna).    |
| `std::queue<std::pair<int, int>>` | Utilizado para propagar o fogo pelas células.      | Permite uma expansão em ondas (BFS-like propagation). |
| `std::vector<int>`              | Representação das direções de propagação com vento.| Simples para indicar as direções válidas dinamicamente.|

As estruturas escolhidas garantem **eficiência de acesso** (`O(1)` para matrizes) e **simplicidade de manipulação**.

---

## 📈 Resultados de Desempenho e Análise


### Análise

- A propagação sem vento tende a consumir rapidamente a floresta inteira.
- Com vento, a propagação é mais lenta e direcional.
- A quantidade e a posição inicial das árvores e da água influenciam diretamente na dificuldade da simulação, tanto para o fogo se propagar quanto para o animal sobreviver.

---

## 🧠 Conclusões Finais

O desenvolvimento da simulação de propagação de incêndio permitiu explorar técnicas de:

- Simulação baseada em autômatos celulares.
- Controle de estados em sistemas dinâmicos.
- Aplicação de algoritmos de busca e propagação simples.

A separação de responsabilidades entre os arquivos melhorou a **modularidade** e facilitou a manutenção e testes.

---
