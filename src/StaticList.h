// src/StaticList.h
#ifndef STATIC_LIST_H
#define STATIC_LIST_H

#include "IDataStructure.h"
#include <array>
#include <vector>
#include <stdexcept>

template <size_t MaxSize>
class StaticList : public IDataStructure {
private:
    std::array<Timestamp, MaxSize> data;
    int currentSize;

public:
    StaticList();
    void add(const Timestamp& ts) override;
    int size() const override;
    size_t getMemoryUsageInBytes() const override;
    std::vector<Timestamp> toVector() const override;
    void fromVector(const std::vector<Timestamp>& vec) override;
    void clear() override;
};

// --- Implementação ---

template <size_t MaxSize>
StaticList<MaxSize>::StaticList() : currentSize(0) {}

template <size_t MaxSize>
void StaticList<MaxSize>::add(const Timestamp& ts) {
    if (currentSize < MaxSize) {
        data[currentSize++] = ts;
    } else {
        throw std::out_of_range("StaticList is full");
    }
}

template <size_t MaxSize>
int StaticList<MaxSize>::size() const {
    return currentSize;
}

template <size_t MaxSize>
std::vector<Timestamp> StaticList<MaxSize>::toVector() const {
    std::vector<Timestamp> vec;
    vec.reserve(currentSize);
    for (int i = 0; i < currentSize; ++i) {
        vec.push_back(data[i]);
    }
    return vec;
}

template <size_t MaxSize>
void StaticList<MaxSize>::fromVector(const std::vector<Timestamp>& vec) {
    clear();
    if (vec.size() > MaxSize) {
        throw std::out_of_range("Vector size exceeds StaticList capacity");
    }
    for (const auto& ts : vec) {
        add(ts);
    }
}

template <size_t MaxSize>
void StaticList<MaxSize>::clear() {
    currentSize = 0;
}

template <size_t MaxSize>
size_t StaticList<MaxSize>::getMemoryUsageInBytes() const {
    return sizeof(data);
}

#endif // STATIC_LIST_H