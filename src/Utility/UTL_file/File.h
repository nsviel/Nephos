#ifndef FILE_H
#define FILE_H

#include <string>
#include <iostream>
#include <fstream>
#include <fcntl.h>
#include <unistd.h>
#include <experimental/filesystem>


namespace file{
  //---------------------------

  std::string get_path_abs_build();
  void clear_file(std::string path);
  bool is_file_exist(std::string fileName);
  bool is_device_connected(const std::string& devicePath);

  //---------------------------
}

#endif
