#ifndef DISCO_H
#define DISCO_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <random>
#include "../include/filesystem.h"

extern std::vector<FileMetadata> metadata_table;
extern std::fstream disk;

void initialize_disk(const std::string& filename);
void load_metadata();
void save_metadata();
void reopen_disk(const std::string& filename);


#endif // DISCO_H