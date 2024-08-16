#pragma once

#include <string>


namespace utl::directory{

//Directory operations
void open(std::string path);
void clean(const char *path);
void remove(const std::string& path);
void create(std::string path);
int size(std::string path);

//Check existence
bool is_exist(std::string path);
bool is_directory(std::string path);

}
