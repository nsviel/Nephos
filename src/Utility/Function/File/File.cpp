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
    std::cout << "[error] File doesn't exists [" << path << "]" << std::endl;
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

//Info
int number_point(std::string path){
  //---------------------------

  int cpt=0;
  std::string line;
  std::ifstream infile(path);
  while (std::getline(infile, line)){
    cpt++;
  }

  //---------------------------
  return cpt;
}
double size(std::string path){
  //---------------------------

  // Open the file and move the file pointer to the end
  std::ifstream in(path, std::ifstream::ate | std::ifstream::binary);
  if (!in.is_open()) {
    throw std::runtime_error("Failed to open file.");
  }

  // Get the file size in bytes
  std::streamoff fileSize = in.tellg();
  if (fileSize == -1) {
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

  while (fileSizeBytes >= 1024.0 && unitIndex < 3) {
    fileSizeBytes /= 1024.0;
    unitIndex++;
  }

  std::stringstream result;
  if (unitIndex == 0) {
    result << std::fixed << std::setprecision(0) << fileSizeBytes << " " << sizeUnits[unitIndex];
  } else {
    result << std::fixed << std::setprecision(1) << fileSizeBytes << " " << sizeUnits[unitIndex];
  }

  //---------------------------
  return result.str();
}

//Operation
void check_or_create(std::string path){
    bool is_exists;
    //---------------------------

    //Check file existence
    std::ifstream infile(path.c_str());
    is_exists = infile.good();

    //Create file
    if(is_exists == false){
      std::ofstream file(path);
    }

    //---------------------------
  }
void clear(std::string path){
  //---------------------------

  // Open the file in the output mode (out), which will clear the file
  std::ofstream outputFile(path.c_str(), std::ofstream::out);

  if (outputFile.is_open()) {
    outputFile.close();
  } else {
    std::cout << "Failed to open the file for clearing." << std::endl;
  }

  //---------------------------
}
uint8_t* load_binary(std::string path){
  //---------------------------

  FILE* file = fopen(path.c_str(), "rb"); // Open the file for reading in binary mode

  uint8_t* buffer;
  if (file != NULL) {
    fseek(file, 0, SEEK_END); // Move the file pointer to the end
    long fileSize = ftell(file); // Get the file size
    fseek(file, 0, SEEK_SET); // Move the file pointer back to the beginning

    // Allocate memory to store the file contents as uint8_t
    buffer = (uint8_t*)malloc(fileSize);

    if (buffer != NULL) {
      // Read the file contents directly into the uint8_t buffer
      size_t bytesRead = fread(buffer, 1, fileSize, file);

      if (bytesRead == fileSize) {
        // Successfully read the file
        // Use the buffer as needed
        free(buffer); // Release the allocated memory
      } else {
        // Handle error if not all bytes were read
        fprintf(stderr, "Error reading all bytes from file\n");
        return nullptr;
      }
    } else {
      // Handle error if memory allocation fails
      fprintf(stderr, "Error allocating memory\n");
      return nullptr;
    }

    fclose(file); // Close the file
  } else {
    // Handle error if file cannot be opened
    fprintf(stderr, "Error opening file for reading: %s\n", "truc.bin");
    return nullptr;
  }

  //---------------------------
  return buffer;
}
std::vector<std::string> read_vec_path(const std::string& path){
  //---------------------------

  std::vector<std::string> vec_path;
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
void write_vec_path(const std::string& path, const std::vector<std::string>& vec_path){
  //---------------------------

  std::ofstream outputFile(path);

  if(outputFile.is_open()){
    for(const std::string& path : vec_path){
      outputFile << path << '\n';
    }
    outputFile.close();
  }else{
    std::cerr << "Unable to open file for writing: " << path << std::endl;
  }

  //---------------------------
}

}
