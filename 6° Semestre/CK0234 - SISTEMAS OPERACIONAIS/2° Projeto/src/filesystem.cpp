#include "../include/filesystem.h"
#include "../include/disco.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <random>
#include <cstring>
#include <time.h>
#include <climits>
#include <filesystem>
#include <ctime>

void create_file(const std::string& name, size_t size) {
    for (const auto& entry : metadata_table) {
        if (entry.name == name) {
            std::cerr << "Erro: Arquivo '" << name << "' já existe.\n";
            return;
        }
    }

    if (!has_sufficient_disk_space(size)) {
        std::cerr << "Erro: Espaço insuficiente no disco para criar o arquivo '" << name << "'.\n";
        return;
    }

    std::vector<int> data(size / sizeof(int));
    
    std::mt19937 gen(static_cast<unsigned int>(std::time(nullptr)));  
    std::uniform_int_distribution<> dis(1, 1000);
    
    for (auto& num : data) {
        num = dis(gen);
    }

    size_t start_block = METADATA_SIZE + metadata_table.size() * sizeof(FileMetadata);

    disk.seekp(start_block, std::ios::beg);
    disk.write(reinterpret_cast<const char*>(data.data()), size);

    FileMetadata entry;
    std::strcpy(entry.name, name.c_str());
    entry.size = size;
    entry.start_block = start_block;

    metadata_table.push_back(entry);
    save_metadata();

    std::cout << "Arquivo '" << name << "' criado com sucesso.\n";
}

void list_files() {
    load_metadata();
    size_t tamanho =0;
    if (metadata_table.empty()) {
        std::cout << "Nenhum arquivo encontrado no disco.\n";
        std::cout << "Espaço em uso: " << tamanho << std::endl;
        return;
    }

    std::cout << "-------------"<< "\n";
    std::cout << "Arquivos no disco:\n";
    std::cout << "-------------"<< "\n";

    for (const auto& entry : metadata_table) {
        tamanho += entry.size;
        std::cout << "Nome: " << entry.name << ", Tamanho: " << entry.size << " bytes\n";
    }

    std::cout << "-------------"<< "\n";
    std::cout << "Espaço em uso: " << tamanho << std::endl;
    std::cout << "Espaço disponível: " << DISK_SIZE - tamanho << std::endl;
}

void sort_file(const std::string& name, const std::string& disk_filename) {
    clock_t begin = clock();

    FileMetadata* entry = nullptr;
    for (auto& e : metadata_table) {
        if (std::string(e.name) == name) {
            entry = &e;
            break;
        }
    }
    if (!entry) {
        std::cerr << "Erro: Arquivo '" << name << "' não encontrado.\n";
        return;
    }

    std::fstream disk(disk_filename, std::ios::in | std::ios::out | std::ios::binary);
    if (!disk) {
        std::cerr << "Erro ao abrir o arquivo " << disk_filename << "\n";
        return;
    }

    const size_t huge_page_size = HUGEPAGE_SIZE;

    const size_t integers_per_huge_page = huge_page_size / sizeof(int);

    const size_t total_integers = entry->size / sizeof(int);

    const size_t num_parts = (total_integers + integers_per_huge_page - 1) / integers_per_huge_page;

    std::vector<size_t> part_start_blocks;

    for (size_t i = 0; i < num_parts; i++) {
        size_t part_size = std::min(integers_per_huge_page, total_integers - i * integers_per_huge_page);

        std::vector<int> data(part_size);
        disk.seekg(entry->start_block + i * integers_per_huge_page * sizeof(int), std::ios::beg);
        disk.read(reinterpret_cast<char*>(data.data()), part_size * sizeof(int));

        std::sort(data.begin(), data.end());

        disk.seekp(entry->start_block + i * integers_per_huge_page * sizeof(int), std::ios::beg);
        disk.write(reinterpret_cast<const char*>(data.data()), part_size * sizeof(int));

        part_start_blocks.push_back(entry->start_block + i * integers_per_huge_page * sizeof(int));
    }

    merge_sorted_parts(disk, entry, part_start_blocks, integers_per_huge_page);

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    std::cout << "Arquivo '" << name << "' ordenado com sucesso em " << time_spent << "s\n";
}


void concatenate_files(const std::string& file1, const std::string& file2, const std::string& disk_filename) {
    FileMetadata* entry1 = nullptr;
    FileMetadata* entry2 = nullptr;

    for (auto& e : metadata_table) {
        if (std::string(e.name) == file1) entry1 = &e;
        if (std::string(e.name) == file2) entry2 = &e;
    }

    if (!entry1 || !entry2) {
        std::cerr << "Erro: Um dos arquivos não foi encontrado.\n";
        return;
    }

    std::fstream disk(disk_filename, std::ios::in | std::ios::out | std::ios::binary);
    if (!disk) {
        std::cerr << "Erro ao abrir o arquivo " << disk_filename << "\n";
        return;
    }

    std::vector<int> data1(entry1->size / sizeof(int));
    disk.seekg(entry1->start_block, std::ios::beg);
    disk.read(reinterpret_cast<char*>(data1.data()), entry1->size);

    std::vector<int> data2(entry2->size / sizeof(int));
    disk.seekg(entry2->start_block, std::ios::beg);
    disk.read(reinterpret_cast<char*>(data2.data()), entry2->size);

    std::vector<int> concatenated_data = data1;
    concatenated_data.insert(concatenated_data.end(), data2.begin(), data2.end());

    size_t concatenated_size = concatenated_data.size() * sizeof(int);

    // Verifica se há espaço suficiente
    if (!has_sufficient_disk_space(concatenated_size)) {
        std::cerr << "Erro: Espaço insuficiente para o arquivo concatenado.\n";
        return;
    }

    // Encontra o primeiro bloco livre para gravar o arquivo concatenado
    size_t new_start_block = METADATA_SIZE + metadata_table.size() * sizeof(FileMetadata);
    for (const auto& entry : metadata_table) {
        size_t entry_end = entry.start_block + entry.size;
        if (entry_end > new_start_block) {
            new_start_block = entry_end;
        }
    }

    disk.seekp(new_start_block, std::ios::beg);
    disk.write(reinterpret_cast<const char*>(concatenated_data.data()), concatenated_size);

    // Atualiza a tabela de metadados
    FileMetadata new_entry;
    strcpy(new_entry.name, file1.c_str());
    new_entry.size = concatenated_size;
    new_entry.start_block = new_start_block;

    // Remove os arquivos antigos
    metadata_table.erase(std::remove_if(metadata_table.begin(), metadata_table.end(),
                        [&](const FileMetadata& e) { return std::string(e.name) == file1 || std::string(e.name) == file2; }),
                        metadata_table.end());

    metadata_table.push_back(new_entry);

    save_metadata();
    std::cout << "Arquivos '" << file1 << "' e '" << file2 << "' concatenados com sucesso.\n";
}

void merge_sorted_parts(std::fstream& disk, FileMetadata* entry, const std::vector<size_t>& part_start_blocks, size_t integers_per_huge_page) {

    std::vector<size_t> current_indices(part_start_blocks.size(), 0);

    std::vector<int> current_values(part_start_blocks.size());

    for (size_t i = 0; i < part_start_blocks.size(); i++) {
        disk.seekg(part_start_blocks[i], std::ios::beg);
        disk.read(reinterpret_cast<char*>(&current_values[i]), sizeof(int));
    }

    std::vector<int> merged_data;
    merged_data.reserve(entry->size / sizeof(int));
    while (true) {
        int min_value = INT_MAX;
        size_t min_part = 0;
        bool all_parts_done = true;

        for (size_t i = 0; i < part_start_blocks.size(); i++) {
            if (current_indices[i] < integers_per_huge_page) {
                all_parts_done = false;

                if (current_values[i] < min_value) {
                    min_value = current_values[i];
                    min_part = i;
                }
            }
        }

        if (all_parts_done) break;

        merged_data.push_back(min_value);
        current_indices[min_part]++;

        if (current_indices[min_part] < integers_per_huge_page) {
            disk.seekg(part_start_blocks[min_part] + current_indices[min_part] * sizeof(int), std::ios::beg);
            disk.read(reinterpret_cast<char*>(&current_values[min_part]), sizeof(int));
        }
    }

    disk.seekp(entry->start_block, std::ios::beg);
    disk.write(reinterpret_cast<const char*>(merged_data.data()), merged_data.size() * sizeof(int));
}

void read_file(const std::string& name, size_t start, size_t end) {
    
    auto it = std::find_if(metadata_table.begin(), metadata_table.end(),
                           [&name](const FileMetadata& entry) { return entry.name == name; });

    if (it == metadata_table.end()) {
        std::cerr << "Erro: Arquivo '" << name << "' não encontrado.\n";
        return;
    }

    if (start >= it->size / sizeof(int) || end > it->size / sizeof(int) || start >= end) {
        std::cerr << "Erro: Intervalo de leitura inválido.\n";
        return;
    }

    std::fstream disk("./discos/disco.img", std::ios::in | std::ios::binary);
    if (!disk) {
        std::cerr << "Erro ao abrir o arquivo disco.\n";
        return;
    }

    // Define a posição inicial para o início do arquivo + o bloco de dados do arquivo
    size_t file_start = it->start_block;
    disk.seekg(file_start + start * sizeof(int), std::ios::beg);  // Multiplicamos start por sizeof(int) para obter o byte correto

    // Calcula o número de inteiros a serem lidos
    size_t num_integers_to_read = end - start;
    std::vector<int> buffer(num_integers_to_read);

    disk.read(reinterpret_cast<char*>(buffer.data()), num_integers_to_read * sizeof(int));

    if (disk.gcount() < num_integers_to_read * sizeof(int)) {
        std::cerr << "Erro: Não foi possível ler o número completo de inteiros.\n";
    } else {
        std::cout << "Leitura bem-sucedida de " << num_integers_to_read << " inteiros de '" << name << "':\n";
        // Exibe os dados lidos (os inteiros)
        for (size_t i = 0; i < buffer.size(); ++i) {
            std::cout << "Inteiro " << i + start << ": " << buffer[i] << "\n";
        }
        std::cout << "\n";
    }

    disk.close();
}



void delete_file(const std::string& name) {
    auto it = std::remove_if(metadata_table.begin(), metadata_table.end(),
                             [&](const FileMetadata& e) { return std::string(e.name) == name; });
    if (it == metadata_table.end()) {
        std::cerr << "Erro: Arquivo '" << name << "' não encontrado.\n";
        return;
    }

    metadata_table.erase(it, metadata_table.end());

    save_metadata();
    std::cout << "Arquivo '" << name << "' deletado com sucesso.\n";
}


bool file_exists(const std::string& filename) {
    return std::filesystem::exists(filename);
}

bool has_sufficient_disk_space(size_t file_size) {
    size_t total_used_space = 0;

    for (const auto& entry : metadata_table) {
        total_used_space += entry.size;
    }

    size_t available_space = DISK_SIZE - total_used_space;

    return available_space >= file_size;
}