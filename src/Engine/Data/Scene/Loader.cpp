#include "Loader.h"
#include "../Format/Format.h"

#include <Utility/Base/Namespace.h>
#include <Utility/Function/File/Directory.h>
#include <Utility/Function/File/Zenity.h>


namespace eng::data{

//Constructor / Destructor
Loader::Loader(eng::data::Node* eng_data){
  //---------------------------

  this->eng_scene = eng_data->get_eng_scene();
  this->eng_format = new eng::data::Format();

  this->path_current_dir = "";

  //---------------------------
}
Loader::~Loader(){
  //---------------------------

  delete eng_format;

  //---------------------------
}

//Main functions
eng::structure::Object* Loader::load_object(std::string path){
  //---------------------------

  if(file::is_file_exist(path) == false){
    cout<<"[error] File doesn't exists at "<<path<<endl;
    return nullptr;
  }

  //Create new object
  eng::structure::Object* object = new eng::structure::Object();
  object->path_file = path;
  object->path_text = "../media/viking_room.png";
  object->draw_type_name = "point";
  object->has_texture = true;

  //Retrieve data and insert into engine
  MyFile* data = eng_format->get_data_from_file(path);
  this->transfert_data(object, data);
  eng_scene->insert_object_scene(object);

  //---------------------------
  return object;
}
std::vector<eng::structure::Object*> Loader::load_objects(std::vector<std::string> path){
  std::vector<eng::structure::Object*> vec_obj;
  //---------------------------

  for(int i=0; i<path.size(); i++){
    eng::structure::Object* object = load_object(path[i]);
    vec_obj.push_back(object);
  }

  //---------------------------
  return vec_obj;
}
void Loader::load_by_zenity(){
  //---------------------------

  //Select files to load
  std::vector<std::string> path_vec = zenity::zenity_file_vec("Load", path_current_dir);

  //Add object in engine
  this->load_objects(path_vec);

  //---------------------------
}

//Subfunctions
void Loader::transfert_data(eng::structure::Object* object, MyFile* file_data){
  //---------------------------

  object->name = file_data->name;
  object->nb_point = file_data->xyz.size();

  object->xyz = file_data->xyz;
  object->rgb = file_data->rgb;
  object->uv = file_data->uv;

  if(object->rgb.size() == 0){
    for(int i=0; i<file_data->xyz.size(); i++){
      object->rgb.push_back(vec4(1,1,1,1));
    }
  }

  //Delete raw data
  delete file_data;

  //---------------------------
}

}
