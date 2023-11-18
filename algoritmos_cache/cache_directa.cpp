/*Definir una estructura para representar un bloque de caché, que incluye un bit de validez y una etiqueta.
Inicializar un array para representar la caché.
Abrir el archivo de entrada.
Leer cada operación y dirección del archivo.
Para cada operación y dirección, extraer el índice y la etiqueta de la dirección.
Comprobar si el bloque está en la caché.
Si la operación es una lectura y el bloque está en la caché, es un acierto. Si no, es un fallo.
Si la operación es una escritura y el bloque está en la caché, es un acierto. Si no, es un fallo y el bloque se carga en la caché.*/
#include <fstream>
#include <bitset>
#include <iostream>

struct Block {
    bool valid = false;
    unsigned int tag;
};

Block cache[1024]; // Asume una caché de 1024 bloques

void simulateCache(std::string operation, unsigned int address) {
    unsigned int index = (address >> 5) & 0x3FF; // Asume un offset de 5 bits
    unsigned int tag = address >> 15; // Asume un índice de 10 bits

    std::cout << "Operation: " << operation << ", Address: " << std::hex << address << "\n";
    std::cout << "Calculated index: " << index << ", Calculated tag: " << tag << "\n";
    std::cout << "Cache block status before operation: Valid = " << cache[index].valid << ", Tag = " << cache[index].tag << "\n";
   
   if (operation == "read") {
        if (cache[index].valid && cache[index].tag == tag) {
            std::cout << "Read operation: Cache hit\n";
        } else {
            cache[index].valid = true; // Carga el bloque en la caché
            cache[index].tag = tag;
            std::cout << "Read operation: Cache miss\n";
        }
    } else if (operation == "write") {
        if (cache[index].valid && cache[index].tag == tag) {
            std::cout << "Write operation: Cache hit\n";
        } else {
            cache[index].valid = true;
            cache[index].tag = tag;
            std::cout << "Write operation: Cache miss\n";
        }
    }
    std::cout << "Cache block status after operation: Valid = " << cache[index].valid << ", Tag = " << cache[index].tag << "\n";
    std::cout << "----------------------------------------\n";
}

int main() {
    std::ifstream file("input.txt");
    std::string operation;
    unsigned int address;

    while (file >> operation >> std::hex >> address) {
        simulateCache(operation, address);
    }

    return 0;
}