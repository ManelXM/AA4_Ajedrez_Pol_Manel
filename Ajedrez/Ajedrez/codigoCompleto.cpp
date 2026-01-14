#include <iostream>

#define FILAS 8 //numero de filas del tablero
#define COLUMNAS 8 //numero de columnas del tablero

void piezas(char tablero[FILAS][COLUMNAS]) {//inicializa el tablero con las piezas en su posicion inicial

    for (int i = 0; i < FILAS; i++) //llenamos el tablero con asteriscos(recorre las filas)
        for (int j = 0; j < COLUMNAS; j++) //recorre las columnas
            tablero[i][j] = '*'; //ponemos asteriscos en todas las posiciones del tablero

    // piezas negras
    tablero[0][0] = 't';
    tablero[0][1] = 'h';
    tablero[0][2] = 'b';
    tablero[0][3] = 'k';
    tablero[0][4] = 'q';
    tablero[0][5] = 'b';
    tablero[0][6] = 'h';
    tablero[0][7] = 't';

    for (int j = 0; j < 8; j++) //llenamos la segunda fila con peones
        tablero[1][j] = 'p';

    // piezas blancas
    tablero[7][0] = 'T';
    tablero[7][1] = 'H';
    tablero[7][2] = 'B';
    tablero[7][3] = 'K';
    tablero[7][4] = 'Q';
    tablero[7][5] = 'B';
    tablero[7][6] = 'H';
    tablero[7][7] = 'T';

    for (int j = 0; j < 8; j++) //llenamos la fila 7 con los peones blancos
        tablero[6][j] = 'P';
}

void tableroPrint(char tablero[FILAS][COLUMNAS]) {//imprime el tablero en consola
    std::cout << "   ";//espacio para que se vea bien la numeracion de las columnas
    for (int i = 0; i < COLUMNAS; i++)
        std::cout << i + 1 << " ";//numeracion de las columnas
    std::cout << "\n";

    for (int i = 0; i < FILAS; i++) {
        std::cout << i + 1 << "  ";//numeracion de las filas
        for (int j = 0; j < COLUMNAS; j++)
            std::cout << tablero[i][j] << " ";//imprime lo que hay en cada posicion del tablero
        std::cout << "\n";
    }
}

void pedirMovimiento(int& filaOrigen, int& columnaOrigen, int& filaDestino, int& columnaDestino) {
    std::cout << "Ingrese la fila de la pieza que se tiene que mover (1-8): ";
    std::cin >> filaOrigen;
    std::cout << "Ingrese la columna de la pieza que se tiene que mover (1-8): ";
    std::cin >> columnaOrigen;
    std::cout << "Ingrese la fila donde quieres mover la pieza (1-8): ";
    std::cin >> filaDestino;
    std::cout << "Ingrese la columna donde quieres mover la pieza (1-8): ";
    std::cin >> columnaDestino;

    filaOrigen--;
    columnaOrigen--;
    filaDestino--;
    columnaDestino--;
}

void moverPieza(char tablero[FILAS][COLUMNAS], int filaOrigen, int columnaOrigen, int filaDestino, int columnaDestino) {
    char pieza = tablero[filaOrigen][columnaOrigen];
    if (pieza != '*') {
        tablero[filaDestino][columnaDestino] = pieza;
        tablero[filaOrigen][columnaOrigen] = '*';
    }
}

bool movimientoValido(char tablero[FILAS][COLUMNAS], int filaOrigen, int columnaOrigen, int filaDestino, int columnaDestino) {

    if (filaOrigen < 0 || filaOrigen >= FILAS || columnaOrigen < 0 || columnaOrigen >= COLUMNAS || filaDestino < 0 || filaDestino >= FILAS || columnaDestino < 0 || columnaDestino >= COLUMNAS)
        return false;

    char pieza = tablero[filaOrigen][columnaOrigen];

    switch (pieza) {

    case 'p':
        if (columnaDestino == columnaOrigen && (filaDestino == filaOrigen + 1 || (filaOrigen == 1 && filaDestino == filaOrigen + 2)))
            return true;
        return false;

    case 'P':
        if (columnaDestino == columnaOrigen && (filaDestino == filaOrigen - 1 || (filaOrigen == 6 && filaDestino == filaOrigen - 2)))
            return true;
        return false;

    case 't':
    case 'T':
        if (filaOrigen == filaDestino || columnaOrigen == columnaDestino)
            return true;
        return false;

    case 'b':
    case 'B':
        if ((filaDestino - filaOrigen == columnaDestino - columnaOrigen) || (filaDestino - filaOrigen == -(columnaDestino - columnaOrigen)))
            return true;
        return false;

    case 'k':
    case 'K':
        if ((filaDestino - filaOrigen >= -1 && filaDestino - filaOrigen <= 1) && (columnaDestino - columnaOrigen >= -1 && columnaDestino - columnaOrigen <= 1) && !((filaDestino - filaOrigen == 0) && (columnaDestino - columnaOrigen == 0)))
            return true;
        return false;

    default:
        return false;
    }
}

void comprobarPeonReina(char tablero[FILAS][COLUMNAS]) {
    for (int i = 0; i < COLUMNAS; i++)
        if (tablero[0][i] == 'P') tablero[0][i] = 'Q';

    for (int i = 0; i < COLUMNAS; i++)
        if (tablero[7][i] == 'p') tablero[7][i] = 'q';
}

bool reymuerto(char tablero[FILAS][COLUMNAS]) {
    for (int i = 0; i < FILAS; i++)
        for (int j = 0; j < COLUMNAS; j++)
            if (tablero[i][j] == 'K' || tablero[i][j] == 'k') return false;
    return true;
}

// Esto es lo que faltaba
int obtenerEquipo(char pieza) {
    if (pieza >= 'A' && pieza <= 'Z') return 1; // blancas
    if (pieza >= 'a' && pieza <= 'z') return 2; // negras
    return 0; // vacío
}

bool jaquemate(char tablero[FILAS][COLUMNAS], bool turnoBlanco) {
    int filaOrigen, columnaOrigen;
    int filaDestino, columnaDestino;
    char tmp, pieza, pieza2;
    int equipo, equipo2;
    bool enJaque, sigueEnJaque;

    // 1. Buscar el rey correspondiente
    for (int i = 0; i < FILAS; i++)
        for (int j = 0; j < COLUMNAS; j++)
            if ((turnoBlanco && tablero[i][j] == 'K') || (!turnoBlanco && tablero[i][j] == 'k')) {
                filaOrigen = i;
                columnaOrigen = j;
            }

    // 2. Verificar si está en jaque
    enJaque = false;
    for (int i = 0; i < FILAS; i++)
        for (int j = 0; j < COLUMNAS; j++) {
            pieza = tablero[i][j];
            equipo = obtenerEquipo(pieza);
            if (equipo != 0 && equipo != (turnoBlanco ? 1 : 2))
                if (movimientoValido(tablero, i, j, filaOrigen, columnaOrigen))
                    enJaque = true;
        }
    if (!enJaque) return false;

    // 3. Revisar si el rey puede moverse a alguna casilla segura
    for (int i = -1; i <= 1; i++)
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;

            filaDestino = filaOrigen + i;
            columnaDestino = columnaOrigen + j;

            if (filaDestino >= 0 && filaDestino < FILAS && columnaDestino >= 0 && columnaDestino < COLUMNAS) {
                tmp = tablero[filaDestino][columnaDestino];
                if (obtenerEquipo(tmp) != (turnoBlanco ? 1 : 2)) {
                    tablero[filaDestino][columnaDestino] = tablero[filaOrigen][columnaOrigen];
                    tablero[filaOrigen][columnaOrigen] = '*';

                    sigueEnJaque = false;
                    for (int a = 0; a < FILAS; a++)
                        for (int b = 0; b < COLUMNAS; b++) {
                            pieza2 = tablero[a][b];
                            equipo2 = obtenerEquipo(pieza2);
                            if (equipo2 != 0 && equipo2 != (turnoBlanco ? 1 : 2))
                                if (movimientoValido(tablero, a, b, filaDestino, columnaDestino))
                                    sigueEnJaque = true;
                        }

                    tablero[filaOrigen][columnaOrigen] = tablero[filaDestino][columnaDestino];
                    tablero[filaDestino][columnaDestino] = tmp;

                    if (!sigueEnJaque) return false;
                }
            }
        }

    return true;
}

void actualizarTablero(char tablero[FILAS][COLUMNAS], int filaOrigen, int columnaOrigen, int filaDestino, int columnaDestino) {
    moverPieza(tablero, filaOrigen, columnaOrigen, filaDestino, columnaDestino);
    comprobarPeonReina(tablero);
    tableroPrint(tablero);
}

int main() {
    char tablero[FILAS][COLUMNAS];
    int filaOrigen, columnaOrigen;
    int filaDestino, columnaDestino;
    bool turnoBlanco = true;

    piezas(tablero);
    tableroPrint(tablero);

    while (true) {
        pedirMovimiento(filaOrigen, columnaOrigen, filaDestino, columnaDestino);

        if (movimientoValido(tablero, filaOrigen, columnaOrigen, filaDestino, columnaDestino)) {
            system("cls");
            actualizarTablero(tablero, filaOrigen, columnaOrigen, filaDestino, columnaDestino);

            if (jaquemate(tablero, turnoBlanco)) std::cout << "¡Jaque!\n";
            if (reymuerto(tablero)) { std::cout << "Rey muerto. Fin del juego\n"; break; }

            turnoBlanco = !turnoBlanco; // cambiar turno
        }
        else {
            std::cout << "Movimiento invalido\n";
        }
    }

    return 0;
}
