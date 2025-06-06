#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <stddef.h>
#include <vector>
#include <string>

#define DISK_SIZE 1024 * 1024 * 1024
#define HUGEPAGE_SIZE 2 * 1024 * 1024 
#define METADATA_SIZE 1024 * 1024 

struct FileMetadata {
    char name[256];      
    size_t size;         
    size_t start_block;  
};

void create_file(const std::string& name, size_t size);
void read_file(const std::string& name, size_t start, size_t end);
void list_files();
void sort_file(const std::string& name, const std::string& disk_filename);
void merge_sorted_parts(std::fstream& disk, FileMetadata* entry, 
    const std::vector<size_t>& part_start_blocks, size_t integers_per_huge_page);
void concatenate_files(const std::string& file1, const std::string& file2, 
    const std::string& disk_filename);
void delete_file(const std::string& name);
bool file_exists(const std::string& filename);
bool has_sufficient_disk_space(size_t file_size);

#endif // FILESYSTEM_H