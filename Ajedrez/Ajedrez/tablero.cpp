//#include <iostream>
//#include <cmath>
//
//#define FILAS 8
//#define COLUMNAS 8
//
//void piezas(char tablero[FILAS][COLUMNAS]) {
//
//    for (int i = 0; i < FILAS; i++)
//        for (int j = 0; j < COLUMNAS; j++)
//            tablero[i][j] = '*';
//
//    tablero[0][0] = 't';
//    tablero[0][1] = 'h';
//    tablero[0][2] = 'b';
//    tablero[0][3] = 'k';
//    tablero[0][4] = 'q';
//    tablero[0][5] = 'b';
//    tablero[0][6] = 'h';
//    tablero[0][7] = 't';
//
//    for (int j = 0; j < 8; j++)
//        tablero[1][j] = 'p';
//
//    tablero[7][0] = 'T';
//    tablero[7][1] = 'H';
//    tablero[7][2] = 'B';
//    tablero[7][3] = 'K';
//    tablero[7][4] = 'Q';
//    tablero[7][5] = 'B';
//    tablero[7][6] = 'H';
//    tablero[7][7] = 'T';
//
//    for (int j = 0; j < 8; j++)
//        tablero[6][j] = 'P';
//}
//
//void tableroPrint(char tablero[FILAS][COLUMNAS]) {
//
//    std::cout << "   ";
//    for (int i = 0; i < COLUMNAS; i++)
//        std::cout << i + 1 << " ";
//    std::cout << "\n";
//
//    for (int i = 0; i < FILAS; i++) {
//        std::cout << i + 1 << "  ";
//        for (int j = 0; j < COLUMNAS; j++)
//            std::cout << tablero[i][j] << " ";
//        std::cout << "\n";
//    }
//}
//
//
//void pedirMovimiento() {
//    int filaOrigen, columnaOrigen;
//    int filaDestino, columnaDestino;
//    std::cout << "Ingrese la fila de la pieza que se tiene que mover: ";
//    std::cin >> filaOrigen;
//    std::cout << "Ingrese la columna de la pieza que se tiene que mover: ";
//    std::cin >> columnaOrigen;
//    std::cout << "Ingrese la fila donde quieres mover la pieza: ";
//    std::cin >> filaDestino;
//    std::cout << "Ingrese la columna donde quieres mover la pieza: ";
//    std::cin >> columnaDestino;
//}
//
//void moverPieza(char tablero[FILAS][COLUMNAS], int filaOrigen, int columnaOrigen, int filaDestino, int columnaDestino) {
//
//    char pieza = tablero[filaOrigen][columnaOrigen];
//
//    if (tablero[filaOrigen][columnaOrigen] != '*') {
//    tablero[filaDestino][columnaDestino] = pieza;
//    }
//}
//
//
//bool esMovimientoValido(char tablero[FILAS][COLUMNAS], int filaOrigen, int columnaOrigen, int filaDestino, int columnaDestino) {
//    
//    
//    
//    return true;
//
//}
//
//
//bool esBlanca(char pieza) {
//    return pieza >= 'A' && pieza <= 'Z';
//}
//
//bool esNegra(char pieza) {
//    return pieza >= 'a' && pieza <= 'z';
//}
//
//void moverTorre(char tablero[FILAS][COLUMNAS], int filaOrigen, int columnaOrigen, int filaDestino, int columnaDestino) {
//
//    char pieza = tablero[filaOrigen][columnaOrigen];
//
//    if (filaOrigen != filaDestino && columnaOrigen != columnaDestino) {
//        std::cout << "Movimiento invalido de la torre\n";
//        return;
//    }
//
//    if (filaOrigen == filaDestino) {
//        int paso = (columnaDestino > columnaOrigen) ? 1 : -1;
//        for (int j = columnaOrigen + paso; j != columnaDestino; j += paso) {
//            if (tablero[filaOrigen][j] != '*') {
//                std::cout << "Hay una pieza en el camino\n";
//                return;
//            }
//        }
//    }
//    else {
//        int paso = (filaDestino > filaOrigen) ? 1 : -1;
//        for (int i = filaOrigen + paso; i != filaDestino; i += paso) {
//            if (tablero[i][columnaOrigen] != '*') {
//                std::cout << "Hay una pieza en el camino\n";
//                return;
//            }
//        }
//    }
//
//    char destino = tablero[filaDestino][columnaDestino];
//    if (destino != '*') {
//        if ((esBlanca(pieza) && esBlanca(destino)) ||
//            (esNegra(pieza) && esNegra(destino))) {
//            std::cout << "No puedes capturar tu propia pieza\n";
//            return;
//        }
//    }
//
//    tablero[filaDestino][columnaDestino] = pieza;
//    tablero[filaOrigen][columnaOrigen] = '*';
//
//    std::cout << "Torre movida correctamente\n";
//}
//
//int main() {
//    char tablero[FILAS][COLUMNAS];
//
//    piezas(tablero);
//    tableroPrint(tablero);
//	pedirMovimiento();
//    return 0;
//}