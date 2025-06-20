// src/FileProcessor.h
#ifndef FILE_PROCESSOR_H
#define FILE_PROCESSOR_H

#include <string>
#include <memory>
#include <vector>
#include "IDataStructure.h"
#include "Timestamp.h"
#include "MemoryMonitor.h"

// Forward declaration for ResultCollector
class ResultCollector;

// Classe responsável por ler, processar e escrever arquivos
class FileProcessor {
private:
    // Ponteiro para o coletor de resultados, para registrar as métricas
    ResultCollector* resultCollector;

    // Métodos auxiliares
    void readCsv(IDataStructure& dataStructure, const std::string& filePath);
    void writeCsv(const std::vector<Timestamp>& data, const std::string& filePath);

public:
    // Construtor que recebe o coletor de resultados
    FileProcessor(ResultCollector* collector) : resultCollector(collector) {}

    // Processa um arquivo CSV com uma estrutura de dados específica
    long processFile(std::unique_ptr<IDataStructure> dataStructure, const std::string& inputFilePath, const std::string& outputFilePath, const std::string& structureType, int dataSize);
};

#endif // FILE_PROCESSOR_H

