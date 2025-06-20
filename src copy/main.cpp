// src/main.cpp
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <filesystem> // Para criar diretórios
#include <functional> 

#include "FileProcessor.h"
#include "DynamicList.h"
#include "StaticList.h"
#include "DynamicStack.h"
#include "StaticStack.h"
#include "DynamicQueue.h"
#include "StaticQueue.h"
#include "ResultCollector.h"

namespace fs = std::filesystem;

int main() {
    std::vector<int> dataset_sizes = {100, 1000, 10000, 100000, 1000000};
    std::string base_input_path = "./datasets/ratings";
    std::string base_output_path = "./ordened/";
    std::string tables_output_path = "./tables/";

    // Criar o diretório 'tables' se não existir
    fs::create_directories(tables_output_path);

    ResultCollector collector;
    FileProcessor processor(&collector);

    std::vector<std::pair<std::string, std::function<std::unique_ptr<IDataStructure>()>>> structures = {
        {"dynamicList", [](){ return std::make_unique<DynamicList>(); }},
        {"staticList", [](){ return std::make_unique<StaticList>(); }},
        {"dynamicStack", [](){ return std::make_unique<DynamicStack>(); }},
        {"staticStack", [](){ return std::make_unique<StaticStack>(); }},
        {"dynamicQueue", [](){ return std::make_unique<DynamicQueue>(); }},
        {"staticQueue", [](){ return std::make_unique<StaticQueue>(); }}
    };

    for (int size : dataset_sizes) {
        std::string input_file = base_input_path + std::to_string(size) + ".csv";

        for (const auto& structure_pair : structures) {
            std::string structure_name = structure_pair.first;
            std::unique_ptr<IDataStructure> data_structure = structure_pair.second();
            std::string output_file_path = base_output_path + structure_name + "/ratings" + std::to_string(size) + ".csv";

            processor.processFile(std::move(data_structure), input_file, output_file_path, structure_name, size);
        }
    }

    // std::string input_file = base_input_path + "100.csv";
    // std::string structure_name = "dynamicQueue";
    // std::unique_ptr<IDataStructure> data_structure = std::make_unique<DynamicQueue>();
    // std::string output_file_path = base_output_path + structure_name + "/ratings100.csv";

    // processor.processFile(std::move(data_structure), input_file, output_file_path, structure_name, 100);



    // Salvar os resultados coletados em arquivos CSV
    collector.saveResultsToCsv(tables_output_path);

    std::cout << "All processing complete. Results saved in 'tables' directory." << std::endl;

    return 0;
}


