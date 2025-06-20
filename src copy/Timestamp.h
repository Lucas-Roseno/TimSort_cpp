// src/Timestamp.h
#ifndef TIMESTAMP_H
#define TIMESTAMP_H

#include <iostream>

// Classe para representar um timestamp
class Timestamp {
public:
    long long value;

    // Construtor padrão
    Timestamp() : value(0) {}

    // Construtor com valor
    Timestamp(long long val) : value(val) {}

    // Operador de comparação para ordenação (menor que)
    bool operator<(const Timestamp& other) const {
        return value < other.value;
    }

    // Operador de comparação para ordenação (maior que)
    bool operator>(const Timestamp& other) const {
        return value > other.value;
    }

    // Operador de igualdade
    bool operator==(const Timestamp& other) const {
        return value == other.value;
    }

    // Sobrecarga do operador de inserção para facilitar a impressão
    friend std::ostream& operator<<(std::ostream& os, const Timestamp& ts) {
        os << ts.value;
        return os;
    }
};

#endif // TIMESTAMP_H

