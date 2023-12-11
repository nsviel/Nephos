#include "ENG_loader.h"
#include "../ENG_format/ENG_format.h"
#include "../Node.h"
#include "../ENG_scene/ENG_scene.h"

#include <Utility/UTL_file/Directory.h>
#include <Utility/UTL_file/File.h>


//Constructor / Destructor
ENG_loader::ENG_loader(eng::data::Node* eng_data){
  //---------------------------

  this->eng_scene = eng_data->get_eng_scene();
  this->eng_format = new ENG_format();

  this->ID = 0;
  this->path_current_dir = "";

  //---------------------------
}
ENG_loader::~ENG_loader(){
  //---------------------------

  delete eng_format;

  //---------------------------
}

//Main functions
eng::structure::Object* ENG_loader::load_object(std::string path){
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
  object->ID = ID++;

  //Retrieve data and insert into engine
  data::File* data = eng_format->get_data_from_file(path);
  this->transfert_data(object, data);
  eng_scene->insert_object_scene(object);

  //---------------------------
  return object;
}
std::vector<eng::structure::Object*> ENG_loader::load_objects(std::vector<std::string> path){
  std::vector<eng::structure::Object*> vec_obj;
  //---------------------------

  for(int i=0; i<path.size(); i++){
    eng::structure::Object* object = load_object(path[i]);
    vec_obj.push_back(object);
  }

  //---------------------------
  return vec_obj;
}
void ENG_loader::load_by_zenity(){
  //---------------------------

  //Select files to load
  std::vector<std::string> path_vec = zenity::zenity_file_vec("Load", path_current_dir);

  //Add object in engine
  this->load_objects(path_vec);

  //---------------------------
}

//Subfunctions
void ENG_loader::transfert_data(eng::structure::Object* object, data::File* data){
  //---------------------------

  object->name = data->name;
  object->nb_point = data->xyz.size();

  object->xyz = data->xyz;
  object->rgb = data->rgb;
  object->uv = data->uv;

  if(object->rgb.size() == 0){
    for(int i=0; i<data->xyz.size(); i++){
      object->rgb.push_back(vec4(1,1,1,1));
    }
  }

  //Delete raw data
  delete data;

  //---------------------------
}
