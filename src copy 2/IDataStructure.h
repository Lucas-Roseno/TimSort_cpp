// src/IDataStructure.h
#ifndef IDATA_STRUCTURE_H
#define IDATA_STRUCTURE_H

#include <vector>
#include <cstddef> // Para size_t
#include "Timestamp.h"

// Interface base para as estruturas de dados
class IDataStructure {
public:
    virtual ~IDataStructure() = default; // Destrutor virtual

    // Adiciona um timestamp à estrutura
    virtual void add(const Timestamp& ts) = 0;

    // Retorna o tamanho atual da estrutura
    virtual int size() const = 0;

    // Retorna o uso de memória da estrutura em bytes
    virtual size_t getMemoryUsageInBytes() const = 0;

    // Converte a estrutura para um vetor de Timestamps
    virtual std::vector<Timestamp> toVector() const = 0;

    // Converte um vetor de Timestamps para a estrutura
    virtual void fromVector(const std::vector<Timestamp>& vec) = 0;

    // Limpa a estrutura
    virtual void clear() = 0;
};

#endif // IDATA_STRUCTURE_H

