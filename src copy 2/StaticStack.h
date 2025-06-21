// src/StaticStack.h
#ifndef STATIC_STACK_H
#define STATIC_STACK_H

#include "IDataStructure.h"
#include <array>
#include "Constants.h"

// Implementação de uma pilha estática usando std::array
class StaticStack : public IDataStructure {
private:
    std::array<Timestamp, MAX_STATIC_SIZE> data;
    int currentSize;

public:
    // Construtor
    StaticStack();

    // Implementação dos métodos da interface IDataStructure
    void add(const Timestamp& ts) override; // Push
    // Removido get e set
    int size() const override;
    size_t getMemoryUsageInBytes() const override; // <-- ADICIONADO
    std::vector<Timestamp> toVector() const override;
    void fromVector(const std::vector<Timestamp>& vec) override;
    void clear() override;

    // Método específico de pilha (opcional, mas útil)
    Timestamp pop();
};

#endif // STATIC_STACK_H

