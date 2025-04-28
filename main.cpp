#include "Floresta.hpp"
#include <iostream>
int main() {
    const int K = 100; // número máximo de interações permitidas
    Floresta floresta;

    if (!floresta.carregar("input.dat")) {
        return 1;
    }

   

    floresta.iniciarFogo();
    floresta.salvarEstado("output.dat", 0);

    int iteracao = 1;
    while (iteracao <= K && floresta.animalVivo() && floresta.propagarFogo()) {
        floresta.moverAnimal();
        floresta.salvarEstado("output.dat", iteracao);
        iteracao++;
    }

    floresta.salvarRelatorio("output.dat");

    std::cout << "Simulação concluída. Resultados em output.dat\n";
    return 0;
}