#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>


namespace utl::transformation{

glm::mat4 find_transformation_from_file(std::string path);
void save_transformation_to_file(glm::mat4& mat, std::string path);
void make_transformation_identity(glm::mat4& mat);
void apply_transformation_capture(glm::mat4& mat);

}
