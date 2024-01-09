#include "Loader.h"
#include "../Format/Format.h"

#include <Engine/Base/Namespace.h>
#include <Utility/Function/File/Directory.h>
#include <Utility/Function/File/Zenity.h>


namespace eng::scene{

//Constructor / Destructor
Loader::Loader(eng::scene::Node* eng_data){
  //---------------------------

  this->eng_scene = eng_data->get_scene();
  this->eng_format = new eng::scene::Format();

  this->path_current_dir = "";
  this->accepted_format.push_back("pts");
  this->accepted_format.push_back("obj");
  this->accepted_format.push_back("ply");
  this->accepted_format.push_back("xyz");
  this->accepted_format.push_back("pcap");
  this->accepted_format.push_back("ptx");
  this->accepted_format.push_back("csv");
  this->accepted_format.push_back("las");
  this->accepted_format.push_back("mkv");

  //---------------------------
}
Loader::~Loader(){
  //---------------------------

  delete eng_format;

  //---------------------------
}

//Main functions
eng::data::Object* Loader::load_object(std::string path){
  //---------------------------

  //Check file existence
  if(file::is_file_exist(path) == false){
    cout<<"[error] File doesn't exists at "<<path<<endl;
    return nullptr;
  }

  //Check file format
  /*if(check_format_viability(item.format)){
    cout<<"[error] File format not supported"<<endl;
    return nullptr;
  }*/

  //Create new object
  eng::data::Object* cloud = new eng::data::Object();
  cloud->path_file = path;
  cloud->draw_type_name = "point";
  cloud->has_texture = true;

  //Retrieve data and insert into engine
  eng::data::File* data = eng_format->get_data_from_file(path);
  this->transfert_data(cloud, data);
  eng_scene->insert_object_scene(cloud);

  //---------------------------
  return cloud;
}
std::vector<eng::data::Object*> Loader::load_objects(std::vector<std::string> path){
  std::vector<eng::data::Object*> vec_obj;
  //---------------------------

  for(int i=0; i<path.size(); i++){
    eng::data::Object* object = load_object(path[i]);
    vec_obj.push_back(object);
  }

  //---------------------------
  return vec_obj;
}

//Subfunctions
void Loader::transfert_data(eng::data::Object* object, eng::data::File* file_data){
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
bool Loader::check_format_viability(string format){
  //---------------------------

  for(int i=0; i<accepted_format.size(); i++){
    if(format == accepted_format[i]){
      return true;
    }
  }

  //---------------------------
  return false;
}


}
