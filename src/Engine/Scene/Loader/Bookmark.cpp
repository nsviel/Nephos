#include "Bookmark.h"

#include <Utility/Function/File/File.h>
#include <image/IconsFontAwesome6.h>


namespace eng::scene{

//Constructor / Destructor
Bookmark::Bookmark(eng::scene::Node* node_scene){
  //---------------------------

  this->path_file = "../media/config/bookmark.txt";

  //---------------------------
}
Bookmark::~Bookmark(){}

//Main functions
void Bookmark::init(){
  //---------------------------

  this->add_relative_path("../media/point_cloud/bunny.ply");
  this->add_relative_path("../media/point_cloud/dragon.ply");

  //Read existing bookmarks
  file::check_or_create_file(path_file);
  vector<string> vec_path = file::read_paths_from_file(path_file);
  for(int i=0; i<vec_path.size(); i++){
    this->add_abs_path(vec_path[i]);
  }

  //---------------------------
}

//Item management
void Bookmark::add_abs_path(string path){
  //---------------------------

  Item item;
  item.path = path;
  item.icon = directory::is_directory(path) ? ICON_FA_FOLDER : ICON_FA_FILE;
  item.color_icon = directory::is_directory(path) ? ImVec4(0.5f, 0.63f, 0.75f, 0.9f) : ImVec4(1.0f, 1.0f, 1.0f, 0.9f);
  item.is_supressible = true;

  this->list_bookmark.push_back(item);

  //---------------------------
}
void Bookmark::add_relative_path(string path){
  //---------------------------

  Item item;
  item.path = file::get_absolute_path(path);
  item.icon = directory::is_directory(path) ? ICON_FA_FOLDER : ICON_FA_FILE;
  item.color_icon = directory::is_directory(path) ? ImVec4(0.5f, 0.63f, 0.75f, 0.9f) : ImVec4(1.0f, 1.0f, 1.0f, 0.9f);
  item.is_supressible = false;

  this->list_bookmark.push_back(item);

  //---------------------------
}
void Bookmark::remove_path(string path){
  //---------------------------

  auto it = std::find_if(list_bookmark.begin(), list_bookmark.end(), [&](const Item& item) { return item.path == path; });
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
    Item& item = *next(list_bookmark.begin(), i);
    if(item.is_supressible){
      vec_path.push_back(item.path);
    }
  }

  file::write_paths_to_file(path_file, vec_path);

  //---------------------------
}
bool Bookmark::is_path_bookmarked(string path){
  //---------------------------

  for(int i=0; i<list_bookmark.size(); i++){
    Item& item = *next(list_bookmark.begin(), i);

    if(path == item.path){
      return true;
    }
  }

  //---------------------------
  return false;
}


}
