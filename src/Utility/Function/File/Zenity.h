#pragma once

#include <string>
#include <vector>


namespace zenity{
  //---------------------------

  std::vector<std::string> selection_file_vec(std::string title, std::string& path_dir);
  std::vector<std::string> selection_file_vec(std::string title);
  std::string selection_directory(std::string title, std::string& path_dir);
  void selection_file(std::string& path_file);
  std::string selection_file();
  void selection_directory(std::string& path_dir);
  std::string selection_saving(std::string& dir, std::string filename);

  //---------------------------
}
