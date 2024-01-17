#include "File.h"

namespace fs = std::experimental::filesystem;


namespace file{

  void check_or_create_file(std::string path){
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
  bool is_file_exist(std::string path){
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
  bool is_file_exist_silent(std::string path){
    bool is_exists;
    //---------------------------

    std::ifstream infile(path.c_str());
    is_exists = infile.good();

    //---------------------------
    return is_exists;
  }
  bool is_device_connected(const std::string& devicePath) {
    int fileDescriptor = open(devicePath.c_str(), O_RDONLY);

    if (fileDescriptor == -1) {
        // Failed to open the device file
        return false;
    }

    close(fileDescriptor);  // Close the file descriptor

    return true;
}
  std::string get_current_path_abs(){
    //---------------------------

    fs::path currentPath = fs::current_path();
    std::string absPath = currentPath.string();
    absPath += "/";

    //---------------------------
    return absPath;
  }
  std::string get_current_parent_path_abs(){
    //---------------------------

    fs::path currentPath = fs::current_path();
    fs::path absolutePath = currentPath.parent_path();

    //---------------------------
    return absolutePath.string();
  }
  std::string get_absolute_path(const std::string& relativePath){
    //---------------------------

    fs::path currentPath = fs::current_path();
    fs::path absolutePath = currentPath / relativePath;

    // Resolve ".." and its parent folder
    if(is_file_exist(absolutePath)){
      absolutePath = fs::canonical(absolutePath);
    }else{
      return "";
    }

    //---------------------------
    return absolutePath.string();
}
  void clear_file(std::string path){
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
  uint8_t* load_file_binary(std::string path){
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
  std::vector<std::string> read_paths_from_file(const std::string& filePath){
    //---------------------------

    std::vector<std::string> paths;
    std::ifstream inputFile(filePath);

    if (inputFile.is_open()) {
      std::string line;
      while (std::getline(inputFile, line)) {
        paths.push_back(line);
      }
      inputFile.close();
    } else {
      std::cerr << "Unable to open file: " << filePath << std::endl;
    }

    //---------------------------
    return paths;
  }
  void write_paths_to_file(const std::string& filePath, const std::vector<std::string>& paths){
    //---------------------------

    std::ofstream outputFile(filePath);

    if (outputFile.is_open()) {
      for (const std::string& path : paths) {
        outputFile << path << '\n';
      }
      outputFile.close();
    } else {
      std::cerr << "Unable to open file for writing: " << filePath << std::endl;
    }

    //---------------------------
}

}
