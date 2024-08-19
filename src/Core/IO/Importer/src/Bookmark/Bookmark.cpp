#include "Bookmark.h"

#include <IO/Importer/Namespace.h>
#include <Utility/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace io::imp{

//Constructor / Destructor
Bookmark::Bookmark(io::imp::Node* node_importer){
  //---------------------------

  this->path_bookmark_file = "../media/config/gui/bookmark.txt";

  //---------------------------
}
Bookmark::~Bookmark(){}

//Main function
void Bookmark::init(){
  //---------------------------

  this->add_relative_path("../media/point_cloud/bunny.ply");
  this->add_relative_path("../media/point_cloud/dragon.ply");
  this->load_file_bookmark();

  //---------------------------
}

//Item management
void Bookmark::load_file_bookmark(){
  utl::file::check_or_create(path_bookmark_file);
  //---------------------------

  //Read existing bookmarks
  std::vector<std::string> vec_path = utl::file::read_vec_path(path_bookmark_file);

  //Insert bookmarks
  for(int i=0; i<vec_path.size(); i++){
    this->add_abs_path(vec_path[i]);
  }

  //---------------------------
}
void Bookmark::save_file_bookmark(){
  //---------------------------

  //Make vector of temporary bookmarks
  std::vector<std::string> vec_path;
  for(int i=0; i<list_item.size(); i++){
    io::imp::bookmark::Item& item = *next(list_item.begin(), i);

    if(item.is_supressible){
      vec_path.push_back(item.path.build());
    }
  }

  //Write them on file
  utl::file::write_vec_path(path_bookmark_file, vec_path);

  //---------------------------
}
void Bookmark::remove_path(std::string path){
  //---------------------------

  for(auto it = list_item.begin(); it != list_item.end(); ++it){
    io::imp::bookmark::Item& item = *it;

    if(item.path.build() == path){
      list_item.erase(it);
      return;
    }
  }

  //---------------------------
}

//Subfunction
void Bookmark::add_abs_path(std::string path){
  if(!utl::file::is_exist_silent(path)) return;
  //---------------------------

  io::imp::bookmark::Item item;
  item.path.insert(path);
  item.type = utl::directory::is_directory(path) ? io::imp::bookmark::FOLDER : io::imp::bookmark::FILE;
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

  io::imp::bookmark::Item item;
  item.path.insert(utl::path::get_absolute_path(path));
  item.icon = utl::directory::is_directory(path) ? ICON_FA_FOLDER : ICON_FA_FILE;
  item.color_icon = utl::directory::is_directory(path) ? glm::vec4(0.5f, 0.63f, 0.75f, 0.9f) : glm::vec4(1.0f, 1.0f, 1.0f, 0.9f);
  item.is_supressible = false;

  this->list_item.push_back(item);
  this->sort_list_item();

  //---------------------------
}
bool Bookmark::is_path_bookmarked(std::string path){
  //---------------------------

  for(int i=0; i<list_item.size(); i++){
    io::imp::bookmark::Item& item = *next(list_item.begin(), i);

    if(path == item.path.build()){
      return true;
    }
  }

  //---------------------------
  return false;
}
void Bookmark::sort_list_item(){
  //---------------------------

  this->list_item.sort([](const io::imp::bookmark::Item& a, const io::imp::bookmark::Item& b){
    switch(a.type){
      case io::imp::bookmark::FOLDER:{
        if(b.type == io::imp::bookmark::FOLDER){
          return a.path.name < b.path.name;
        }else{
          return true;
        }
        break;
      }
      case io::imp::bookmark::FILE:{
        if(b.type == io::imp::bookmark::FOLDER){
          return false;
        }else{
          return a.path.name < b.path.name;
        }
        break;
      }
      default:{
        return a.path.name < b.path.name;
      }
    }
  });

  //---------------------------
}


}
