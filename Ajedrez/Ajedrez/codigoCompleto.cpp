#include <iostream>

// Definición de constantes para las dimensiones del tablero (8x8)
#define FILAS 8 //numero de filas del tablero
#define COLUMNAS 8 //numero de columnas del tablero

/**
 * Inicializa el tablero con las piezas en sus posiciones de inicio.
 * Utiliza caracteres minúsculos para piezas negras y mayúsculas para blancas.
 * '*' representa una casilla vacía.
 */
void piezas(char tablero[FILAS][COLUMNAS]) {//inicializa el tablero con las piezas en su posicion inicial

    // Relleno inicial del tablero con espacios vacíos (*)
    for (int i = 0; i < FILAS; i++) //llenamos el tablero con asteriscos(recorre las filas)
        for (int j = 0; j < COLUMNAS; j++) //recorre las columnas
            tablero[i][j] = '*'; //ponemos asteriscos en todas las posiciones del tablero

    // Configuración de las piezas negras (Fila 0 y Fila 1)
    tablero[0][0] = 't'; // Torre
    tablero[0][1] = 'h'; // Caballo (Horse)
    tablero[0][2] = 'b'; // Alfil (Bishop)
    tablero[0][3] = 'k'; // Rey (King)
    tablero[0][4] = 'q'; // Reina (Queen)
    tablero[0][5] = 'b';
    tablero[0][6] = 'h';
    tablero[0][7] = 't';

    for (int j = 0; j < 8; j++) //llenamos la segunda fila con peones negros
        tablero[1][j] = 'p';

    // Configuración de las piezas blancas (Fila 7 y Fila 6)
    tablero[7][0] = 'T'; // Torre
    tablero[7][1] = 'H'; // Caballo
    tablero[7][2] = 'B'; // Alfil
    tablero[7][3] = 'K'; // Rey
    tablero[7][4] = 'Q'; // Reina
    tablero[7][5] = 'B';
    tablero[7][6] = 'H';
    tablero[7][7] = 'T';

    for (int j = 0; j < 8; j++) //llenamos la fila 6 con los peones blancos
        tablero[6][j] = 'P';
}

/**
 * Muestra el estado actual del tablero en la consola,
 * incluyendo índices de filas y columnas para facilitar el juego.
 */
void tableroPrint(char tablero[FILAS][COLUMNAS]) {//imprime el tablero en consola
    std::cout << "    ";//espacio para que se vea bien la numeracion de las columnas
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

/**
 * Solicita al usuario las coordenadas de origen y destino.
 * Ajusta los valores restando 1 para que coincidan con los índices de la matriz (0-7).
 */
void pedirMovimiento(int& filaOrigen, int& columnaOrigen, int& filaDestino, int& columnaDestino) {
    std::cout << "Ingrese la fila de la pieza que se tiene que mover (1-8): ";
    std::cin >> filaOrigen;
    std::cout << "Ingrese la columna de la pieza que se tiene que mover (1-8): ";
    std::cin >> columnaOrigen;
    std::cout << "Ingrese la fila donde quieres mover la pieza (1-8): ";
    std::cin >> filaDestino;
    std::cout << "Ingrese la columna donde quieres mover la pieza (1-8): ";
    std::cin >> columnaDestino;

    // Ajuste de 1-8 a 0-7 para manejo de arrays
    filaOrigen--;
    columnaOrigen--;
    filaDestino--;
    columnaDestino--;
}

/**
 * Ejecuta el movimiento físico de la pieza en la matriz.
 * Para esta parte hemos utilizado IA para que nos auyde con el movimiento ya que estabamos debatiendo diferentes formas pero no veiamos que ninguna funcionara como queriamos.
 */
void moverPieza(char tablero[FILAS][COLUMNAS], int filaOrigen, int columnaOrigen, int filaDestino, int columnaDestino) {
    char pieza = tablero[filaOrigen][columnaOrigen];
    if (pieza != '*') {
        tablero[filaDestino][columnaDestino] = pieza; // Coloca la pieza en el destino
        tablero[filaOrigen][columnaOrigen] = '*';      // Limpia el origen
    }
}

/**
 * Verifica si el movimiento solicitado cumple con las reglas básicas
 * de cada pieza (Peones, Torres, Alfiles y Reyes).
 */
bool movimientoValido(char tablero[FILAS][COLUMNAS], int filaOrigen, int columnaOrigen, int filaDestino, int columnaDestino) {

    // Validar que las coordenadas estén dentro del rango del tablero
    if (filaOrigen < 0 || filaOrigen >= FILAS || columnaOrigen < 0 || columnaOrigen >= COLUMNAS || filaDestino < 0 || filaDestino >= FILAS || columnaDestino < 0 || columnaDestino >= COLUMNAS)
        return false;

    char pieza = tablero[filaOrigen][columnaOrigen];

    switch (pieza) {

    case 'p': // Peón negro (baja filas)
        if (columnaDestino == columnaOrigen && (filaDestino == filaOrigen + 1 || (filaOrigen == 1 && filaDestino == filaOrigen + 2)))
            return true;
        return false;

    case 'P': // Peón blanco (sube filas)
        if (columnaDestino == columnaOrigen && (filaDestino == filaOrigen - 1 || (filaOrigen == 6 && filaDestino == filaOrigen - 2)))
            return true;
        return false;

    case 't': // Torres (movimiento recto)
    case 'T':
        if (filaOrigen == filaDestino || columnaOrigen == columnaDestino)
            return true;
        return false;

    case 'b': // Alfiles (movimiento diagonal)
    case 'B':
        if ((filaDestino - filaOrigen == columnaDestino - columnaOrigen) || (filaDestino - filaOrigen == -(columnaDestino - columnaOrigen)))
            return true;
        return false;

    case 'k': // Rey (una casilla en cualquier dirección)
    case 'K':
        if ((filaDestino - filaOrigen >= -1 && filaDestino - filaOrigen <= 1) && (columnaDestino - columnaOrigen >= -1 && columnaDestino - columnaOrigen <= 1) && !((filaDestino - filaOrigen == 0) && (columnaDestino - columnaOrigen == 0)))
            return true;
        return false;

    default:
        return false;
    }
}

/**
 * Revisa si un peón ha llegado al extremo opuesto para promocionarlo a Reina.
 */
void comprobarPeonReina(char tablero[FILAS][COLUMNAS]) {
    // Peón blanco llega a la fila superior
    for (int i = 0; i < COLUMNAS; i++)
        if (tablero[0][i] == 'P') tablero[0][i] = 'Q';

    // Peón negro llega a la fila inferior
    for (int i = 0; i < COLUMNAS; i++)
        if (tablero[7][i] == 'p') tablero[7][i] = 'q';
}

/**
 * Verifica si alguno de los reyes ha sido capturado.
 */
bool reymuerto(char tablero[FILAS][COLUMNAS]) {
    for (int i = 0; i < FILAS; i++)
        for (int j = 0; j < COLUMNAS; j++)
            if (tablero[i][j] == 'K' || tablero[i][j] == 'k') return false; // El rey sigue vivo
    return true; // Al menos un rey falta
}

/**
 * Identifica a qué equipo pertenece una pieza según sea mayúscula o minúscula.
 */
int obtenerEquipo(char pieza) {
    if (pieza >= 'A' && pieza <= 'Z') return 1; // Equipo blanco
    if (pieza >= 'a' && pieza <= 'z') return 2; // Equipo negro
    return 0; // Espacio vacío
}

/**
 * Lógica para detectar si el rey del turno actual está en una posición de peligro (Jaque).
 * También intenta simular movimientos del rey para ver si puede escapar.
 * Para esta parte nos hemos ayudado de la IA ya que se nos ha complicado y no veiamos la forma de empezar.
 */
bool jaquemate(char tablero[FILAS][COLUMNAS], bool turnoBlanco) {
    int filaOrigen, columnaOrigen;
    int filaDestino, columnaDestino;
    char tmp, pieza, pieza2;
    int equipo, equipo2;
    bool enJaque, sigueEnJaque;

    // 1. Localizar la posición actual del Rey del jugador en turno
    for (int i = 0; i < FILAS; i++)
        for (int j = 0; j < COLUMNAS; j++)
            if ((turnoBlanco && tablero[i][j] == 'K') || (!turnoBlanco && tablero[i][j] == 'k')) {
                filaOrigen = i;
                columnaOrigen = j;
            }

    // 2. Verificar si alguna pieza enemiga puede alcanzar la posición del Rey
    enJaque = false;
    for (int i = 0; i < FILAS; i++)
        for (int j = 0; j < COLUMNAS; j++) {
            pieza = tablero[i][j];
            equipo = obtenerEquipo(pieza);
            // Si es pieza enemiga, comprobar si tiene movimiento válido hacia el rey
            if (equipo != 0 && equipo != (turnoBlanco ? 1 : 2))
                if (movimientoValido(tablero, i, j, filaOrigen, columnaOrigen))
                    enJaque = true;
        }
    if (!enJaque) return false; // No hay jaque

    // 3. Simulación: ¿Puede el rey moverse a una casilla adyacente para escapar?
    for (int i = -1; i <= 1; i++)
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue; // Misma casilla del rey

            filaDestino = filaOrigen + i;
            columnaDestino = columnaOrigen + j;

            // Validar límites del tablero
            if (filaDestino >= 0 && filaDestino < FILAS && columnaDestino >= 0 && columnaDestino < COLUMNAS) {
                tmp = tablero[filaDestino][columnaDestino];
                // Si la casilla está vacía o tiene un enemigo (posible captura)
                if (obtenerEquipo(tmp) != (turnoBlanco ? 1 : 2)) {
                    // Mover virtualmente al rey
                    tablero[filaDestino][columnaDestino] = tablero[filaOrigen][columnaOrigen];
                    tablero[filaOrigen][columnaOrigen] = '*';

                    sigueEnJaque = false;
                    // Comprobar si tras el movimiento sigue bajo ataque
                    for (int a = 0; a < FILAS; a++)
                        for (int b = 0; b < COLUMNAS; b++) {
                            pieza2 = tablero[a][b];
                            equipo2 = obtenerEquipo(pieza2);
                            if (equipo2 != 0 && equipo2 != (turnoBlanco ? 1 : 2))
                                if (movimientoValido(tablero, a, b, filaDestino, columnaDestino))
                                    sigueEnJaque = true;
                        }

                    // Revertir el movimiento virtual
                    tablero[filaOrigen][columnaOrigen] = tablero[filaDestino][columnaDestino];
                    tablero[filaDestino][columnaDestino] = tmp;

                    // Si encontró un movimiento donde ya no está en jaque, no es mate
                    if (!sigueEnJaque) return false;
                }
            }
        }

    return true; // No hubo escape posible
}

/**
 * Agrupa las acciones de mover, promocionar peones y redibujar el tablero.
 */
void actualizarTablero(char tablero[FILAS][COLUMNAS], int filaOrigen, int columnaOrigen, int filaDestino, int columnaDestino) {
    moverPieza(tablero, filaOrigen, columnaOrigen, filaDestino, columnaDestino);
    comprobarPeonReina(tablero);
    tableroPrint(tablero);
}

/**
 * Función principal: Controla el flujo del juego, los turnos y la finalización.
 */
int main() {
    char tablero[FILAS][COLUMNAS];
    int filaOrigen, columnaOrigen;
    int filaDestino, columnaDestino;
    bool turnoBlanco = true; // Empiezan las blancas

    piezas(tablero);       // Inicialización
    tableroPrint(tablero); // Primer renderizado

    while (true) {
        pedirMovimiento(filaOrigen, columnaOrigen, filaDestino, columnaDestino);

        // Validar si el movimiento es legal según las reglas definidas
        if (movimientoValido(tablero, filaOrigen, columnaOrigen, filaDestino, columnaDestino)) {
            system("cls"); // Limpia la consola (Windows) para refrescar la imagen
            actualizarTablero(tablero, filaOrigen, columnaOrigen, filaDestino, columnaDestino);

            // Verificar condiciones de estado del juego
            if (jaquemate(tablero, turnoBlanco)) std::cout << "¡Jaque!\n";
            if (reymuerto(tablero)) { std::cout << "Rey muerto. Fin del juego\n"; break; }

            turnoBlanco = !turnoBlanco; // Alternar el turno entre jugadores
        }
        else {
            std::cout << "Movimiento invalido\n";
        }
    }

    return 0;
}