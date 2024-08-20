#include "Path.h"

#include <Utility/Function/File/Directory.h>
#include <Utility/Function/File/File.h>
#include <iomanip>
#include <vector>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <random>
#include <list>
#include <fstream>
#include <unistd.h>
#include <filesystem>
#include <iostream>
#include <algorithm>
#include <fcntl.h>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;


namespace utl::path{

std::string get_name_from_path(std::string path){
  //Return file name
  //---------------------------

  if(path == "") return "(not defined)";
  std::string name_format = path.substr(path.find_last_of("/\\") + 1);
  std::string name = name_format.substr(0, name_format.find_last_of("."));

  //---------------------------
  return name;
}
std::string get_filename_from_path(std::string path){
  // Return file name.format
  //---------------------------

  if(path == "") return "(not defined)";
  std::string filename = path.substr(path.find_last_of("/\\") + 1);

  //---------------------------
  return filename;
}
std::string get_name_and_parent_from_path(std::string path){
  //Return file parent/name
  //---------------------------

  if(path == "") return "(not defined)";
  std::string path_parent = path.substr(0, path.find_last_of("/\\"));
  std::string parent = path_parent.substr(path_parent.find_last_of("/\\"));
  std::string name_format = path.substr(path.find_last_of("/\\"));
  std::string parent_name_format = parent + name_format;
  std::string parent_name = parent_name_format.substr(0, parent_name_format.find_last_of("."));

  //---------------------------
  return parent_name;
}
std::string get_format_from_path(std::string path){
  //Return file format
  //---------------------------

  if(path == "") return "(not defined)";

  std::string name_format = path.substr(path.find_last_of("/\\") + 1);
  size_t dot_position = name_format.find_last_of(".");
  if(dot_position == std::string::npos){
    return "";
  }

  std::string format = name_format.substr(dot_position);

  //---------------------------
  return format;
}
std::string get_format_from_filename(std::string filename){
  //---------------------------

  if(filename == "") return "(not defined)";
  std::string format = filename.substr(filename.find_last_of("."), std::string::npos);

  //---------------------------
  return format;
}
std::string get_name_from_filename(const std::string& filename){
  std::string name;
  //---------------------------

  if(filename.empty()) return "(not defined)";
  size_t last_dot = filename.find_last_of('.');
  if(last_dot != std::string::npos){
    name = filename.substr(0, last_dot);
  }else{
    name = filename;
  }

  //---------------------------
  return name;
}
std::string get_type_from_path(std::string path){
  //Return file type (folder / file)
  //---------------------------

  std::string type;
  if(std::filesystem::is_directory(path)){
    type = "Folder";
  }else{
    type = "File";
  }

  //---------------------------
  return type;
}
std::string get_current_path_abs(){
  //---------------------------

  fs::path currentPath = fs::current_path();
  std::string absPath = currentPath.string();
  absPath += "/";

  //---------------------------
  return absPath;
}
std::string get_current_directory_path(){
  //---------------------------

  fs::path currentPath = fs::current_path();
  std::string dir_path = currentPath.parent_path().string();

  // Ensure the parent path ends with a slash
  if(!dir_path.empty() && dir_path.back() != '/'){
    dir_path += '/';
  }

  //---------------------------
  return dir_path;
}
std::string get_absolute_path(const std::string& relativePath){
  //---------------------------

  fs::path currentPath = fs::current_path();
  fs::path absolutePath = currentPath / relativePath;

  // Resolve ".." and its parent folder
  if(utl::file::is_exist(absolutePath)){
    absolutePath = fs::canonical(absolutePath);
  }else{
    return "";
  }

  //---------------------------
  return absolutePath.string();
}
std::string get_dir_from_path(std::string path){
  if(path == "") return "";
  //---------------------------

  std::filesystem::path path_obj(path);

  // Get the parent directory
  std::filesystem::path dir_path = path_obj.parent_path();

  // Convert the directory path to a string
  std::string directory = dir_path.string() + "/";

  //---------------------------
  return directory;
}
std::string get_parent_path(std::string path){
  if(path == "") return "(not defined)";
  //---------------------------

  //Remove the trailing slash if it exists
  if(path.back() == '/'){
    path.pop_back();
  }

  std::filesystem::path fs_path(path);
  std::string parent = fs_path.parent_path().string();

  // Ensure the parent path ends with a slash
  if(!parent.empty() && parent.back() != '/'){
    parent += '/';
  }

  //---------------------------
  return parent;
}
std::string is_dir_or_file(std::string path){
  std::string type;
  //---------------------------

  struct stat s;
  if(stat(path.c_str(), &s) == 0){
    if(s.st_mode & S_IFDIR){
      type = "directory";
    }
    else if(s.st_mode & S_IFREG){
      type = "file";
    }
  }

  //---------------------------
  return type;
}
std::vector<std::string> list_all_file(std::string path, std::string required_format){
  //---------------------------

  struct dirent* files;
  DIR* directory = opendir(path.c_str());
  std::vector<std::string> path_vec;

  if(!utl::directory::is_exist(path) || is_dir_or_file(path) == "file"){
    std::cout << "[error] Directory does not exist: " << path << std::endl;
    return path_vec;
  }

  // Filtre and store files present in the folder
  while((files = readdir(directory)) != NULL){
    std::string filename = files->d_name;
    std::string format = utl::path::get_format_from_filename(filename);

    // Skip the special directories "." and ".."
    if(filename != "." && filename != ".." && format == required_format){
      path_vec.push_back(filename);
    }
  }

  // Close and return the file names list
  closedir(directory);

  // Sort vector in alphabetical order
  std::sort(path_vec.begin(), path_vec.end());

  //---------------------------
  return path_vec;
}
std::vector<std::string> list_all_file(std::string path){
  //---------------------------

  struct dirent* files;
  DIR* directory = opendir(path.c_str());
  std::vector<std::string> path_vec;

  if(utl::directory::is_exist(path) == false || is_dir_or_file(path) == "file"){
    std::cout << "[error] Directory does not exists: " << path << std::endl;
    return path_vec;
  }

  // Filter and store files present in the folder
  while((files = readdir(directory)) != NULL){
    std::string name = files->d_name;

    if(name != "." && name != ".."){
      std::string full_path = path + "/" + name;

      struct stat path_stat;
      stat(full_path.c_str(), &path_stat);

      // Check if it is a regular file
      if(S_ISREG(path_stat.st_mode)){
        path_vec.push_back(name);
      }
    }
  }

  // Close and return the file names list
  closedir(directory);

  // Sort vector in alphabetic order
  std::sort(path_vec.begin(), path_vec.end());

  //---------------------------
  return path_vec;
}
std::vector<std::string> list_all_path(std::string path_dir){
  //---------------------------

  struct dirent* files;
  DIR* directory = opendir(path_dir.c_str());
  std::vector<std::string> path_vec;

  //Check if directory exists
  if(utl::directory::is_exist(path_dir) == false || is_dir_or_file(path_dir) == "file"){
    return path_vec;
  }

  //Supress unwanted line break
  if(path_dir.find('\n')){
    path_dir.erase(std::remove(path_dir.begin(), path_dir.end(), '\n'), path_dir.end());
  }

  //Filtre and store files present in the folder
  while((files = readdir(directory)) != NULL){
    std::string path_file = files->d_name;
    std::string path_full = path_dir + path_file;

    if(path_file != "."){
      path_vec.push_back(path_full);
    }
  }

  //Close and return the file names list
  closedir(directory);

  //Sort vector in alphabetic order
  std::sort(path_vec.begin(), path_vec.end());

  //---------------------------
  return path_vec;
}
std::vector<std::string> list_all_dir(std::string path){
  //---------------------------

  struct dirent* files;
  DIR* directory = opendir(path.c_str());
  std::vector<std::string> vec_dir;

  //Check if directory exists
  if(utl::directory::is_exist(path) == false || is_dir_or_file(path) == "file"){
    return vec_dir;
  }

  //Filtre and store files present in the folder
  while((files = readdir(directory)) != NULL){
    std::string name = files->d_name;
    if((strchr(files->d_name, '.')) == NULL){
      vec_dir.push_back(name + "/");
    }
  }

  //Close and return the file names list
  closedir(directory);

  //---------------------------
  return vec_dir;
}

}
