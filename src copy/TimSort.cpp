// src/TimSort.cpp
#include "TimSort.h"
#include <algorithm>

// Tamanho mínimo para uma 'run' no TimSort. Geralmente é 32 ou 64.
const int MIN_RUN = 32;

// Função auxiliar para o Insertion Sort (usado em pequenas 'runs')
// Ordena o sub-array data[left...right]
void TimSort::insertionSort(std::vector<Timestamp>& data, int left, int right) {
    for (int i = left + 1; i <= right; ++i) {
        Timestamp temp = data[i];
        int j = i - 1;
        while (j >= left && data[j] > temp) {
            data[j + 1] = data[j];
            j--;
        }
        data[j + 1] = temp;
    }
}

// Função auxiliar para o Merge Sort (combina duas 'runs' ordenadas)
// Combina os sub-arrays data[l...m] e data[m+1...r]
void TimSort::merge(std::vector<Timestamp>& data, int l, int m, int r) {
    int len1 = m - l + 1;
    int len2 = r - m;

    // Cria arrays temporários para armazenar as duas 'runs'
    std::vector<Timestamp> leftArray(len1);
    std::vector<Timestamp> rightArray(len2);

    // Copia os dados para os arrays temporários
    for (int i = 0; i < len1; i++)
        leftArray[i] = data[l + i];
    for (int j = 0; j < len2; j++)
        rightArray[j] = data[m + 1 + j];

    int i = 0; // Índice inicial do primeiro sub-array
    int j = 0; // Índice inicial do segundo sub-array
    int k = l; // Índice inicial do sub-array mesclado

    // Mescla os arrays temporários de volta para data[l...r]
    while (i < len1 && j < len2) {
        if (leftArray[i] < rightArray[j]) {
            data[k] = leftArray[i];
            i++;
        } else {
            data[k] = rightArray[j];
            j++;
        }
        k++;
    }

    // Copia os elementos restantes do leftArray, se houver algum
    while (i < len1) {
        data[k] = leftArray[i];
        i++;
        k++;
    }

    // Copia os elementos restantes do rightArray, se houver algum
    while (j < len2) {
        data[k] = rightArray[j];
        j++;
        k++;
    }
}

// Função principal do TimSort que ordena um vetor de Timestamps
void TimSort::sort(std::vector<Timestamp>& data) {
    int n = data.size();

    // 1. Ordena 'runs' individuais de tamanho MIN_RUN usando Insertion Sort
    for (int i = 0; i < n; i += MIN_RUN) {
        insertionSort(data, i, std::min((i + MIN_RUN - 1), (n - 1)));
    }

    // 2. Mescla as 'runs' ordenadas
    // Começa mesclando 'runs' de tamanho MIN_RUN, depois 2*MIN_RUN, 4*MIN_RUN, etc.
    for (int size = MIN_RUN; size < n; size = 2 * size) {
        // Pega os pontos de início das 'runs' esquerda e direita
        for (int left = 0; left < n; left += 2 * size) {
            // Encontra o ponto final da 'run' esquerda e o ponto inicial da 'run' direita
            int mid = left + size - 1;
            // Encontra o ponto final da 'run' direita
            int right = std::min((left + 2 * size - 1), (n - 1));

            // Mescla data[left...mid] e data[mid+1...right]
            // Verifica se mid não ultrapassa os limites do array
            if (mid < right) {
                merge(data, left, mid, right);
            }
        }
    }
}


