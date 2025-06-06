#include <iostream>
#include <fstream>
#include <sstream>
#include "include/disco.h"
#include "include/filesystem.h"

std::vector<std::string> split_command(const std::string& command) {
    std::vector<std::string> args;
    std::istringstream stream(command);
    std::string arg;
    while (stream >> arg) {
        args.push_back(arg);
    }
    return args;
}

int main() {
    const std::string disk_filename = "./discos/disco.img";
    
    if (file_exists(disk_filename)) {
        std::cout << "Arquivo " << disk_filename << " encontrado. Carregando metadados...\n";
        load_metadata(); 
    } else {
        std::cout << "Arquivo " << disk_filename << " não encontrado. Criando novo disco...\n";
        initialize_disk(disk_filename);
        reopen_disk(disk_filename);
    }

    std::string command;
    while (true) {
        std::cout << "> manda ver > ";
        std::getline(std::cin, command);
        std::vector<std::string> args = split_command(command);
        if (args.empty()) continue;

        try {
            if (args[0] == "criar" && args.size() == 3) {
                create_file(args[1], std::stoul(args[2]));
            } else if (args[0] == "apagar" && args.size() == 2) {
                delete_file(args[1]);
            } else if (args[0] == "listar" && args.size() == 1) {
                list_files();
            } else if (args[0] == "ordenar" && args.size() == 2) {
                sort_file(args[1], disk_filename);
            } else if (args[0] == "ler" && args.size() == 4) {
                read_file(args[1], std::stoul(args[2]), std::stoul(args[3]));
            } else if (args[0] == "concatenar" && args.size() == 3) {
                concatenate_files(args[1], args[2], disk_filename);
            } else if (args[0] == "sair") {
                save_metadata();
                break;
            } else {
                std::cout << "Comando inválido\n";
            }
        } catch (const std::exception& e) {
            std::cerr << "Erro: " << e.what() << "\n";
        }
    }

    return 0;
}