#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <filesystem>
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

#define TEST_STRUCTURE_NAME "staticStack"
#define TEST_DATASET_SIZE 1000000

int main() {
    std::string base_input_path = "../datasets/ratings";
    std::string base_output_path = "../ordened/";
    std::string tables_output_path = "../tables/";

    fs::create_directories(tables_output_path);

    ResultCollector collector;
    FileProcessor processor(&collector);

    std::unique_ptr<IDataStructure> data_structure;

    // Seleciona a estrutura de dados com base no define
    std::string structure_name = TEST_STRUCTURE_NAME;
    int dataset_size = TEST_DATASET_SIZE;


    std::string input_file = base_input_path + std::to_string(dataset_size) + ".csv";
    std::string output_file_path = base_output_path + structure_name + "/ratings" + std::to_string(dataset_size) + ".csv";

    long long memory_sum = 0;

    for (int i = 0; i < 10; i++)
    {
        // Cria uma nova instância da estrutura de dados em cada iteração
        std::unique_ptr<IDataStructure> current_data_structure;
        if (structure_name == "dynamicList") {
            current_data_structure = std::make_unique<DynamicList>();
        } else if (structure_name == "staticList") {
            current_data_structure = std::make_unique<StaticList>();
        } else if (structure_name == "dynamicStack") {
            current_data_structure = std::make_unique<DynamicStack>();
        } else if (structure_name == "staticStack") {
            current_data_structure = std::make_unique<StaticStack>();
        } else if (structure_name == "dynamicQueue") {
            current_data_structure = std::make_unique<DynamicQueue>();
        } else if (structure_name == "staticQueue") {
            current_data_structure = std::make_unique<StaticQueue>();
        }

        memory_sum += processor.processFile(std::move(current_data_structure), input_file, output_file_path, structure_name, dataset_size);
        
    }
    
    

    // Não salva os resultados em CSV quando testando individualmente, o foco é a saída do /usr/bin/time -v
    // collector.saveResultsToCsv(tables_output_path);

    // Adicionado para evitar double free se o programa for executado múltiplas vezes no mesmo processo
    // data_structure.release(); // Removido, pois não é necessário e pode causar problemas se o unique_ptr for usado novamente

    std::cout << "Processamento para " << structure_name << " com dataset de " << dataset_size << " completo." << std::endl;
    std::cout <<"A média, de 10 execuções, da memória é: " << memory_sum/10 << "kb." << std::endl;
    return 0;
}


