// src/StaticList.h
#ifndef STATIC_LIST_H
#define STATIC_LIST_H

#include "IDataStructure.h"
#include <array>
#include "Constants.h"

class StaticList : public IDataStructure {
private:
    std::array<Timestamp, MAX_STATIC_SIZE> data;
    int currentSize;

public:
    StaticList();
    void add(const Timestamp& ts) override;
    // Removido get e set
    int size() const override;
    size_t getMemoryUsageInBytes() const override;
    std::vector<Timestamp> toVector() const override;
    void fromVector(const std::vector<Timestamp>& vec) override;
    void clear() override;
};

#endif // STATIC_LIST_H

