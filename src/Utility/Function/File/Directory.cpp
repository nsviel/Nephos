#include "Directory.h"


namespace utl::directory{

//Operation
void create_new(std::string path){
  //---------------------------

  //If path dir end with a / (/path/dir_to_create/)
  if(path.find_last_of(path) == path.find_last_of("/")){
    path = path.substr(0, path.find_last_of("/"));
  }

  //Retrieve parent path
  std::string parent = path.substr(0, path.find_last_of("/"));

  //If the parent exist and dir_to_create not
  if(is_dir_exist(parent) == true && is_dir_exist(path) == false){
    std::filesystem::create_directory(path);
  }

  //---------------------------
}
void clean_file(const char *path){
  struct stat buffer;
  if(stat (path, &buffer) != 0) return;
  //---------------------------

  std::vector<std::string> path_vec = list_all_file(path);
  for(int i=0; i<path_vec.size(); i++){
    std::string path_full = path + path_vec[i];
    std::remove (path_full.c_str());
  }

  //---------------------------
}
void clean_folder(const std::string& path){
  if(!is_dir_exist(path)) return;
  //---------------------------

  for (const auto& entry : std::filesystem::directory_iterator(path)) {
    if (std::filesystem::is_regular_file(entry)) {
      std::filesystem::remove(entry.path());
    }
  }

  //---------------------------
}
int get_number_file(std::string path){
  DIR *dp;
  //---------------------------

  int i = 0;
  struct dirent *ep;
  dp = opendir (path.c_str());

  if (dp != NULL){
    while (ep = readdir (dp)){
      i++;
    }
    (void) closedir (dp);
  }
  else{
    return -1;
  }

  //Since ./ and ../ are counted
  i = i-2;

  //---------------------------
  return i;
}

//Check
bool is_dir_exist(std::string path){
  //---------------------------

  if(std::filesystem::exists(path)){
    return true;
  }else{
    return false;
  }

  //---------------------------
}
bool is_directory(std::string path){
    std::string type;
    //---------------------------

    struct stat s;
    if(stat(path.c_str(), &s) == 0 && s.st_mode & S_IFDIR){
      return true;
    }

    //---------------------------
    return false;
  }

}
