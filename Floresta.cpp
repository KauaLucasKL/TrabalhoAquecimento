#include "Floresta.hpp"
#include <fstream>
#include <iostream>
#include <cstdlib>  // para rand()
#include <ctime>    // para time()
#include "config.hpp"  // Incluindo o arquivo de configurações

Floresta::Floresta()
    : linhas(0), colunas(0),
      linhaFogo(0), colunaFogo(0),
      linhaAnimal(-1), colunaAnimal(-1),
      passosAnimal(0), aguaEncontrada(0),
      iteracaoMorte(-1), tempoSeguro(0),
      caminhoAnimal() {}

bool Floresta::carregar(const std::string& nomeArquivo) {
    std::ifstream input(nomeArquivo);
    if (!input.is_open()) {
        std::cerr << "Erro ao abrir o arquivo de entrada.\n";
        return false;
    }

    input >> linhas >> colunas >> linhaFogo >> colunaFogo;
    matriz.resize(linhas, std::vector<int>(colunas));

    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            input >> matriz[i][j];
        }
    }
    input.close();

    // Encontrar posição segura para o animal
    std::srand(std::time(nullptr));
    std::vector<std::pair<int, int>> posicoesSeguras;
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            if (matriz[i][j] == 0) {
                posicoesSeguras.push_back({i, j});
            }
        }
    }

    if (posicoesSeguras.empty()) {
        std::cerr << "Nao ha celulas seguras para posicionar o animal.\n";
        return false;
    }

    int indice = std::rand() % posicoesSeguras.size();
    linhaAnimal = posicoesSeguras[indice].first;
    colunaAnimal = posicoesSeguras[indice].second;
    caminhoAnimal.push_back({linhaAnimal, colunaAnimal});

    return true;
}

void Floresta::iniciarFogo() {
    if (linhaFogo >= 0 && linhaFogo < linhas && colunaFogo >= 0 && colunaFogo < colunas) {
        if (matriz[linhaFogo][colunaFogo] == 1 || matriz[linhaFogo][colunaFogo] == 5) {
            matriz[linhaFogo][colunaFogo] = 2; // fogo ativo
        }
    }
}

bool Floresta::propagarFogo() {
    bool houvePropagacao = false;
    std::vector<std::vector<int>> proximaMatriz = matriz;

    const int dx[] = {-1, 1, 0, 0};  // cima, baixo, esquerda, direita
    const int dy[] = {0, 0, -1, 1};

    // Se não há influência do vento, propagação normal (em 4 direções)
    if (ESTRATEGIA_PROPAGACAO == SEM_INFLUENCIA_VENTO) {
        for (int i = 0; i < linhas; ++i) {
            for (int j = 0; j < colunas; ++j) {
                if (matriz[i][j] == 2) {
                    proximaMatriz[i][j] = 3;

                    // Propagar para as 4 direções (sem vento)
                    for (int dir = 0; dir < 4; ++dir) {
                        int ni = i + dx[dir];
                        int nj = j + dy[dir];
                        if (ni >= 0 && ni < linhas && nj >= 0 && nj < colunas) {
                            if (matriz[ni][nj] == 1 || matriz[ni][nj] == 5) {
                                proximaMatriz[ni][nj] = 2;
                                houvePropagacao = true;
                            }
                        }
                    }
                }
            }
        }
    }
    // Se há influência do vento, propagação controlada
    else if (ESTRATEGIA_PROPAGACAO == COM_INFLUENCIA_VENTO) {
        // Direções de vento configuradas no config.hpp
        int direcoesVento[] = DIRECOES_VENTO;

        for (int i = 0; i < linhas; ++i) {
            for (int j = 0; j < colunas; ++j) {
                if (matriz[i][j] == 2) {
                    proximaMatriz[i][j] = 3;

                    // Propagar de acordo com as direções de vento configuradas
                    for (int dir : direcoesVento) {
                        int ni = i + dx[dir];
                        int nj = j + dy[dir];
                        if (ni >= 0 && ni < linhas && nj >= 0 && nj < colunas) {
                            if (matriz[ni][nj] == 1 || matriz[ni][nj] == 5) {
                                proximaMatriz[ni][nj] = 2;
                                houvePropagacao = true;
                            }
                        }
                    }
                }
            }
        }
    }

    matriz = proximaMatriz;

    // Verificar se o animal foi atingido pelo fogo
    if (linhaAnimal != -1 && matriz[linhaAnimal][colunaAnimal] == 2) {
        if (!moverAnimal()) {
            iteracaoMorte = passosAnimal;
            linhaAnimal = -1;
            colunaAnimal = -1;
        }
    }

    return houvePropagacao;
}

bool Floresta::moverAnimal() {
    if (linhaAnimal == -1 || colunaAnimal == -1) return false; // Animal já morreu

    const int dx[] = {-1, 1, 0, 0};
    const int dy[] = {0, 0, -1, 1};

    int melhorValor = 5; // maior que qualquer valor de célula
    int novoX = linhaAnimal;
    int novoY = colunaAnimal;

    for (int dir = 0; dir < 4; ++dir) {
        int nx = linhaAnimal + dx[dir];
        int ny = colunaAnimal + dy[dir];
        if (nx >= 0 && nx < linhas && ny >= 0 && ny < colunas) {
            int valor = matriz[nx][ny];
            if (valor == 4 && melhorValor > 1) { // água
                melhorValor = 1;
                novoX = nx;
                novoY = ny;
            } else if (valor == 0 && melhorValor > 2) { // vazio
                melhorValor = 2;
                novoX = nx;
                novoY = ny;
            } else if (valor == 1 && melhorValor > 3) { // árvore saudável
                melhorValor = 3;
                novoX = nx;
                novoY = ny;
            }
        }
    }

    if (novoX != linhaAnimal || novoY != colunaAnimal) {
        linhaAnimal = novoX;
        colunaAnimal = novoY;
        caminhoAnimal.push_back({linhaAnimal, colunaAnimal});
        passosAnimal++;
        tempoSeguro = 0;

        if (matriz[linhaAnimal][colunaAnimal] == 4) {
            aguaEncontrada++;
            matriz[linhaAnimal][colunaAnimal] = 0;
            for (int dir = 0; dir < 4; ++dir) {
                int adjX = linhaAnimal + dx[dir];
                int adjY = colunaAnimal + dy[dir];
                if (adjX >= 0 && adjX < linhas && adjY >= 0 && adjY < colunas) {
                    matriz[adjX][adjY] = 1;
                }
            }
        }
        return true;
    } else {
        if (matriz[linhaAnimal][colunaAnimal] == 0) {
            tempoSeguro++;
            if (tempoSeguro > 3) {
                return false;
            }
        }
    }
    return true;
}

bool Floresta::animalVivo() const {
    return linhaAnimal != -1 && colunaAnimal != -1;
}

void Floresta::salvarEstado(const std::string& nomeArquivo, int iteracao) {
    std::ofstream output(nomeArquivo, std::ios::app);
    if (!output.is_open()) {
        std::cerr << "Erro ao abrir o arquivo de saída.\n";
        return;
    }

    output << "Iteracao " << iteracao << ":\n";
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            if (i == linhaAnimal && j == colunaAnimal)
                output << "A ";
            else
                output << matriz[i][j] << " ";
        }
        output << "\n";
    }
    output << "\n";
    output.close();
}

void Floresta::salvarRelatorio(const std::string& nomeArquivo) {
    std::ofstream output(nomeArquivo, std::ios::app);
    if (!output.is_open()) {
        std::cerr << "Erro ao abrir o arquivo de relatório.\n";
        return;
    }

    output << "Relatorio final:\n";
    output << "Passos percorridos pelo animal: " << passosAnimal << "\n";
    output << "Quantidade de fontes de agua encontradas: " << aguaEncontrada << "\n";
    if (iteracaoMorte != -1)
        output << "Animal morto na iteracao: " << iteracaoMorte << "\n";
    else
        output << "Animal sobreviveu ate o final.\n";

    output << "Caminho percorrido pelo animal:\n";
    for (const auto& pos : caminhoAnimal) {
        output << "(" << pos.first << ", " << pos.second << ") ";
    }
    output << "\n";

    output.close();
}
