// src/FileProcessor.cpp
#include "FileProcessor.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <chrono>
#include "TimSort.h"
#include "ResultCollector.h" // Incluir o cabeçalho do coletor de resultados
#include "MemoryMonitor.h" // Incluir o cabeçalho do monitor de memória

// Processa um arquivo CSV com uma estrutura de dados específica
void FileProcessor::processFile(std::unique_ptr<IDataStructure> dataStructure, const std::string& inputFilePath, const std::string& outputFilePath, const std::string& structureType, int dataSize) {
    std::cout << "Processing file: " << inputFilePath << " with structure: " << structureType << std::endl;

    // 1. Ler dados do CSV para a estrutura de dados
    readCsv(*dataStructure, inputFilePath);

    // 2. Medir o pico de consumo de memória durante o processo de ordenação
    long initial_memory_kb = MemoryMonitor::getCurrentRSS(); // Captura a memória antes de qualquer operação com a estrutura

    // 3. Medir o tempo de ordenação e o pico de memória simultaneamente
    auto start_time = std::chrono::high_resolution_clock::now();
    
    std::vector<Timestamp> data_vector = dataStructure->toVector();
    long memory_after_to_vector = MemoryMonitor::getCurrentRSS();

    TimSort::sort(data_vector);
    
    dataStructure->fromVector(data_vector);
    long memory_after_from_vector = MemoryMonitor::getCurrentRSS();

    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds = end_time - start_time;

    // O pico de memória será o máximo entre a memória após toVector e após fromVector, subtraindo a memória antes das operações da estrutura
    long peak_memory_kb = std::max(initial_memory_kb, std::max(memory_after_to_vector, memory_after_from_vector));

    std::cout << "Sorting (including conversions) time: " << elapsed_seconds.count() << " seconds" << std::endl;
    std::cout << "Peak memory used during sorting: " << peak_memory_kb << " KB" << std::endl;

    // Registrar os resultados no coletor
    if (resultCollector) {
        resultCollector->addResult(structureType, dataSize, elapsed_seconds.count(), peak_memory_kb);
    }

    // 4. Escrever dados ordenados de volta para um novo CSV
    writeCsv(data_vector, outputFilePath);

    // 5. Limpar a estrutura de dados para o próximo uso
    dataStructure->clear();

    std::cout << "Processing complete. Output saved to: " << outputFilePath << std::endl;
    std::cout << "==================================================================" << std::endl;
}

// Lê timestamps de um arquivo CSV e os adiciona à estrutura de dados
void FileProcessor::readCsv(IDataStructure& dataStructure, const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Error opening input file: " << filePath << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line); // Ignorar cabeçalho

    while (std::getline(file, line)) {
        if (line.empty()) continue;
        try {
            long long timestamp_value = std::stoll(line);
            dataStructure.add(Timestamp(timestamp_value));
        } catch (const std::exception& e) {
            std::cerr << "Error converting line to long long: " << line << " - " << e.what() << std::endl;
        }
    }
    file.close();
}

// Escreve timestamps ordenados de um vetor para um arquivo CSV
void FileProcessor::writeCsv(const std::vector<Timestamp>& data, const std::string& filePath) {
    std::ofstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Error opening output file: " << filePath << std::endl;
        return;
    }

    file << "timestamp\n";
    for (const auto& ts : data) {
        file << ts.value << "\n";
    }
    file.close();
}

