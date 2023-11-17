#include "File.h"

namespace fs = std::experimental::filesystem;


namespace file{
  //---------------------------

  bool is_file_exist(std::string path){
    //---------------------------

    std::ifstream infile(path.c_str());

    //---------------------------
    return infile.good();
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
  std::string get_path_abs_build(){
    //---------------------------

    fs::path currentPath = fs::current_path();
    std::string absPath = currentPath.string();
    absPath += "/";

    //---------------------------
    return absPath;
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

  //---------------------------
}
