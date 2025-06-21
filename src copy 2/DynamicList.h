// src/DynamicList.h
#ifndef DYNAMIC_LIST_H
#define DYNAMIC_LIST_H

#include "IDataStructure.h"
#include <vector>

class DynamicList : public IDataStructure {
private:
    std::vector<Timestamp> data;

public:
    DynamicList() = default;
    void add(const Timestamp& ts) override;
    // Removido get e set
    int size() const override;
    size_t getMemoryUsageInBytes() const override;
    std::vector<Timestamp> toVector() const override;
    void fromVector(const std::vector<Timestamp>& vec) override;
    void clear() override;
};

#endif // DYNAMIC_LIST_H

