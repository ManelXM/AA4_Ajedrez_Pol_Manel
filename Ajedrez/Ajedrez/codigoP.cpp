/*#include <iostream>

#define FILAS 8//numero de filas del tablero
#define COLUMNAS 8//numero de columnas del tablero

void piezas(char tablero[FILAS][COLUMNAS]) {//inicializa el tablero con las piezas en su posicion inicial

    for (int i = 0; i < FILAS; i++)//llenamos el tablero con asteriscos(recorre las filas)
        for (int j = 0; j < COLUMNAS; j++)//recorre las columnas
            tablero[i][j] = '*';//ponemkos asteriscos en todas las posiciones del tablero
    // piezas negras
    tablero[0][0] = 't';
    tablero[0][1] = 'h';
    tablero[0][2] = 'b';
    tablero[0][3] = 'k';
    tablero[0][4] = 'q';
    tablero[0][5] = 'b';
    tablero[0][6] = 'h';
    tablero[0][7] = 't';

    for (int j = 0; j < 8; j++)//llenamos la segunda fila con peones
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

    for (int j = 0; j < 8; j++)//llenamos la fila 7 con los peones blancos
        tablero[6][j] = 'P';
}

void tableroPrint(char tablero[FILAS][COLUMNAS]) {//imprime el tablero en consola

    std::cout << "   ";//espacio para que se vea bien la numeracion de las columnas
    for (int i = 0; i < COLUMNAS; i++)
        std::cout << i + 1 << " ";//numeracion de las columnas
    std::cout << "\n";

    for (int i = 0; i < FILAS; i++) {
        std::cout << i + 1 << "  ";//numeracion de las filas
        for (int j = 0; j < COLUMNAS; j++)//recorre las columnas
            std::cout << tablero[i][j] << " ";//imprime lo que hay en cada posicion del tablero y deja un pequeño espacio
        std::cout << "\n";
    }
}

void pedirMovimiento(int& filaOrigen, int& columnaOrigen, int& filaDestino, int& columnaDestino) {//pide al usuario el movimiento que quiere hacer
    std::cout << "Ingrese la fila de la pieza que se tiene que mover (1-8): ";//pide la fila de la pieza que se quiere mover
    std::cin >> filaOrigen;
    std::cout << "Ingrese la columna de la pieza que se tiene que mover (1-8): ";//pide la columna de la pieza que se quiere mover
    std::cin >> columnaOrigen;
    std::cout << "Ingrese la fila donde quieres mover la pieza (1-8): ";//pide la fila donde se quiere mover la pieza
    std::cin >> filaDestino;
    std::cout << "Ingrese la columna donde quieres mover la pieza (1-8): ";//pide la columna donde se quiere mover la pieza
    std::cin >> columnaDestino;

    // Ajustar indices para que comiencen desde 0 para que no den error al acceder a las posiciones
    filaOrigen--;
    columnaOrigen--;
    filaDestino--;
    columnaDestino--;
}

void moverPieza(char tablero[FILAS][COLUMNAS], int filaOrigen, int columnaOrigen, int filaDestino, int columnaDestino) {//mueve la pieza de una posicion a otra
    char pieza = tablero[filaOrigen][columnaOrigen];//guarda la pieza que se va a mover
    if (pieza != '*') {//verifica que la casilla de origen no este vacia
        tablero[filaDestino][columnaDestino] = pieza;//mueve la pieza a la casilla de destino
        tablero[filaOrigen][columnaOrigen] = '*';  // cambia la casilla donde estaba por un asterisco
    }
}

bool movimientoValido(char tablero[FILAS][COLUMNAS], int filaOrigen, int columnaOrigen, int filaDestino, int columnaDestino) {//verifica si el movimiento es valido segun las reglas del ajedrez basicas

    if (filaOrigen < 0 || filaOrigen >= FILAS || columnaOrigen < 0 || columnaOrigen >= COLUMNAS || filaDestino < 0 || filaDestino >= FILAS || columnaDestino < 0 || columnaDestino >= COLUMNAS) //verifica que las posiciones esten dentro del tablero
        return false;

    char pieza = tablero[filaOrigen][columnaOrigen];//guarda la pieza que se va a mover

    switch (pieza) {//haxmeos un switch por cdada pieza para verificar si el movimiento es valido

    case 'p': // peon negro
        // avanza 1 o 2 casillas desde la fila inicial
        if (columnaDestino == columnaOrigen && (filaDestino == filaOrigen + 1 || (filaOrigen == 1 && filaDestino == filaOrigen + 2))) {// avanza 1 o 2 casillas desde la fila inicial
            return true;
        }

        return false;

    case 'P': // peon blanco
        if (columnaDestino == columnaOrigen &&
            (filaDestino == filaOrigen - 1 || (filaOrigen == 6 && filaDestino == filaOrigen - 2))) {// avanza 1 o 2 casillas desde la fila inicial
            return true;
        }
        return false;

     
    case 't'://torre negra
        if (filaOrigen == filaDestino || columnaOrigen == columnaDestino) {
            return true;
        } // commo no puede moverse en diagonal solo puede moverse on en la misma fila o columna
        return false;

    case 'T'://torre blanca
        if (filaOrigen == filaDestino || columnaOrigen == columnaDestino) { 
            return true; }

        return false;

    case 'b'://alfil negro
        if ((filaDestino - filaOrigen == columnaDestino - columnaOrigen) || (filaDestino - filaOrigen == -(columnaDestino - columnaOrigen))) return true;
        return false;

    case 'B'://alfil blanco
        if ((filaDestino - filaOrigen == columnaDestino - columnaOrigen) || (filaDestino - filaOrigen == -(columnaDestino - columnaOrigen))) return true;
        return false;

    case 'k'://rey negro
        if ((filaDestino - filaOrigen >= -1 && filaDestino - filaOrigen <= 1) && (columnaDestino - columnaOrigen >= -1 && columnaDestino - columnaOrigen <= 1) && !((filaDestino - filaOrigen == 0) && (columnaDestino - columnaOrigen == 0))) return true;
        return false;

    case 'K'://rey blanco
        if ((filaDestino - filaOrigen >= -1 && filaDestino - filaOrigen <= 1) && (columnaDestino - columnaOrigen >= -1 && columnaDestino - columnaOrigen <= 1) && !((filaDestino - filaOrigen == 0) && (columnaDestino - columnaOrigen == 0))) return true;
        return false;

    default:
        return false;
    }
}

void comprobarPeonReina(char tablero[FILAS][COLUMNAS]) {//recorremos el teblero parqqa comprobar si el peon ha llegado alfinal del tablero para convertirlo en reina

    for (int i = 0; i < COLUMNAS; i++) {//el for que usaremos para recorrer las columnas
        if (tablero[0][i] == 'P') {//miramos el peon blanco si ha llegado
            tablero[0][i] = 'Q';//lo convertimos en reina 
        }
    }

    
    for (int i = 0; i < COLUMNAS; i++) {// lo mismo con los negros
        if (tablero[7][i] == 'p') {
            tablero[7][i] = 'q';
        }
    }
}

bool jaquemate(char tablero[FILAS][COLUMNAS]) {
    int filaBlanco; 
    int  columnaBlanco;
    int filaNegro;
    int columnaNegro;

    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            if (tablero[i][j] == 'K') {
                filaBlanco = i;
                columnaBlanco = j;
            }
            if (tablero[i][j] == 'k') {
                filaNegro = i;
                columnaNegro = j;
            }
        }
    }

    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            if (tablero[i][j] >= 'a' && tablero[i][j] <= 'z') { 
                if (movimientoValido(tablero, i, j, filaBlanco, columnaBlanco)) {
                }
            }
        }
    }

    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            if (tablero[i][j] >= 'A' && tablero[i][j] <= 'Z') { 
                if (movimientoValido(tablero, i, j, filaNegro, columnaNegro)) {
                }
            }
        }
    }


}

//rey muerto
bool reymuerto(char tablero[FILAS][COLUMNAS]) {

    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
        
            if (tablero[i][j] !='K') {//buscamos si exsiste en el yablero el rei

                return false;//si esta devolvemos como false el reymuerto
            }   
        }
    }

    return true;//si no lo encuentra lo devolvera como true
}



void actualizarTablero(char tablero[FILAS][COLUMNAS], int filaOrigen, int columnaOrigen, int filaDestino, int columnaDestino) {//actualiza el tablero despues de un movimiento valido
    moverPieza(tablero, filaOrigen, columnaOrigen, filaDestino, columnaDestino);//mueve la pieza
    tableroPrint(tablero);//imprime el tablero actualizado
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
            std::cout << "Movimiento invalido\n";
        }
    }

    return 0;
}
*/
