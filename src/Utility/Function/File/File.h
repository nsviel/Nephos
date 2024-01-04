#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <fcntl.h>
#include <unistd.h>
#include <experimental/filesystem>


namespace file{
  //---------------------------

  std::string get_current_path_abs();
  std::string get_absolute_path(const std::string& relativePath);
  std::string get_current_parent_path_abs();
  void clear_file(std::string path);
  bool is_file_exist(std::string fileName);
  bool is_device_connected(const std::string& devicePath);
  uint8_t* load_file_binary(std::string path);

  //---------------------------
}
