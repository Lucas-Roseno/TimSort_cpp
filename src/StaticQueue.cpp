// src/StaticQueue.cpp
#include "StaticQueue.h"
#include <stdexcept>

// Construtor: inicializa head, tail e currentSize
StaticQueue::StaticQueue() : head(0), tail(0), currentSize(0) {}

// Adiciona um timestamp ao final da fila (enqueue)
void StaticQueue::add(const Timestamp& ts) {
    if (currentSize < MAX_STATIC_SIZE) {
        data[tail] = ts;
        tail = (tail + 1) % MAX_STATIC_SIZE; // Move o tail circularmente
        currentSize++;
    } else {
        throw std::out_of_range("StaticQueue is full");
    }
}

// Removido get e set
// Timestamp& StaticQueue::get(int index) {
//     if (index >= 0 && index < currentSize) {
//         return data[(head + index) % MAX_STATIC_SIZE];
//     } else {
//         throw std::out_of_range("Index out of bounds for StaticQueue");
//     }
// }

// void StaticQueue::set(int index, const Timestamp& ts) {
//     if (index >= 0 && index < currentSize) {
//         data[(head + index) % MAX_STATIC_SIZE] = ts;
//     } else {
//         throw std::out_of_range("Index out of bounds for StaticQueue");
//     }
// }

// Retorna o número de elementos na fila
int StaticQueue::size() const {
    return currentSize;
}

// Converte a fila estática para um vetor de Timestamps
std::vector<Timestamp> StaticQueue::toVector() const {
    std::vector<Timestamp> vec;
    vec.reserve(currentSize);
    int current = head;
    for (int i = 0; i < currentSize; ++i) {
        vec.push_back(data[current]);
        current = (current + 1) % MAX_STATIC_SIZE;
    }
    return vec;
}

// Converte um vetor de Timestamps para a fila estática
void StaticQueue::fromVector(const std::vector<Timestamp>& vec) {
    clear();
    if (vec.size() > MAX_STATIC_SIZE) {
        throw std::out_of_range("Vector size exceeds StaticQueue capacity");
    }
    for (const auto& ts : vec) {
        add(ts);
    }
}

// Limpa a fila estática redefinindo head, tail e currentSize
void StaticQueue::clear() {
    head = 0;
    tail = 0;
    currentSize = 0;
}

// Remove e retorna o timestamp do início da fila (dequeue)
Timestamp StaticQueue::dequeue() {
    if (currentSize > 0) {
        Timestamp front = data[head];
        head = (head + 1) % MAX_STATIC_SIZE;
        currentSize--;
        return front;
    } else {
        throw std::out_of_range("Dequeue from empty StaticQueue");
    }
}

// Retorna o uso de memória da estrutura em bytes
size_t StaticQueue::getMemoryUsageInBytes() const {
    return sizeof(data);
}

