// src/DynamicStack.cpp
#include "DynamicStack.h"
#include <stdexcept>
#include <vector>
#include <algorithm> // Adicionado para std::reverse
#include <stack>

// Adiciona um timestamp ao topo da pilha (push)
void DynamicStack::add(const Timestamp& ts) {
    data.push(ts);
}

// Removendo get e set, pois std::stack não suporta acesso por índice.
// Timestamp& DynamicStack::get(int index) {
//     throw std::logic_error("std::stack does not support direct indexed access (get)");
// }

// void DynamicStack::set(int index, const Timestamp& ts) {
//     throw std::logic_error("std::stack does not support direct indexed access (set)");
// }

// Retorna o número de elementos na pilha
int DynamicStack::size() const {
    return data.size();
}

// Converte a pilha dinâmica para um vetor de Timestamps
// ATENÇÃO: Esta operação esvazia a pilha original.
std::vector<Timestamp> DynamicStack::toVector() const {
    std::stack<Timestamp> temp_stack = data; // Copia a pilha para não modificar a original
    std::vector<Timestamp> vec;
    while (!temp_stack.empty()) {
        vec.push_back(temp_stack.top());
        temp_stack.pop();
    }
    std::reverse(vec.begin(), vec.end()); // Reverte para manter a ordem original da base ao topo
    return vec;
}

// Converte um vetor de Timestamps para a pilha dinâmica
void DynamicStack::fromVector(const std::vector<Timestamp>& vec) {
    // Limpa a pilha atual
    while (!data.empty()) {
        data.pop();
    }
    // Adiciona os elementos do vetor à pilha
    for (const auto& ts : vec) {
        data.push(ts);
    }
}

// Limpa todos os elementos da pilha
void DynamicStack::clear() {
    while (!data.empty()) {
        data.pop();
    }
}

// Remove e retorna o timestamp do topo da pilha (pop)
Timestamp DynamicStack::pop() {
    if (data.empty()) {
        throw std::out_of_range("Pop from empty DynamicStack");
    }
    Timestamp top = data.top();
    data.pop();
    return top;
}

// Estimativa de uso de memória. std::stack não expõe diretamente a capacidade
// do contêiner subjacente. Esta é uma estimativa simplificada.
size_t DynamicStack::getMemoryUsageInBytes() const {
    // std::stack usa std::deque por padrão. Estimar o tamanho de um deque é complexo.
    // Para uma estimativa simples, podemos considerar o número de elementos * tamanho de Timestamp.
    // Isso não inclui a sobrecarga do contêiner ou a capacidade alocada.
    return data.size() * sizeof(Timestamp);
}

