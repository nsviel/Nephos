#pragma once

#include <string>
#include <vector>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <random>
#include <fstream>
#include <unistd.h>
#include <filesystem>
#include <iostream>
#include <algorithm>
#include <experimental/filesystem>


namespace utl::directory{

//Directory operations
void clean_file(const char *path);
void clean_folder(const std::string& path);
void create_new(std::string path);
int get_number_file(std::string path);

//Check existence
bool is_dir_exist(std::string path);
bool is_directory(std::string path);

}
