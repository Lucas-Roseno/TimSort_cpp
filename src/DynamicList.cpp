// src/DynamicList.cpp
#include "DynamicList.h"

void DynamicList::add(const Timestamp& ts) { data.push_back(ts); }
// Removido get e set
// Timestamp& DynamicList::get(int index) { return data.at(index); }
// void DynamicList::set(int index, const Timestamp& ts) { data.at(index) = ts; }
int DynamicList::size() const { return data.size(); }
std::vector<Timestamp> DynamicList::toVector() const { return data; }
void DynamicList::fromVector(const std::vector<Timestamp>& vec) { data.assign(vec.begin(), vec.end()); }
void DynamicList::clear() { data.clear(); }

size_t DynamicList::getMemoryUsageInBytes() const {
    return data.capacity() * sizeof(Timestamp);
}

