#include "Bookmark.h"

#include <Utility/Function/File/File.h>


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

  this->vec_bookmark.push_back("../media/point_cloud/bunny.ply");
  this->vec_bookmark.push_back("../media/point_cloud/dragon.ply");

  //Read existing bookmarks
  file::check_or_create_file(path_file);
  vector<string> vec_path = file::read_paths_from_file(path_file);

  for(int i=0; i<vec_path.size(); i++){
    this->vec_bookmark.push_back(vec_path[i]);
  }

  //---------------------------
}


}
