/*Define las estructuras de datos necesarias: una estructura Block que contiene un campo valid, un campo tag y un campo lastUsed, y una estructura Set que contiene un array de Block.

Inicializa la caché: crea un array de Set con el tamaño de la caché y establece el campo valid de cada bloque a false.

Lee el archivo de entrada línea por línea. Para cada línea, extrae la operación (read o write) y la dirección.

Para cada operación, calcula el índice y la etiqueta de la dirección.

Busca en el conjunto correspondiente al índice un bloque con la misma etiqueta y el campo valid establecido a true. Si se encuentra un bloque, es un acierto de caché. Actualiza el campo lastUsed del bloque con el tiempo actual.

Si no se encuentra un bloque, es un fallo de caché. Busca en el conjunto un bloque con el campo valid establecido a false. Si se encuentra un bloque, establece el campo valid a true, actualiza la etiqueta y el campo lastUsed con la etiqueta y el tiempo actuales, respectivamente.

Si no se encuentra un bloque con el campo valid establecido a false, busca en el conjunto el bloque menos recientemente utilizado (el bloque con el valor más pequeño en el campo lastUsed). Reemplaza la etiqueta de este bloque con la etiqueta actual y actualiza el campo lastUsed con el tiempo actual.

Incrementa el tiempo después de cada operación.*/





#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct Block {
    bool valid = false;
    unsigned int tag = 0;
    unsigned int lastUsed = 0;
};

struct Set {
    std::vector<Block> blocks;
};

std::vector<Set> cache; // Asume una caché con un número determinado de conjuntos y bloques
unsigned int time = 0;

void simulateCache(std::string operation, unsigned int address) {
    unsigned int index = (address >> 5) & 0x3; // Asume un offset de 5 bits y 4 conjuntos
    unsigned int tag = address >> 7; // Asume un offset de 7 bits

    bool hit = false;
    for (Block &block : cache[index].blocks) {
        if (block.valid && block.tag == tag) {
            hit = true;
            block.lastUsed = time;
            std::cout << operation << " operation: Cache hit at block in set " << index << "\n";
            break;
        }
    }

    if (!hit) {
        Block *lruBlock = &cache[index].blocks[0];
        for (Block &block : cache[index].blocks) {
            if (!block.valid) {
                lruBlock = &block;
                break;
            } else if (block.lastUsed < lruBlock->lastUsed) {
                lruBlock = &block;
            }
        }

        lruBlock->valid = true;
        lruBlock->tag = tag;
        lruBlock->lastUsed = time;
        std::cout << operation << " operation: Cache miss, replacing block in set " << index << "\n";
    }

    ++time;
}

int main() {
    // Inicializa la caché con 4 conjuntos y 2 bloques por conjunto
    for (int i = 0; i < 4; ++i) {
        Set set;
        set.blocks.resize(2);
        cache.push_back(set);
    }

    std::ifstream file("input.txt");
    std::string operation;
    unsigned int address;

    while (file >> operation >> std::hex >> address) {
        simulateCache(operation, address);
    }

    return 0;
}