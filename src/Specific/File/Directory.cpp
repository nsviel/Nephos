#include "Directory.h"


//Directory operations
void dir_create_new(std::string path){
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
void dir_clean_file(const char *path){
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
int dir_number_file(std::string path){
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
   perror ("Couldn't open the directory");
  }

  //Since ./ and ../ are counted
  i = i-2;

  //---------------------------
  return i;
}

//Check existence
bool is_file_exist(std::string path){
  //---------------------------

  std::ifstream infile(path.c_str());

  //---------------------------
  return infile.good();
}
bool is_dir_exist(std::string path){
  //---------------------------

  if(std::filesystem::exists(path)){
    return true;
  }else{
    return false;
  }

  //---------------------------
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

//List files & paths
std::vector<std::string> list_all_file(std::string path){
  //---------------------------

  struct dirent* files;
  DIR* directory = opendir(path.c_str());
  std::vector<std::string> path_vec;

  if(is_dir_exist(path) == false || is_dir_or_file(path) == "file"){
    std::cout<<"[error] Directory does not exists: "<<path<<std::endl;
    return path_vec;
  }

  //Filtre and store files present in the folder
  while ((files = readdir(directory)) != NULL){
    std::string name = files->d_name;

    if(name != "." && name != ".."){
      path_vec.push_back(name);
    }
  }

  //Close and return the file names list
  closedir(directory);

  //Sort vector in alphabetic order
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
  if(is_dir_exist(path_dir) == false || is_dir_or_file(path_dir) == "file"){
    return path_vec;
  }

  //Supress unwanted line break
  if(path_dir.find('\n')){
    path_dir.erase(std::remove(path_dir.begin(), path_dir.end(), '\n'), path_dir.end());
  }

  //Filtre and store files present in the folder
  while ((files = readdir(directory)) != NULL){
    std::string path_file = files->d_name;
    std::string path_full = path_dir + "/" + path_file;

    if(path_file != "." && path_file != ".."){
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
  std::vector<std::string> list;

  //Check if directory exists
  if(is_dir_exist(path) == false || is_dir_or_file(path) == "file"){
    return list;
  }

  //Filtre and store files present in the folder
  while ((files = readdir(directory)) != NULL){
    std::string name = files->d_name;
    if((strchr(files->d_name, '.')) == NULL){
      list.push_back(name + "/");
    }
  }

  //Close and return the file names list
  closedir(directory);

  //---------------------------
  return list;
}
