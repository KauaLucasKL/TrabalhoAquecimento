#ifndef FLORESTA_HPP
#define FLORESTA_HPP

#include <vector>
#include <string>
#include <utility> // para usar std::pair

// Incluindo o arquivo de configurações
#include "config.hpp"

class Floresta {
private:
    int linhas;
    int colunas;
    int linhaFogo;
    int colunaFogo;
    int linhaAnimal;
    int colunaAnimal;
    std::vector<std::vector<int>> matriz;
    std::vector<std::pair<int, int>> caminhoAnimal;

    int passosAnimal;
    int aguaEncontrada;
    int iteracaoMorte;
    int tempoSeguro;

public:
    Floresta();
    bool carregar(const std::string& nomeArquivo);
    void iniciarFogo();
    bool propagarFogo();
    bool moverAnimal();
    bool animalVivo() const;
    void salvarEstado(const std::string& nomeArquivo, int iteracao);
    void salvarRelatorio(const std::string& nomeArquivo);
};

#endif
