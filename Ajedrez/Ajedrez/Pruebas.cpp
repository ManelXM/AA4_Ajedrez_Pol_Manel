/*#include <iostream>
#include <cstdlib>

#define FILAS 8
#define COLUMNAS 8


void piezas(char tablero[FILAS][COLUMNAS]);
void tableroPrint(char tablero[FILAS][COLUMNAS]);
void pedirMovimiento(int& fo, int& co, int& fd, int& cd);

bool esBlanca(char pieza);
bool esNegra(char pieza);

void moverTorre(char tablero[FILAS][COLUMNAS],
    int filaOrigen, int columnaOrigen,
    int filaDestino, int columnaDestino);

void moverPeon(char tablero[FILAS][COLUMNAS],
    int filaOrigen, int columnaOrigen,
    int filaDestino, int columnaDestino);


void piezas(char tablero[FILAS][COLUMNAS]) {

    for (int i = 0; i < FILAS; i++)
        for (int j = 0; j < COLUMNAS; j++)
            tablero[i][j] = '*';

    // Negras
    tablero[0][0] = 't';
    tablero[0][0] = 'h';
    tablero[0][0] = 'b';
    tablero[0][0] = 'k';
    tablero[0][0] = 'q';
    tablero[0][0] = 'b';
    tablero[0][0] = 'h';
    tablero[0][7] = 't';
    for (int j = 0; j < 8; j++)
        tablero[1][j] = 'p';

    // Blancas
    tablero[7][0] = 'T';
    tablero[7][0] = 'H';
    tablero[7][0] = 'B';
    tablero[7][0] = 'Q';
    tablero[7][0] = 'K';
    tablero[7][0] = 'B';
    tablero[7][0] = 'H';
    tablero[7][7] = 'T';
    for (int j = 0; j < 8; j++)
        tablero[6][j] = 'P';
}

void tableroPrint(char tablero[FILAS][COLUMNAS]) {

    std::cout << "\n   ";
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

void pedirMovimiento(int& fo, int& co, int& fd, int& cd) {
    std::cout << "\nFila origen (1-8): ";
    std::cin >> fo;
    std::cout << "Columna origen (1-8): ";
    std::cin >> co;
    std::cout << "Fila destino (1-8): ";
    std::cin >> fd;
    std::cout << "Columna destino (1-8): ";
    std::cin >> cd;

    // Pasar de 1-8 a 0-7
    fo--; co--; fd--; cd--;
}

// ===== FUNCIONES DE COLOR =====
bool esBlanca(char pieza) {
    return pieza >= 'A' && pieza <= 'Z';
}

bool esNegra(char pieza) {
    return pieza >= 'a' && pieza <= 'z';
}

// ===== TORRE =====
void moverTorre(char tablero[FILAS][COLUMNAS],
    int fo, int co, int fd, int cd) {

    char pieza = tablero[fo][co];

    if (pieza != 'T' && pieza != 't') {
        std::cout << "No es una torre\n";
        return;
    }

    if (fo != fd && co != cd) {
        std::cout << "Movimiento invalido de torre\n";
        return;
    }

    if (fo == fd) {
        int paso = (cd > co) ? 1 : -1;
        for (int j = co + paso; j != cd; j += paso)
            if (tablero[fo][j] != '*') {
                std::cout << "Hay una pieza en el camino\n";
                return;
            }
    }
    else {
        int paso = (fd > fo) ? 1 : -1;
        for (int i = fo + paso; i != fd; i += paso)
            if (tablero[i][co] != '*') {
                std::cout << "Hay una pieza en el camino\n";
                return;
            }
    }

    char destino = tablero[fd][cd];
    if (destino != '*') {
        if ((esBlanca(pieza) && esBlanca(destino)) ||
            (esNegra(pieza) && esNegra(destino))) {
            std::cout << "No puedes capturar tu propia pieza\n";
            return;
        }
    }

    tablero[fd][cd] = pieza;
    tablero[fo][co] = '*';
}

// ===== PEÓN =====
void moverPeon(char tablero[FILAS][COLUMNAS],
    int fo, int co, int fd, int cd) {

    char pieza = tablero[fo][co];

    if (pieza != 'P' && pieza != 'p') {
        std::cout << "No es un peon\n";
        return;
    }

    int direccion = (pieza == 'P') ? -1 : 1;
    int filaInicial = (pieza == 'P') ? 6 : 1;

    // Avance 1
    if (co == cd && fd == fo + direccion &&
        tablero[fd][cd] == '*') {

        tablero[fd][cd] = pieza;
        tablero[fo][co] = '*';
        return;
    }

    // Avance 2 desde inicio
    if (fo == filaInicial && co == cd &&
        fd == fo + 2 * direccion &&
        tablero[fo + direccion][co] == '*' &&
        tablero[fd][cd] == '*') {

        tablero[fd][cd] = pieza;
        tablero[fo][co] = '*';
        return;
    }

    // Captura diagonal
    if (abs(cd - co) == 1 &&
        fd == fo + direccion &&
        tablero[fd][cd] != '*') {

        char destino = tablero[fd][cd];
        if ((esBlanca(pieza) && esNegra(destino)) ||
            (esNegra(pieza) && esBlanca(destino))) {

            tablero[fd][cd] = pieza;
            tablero[fo][co] = '*';
            return;
        }
    }

    std::cout << "Movimiento invalido del peon\n";
}



// ===== MAIN =====
int main() {
    char tablero[FILAS][COLUMNAS];
    int fo, co, fd, cd;

    piezas(tablero);

    while (true) {
        tableroPrint(tablero);

        pedirMovimiento(fo, co, fd, cd);

        // Salir si se ingresa 0
        if (fo < 0 || co < 0 || fd < 0 || cd < 0) {
            std::cout << "Juego terminado\n";
            break;
        }

        char pieza = tablero[fo][co];

        if (pieza == '*') {
            std::cout << "No hay pieza en esa posicion\n";
            continue;
        }

        if (pieza == 'T' || pieza == 't')
            moverTorre(tablero, fo, co, fd, cd);
        else if (pieza == 'P' || pieza == 'p')
            moverPeon(tablero, fo, co, fd, cd);
        else
            std::cout << "Pieza no implementada\n";
    }

    return 0;
}
*/










