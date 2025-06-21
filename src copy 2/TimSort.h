// src/TimSort.h
#ifndef TIM_SORT_H
#define TIM_SORT_H

#include <vector>
#include "Timestamp.h"

// Implementação do algoritmo de ordenação TimSort
namespace TimSort {
    // Função principal do TimSort que ordena um vetor de Timestamps
    void sort(std::vector<Timestamp>& data);

    // Função auxiliar para o Insertion Sort (usado em pequenas 'runs')
    void insertionSort(std::vector<Timestamp>& data, int left, int right);

    // Função auxiliar para o Merge Sort (combina duas 'runs' ordenadas)
    void merge(std::vector<Timestamp>& data, int l, int m, int r);
}

#endif // TIM_SORT_H

