// src/StaticStack.h
#ifndef STATIC_STACK_H
#define STATIC_STACK_H

#include "IDataStructure.h"
#include <array>
#include <vector>
#include <stdexcept>

template <size_t MaxSize>
class StaticStack : public IDataStructure {
private:
    std::array<Timestamp, MaxSize> data;
    int currentSize;

public:
    StaticStack();
    void add(const Timestamp& ts) override; // Push
    int size() const override;
    size_t getMemoryUsageInBytes() const override;
    std::vector<Timestamp> toVector() const override;
    void fromVector(const std::vector<Timestamp>& vec) override;
    void clear() override;
    Timestamp pop();
};

// --- Implementação ---

template <size_t MaxSize>
StaticStack<MaxSize>::StaticStack() : currentSize(0) {}

template <size_t MaxSize>
void StaticStack<MaxSize>::add(const Timestamp& ts) {
    if (currentSize < MaxSize) {
        data[currentSize++] = ts;
    } else {
        throw std::out_of_range("StaticStack is full");
    }
}

template <size_t MaxSize>
int StaticStack<MaxSize>::size() const {
    return currentSize;
}

template <size_t MaxSize>
std::vector<Timestamp> StaticStack<MaxSize>::toVector() const {
    std::vector<Timestamp> vec;
    vec.reserve(currentSize);
    for (int i = 0; i < currentSize; ++i) {
        vec.push_back(data[i]);
    }
    return vec;
}

template <size_t MaxSize>
void StaticStack<MaxSize>::fromVector(const std::vector<Timestamp>& vec) {
    clear();
    if (vec.size() > MaxSize) {
        throw std::out_of_range("Vector size exceeds StaticStack capacity");
    }
    for (const auto& ts : vec) {
        add(ts);
    }
}

template <size_t MaxSize>
void StaticStack<MaxSize>::clear() {
    currentSize = 0;
}

template <size_t MaxSize>
Timestamp StaticStack<MaxSize>::pop() {
    if (currentSize > 0) {
        return data[--currentSize];
    } else {
        throw std::out_of_range("Pop from empty StaticStack");
    }
}

template <size_t MaxSize>
size_t StaticStack<MaxSize>::getMemoryUsageInBytes() const {
    return sizeof(data);
}

#endif // STATIC_STACK_H