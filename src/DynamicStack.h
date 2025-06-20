// src/DynamicStack.h
#ifndef DYNAMIC_STACK_H
#define DYNAMIC_STACK_H

#include "IDataStructure.h"
#include <stack>

class DynamicStack : public IDataStructure {
private:
    std::stack<Timestamp> data;

public:
    DynamicStack() = default;
    void add(const Timestamp& ts) override;
    // Removendo get e set, pois std::stack não suporta acesso por índice.
    // Isso significa que DynamicStack não pode mais ser usada com algoritmos que exigem acesso aleatório.
    // Timestamp& get(int index) override; 
    // void set(int index, const Timestamp& ts) override; 
    int size() const override;
    size_t getMemoryUsageInBytes() const override;
    std::vector<Timestamp> toVector() const override;
    void fromVector(const std::vector<Timestamp>& vec) override;
    void clear() override;
    Timestamp pop();
};

#endif // DYNAMIC_STACK_H

