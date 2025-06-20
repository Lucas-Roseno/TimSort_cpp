// src/ResultCollector.h
#ifndef RESULT_COLLECTOR_H
#define RESULT_COLLECTOR_H

#include <vector>
#include <string>
#include <map>

// Estrutura para armazenar um único resultado de teste
struct TestResult {
    std::string structureType;
    int dataSize;
    double timeSeconds;
    long memoryUsedKB;
    // Desempenho computacional pode ser inferido do tempo ou adicionado aqui se houver uma métrica específica
};

// Classe para coletar e gerenciar todos os resultados dos testes
class ResultCollector {
private:
    std::vector<TestResult> results;

public:
    // Adiciona um novo resultado à coleção
    void addResult(const std::string& structureType, int dataSize, double timeSeconds, long memoryUsedKB);

    // Retorna todos os resultados coletados
    const std::vector<TestResult>& getResults() const;

    // Salva os resultados em arquivos CSV separados
    void saveResultsToCsv(const std::string& outputDir) const;
};

#endif // RESULT_COLLECTOR_H

