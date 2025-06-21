#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <filesystem>
#include <functional>
#include <map>
#include <unistd.h>
#include <sys/wait.h>

#include "FileProcessor.h"
#include "DynamicList.h"
#include "StaticList.h"
#include "DynamicStack.h"
#include "StaticStack.h"
#include "DynamicQueue.h"
#include "StaticQueue.h"
#include "ResultCollector.h"

namespace fs = std::filesystem;

// Função auxiliar para executar o teste e escrever os resultados no pipe
void run_test_and_report(std::unique_ptr<IDataStructure> data_structure, const std::string& input_file, const std::string& output_file, const std::string& structure_name, int size, int pipe_write_fd) {
    FileProcessor processor;
    ProcessingMetrics metrics = processor.processFile(std::move(data_structure), input_file, output_file, structure_name, size);
    write(pipe_write_fd, &metrics, sizeof(ProcessingMetrics));
    close(pipe_write_fd);
    exit(EXIT_SUCCESS);
}

int main() {
    std::string base_input_path = "../datasets/ratings";
    std::string base_output_path = "../ordened/";
    std::string tables_output_path = "../results/";

    fs::create_directories(base_output_path);
    fs::create_directories(tables_output_path);

    ResultCollector collector;

    std::vector<std::string> structure_names = {
        "dynamicList", "dynamicQueue", "dynamicStack",
        "staticList", "staticQueue", "staticStack"
    };

    std::vector<int> dataset_sizes = {100, 1000, 10000, 100000, 1000000};

    for (const auto& structure_name : structure_names) {
        std::cout << "===== Iniciando processamento para a estrutura: " << structure_name << " =====" << std::endl;
        fs::create_directories(base_output_path + structure_name);

        for (int size : dataset_sizes) {
            std::string input_file = base_input_path + std::to_string(size) + ".csv";
            std::string output_file = base_output_path + structure_name + "/ratings" + std::to_string(size) + ".csv";

            if (!fs::exists(input_file)) {
                std::cerr << "Arquivo de entrada nao encontrado, pulando: " << input_file << std::endl;
                continue;
            }

            int pipefd[2];
            if (pipe(pipefd) == -1) {
                perror("pipe");
                exit(EXIT_FAILURE);
            }

            pid_t pid = fork();
            if (pid == -1) {
                perror("fork");
                exit(EXIT_FAILURE);
            }

            if (pid == 0) { // Processo Filho
                close(pipefd[0]); // Fecha a ponta de leitura

                // Lógica para selecionar a estrutura correta (dinâmica ou template estática)
                if (structure_name == "dynamicList") {
                    run_test_and_report(std::make_unique<DynamicList>(), input_file, output_file, structure_name, size, pipefd[1]);
                } else if (structure_name == "dynamicQueue") {
                    run_test_and_report(std::make_unique<DynamicQueue>(), input_file, output_file, structure_name, size, pipefd[1]);
                } else if (structure_name == "dynamicStack") {
                    run_test_and_report(std::make_unique<DynamicStack>(), input_file, output_file, structure_name, size, pipefd[1]);
                } else if (structure_name == "staticList") {
                    if (size == 100) run_test_and_report(std::make_unique<StaticList<100>>(), input_file, output_file, structure_name, size, pipefd[1]);
                    else if (size == 1000) run_test_and_report(std::make_unique<StaticList<1000>>(), input_file, output_file, structure_name, size, pipefd[1]);
                    else if (size == 10000) run_test_and_report(std::make_unique<StaticList<10000>>(), input_file, output_file, structure_name, size, pipefd[1]);
                    else if (size == 100000) run_test_and_report(std::make_unique<StaticList<100000>>(), input_file, output_file, structure_name, size, pipefd[1]);
                    else if (size == 1000000) run_test_and_report(std::make_unique<StaticList<1000000>>(), input_file, output_file, structure_name, size, pipefd[1]);
                } else if (structure_name == "staticQueue") {
                    if (size == 100) run_test_and_report(std::make_unique<StaticQueue<100>>(), input_file, output_file, structure_name, size, pipefd[1]);
                    else if (size == 1000) run_test_and_report(std::make_unique<StaticQueue<1000>>(), input_file, output_file, structure_name, size, pipefd[1]);
                    else if (size == 10000) run_test_and_report(std::make_unique<StaticQueue<10000>>(), input_file, output_file, structure_name, size, pipefd[1]);
                    else if (size == 100000) run_test_and_report(std::make_unique<StaticQueue<100000>>(), input_file, output_file, structure_name, size, pipefd[1]);
                    else if (size == 1000000) run_test_and_report(std::make_unique<StaticQueue<1000000>>(), input_file, output_file, structure_name, size, pipefd[1]);
                } else if (structure_name == "staticStack") {
                    if (size == 100) run_test_and_report(std::make_unique<StaticStack<100>>(), input_file, output_file, structure_name, size, pipefd[1]);
                    else if (size == 1000) run_test_and_report(std::make_unique<StaticStack<1000>>(), input_file, output_file, structure_name, size, pipefd[1]);
                    else if (size == 10000) run_test_and_report(std::make_unique<StaticStack<10000>>(), input_file, output_file, structure_name, size, pipefd[1]);
                    else if (size == 100000) run_test_and_report(std::make_unique<StaticStack<100000>>(), input_file, output_file, structure_name, size, pipefd[1]);
                    else if (size == 1000000) run_test_and_report(std::make_unique<StaticStack<1000000>>(), input_file, output_file, structure_name, size, pipefd[1]);
                }
                // Se nenhum teste for executado, o filho sai
                exit(EXIT_FAILURE);

            } else { // Processo Pai
                close(pipefd[1]);
                wait(NULL);

                ProcessingMetrics metrics;
                if (read(pipefd[0], &metrics, sizeof(ProcessingMetrics)) > 0) {
                    collector.addResult(structure_name, size, metrics.timeSeconds, metrics.memoryUsedKB);
                }
                close(pipefd[0]);
            }
        }
        std::cout << "===== Processamento para " << structure_name << " finalizado. =====\n" << std::endl;
    }

    collector.saveResultsToCsv(tables_output_path);
    std::cout << "Todos os processamentos foram concluidos. As tabelas de resultados foram salvas em: " << tables_output_path << std::endl;

    return 0;
}