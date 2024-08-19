#include "File.h"

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
#include <fstream>
#include <unistd.h>
#include <filesystem>
#include <iostream>
#include <algorithm>
#include <fcntl.h>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;


namespace utl::file{

//Check
bool is_exist(std::string path){
  bool is_exists;
  //---------------------------

  std::ifstream infile(path.c_str());
  is_exists = infile.good();

  if(!is_exists){
    std::cerr<<"[error] File at ["<<path<<"] doesn't exists"<<std::endl;
  }

  //---------------------------
  return is_exists;
}
bool is_exist_silent(std::string path){
  bool is_exists;
  //---------------------------

  std::ifstream infile(path.c_str());
  is_exists = infile.good();

  //---------------------------
  return is_exists;
}
bool is_empty(const std::string& path){
  //---------------------------

  std::ifstream file(path, std::ios::binary | std::ios::ate);

  //---------------------------
  return file.is_open() && file.tellg() == 0;
}

//Info
int number_point(std::string path){
  //---------------------------

  int cpt=0;
  std::string line;
  std::ifstream infile(path);
  while(std::getline(infile, line)){
    cpt++;
  }

  //---------------------------
  return cpt;
}
double size(std::string path){
  //---------------------------

  // Open the file and move the file pointer to the end
  std::ifstream in(path, std::ifstream::ate | std::ifstream::binary);
  if(!in.is_open()){
    throw std::runtime_error("Failed to open file.");
  }

  // Get the file size in bytes
  std::streamoff fileSize = in.tellg();
  if(fileSize == -1){
    throw std::runtime_error("Failed to get file size.");
  }

  double result = static_cast<double>(fileSize) / (1024 * 1024);

  //---------------------------
  return result;
}
std::string formatted_size(std::string path){
  const char* sizeUnits[] = {"bytes", "kB", "MB", "GB"};
  int unitIndex = 0;
  //---------------------------

  std::ifstream in(path.c_str(), std::ifstream::ate | std::ifstream::binary);
  float fileSizeBytes = static_cast<float>(in.tellg());

  while(fileSizeBytes >= 1024.0 && unitIndex < 3){
    fileSizeBytes /= 1024.0;
    unitIndex++;
  }

  std::stringstream result;
  if(unitIndex == 0){
    result << std::fixed << std::setprecision(0) << fileSizeBytes << " " << sizeUnits[unitIndex];
  }else{
    result << std::fixed << std::setprecision(1) << fileSizeBytes << " " << sizeUnits[unitIndex];
  }

  //---------------------------
  return result.str();
}

//Operation
bool check_or_create(std::string path){
  //---------------------------

  //Check file existence
  std::ifstream infile(path.c_str());
  bool is_exists = infile.good();

  //Create file
  if(is_exists == false){
    std::ofstream file(path);
    file.close();
    return false;
  }

  //---------------------------
  return true;
}
void clear(std::string path){
  //---------------------------

  // Open the file in the output mode (out), which will clear the file
  std::ofstream outputFile(path.c_str(), std::ofstream::out);

  if(outputFile.is_open()){
    outputFile.close();
  }else{
    std::cout << "Failed to open the file forclearing." << std::endl;
  }

  //---------------------------
}
uint8_t* load_binary(std::string path){
  //---------------------------

  FILE* file = fopen(path.c_str(), "rb"); // Open the file forreading in binary mode

  uint8_t* buffer;
  if(file != NULL){
    fseek(file, 0, SEEK_END); // Move the file pointer to the end
    long fileSize = ftell(file); // Get the file size
    fseek(file, 0, SEEK_SET); // Move the file pointer back to the beginning

    // Allocate memory to store the file contents as uint8_t
    buffer = (uint8_t*)malloc(fileSize);

    if(buffer != NULL){
      // Read the file contents directly into the uint8_t buffer
      size_t bytesRead = fread(buffer, 1, fileSize, file);

      if(bytesRead == fileSize){
        // Successfully read the file
        // Use the buffer as needed
        free(buffer); // Release the allocated memory
      }else{
        // Handle error ifnot all bytes were read
        fprintf(stderr, "Error reading all bytes from file\n");
        return nullptr;
      }
    }else{
      // Handle error ifmemory allocation fails
      fprintf(stderr, "Error allocating memory\n");
      return nullptr;
    }

    fclose(file); // Close the file
  }else{
    // Handle error iffile cannot be opened
    fprintf(stderr, "Error opening file forreading: %s\n", "truc.bin");
    return nullptr;
  }

  //---------------------------
  return buffer;
}

//Export / import
void write_vec_path(const std::string& path, const std::vector<std::string>& vec_path){
  //---------------------------

  if(utl::file::is_exist(path) == false) return;

  std::ofstream outputFile(path);

  if(outputFile.is_open()){
    for(const std::string& path : vec_path){
      outputFile << path << '\n';
    }
    outputFile.close();
  }else{
    std::cerr << "Unable to open file forwriting: " << path << std::endl;
  }

  //---------------------------
}
void write_vector(const std::string& path, const std::vector<glm::vec3>& vec){
  //---------------------------

  if(utl::file::is_exist(path) == false) return;

  std::ofstream file(path);
  if(!file.is_open()){
    std::cerr<<"[error] Failed to open file at "<<path<<std::endl;
    return;
  }

  for(const auto& v : vec){
    file << v.x << ' ' << v.y << ' ' << v.z << '\n';
  }

  //---------------------------
  file.close();
}
void write_vector(const std::string& path, const std::vector<float>& vec){
  //---------------------------

  if(utl::file::is_exist(path) == false) return;

  std::ofstream file(path);
  if(!file.is_open()){
    std::cerr<<"[error] Failed to open file at "<<path<<std::endl;
    return;
  }

  for(const float& v : vec){
    file << v << '\n';
  }

  //---------------------------
  file.close();
}
std::vector<std::string> read_vec_path(const std::string& path){
  std::vector<std::string> vec_path;
  //---------------------------

  if(utl::file::is_exist(path) == false) return vec_path;

  std::ifstream inputFile(path);

  if(inputFile.is_open()){
    std::string line;
    while(std::getline(inputFile, line)){
      vec_path.push_back(line);
    }
    inputFile.close();
  }else{
    std::cerr << "Unable to open file: " << path << std::endl;
  }

  //---------------------------
  return vec_path;
}
std::vector<glm::vec3> read_vector(const std::string& path){
  std::vector<glm::vec3> vec;
  //---------------------------

  if(utl::file::is_exist(path) == false) return vec;

  std::ifstream file(path);
  if(!file.is_open()){
    std::cerr<<"[error] Failed to open file at "<<path<<std::endl;
    return vec;
  }

  std::string line;
  while(std::getline(file, line)){
    std::istringstream iss(line);
    glm::vec3 v;
    if(!(iss >> v.x >> v.y >> v.z)){
      std::cerr << "[error] Failed to read line from file." << std::endl;
      return vec;
    }
    vec.push_back(v);
  }

  file.close();

  //---------------------------
  return vec;
}

}
