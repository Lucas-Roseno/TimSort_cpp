// src/DynamicQueue.cpp
#include "DynamicQueue.h"
#include <stdexcept>
#include <vector>
#include <algorithm> // Para std::reverse
#include <queue>

// Adiciona um timestamp ao final da fila (enqueue)
void DynamicQueue::add(const Timestamp& ts) {
    data.push(ts);
}

// Retorna o número de elementos na fila
int DynamicQueue::size() const {
    return data.size();
}

// Converte a fila dinâmica para um vetor de Timestamps
// ATENÇÃO: Esta operação esvazia a fila original se não for feita em uma cópia.
std::vector<Timestamp> DynamicQueue::toVector() const {
    std::queue<Timestamp> temp_queue = data; // Copia a fila para não modificar a original
    std::vector<Timestamp> vec;
    while (!temp_queue.empty()) {
        vec.push_back(temp_queue.front());
        temp_queue.pop();
    }
    return vec;
}

// Converte um vetor de Timestamps para a fila dinâmica
void DynamicQueue::fromVector(const std::vector<Timestamp>& vec) {
    // Limpa a fila atual
    while (!data.empty()) {
        data.pop();
    }
    // Adiciona os elementos do vetor à fila
    for (const auto& ts : vec) {
        data.push(ts);
    }
}

// Limpa todos os elementos da fila
void DynamicQueue::clear() {
    while (!data.empty()) {
        data.pop();
    }
}

// Remove e retorna o timestamp do início da fila (dequeue)
Timestamp DynamicQueue::dequeue() {
    if (data.empty()) {
        throw std::out_of_range("Dequeue from empty DynamicQueue");
    }
    Timestamp front_val = data.front();
    data.pop();
    return front_val;
}

size_t DynamicQueue::getMemoryUsageInBytes() const {
    // std::queue usa std::deque por padrão. Estimar o tamanho de um deque é complexo.
    // Para uma estimativa simples, podemos considerar o número de elementos * tamanho de Timestamp.
    // Isso não inclui a sobrecarga do contêiner ou a capacidade alocada.
    return data.size() * sizeof(Timestamp);
}

