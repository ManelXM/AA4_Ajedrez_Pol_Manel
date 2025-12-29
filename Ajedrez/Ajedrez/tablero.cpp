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

    tablero[7][0] = 'T';
    tablero[7][1] = 'H';
    tablero[7][2] = 'B';
    tablero[7][3] = 'K';
    tablero[7][4] = 'Q';
    tablero[7][5] = 'B';
    tablero[7][6] = 'H';
    tablero[7][7] = 'T';

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

// Pasamos las variables por referencia para modificar en main
void pedirMovimiento(int& filaOrigen, int& columnaOrigen, int& filaDestino, int& columnaDestino) {
    std::cout << "Ingrese la fila de la pieza que se tiene que mover (1-8): ";
    std::cin >> filaOrigen;
    std::cout << "Ingrese la columna de la pieza que se tiene que mover (1-8): ";
    std::cin >> columnaOrigen;
    std::cout << "Ingrese la fila donde quieres mover la pieza (1-8): ";
    std::cin >> filaDestino;
    std::cout << "Ingrese la columna donde quieres mover la pieza (1-8): ";
    std::cin >> columnaDestino;

    // Ajustamos a índices de 0
    filaOrigen--;
    columnaOrigen--;
    filaDestino--;
    columnaDestino--;
}

void moverPieza(char tablero[FILAS][COLUMNAS], int filaOrigen, int columnaOrigen, int filaDestino, int columnaDestino) {
    char pieza = tablero[filaOrigen][columnaOrigen];
    if (pieza != '*') {
        tablero[filaDestino][columnaDestino] = pieza;
        tablero[filaOrigen][columnaOrigen] = '*';  // Limpiar casilla origen
    }
}

bool movimientoValido(char tablero[FILAS][COLUMNAS],int filaOrigen, int columnaOrigen,int filaDestino, int columnaDestino) {

    if (filaOrigen < 0 || filaOrigen >= FILAS || columnaOrigen < 0 || columnaOrigen >= COLUMNAS || filaDestino < 0 || filaDestino >= FILAS || columnaDestino < 0 || columnaDestino >= COLUMNAS) return false;

    char pieza = tablero[filaOrigen][columnaOrigen];

    switch (pieza) {

    case 'p':
        if (filaDestino == filaOrigen + 1 && columnaDestino == columnaOrigen && tablero[filaDestino][columnaDestino] == '*') return true;
        return false;

    case 'P':
        if (filaDestino == filaOrigen - 1 && columnaDestino == columnaOrigen && tablero[filaDestino][columnaDestino] == '*') return true;
        return false;

    case 't':
        if (filaOrigen == filaDestino || columnaOrigen == columnaDestino) return true;
        return false;

    case 'T':
        if (filaOrigen == filaDestino || columnaOrigen == columnaDestino) return true;
        return false;

    case 'b':
        if ((filaDestino - filaOrigen == columnaDestino - columnaOrigen) || (filaDestino - filaOrigen == -(columnaDestino - columnaOrigen))) return true;
        return false;

    case 'B':
        if ((filaDestino - filaOrigen == columnaDestino - columnaOrigen) || (filaDestino - filaOrigen == -(columnaDestino - columnaOrigen))) return true;
        return false;

    case 'k':
        if ((filaDestino - filaOrigen >= -1 && filaDestino - filaOrigen <= 1) && (columnaDestino - columnaOrigen >= -1 && columnaDestino - columnaOrigen <= 1) && !((filaDestino - filaOrigen == 0) && (columnaDestino - columnaOrigen == 0))) return true;
        return false;

    case 'K':
        if ((filaDestino - filaOrigen >= -1 && filaDestino - filaOrigen <= 1) && (columnaDestino - columnaOrigen >= -1 && columnaDestino - columnaOrigen <= 1) && !((filaDestino - filaOrigen == 0) && (columnaDestino - columnaOrigen == 0))) return true;
        return false;

    default:
        return false;
    }
}


void actualizarTablero(char tablero[FILAS][COLUMNAS], int filaOrigen, int columnaOrigen, int filaDestino, int columnaDestino) {
    moverPieza(tablero, filaOrigen, columnaOrigen, filaDestino, columnaDestino);
    tableroPrint(tablero);
}

int main() {
    char tablero[FILAS][COLUMNAS];
    int filaOrigen, columnaOrigen;
    int filaDestino, columnaDestino;

    piezas(tablero);
    tableroPrint(tablero);
    while (true) {
        pedirMovimiento(filaOrigen, columnaOrigen, filaDestino, columnaDestino);

        if (movimientoValido(tablero, filaOrigen, columnaOrigen, filaDestino, columnaDestino)) {
			system("cls"); 
            actualizarTablero(tablero, filaOrigen, columnaOrigen, filaDestino, columnaDestino);
        }
        else {
            std::cout << "Movimiento inválido\n";
        }
    }

    return 0;
}
