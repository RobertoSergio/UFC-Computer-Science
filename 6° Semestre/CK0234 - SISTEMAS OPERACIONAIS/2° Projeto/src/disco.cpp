#include "../include/disco.h"
#include <vector>

std::vector<FileMetadata> metadata_table;
std::fstream disk("./discos/disco.img", std::ios::in | std::ios::out | std::ios::binary);

void initialize_disk(const std::string& filename) {
    std::ofstream disk(filename, std::ios::binary);
    if (!disk) {
        std::cerr << "Erro ao criar o arquivo disco.img\n";
        return;
    }


    std::vector<char> empty(DISK_SIZE, 0);
    disk.write(empty.data(), DISK_SIZE);


    size_t huge_page_start = DISK_SIZE - HUGEPAGE_SIZE;
    disk.seekp(huge_page_start, std::ios::beg);
    disk.write(empty.data(), HUGEPAGE_SIZE);

    std::cout << "Arquivo "  << filename << " criado com sucesso!\n";
    std::cout << "Huge Page de " << HUGEPAGE_SIZE << " bytes reservada.\n";
}

void save_metadata() {
    disk.seekp(0, std::ios::beg);
    for (const auto& entry : metadata_table) {
        disk.write(reinterpret_cast<const char*>(&entry), sizeof(FileMetadata));
    }

    FileMetadata end_entry = {};
    disk.write(reinterpret_cast<const char*>(&end_entry), sizeof(FileMetadata));
}

void load_metadata() {
    disk.seekg(0, std::ios::beg);
    metadata_table.clear();
    FileMetadata entry;
    while (disk.read(reinterpret_cast<char*>(&entry), sizeof(FileMetadata))) {
        if (entry.name[0] == '\0') break;
        metadata_table.push_back(entry);
    }
}

void reopen_disk(const std::string& filename) {
    disk.open(filename, std::ios::in | std::ios::out | std::ios::binary);
    if (!disk) {
        std::cerr << "Erro ao reabrir o arquivo " << filename << "\n";
        return;
    }
}