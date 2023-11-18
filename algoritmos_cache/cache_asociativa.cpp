/*Define las estructuras de datos necesarias: una estructura Block que contiene un campo valid, un campo tag y un campo lastUsed, y una estructura Cache que contiene un array de Block.

Inicializa la caché: crea un array de Block con el tamaño de la caché y establece el campo valid de cada bloque a false.

Lee el archivo de entrada línea por línea. Para cada línea, extrae la operación (read o write) y la dirección.

Para cada operación, calcula el índice y la etiqueta de la dirección.

Busca en la caché un bloque con la misma etiqueta y el campo valid establecido a true. Si se encuentra un bloque, es un acierto de caché. Actualiza el campo lastUsed del bloque con el tiempo actual.

Si no se encuentra un bloque, es un fallo de caché. Busca en la caché un bloque con el campo valid establecido a false. Si se encuentra un bloque, establece el campo valid a true, actualiza la etiqueta y el campo lastUsed con la etiqueta y el tiempo actuales, respectivamente.

Si no se encuentra un bloque con el campo valid establecido a false, busca el bloque menos recientemente utilizado (el bloque con el valor más pequeño en el campo lastUsed). Reemplaza la etiqueta de este bloque con la etiqueta actual y actualiza el campo lastUsed con el tiempo actual.

Incrementa el tiempo después de cada operación.*/


#include <fstream>
#include <iostream>
#include <string>

struct Block {
    bool valid = false;
    unsigned int tag = 0;
    unsigned int lastUsed = 0;
};

Block cache[2]; // Asume una caché con 2 bloques
unsigned int time = 0;

void simulateCache(std::string operation, unsigned int address) {
    unsigned int tag = address >> 5; // Asume un offset de 5 bits

    bool hit = false;
    for (int i = 0; i < 2; ++i) {
        if (cache[i].valid && cache[i].tag == tag) {
            hit = true;
            cache[i].lastUsed = time;
            std::cout << operation << " operation: Cache hit at block " << i << "\n";
            break;
        }
    }

    if (!hit) {
        int lruIndex = (cache[0].lastUsed < cache[1].lastUsed) ? 0 : 1;
        cache[lruIndex].valid = true;
        cache[lruIndex].tag = tag;
        cache[lruIndex].lastUsed = time;
        std::cout << operation << " operation: Cache miss, replacing block " << lruIndex << "\n";
    }

    ++time;
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