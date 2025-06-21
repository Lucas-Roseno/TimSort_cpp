// src/StaticQueue.h
#ifndef STATIC_QUEUE_H
#define STATIC_QUEUE_H

#include "IDataStructure.h"
#include <array>
#include <vector>
#include <stdexcept>

template <size_t MaxSize>
class StaticQueue : public IDataStructure {
private:
    std::array<Timestamp, MaxSize> data;
    int head;
    int tail;
    int currentSize;

public:
    StaticQueue();
    void add(const Timestamp& ts) override; // Enqueue
    int size() const override;
    size_t getMemoryUsageInBytes() const override;
    std::vector<Timestamp> toVector() const override;
    void fromVector(const std::vector<Timestamp>& vec) override;
    void clear() override;
    Timestamp dequeue();
};

// --- Implementação ---

template <size_t MaxSize>
StaticQueue<MaxSize>::StaticQueue() : head(0), tail(0), currentSize(0) {}

template <size_t MaxSize>
void StaticQueue<MaxSize>::add(const Timestamp& ts) {
    if (currentSize < MaxSize) {
        data[tail] = ts;
        tail = (tail + 1) % MaxSize;
        currentSize++;
    } else {
        throw std::out_of_range("StaticQueue is full");
    }
}

template <size_t MaxSize>
int StaticQueue<MaxSize>::size() const {
    return currentSize;
}

template <size_t MaxSize>
std::vector<Timestamp> StaticQueue<MaxSize>::toVector() const {
    std::vector<Timestamp> vec;
    vec.reserve(currentSize);
    int current = head;
    for (int i = 0; i < currentSize; ++i) {
        vec.push_back(data[current]);
        current = (current + 1) % MaxSize;
    }
    return vec;
}

template <size_t MaxSize>
void StaticQueue<MaxSize>::fromVector(const std::vector<Timestamp>& vec) {
    clear();
    if (vec.size() > MaxSize) {
        throw std::out_of_range("Vector size exceeds StaticQueue capacity");
    }
    for (const auto& ts : vec) {
        add(ts);
    }
}

template <size_t MaxSize>
void StaticQueue<MaxSize>::clear() {
    head = 0;
    tail = 0;
    currentSize = 0;
}

template <size_t MaxSize>
Timestamp StaticQueue<MaxSize>::dequeue() {
    if (currentSize > 0) {
        Timestamp front = data[head];
        head = (head + 1) % MaxSize;
        currentSize--;
        return front;
    } else {
        throw std::out_of_range("Dequeue from empty StaticQueue");
    }
}

template <size_t MaxSize>
size_t StaticQueue<MaxSize>::getMemoryUsageInBytes() const {
    return sizeof(data);
}

#endif // STATIC_QUEUE_H