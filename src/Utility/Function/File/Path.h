#pragma once

#include <string>
#include <vector>


namespace utl::path{

std::string get_name_from_path(std::string path);
std::string get_format_from_path(std::string path);
std::string get_format_from_filename(std::string path);
std::string get_name_from_filename(const std::string& path);
std::string get_name_and_parent_from_path(std::string path);
std::string get_filename_from_path(std::string path);
std::string get_type_from_path(std::string path);
std::string get_current_path_abs();
std::string get_absolute_path(const std::string& relativePath);
std::string get_current_parent_path_abs();
std::string get_dir_from_path(std::string path);
std::string is_dir_or_file(std::string path);
std::string reconstruct_path(std::string dir, std::string name, std::string format);

std::vector<std::string> list_all_file(std::string path, std::string format);
std::vector<std::string> list_all_file(std::string path);
std::vector<std::string> list_all_path(std::string path);
std::vector<std::string> list_all_dir(std::string path);

}
