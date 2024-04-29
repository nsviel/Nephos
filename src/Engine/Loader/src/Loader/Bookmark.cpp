#include "Bookmark.h"

#include <Loader/Namespace.h>
#include <Scene/Namespace.h>
#include <Utility/Namespace.h>
#include <image/IconsFontAwesome6.h>


namespace sce{

//Constructor / Destructor
Bookmark::Bookmark(sce::Node* node_scene){
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
  vector<string> vec_path = utl::file::read_vec_path(path_bookmark_file);
  for(int i=0; i<vec_path.size(); i++){
    this->add_abs_path(vec_path[i]);
  }

  //---------------------------
}

//Item management
void Bookmark::add_abs_path(string path){
  if(!utl::file::is_exist_silent(path)) return;
  //---------------------------

  eng::loader::Item item;
  item.path = path;
  item.name = utl::path::get_name_from_path(path);
  item.type = utl::directory::is_directory(path) ? eng::loader::FOLDER : eng::loader::FILE;
  item.icon = utl::directory::is_directory(path) ? ICON_FA_FOLDER : ICON_FA_FILE;
  item.color_icon = utl::directory::is_directory(path) ? ImVec4(0.5f, 0.63f, 0.75f, 0.9f) : ImVec4(1.0f, 1.0f, 1.0f, 0.9f);
  item.is_supressible = true;

  this->list_bookmark.push_back(item);
  this->sort_list_bookmark();

  //---------------------------
}
void Bookmark::add_relative_path(string path){
  if(!utl::file::is_exist_silent(path)) return;
  //---------------------------

  eng::loader::Item item;
  item.path = utl::path::get_absolute_path(path);
  item.name = utl::path::get_name_from_path(path);
  item.icon = utl::directory::is_directory(path) ? ICON_FA_FOLDER : ICON_FA_FILE;
  item.color_icon = utl::directory::is_directory(path) ? ImVec4(0.5f, 0.63f, 0.75f, 0.9f) : ImVec4(1.0f, 1.0f, 1.0f, 0.9f);
  item.is_supressible = false;

  this->list_bookmark.push_back(item);
  this->sort_list_bookmark();

  //---------------------------
}
void Bookmark::remove_path(string path){
  //---------------------------

  auto it = std::find_if(list_bookmark.begin(), list_bookmark.end(), [&](const eng::loader::Item& item) { return item.path == path; });
  if(it != list_bookmark.end()){
    list_bookmark.erase(it);
  }

  //---------------------------
}

//Subfunction
void Bookmark::save_on_file(){
  //---------------------------

  vector<string> vec_path;
  for(int i=0; i<list_bookmark.size(); i++){
    eng::loader::Item& item = *next(list_bookmark.begin(), i);
    if(item.is_supressible){
      vec_path.push_back(item.path);
    }
  }

  utl::file::write_vec_path(path_bookmark_file, vec_path);

  //---------------------------
}
bool Bookmark::is_path_bookmarked(string path){
  //---------------------------

  for(int i=0; i<list_bookmark.size(); i++){
    eng::loader::Item& item = *next(list_bookmark.begin(), i);

    if(path == item.path){
      return true;
    }
  }

  //---------------------------
  return false;
}
void Bookmark::sort_list_bookmark(){
  //---------------------------

  this->list_bookmark.sort([](const eng::loader::Item& a, const eng::loader::Item& b){
    switch(a.type){
      case eng::loader::FOLDER:{
        if(b.type == eng::loader::FOLDER){
          return a.name < b.name;
        }else{
          return true;
        }
        break;
      }
      case eng::loader::FILE:{
        if(b.type == eng::loader::FOLDER){
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
