#include "Bookmark.h"

#include <Loader/Namespace.h>
#include <Utility/Namespace.h>
#include <image/IconsFontAwesome6.h>


namespace ldr{

//Constructor / Destructor
Bookmark::Bookmark(ldr::Node* node_loader){
  //---------------------------

  this->path_bookmark_file = "../media/config/gui/bookmark.txt";

  //---------------------------
}
Bookmark::~Bookmark(){}

//Main functions
void Bookmark::init(){
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
void Bookmark::add_abs_path(std::string path){
  if(!utl::file::is_exist_silent(path)) return;
  //---------------------------

  ldr::Item item;
  item.path = path;
  item.name = utl::path::get_name_from_path(path);
  item.type = utl::directory::is_directory(path) ? ldr::item::FOLDER : ldr::item::FILE;
  item.icon = utl::directory::is_directory(path) ? ICON_FA_FOLDER : ICON_FA_FILE;
  item.color_icon = utl::directory::is_directory(path) ? glm::vec4(0.5f, 0.63f, 0.75f, 0.9f) : glm::vec4(1.0f, 1.0f, 1.0f, 0.9f);
  item.is_supressible = true;

  this->list_item.push_back(item);
  this->sort_list_item();

  //---------------------------
}
void Bookmark::add_relative_path(std::string path){
  if(!utl::file::is_exist_silent(path)) return;
  //---------------------------

  ldr::Item item;
  item.path = utl::path::get_absolute_path(path);
  item.name = utl::path::get_name_from_path(path);
  item.icon = utl::directory::is_directory(path) ? ICON_FA_FOLDER : ICON_FA_FILE;
  item.color_icon = utl::directory::is_directory(path) ? glm::vec4(0.5f, 0.63f, 0.75f, 0.9f) : glm::vec4(1.0f, 1.0f, 1.0f, 0.9f);
  item.is_supressible = false;

  this->list_item.push_back(item);
  this->sort_list_item();

  //---------------------------
}
void Bookmark::remove_path(std::string path){
  //---------------------------

  auto it = std::find_if(list_item.begin(), list_item.end(), [&](const ldr::Item& item) { return item.path == path; });
  if(it != list_item.end()){
    list_item.erase(it);
  }

  //---------------------------
}

//Subfunction
void Bookmark::save_on_file(){
  //---------------------------

  vector<std::string> vec_path;
  for(int i=0; i<list_item.size(); i++){
    ldr::Item& item = *next(list_item.begin(), i);
    if(item.is_supressible){
      vec_path.push_back(item.path);
    }
  }

  utl::file::write_vec_path(path_bookmark_file, vec_path);

  //---------------------------
}
bool Bookmark::is_path_bookmarked(std::string path){
  //---------------------------

  for(int i=0; i<list_item.size(); i++){
    ldr::Item& item = *next(list_item.begin(), i);

    if(path == item.path){
      return true;
    }
  }

  //---------------------------
  return false;
}
void Bookmark::sort_list_item(){
  //---------------------------

  this->list_item.sort([](const ldr::Item& a, const ldr::Item& b){
    switch(a.type){
      case ldr::item::FOLDER:{
        if(b.type == ldr::item::FOLDER){
          return a.name < b.name;
        }else{
          return true;
        }
        break;
      }
      case ldr::item::FILE:{
        if(b.type == ldr::item::FOLDER){
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
