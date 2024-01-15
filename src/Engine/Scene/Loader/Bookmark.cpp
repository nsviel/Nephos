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

  this->add_item("../media/point_cloud/bunny.ply", false);
  this->add_item("../media/point_cloud/dragon.ply", false);

  //Read existing bookmarks
  file::check_or_create_file(path_file);
  vector<string> vec_path = file::read_paths_from_file(path_file);
  for(int i=0; i<vec_path.size(); i++){
    this->add_item(vec_path[i], true);
  }

  //---------------------------
}
void Bookmark::add_item(string path, bool supressible){
  //---------------------------

  Item item;
  item.path = path;
  item.icon = directory::is_directory(path) ? ICON_FA_FOLDER : ICON_FA_FILE;
  item.color_icon = directory::is_directory(path) ? ImVec4(0.5f, 0.63f, 0.75f, 0.9f) : ImVec4(1.0f, 1.0f, 1.0f, 0.9f);
  item.is_supressible = supressible;

  this->vec_bookmark.push_back(item);

  //---------------------------
}


}
