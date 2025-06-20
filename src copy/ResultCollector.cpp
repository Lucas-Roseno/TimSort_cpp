// src/ResultCollector.cpp
#include "ResultCollector.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <iomanip>

// Adiciona um novo resultado à coleção
void ResultCollector::addResult(const std::string& structureType, int dataSize, double timeSeconds, long memoryUsedKB) {
    results.push_back({structureType, dataSize, timeSeconds, memoryUsedKB});
}

// Retorna todos os resultados coletados
const std::vector<TestResult>& ResultCollector::getResults() const {
    return results;
}

// Salva os resultados em arquivos CSV separados
void ResultCollector::saveResultsToCsv(const std::string& outputDir) const {
    // Garante que o diretório de saída exista
    // Em um ambiente real, isso exigiria chamadas de sistema (mkdir -p)
    // Para este ambiente de sandbox, assumimos que o diretório 'tables' será criado no main.

    // Mapas para organizar os dados por tipo de estrutura e tamanho de dados
    std::map<std::string, std::map<int, double>> timeResultsMap;
    std::map<std::string, std::map<int, long>> memoryResultsMap;

    // Preencher os mapas com os resultados
    for (const auto& result : results) {
        timeResultsMap[result.structureType][result.dataSize] = result.timeSeconds;
        memoryResultsMap[result.structureType][result.dataSize] = result.memoryUsedKB;
    }

    // Obter todos os tamanhos de dados únicos e ordená-los
    std::vector<int> dataSizes;
    for (const auto& pair : timeResultsMap.begin()->second) {
        dataSizes.push_back(pair.first);
    }
    std::sort(dataSizes.begin(), dataSizes.end());

    // --- Salvar Tabela de Tempos de Execução ---
    std::ofstream timeFile(outputDir + "/time_results.csv");
    if (!timeFile.is_open()) {
        std::cerr << "Error opening time_results.csv for writing." << std::endl;
        return;
    }

    // Escrever cabeçalho
    timeFile << "StructureType";
    for (int size : dataSizes) {
        timeFile << "," << size;
    }
    timeFile << "\n";

    // Escrever dados
    for (const auto& pair : timeResultsMap) {
        timeFile << pair.first; // Nome da estrutura
        for (int size : dataSizes) {
            timeFile << "," << std::fixed << std::setprecision(8) << pair.second.at(size);
        }
        timeFile << "\n";
    }
    timeFile.close();
    std::cout << "Time results saved to " << outputDir << "/time_results.csv" << std::endl;

    // --- Salvar Tabela de Consumo de Memória ---
    std::ofstream memoryFile(outputDir + "/memory_results.csv");
    if (!memoryFile.is_open()) {
        std::cerr << "Error opening memory_results.csv for writing." << std::endl;
        return;
    }

    // Escrever cabeçalho
    memoryFile << "StructureType";
    for (int size : dataSizes) {
        memoryFile << "," << size;
    }
    memoryFile << "\n";

    // Escrever dados
    for (const auto& pair : memoryResultsMap) {
        memoryFile << pair.first; // Nome da estrutura
        for (int size : dataSizes) {
            memoryFile << "," << pair.second.at(size);
        }
        memoryFile << "\n";
    }
    memoryFile.close();
    std::cout << "Memory results saved to " << outputDir << "/memory_results.csv" << std::endl;

    // --- Salvar Tabela de Desempenho Computacional (inferido do tempo) ---
    // Para este projeto, o desempenho computacional é diretamente o inverso do tempo.
    // Ou seja, menor tempo = maior desempenho.
    std::map<std::string, std::map<int, double>> computationalPerformanceResultsMap;
    for (const auto& result : results) {
        if (result.timeSeconds > 0) {
            computationalPerformanceResultsMap[result.structureType][result.dataSize] = 1.0 / result.timeSeconds;
        } else {
            computationalPerformanceResultsMap[result.structureType][result.dataSize] = 0.0; // Evitar divisão por zero
        }
    }

    std::ofstream perfFile(outputDir + "/computational_performance_results.csv");
    if (!perfFile.is_open()) {
        std::cerr << "Error opening computational_performance_results.csv for writing." << std::endl;
        return;
    }

    // Escrever cabeçalho
    perfFile << "StructureType";
    for (int size : dataSizes) {
        perfFile << "," << size;
    }
    perfFile << "\n";

    // Escrever dados
    for (const auto& pair : computationalPerformanceResultsMap) {
        perfFile << pair.first; // Nome da estrutura
        for (int size : dataSizes) {
            perfFile << "," << std::fixed << std::setprecision(8) << pair.second.at(size);
        }
        perfFile << "\n";
    }
    perfFile.close();
    std::cout << "Computational performance results saved to " << outputDir << "/computational_performance_results.csv" << std::endl;



}

