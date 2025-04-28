#ifndef CONFIG_HPP
#define CONFIG_HPP

// Número máximo de iterações para a simulação
#define MAX_ITERACOES 1000

// Estratégia de propagação do fogo
#define SEM_INFLUENCIA_VENTO 0
#define COM_INFLUENCIA_VENTO 1

// Escolha a estratégia de propagação do fogo
#define ESTRATEGIA_PROPAGACAO COM_INFLUENCIA_VENTO

// Direções de propagação do fogo quando há influência do vento
// 0 - Sem vento (propaga em todas as 4 direções)
// 1 - Direção para a esquerda
// 2 - Direção para a direita
// 3 - Direção para cima
// 4 - Direção para baixo
#define DIRECOES_VENTO {1, 3} // Exemplo: vento para esquerda e para cima

#endif // CONFIG_HPP
