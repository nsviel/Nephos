#pragma once

#include <Utility/Function/File/Path.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>


namespace utl::base{

struct Path{
  //---------------------------

  Path(){}
  Path(std::string path){insert(path);}

  void insert(utl::base::Path path){
    this->directory = path.directory;
    this->name = path.name;
    this->format = path.format;
  }
  void insert(std::string path){
    this->directory = utl::path::get_dir_from_path(path);
    this->name = utl::path::get_name_from_path(path);
    this->format = utl::path::get_format_from_path(path);
  }
  void insert_filename(std::string filename){
    this->name = utl::path::get_name_from_filename(filename);
    this->format = utl::path::get_format_from_filename(filename);
  }
  std::string build(){return directory + name + format;}
  std::string filename(){return name + format;}

  std::string directory = "";
  std::string name = "";
  std::string format = "";

  //---------------------------
};

}
