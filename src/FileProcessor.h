// src/FileProcessor.h
#ifndef FILE_PROCESSOR_H
#define FILE_PROCESSOR_H

#include <string>
#include <memory>
#include <vector>
#include "IDataStructure.h"
#include "Timestamp.h"

// Estrutura para retornar as métricas de um processamento
struct ProcessingMetrics {
    double timeSeconds;
    long memoryUsedKB;
};

// Classe responsável por ler, processar e escrever arquivos
class FileProcessor {
private:
    void readCsv(IDataStructure& dataStructure, const std::string& filePath);
    void writeCsv(const std::vector<Timestamp>& data, const std::string& filePath);

public:
    // Construtor padrão
    FileProcessor() = default;

    // Processa um arquivo e retorna as métricas de tempo e memória
    ProcessingMetrics processFile(std::unique_ptr<IDataStructure> dataStructure, const std::string& inputFilePath, const std::string& outputFilePath, const std::string& structureType, int dataSize);
};

#endif // FILE_PROCESSOR_H