#include <iostream>

#define FILAS 8
#define COLUMNAS 8

void piezas(char tablero[FILAS][COLUMNAS]) {

    for (int i = 0; i < FILAS; i++)
        for (int j = 0; j < COLUMNAS; j++)
            tablero[i][j] = '*';

    tablero[0][0] = 't';
    tablero[0][1] = 'h';
    tablero[0][2] = 'b';
    tablero[0][3] = 'k';
    tablero[0][4] = 'q';
    tablero[0][5] = 'b';
    tablero[0][6] = 'h';
    tablero[0][7] = 't';

    for (int j = 0; j < 8; j++)
        tablero[1][j] = 'p';

    tablero[7][0] = 't';
    tablero[7][1] = 'h';
    tablero[7][2] = 'b';
    tablero[7][3] = 'k';
    tablero[7][4] = 'q';
    tablero[7][5] = 'b';
    tablero[7][6] = 'h';
    tablero[7][7] = 't';

    for (int j = 0; j < 8; j++)
        tablero[6][j] = 'P';
}

void tableroPrint(char tablero[FILAS][COLUMNAS]) {

    std::cout << "   ";
    for (int i = 0; i < COLUMNAS; i++)
        std::cout << i + 1 << " ";
    std::cout << "\n";

    for (int i = 0; i < FILAS; i++) {
        std::cout << i + 1 << "  ";
        for (int j = 0; j < COLUMNAS; j++)
            std::cout << tablero[i][j] << " ";
        std::cout << "\n";
    }
}

int main() {
    char tablero[FILAS][COLUMNAS];

    piezas(tablero);
    tableroPrint(tablero);

    return 0;
}
