#include <iostream>

#define FILAS 10
#define COLUMNAS 10
#define NUMEROS 9

void tablero();

int main() {
    tablero();
    return 0;
}

void tablero() {
    for (int i = 0; i < FILAS; i++) {
        for (int x = 0; x < COLUMNAS; x++) {

            if (i == 0 || i == FILAS - 1) {
                std::cout << " -";
            }
            else if (x == 0) {
                std::cout << "|";
            }
            else if (x == COLUMNAS - 2) {
                std::cout << "-|";
            }
            else if (x == COLUMNAS - 1) {
                std::cout << i;
            }
            else {
                std::cout << "-|";
            }

        }
        std::cout << "\n";
    }
}
