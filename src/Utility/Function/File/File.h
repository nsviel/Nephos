#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <fcntl.h>
#include <unistd.h>
#include <experimental/filesystem>


namespace utl::fct::file{
  //---------------------------

  std::string get_current_path_abs();
  std::string get_absolute_path(const std::string& relativePath);
  std::string get_current_parent_path_abs();
  void clear_file(std::string path);
  bool is_file_exist(std::string fileName);
  bool is_file_exist_silent(std::string fileName);
  void check_or_create_file(std::string fileName);
  bool is_device_connected(const std::string& devicePath);
  uint8_t* load_file_binary(std::string path);
  std::vector<std::string> read_paths_from_file(const std::string& filePath);
  void write_paths_to_file(const std::string& filePath, const std::vector<std::string>& paths);

  //---------------------------
}
