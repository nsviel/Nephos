#include "Info.h"


namespace utl::fct::info{

//Retrieve string info from path
std::string get_name_from_path(std::string path){
  //Return file name
  //---------------------------

  if(path != ""){
    std::string name_format = path.substr(path.find_last_of("/\\") + 1);
    return name_format.substr(0, name_format.find_last_of("."));
  }else{
    return "";
  }

  //---------------------------
}
std::string get_filename_from_path(std::string path){
  // Return file name.format
  //---------------------------

  if(path != ""){
    std::string name_format = path.substr(path.find_last_of("/\\") + 1);
    return name_format;
  }else{
    return "";
  }

  //---------------------------
}
std::string get_path_from_filepath(std::string filepath){
  // Return path abs or relative from file path
  //---------------------------

  if(filepath != ""){
    std::string path = filepath.substr(0, filepath.find_last_of("/\\") + 1);
    return path;
  }else{
    return "";
  }

  //---------------------------
}
std::string get_name_and_parent_from_path(std::string path){
  //Return file parent/name
  //---------------------------

  if(path != ""){
    std::string path_parent = path.substr(0, path.find_last_of("/\\"));
    std::string parent = path_parent.substr(path_parent.find_last_of("/\\"));
    std::string name_format = path.substr(path.find_last_of("/\\"));
    std::string parent_name_format = parent + name_format;
    std::string parent_name = parent_name_format.substr(0, parent_name_format.find_last_of("."));
    return parent_name;
  }else{
    return "";
  }

  //---------------------------
}
std::string get_format_from_path(std::string path){
  //Return file format
  //---------------------------

  if(path != ""){
    std::string name_format = path.substr(path.find_last_of("/\\") + 1);
    return name_format.substr(name_format.find_last_of(".") + 1, std::string::npos);
  }else{
    return "";
  }

  //---------------------------
}
std::string get_format_from_filename(std::string path){
  //---------------------------

  std::string format = path.substr(path.find_last_of("."), std::string::npos);

  //---------------------------
  return format;
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

//Retrieve quantity info from path
int get_file_nbPoint(std::string path){
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
double get_file_size(std::string path){
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
std::string get_file_formatted_size(std::string path){
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

}
