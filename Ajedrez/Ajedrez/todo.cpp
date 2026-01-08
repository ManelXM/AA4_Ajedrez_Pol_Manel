#include <iostream>

// Definición de constantes para el tamaño del tablero
#define FILAS 8
#define COLUMNAS 8

// Función para colocar las piezas en su posición inicial al empezar la partida
void piezas(char tablero[FILAS][COLUMNAS]) {
    // Primero llenamos todo el tablero con asteriscos (casillas vacías)
    for (int i = 0; i < FILAS; i++)
        for (int j = 0; j < COLUMNAS; j++)
            tablero[i][j] = '*';

    // Colocación de piezas negras (representadas con minúsculas)
    tablero[0][0] = 't';
    tablero[0][1] = 'h';
    tablero[0][2] = 'b';
    tablero[0][3] = 'k';
    tablero[0][4] = 'q';
    tablero[0][5] = 'b';
    tablero[0][6] = 'h';
    tablero[0][7] = 't';

    for (int j = 0; j < 8; j++) tablero[1][j] = 'p'; // Fila de peones negros

    // Colocación de piezas blancas (representadas con mayúsculas)
    tablero[7][0] = 'T';
    tablero[7][1] = 'H';
    tablero[7][2] = 'B';
    tablero[7][3] = 'K';
    tablero[7][4] = 'Q';
    tablero[7][5] = 'B';
    tablero[7][6] = 'H';
    tablero[7][7] = 'T';           

    for (int j = 0; j < 8; j++) tablero[6][j] = 'P'; // Fila de peones blancos
}

// Retorna el bando de la pieza: 1 para blancas o 2 para negras
int obtenerEquipo(char p) {
    if (p >= 'A' && p <= 'Z') return 1; // Letra mayúscula = Blanco
    if (p >= 'a' && p <= 'z') return 2; // Letra minúscula = Negro
}

// Función para dibujar el tablero y las coordenadas en la consola
void tableroPrint(char tablero[FILAS][COLUMNAS]) {
    std::cout << "\n    ";
    for (int i = 0; i < COLUMNAS; i++) std::cout << i + 1 << " "; // Números de columnas
    std::cout << "\n";
    for (int i = 0; i < FILAS; i++) {
        std::cout << i + 1 << "   "; // Números de filas
        for (int j = 0; j < COLUMNAS; j++) std::cout << tablero[i][j] << " ";
        std::cout << "\n";
    }
}

// Verifica que no haya piezas bloqueando el camino
bool caminoDespejado(char tablero[FILAS][COLUMNAS], int fo, int co, int fd, int cd) {
    // Determinamos la dirección del paso (-1, 0 o 1)
    int FilaPaso = (fd > fo ? 1 : -1);
    int ColumnaPaso = (cd > co ? 1 : -1);

    // Empezamos a revisar desde la casilla siguiente al origen
    int fActual = fo + FilaPaso;
    int cActual = co + ColumnaPaso;

    // Recorremos hasta llegar justo antes de la casilla de destino
    while (fActual != fd || cActual != cd) {
        if (tablero[fActual][cActual] != '*') return false; // Si hay algo, el camino está obstruido
        fActual += FilaPaso;
        cActual += ColumnaPaso;
    }
    return true; // Camino libre
}

// Comprobamos si un movimiento es valido o no
bool movimientoValido(char tablero[FILAS][COLUMNAS], int FilaOrigen, int ColumnaOrigen, int FilaDestino, int ColumnaDestino, int turnoActual) {
    // 1. Validar límites del tablero
    if (FilaOrigen < 0 || FilaOrigen >= FILAS || ColumnaOrigen < 0 || ColumnaOrigen >= COLUMNAS || FilaDestino < 0 || FilaDestino >= FILAS || ColumnaDestino < 0 || ColumnaDestino >= COLUMNAS)
        return false;

    char PiezasOrigen = tablero[FilaOrigen][ColumnaOrigen];
    char PiezasDestino = tablero[FilaDestino][ColumnaDestino];

    // 2. Validar que muevas tu propia pieza y no comas a tus aliados
    if (obtenerEquipo(PiezasOrigen) != turnoActual) return false;
    if (obtenerEquipo(PiezasDestino) == turnoActual) return false;

    // 3. Cálculos de distancia (df/dc son con signo, distFila/distCol son valores absolutos)
    int DiferenciaFila = FilaDestino - FilaOrigen;
    int DiferenciaColumna = ColumnaDestino - ColumnaOrigen;
    int distFila = (DiferenciaFila < 0) ? -DiferenciaFila : DiferenciaFila;
    int distCol = (DiferenciaColumna < 0) ? -DiferenciaColumna : DiferenciaColumna;

    // 4. Lógica específica por tipo de pieza
    switch (PiezasOrigen) {
    case 'p': case 'P':
    {
        int direccion = (PiezasOrigen == 'p') ? 1 : -1;  // Negro suma filas, Blanco resta
        int filaInicial = (PiezasOrigen == 'p') ? 1 : 6; // Posición de salida
        int equipoEnemigo = (PiezasOrigen == 'p') ? 1 : 2;

        // Movimiento hacia adelante (solo si la casilla destino está vacía)
        if (DiferenciaColumna == 0 && PiezasDestino == '*') {
            if (DiferenciaFila == direccion) return true; // Paso normal
            // Salto inicial de 2 casillas (revisando que la casilla intermedia esté vacía)
            if (FilaOrigen == filaInicial && DiferenciaFila == 2 * direccion && tablero[FilaOrigen + direccion][ColumnaOrigen] == '*') return true;
        }
        // Captura diagonal (solo si hay una pieza enemiga)
        if (DiferenciaFila == direccion && distCol == 1 && obtenerEquipo(PiezasDestino) == equipoEnemigo) return true;
        return false;
    }

    case 't': case 'T': // Torre: Movimiento recto + camino despejado
        if (FilaOrigen == FilaDestino || ColumnaOrigen == ColumnaDestino) return caminoDespejado(tablero, FilaOrigen, ColumnaOrigen, FilaDestino, ColumnaDestino);
        return false;

    case 'b': case 'B': // Alfil: Movimiento diagonal (distancias iguales) + camino despejado
        if (distFila == distCol) return caminoDespejado(tablero, FilaOrigen, ColumnaOrigen, FilaDestino, ColumnaDestino);
        return false;

    case 'h': case 'H': // Caballo: Movimiento en 'L' (2x1 o 1x2). Puede saltar piezas.
        return (distFila == 2 && distCol == 1) || (distFila == 1 && distCol == 2);

    case 'q': case 'Q': // Reina: Combinación de Torre y Alfil
        if ((FilaOrigen == FilaDestino || ColumnaOrigen == ColumnaDestino) || (distFila == distCol)) return caminoDespejado(tablero, FilaOrigen, ColumnaOrigen, FilaDestino, ColumnaDestino);
        return false;

    case 'k': case 'K': // Rey: Solo una casilla en cualquier dirección
        return (distFila <= 1 && distCol <= 1 && !(distFila == 0 && distCol == 0));

    default:
        return false;
    }
}

int main() {
    char tablero[FILAS][COLUMNAS];
    int FilaOrigen, ColumnaOrigen, FilaDestino, ColumnaDestino, turno = 1; // Empezamos con el equipo 1 (Blancas)

    piezas(tablero); // Inicializamos piezas

    while (true) {
        system("cls"); // Limpia la pantalla para cada turno
        std::cout << "--- TURNO DE LAS " << (turno == 1 ? "BLANCAS (Mayus)" : "NEGRAS (Minus)") << " ---" << std::endl;
        tableroPrint(tablero);

        // Pedir coordenadas al usuario
        std::cout << "\nOrigen (Fila Columna): "; std::cin >> FilaOrigen >> ColumnaOrigen;
        std::cout << "Destino (Fila Columna): "; std::cin >> FilaDestino >> ColumnaDestino;

        // Ajustamos la entrada humana (1-8) al índice de la matriz (0-7)
        FilaOrigen--; ColumnaOrigen--; FilaDestino--; ColumnaDestino--;

        // Si el movimiento es válido según las reglas
        if (movimientoValido(tablero, FilaOrigen, ColumnaOrigen, FilaDestino, ColumnaDestino, turno)) {
            tablero[FilaDestino][ColumnaDestino] = tablero[FilaOrigen][ColumnaOrigen]; // Colocamos la pieza en el destino (matando si hay enemigo)
            tablero[FilaOrigen][ColumnaOrigen] = '*';              // Vaciamos la casilla de origen
            turno = (turno == 1) ? 2 : 1;      // Cambiamos el turno al otro jugador
        }
        else {
            // Si el movimiento falla, mostramos error y esperamos un Enter
            std::cout << "\n[!] Movimiento invalido.";
            system("pause");
        }
    }
    return 0;
}