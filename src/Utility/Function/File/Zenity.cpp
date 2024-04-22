#include "Zenity.h"

#include <Utility/Function/File/Directory.h>
#include <Utility/Function/File/File.h>
#include <Utility/Function/File/Path.h>
#include <algorithm>
#include <iostream>


namespace zenity{

std::vector<std::string> selection_file_vec(std::string title, std::string& path){
  //---------------------------

  //Open zenity file manager
  std::string zenity = "zenity --file-selection --multiple --title=" + title + " --filename=" + path + " 2> /dev/null";

  FILE *file = popen(zenity.c_str(), "r");
  char filename[1000000];
  const char* path_char = fgets(filename, 1000000, file);
  std::vector<std::string> path_vec;

  //Check if not empty
  if ((path_char != NULL) && (path_char[0] != '\0')){
    std::string path_str(path_char);

    //Check for multiple
    if (path_str.find('|')){
      int N = count(path_str.begin(), path_str.end(), '|');
      for(int i=0; i<N; i++){
        std::string path = path_str.substr(0, path_str.find('|'));

        if (path.find('\n')){
          path.erase(std::remove(path.begin(), path.end(), '\n'), path.end());
        }

        path_vec.push_back(path);

        //Supress retrieved path from path list
        path_str = path_str.substr(path_str.find('|')+1);
      }
    }

    //Retrieve the last selected path
    if (path_str.find('\n')){
      path_str.erase(std::remove(path_str.begin(), path_str.end(), '\n'), path_str.end());
      path = path_str;
    }
    path_vec.push_back(path_str);
  }

  //---------------------------
  return path_vec;
}
std::vector<std::string> selection_file_vec(std::string title){
  //---------------------------

  //Open zenity file manager
  std::string zenity = "zenity --file-selection --multiple --title=" + title + " 2> /dev/null";
  FILE *file = popen(zenity.c_str(), "r");
  char filename[32768];
  const char* path_char = fgets(filename, 32768, file);
  std::vector<std::string> path_vec;

  //Check if not empty
  if ((path_char != NULL) && (path_char[0] != '\0')){
    std::string path_str(path_char);

    //Check for multiple
    if (path_str.find('|')){
      int N = count(path_str.begin(), path_str.end(), '|');
      for(int i=0; i<N; i++){
        std::string path = path_str.substr(0, path_str.find('|'));

        if(path.find('\n')){
          path.erase(std::remove(path.begin(), path.end(), '\n'), path.end());
        }

        path_vec.push_back(path);

        //Supress retrieved path from path list
        path_str = path_str.substr(path_str.find('|')+1);
      }
    }

    //Retrieve the last selected path
    if (path_str.find('\n')){
      path_str.erase(std::remove(path_str.begin(), path_str.end(), '\n'), path_str.end());
    }
    path_vec.push_back(path_str);
  }

  //---------------------------
  return path_vec;
}
std::string selection_directory(std::string title, std::string& path){
  std::string path_directory = "";
  //---------------------------

  //Retrieve dir path
  std::string zenity = "zenity --file-selection --directory --title=" + title + " --filename=" + path;
  FILE *file = popen(zenity.c_str(), "r");
  char filename[1024];
  char* path_char = fgets(filename, 1024, file);

  //Check if empty
  if((path_char != NULL) && (path_char[0] != '\0')){
    std::string path_str(path_char);

    //Remove unwanted break line
    if(path_str.find('\n')){
      path_str.erase(std::remove(path_str.begin(), path_str.end(), '\n'), path_str.end());
    }

    path_directory = path_str;
  }

  //---------------------------
  return path_directory;
}
std::string selection_file(){
  std::string path_saving = "";
  //---------------------------

  //Open Zenity window
  std::string zenity = "zenity --file-selection --save";
  FILE *file = popen(zenity.c_str(), "r");
  char filename[1024];
  char* path_char = fgets(filename, 1024, file);

  //Check if empty
  if ((path_char != NULL) && (path_char[0] != '\0')) {
    std::string path_str(path_char);

    //Supress unwanted line break
    if (path_str.find('\n')){
      path_str.erase(std::remove(path_str.begin(), path_str.end(), '\n'), path_str.end());
    }

    path_saving = path_str;
  }

  //---------------------------
  return path_saving;
}
std::string selection_saving(std::string& dir, std::string filename){
  //---------------------------

  std::string path = dir + filename;
  std::string path_saving = "";

  //Open Zenity window
  std::string zenity = "zenity --file-selection --save --title=Save --filename=" + path;
  FILE *file = popen(zenity.c_str(), "r");
  char path_buffer[1024];
  char* path_char = fgets(path_buffer, 1024, file);

  //Check if empty
  if ((path_char != NULL) && (path_char[0] != '\0')) {
    //Supress unwanted line break
    std::string path_str(path_char);
    if (path_str.find('\n')){
      path_str.erase(std::remove(path_str.begin(), path_str.end(), '\n'), path_str.end());
    }
    path_saving = path_str;
  }

  //Set current directory
  dir = path_saving.substr(0, path_saving.find_last_of("/") + 1);

  //---------------------------
  return path_saving;
}
void selection_file(std::string& path){
  //---------------------------

  //Open Zenity window
  std::string path_abs = utl::path::get_absolute_path(path);
  std::string zenity = "zenity --file-selection --save --filename=" + path_abs;
  FILE *file = popen(zenity.c_str(), "r");
  char filename[1024];
  char* path_char = fgets(filename, 1024, file);

  //Check if empty
  if ((path_char != NULL) && (path_char[0] != '\0')) {
    std::string path_str(path_char);

    //Supress unwanted line break
    if (path_str.find('\n')){
      path_str.erase(std::remove(path_str.begin(), path_str.end(), '\n'), path_str.end());
    }

    path = path_str;
  }

  //---------------------------
}
void selection_directory(std::string& path){
  //---------------------------

  //Get absolute executable location
  std::string zenity = "zenity --file-selection --directory --title='Select directory' --filename=" + path + "/";

  //Retrieve dir path
  FILE *file = popen(zenity.c_str(), "r");
  char filename[1024];
  char* path_char = fgets(filename, 1024, file);

  //Check if empty
  if ((path_char != NULL) && (path_char[0] != '\0')) {
    std::string path_str(path_char);

    //Supress unwanted line break
    if (path_str.find('\n')){
      path_str.erase(std::remove(path_str.begin(), path_str.end(), '\n'), path_str.end());
    }

    path = path_str;
  }

  //---------------------------
}

}
