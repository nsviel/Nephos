#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <fcntl.h>
#include <unistd.h>
#include <experimental/filesystem>


namespace utl::file{

//Check
bool is_file_exist(std::string path);
bool is_file_exist_silent(std::string path);

//Info
int get_file_nbPoint(std::string pathFile);
double get_file_size(std::string path);
std::string get_file_formatted_size(std::string path);

//Operation
void clear_file(std::string path);
void check_or_create_file(std::string path);
uint8_t* load_file_binary(std::string path);
std::vector<std::string> read_paths_from_file(const std::string& filePath);
void write_paths_to_file(const std::string& filePath, const std::vector<std::string>& paths);

}
