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


void pedirMovimiento() {
    int filaOrigen, columnaOrigen;
    int filaDestino, columnaDestino;
    std::cout << "Ingrese la fila de la pieza que se tiene que movver: ";
    std::cin >> filaOrigen;
    std::cout << "Ingrese la columna de la pieza que se tiene que movver: ";
    std::cin >> columnaOrigen;
    std::cout << "Ingrese la fila donde quieres mover la pieza : ";
    std::cin >> filaDestino;
    std::cout << "Ingrese la columna donde quieres mover la pieza : ";
    std::cin >> columnaDestino;
}

void moverPieza(char tablero[FILAS][COLUMNAS], int filaOrigen, int columnaOrigen, int filaDestino, int columnaDestino) {

    char pieza = tablero[filaOrigen][columnaOrigen];

    if (tablero[filaOrigen][columnaOrigen] != '*') {
    tablero[filaDestino][columnaDestino] = pieza;
    }
}


bool esMovimientoValido(char tablero[FILAS][COLUMNAS], int filaOrigen, int columnaOrigen, int filaDestino, int columnaDestino) {
    
    
    
    return true;

}




int main() {
    char tablero[FILAS][COLUMNAS];

    piezas(tablero);
    tableroPrint(tablero);
	pedirMovimiento();
    return 0;
}
