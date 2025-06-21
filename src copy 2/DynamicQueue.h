// src/DynamicQueue.h
#ifndef DYNAMIC_QUEUE_H
#define DYNAMIC_QUEUE_H

#include "IDataStructure.h"
#include <queue> // Usar std::queue

class DynamicQueue : public IDataStructure {
private:
    std::queue<Timestamp> data;

public:
    DynamicQueue() = default;
    void add(const Timestamp& ts) override;
    int size() const override;
    size_t getMemoryUsageInBytes() const override;
    std::vector<Timestamp> toVector() const override;
    void fromVector(const std::vector<Timestamp>& vec) override;
    void clear() override;
    Timestamp dequeue();
};

#endif // DYNAMIC_QUEUE_H

