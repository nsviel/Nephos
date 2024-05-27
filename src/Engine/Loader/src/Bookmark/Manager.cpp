#include "Manager.h"

#include <Loader/Namespace.h>
#include <Utility/Namespace.h>
#include <image/IconsFontAwesome6.h>


namespace ldr::bookmark{

//Constructor / Destructor
Manager::Manager(ldr::Node* node_loader){
  //---------------------------

  this->path_bookmark_file = "../media/config/gui/bookmark.txt";

  //---------------------------
}
Manager::~Manager(){}

//Main functions
void Manager::init(){
  //---------------------------

  this->add_relative_path("../media/point_cloud/bunny.ply");
  this->add_relative_path("../media/point_cloud/dragon.ply");

  //Read existing bookmarks
  utl::file::check_or_create(path_bookmark_file);
  vector<std::string> vec_path = utl::file::read_vec_path(path_bookmark_file);
  for(int i=0; i<vec_path.size(); i++){
    this->add_abs_path(vec_path[i]);
  }

  //---------------------------
}

//Item management
void Manager::add_abs_path(std::string path){
  if(!utl::file::is_exist_silent(path)) return;
  //---------------------------

  ldr::bookmark::Item item;
  item.path = path;
  item.name = utl::path::get_name_from_path(path);
  item.type = utl::directory::is_directory(path) ? ldr::bookmark::FOLDER : ldr::bookmark::FILE;
  item.icon = utl::directory::is_directory(path) ? ICON_FA_FOLDER : ICON_FA_FILE;
  item.color_icon = utl::directory::is_directory(path) ? glm::vec4(0.5f, 0.63f, 0.75f, 0.9f) : glm::vec4(1.0f, 1.0f, 1.0f, 0.9f);
  item.is_supressible = true;

  this->list_item.push_back(item);
  this->sort_list_item();

  //---------------------------
}
void Manager::add_relative_path(std::string path){
  if(!utl::file::is_exist_silent(path)) return;
  //---------------------------

  ldr::bookmark::Item item;
  item.path = utl::path::get_absolute_path(path);
  item.name = utl::path::get_name_from_path(path);
  item.icon = utl::directory::is_directory(path) ? ICON_FA_FOLDER : ICON_FA_FILE;
  item.color_icon = utl::directory::is_directory(path) ? glm::vec4(0.5f, 0.63f, 0.75f, 0.9f) : glm::vec4(1.0f, 1.0f, 1.0f, 0.9f);
  item.is_supressible = false;

  this->list_item.push_back(item);
  this->sort_list_item();

  //---------------------------
}
void Manager::remove_path(std::string path){
  //---------------------------

  auto it = std::find_if(list_item.begin(), list_item.end(), [&](const ldr::bookmark::Item& item){ return item.path == path; });
  if(it != list_item.end()){
    list_item.erase(it);
  }

  //---------------------------
}

//Subfunction
void Manager::save_on_file(){
  //---------------------------

  vector<std::string> vec_path;
  for(int i=0; i<list_item.size(); i++){
    ldr::bookmark::Item& item = *next(list_item.begin(), i);
    if(item.is_supressible){
      vec_path.push_back(item.path);
    }
  }

  utl::file::write_vec_path(path_bookmark_file, vec_path);

  //---------------------------
}
bool Manager::is_path_bookmarked(std::string path){
  //---------------------------

  for(int i=0; i<list_item.size(); i++){
    ldr::bookmark::Item& item = *next(list_item.begin(), i);

    if(path == item.path){
      return true;
    }
  }

  //---------------------------
  return false;
}
void Manager::sort_list_item(){
  //---------------------------

  this->list_item.sort([](const ldr::bookmark::Item& a, const ldr::bookmark::Item& b){
    switch(a.type){
      case ldr::bookmark::FOLDER:{
        if(b.type == ldr::bookmark::FOLDER){
          return a.name < b.name;
        }else{
          return true;
        }
        break;
      }
      case ldr::bookmark::FILE:{
        if(b.type == ldr::bookmark::FOLDER){
          return false;
        }else{
          return a.name < b.name;
        }
        break;
      }
      default:{
        return a.name < b.name;
      }
    }
  });

  //---------------------------
}


}
