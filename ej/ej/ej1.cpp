#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

int cantidad = 0;

int main() {

    std::cout << "Introduce la cantidad de letras a generar: ";
    std::cin >> cantidad;

    std::srand(std::time(nullptr)); //ponemos "nullptr" porque no queremos que guarde un valor solo queremos que lo devuelva

    std::ofstream letras_random("letras.txt");

    for (int i = 0; i < cantidad; i++) {
        char letra = 'a' + (std::rand() % 26);
        letras_random << letra;
    }

    letras_random.close();

    return 0;
}
