#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>


namespace utl::file{

//Check
bool is_exist(std::string path);
bool is_exist_silent(std::string path);
bool is_empty(const std::string& path);

//Info
int number_point(std::string path);
double size(std::string path);
std::string formatted_size(std::string path);

//Operation
void clear(std::string path);
bool check_or_create(std::string path);
uint8_t* load_binary(std::string path);

//Export / import
void write_vec_path(const std::string& path, const std::vector<std::string>& vec_path);
void write_vector(const std::string& path, const std::vector<glm::vec3>& vec);
void write_vector(const std::string& path, const std::vector<float>& vec);
std::vector<std::string> read_vec_path(const std::string& path);
std::vector<glm::vec3> read_vector(const std::string& path);

}
