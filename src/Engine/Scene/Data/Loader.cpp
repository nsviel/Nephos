#include "Loader.h"
#include "../Format/Format.h"

#include <Engine/Base/Namespace.h>
#include <Utility/Function/File/Directory.h>
#include <Utility/Function/File/Zenity.h>
#include <Utility/Function/File/Info.h>


namespace eng::scene{

//Constructor / Destructor
Loader::Loader(eng::scene::Node* node_scene){
  //---------------------------

  this->eng_format = new eng::scene::Format();

  this->path_current_dir = "";
  this->supported_format.push_back("pts");
  this->supported_format.push_back("obj");
  this->supported_format.push_back("ply");
  this->supported_format.push_back("xyz");
  this->supported_format.push_back("pcap");
  this->supported_format.push_back("ptx");
  this->supported_format.push_back("csv");
  this->supported_format.push_back("las");
  this->supported_format.push_back("mkv");

  //---------------------------
}
Loader::~Loader(){
  //---------------------------

  delete eng_format;

  //---------------------------
}

//Main functions
eng::data::Object* Loader::load_entity(std::string path){
  eng::data::Object* object = nullptr;
  //---------------------------

  //Check file existence
  if(file::is_file_exist(path) == false){
    cout<<"[error] File doesn't exists at "<<path<<endl;
    return nullptr;
  }

  //Check file format
  string format = info::get_format_from_path(path);
  if(!is_format_supported(format)){
    cout<<"[error] File format not supported -> "<<format<<endl;
    return nullptr;
  }

  if(format == "mkv"){

  }else{
    //Retrieve data and insert into engine
    object = load_object(path);
  }

  //---------------------------
  return object;
}

//Subfunctions
eng::data::Object* Loader::load_object(string path){
  //---------------------------

  eng::data::File* data = eng_format->get_data_from_file(path);

  eng::data::Object* object = new eng::data::Object();
  object->path_file = path;
  object->has_texture = true;
  object->name = data->name;
  object->nb_point = data->xyz.size();
  object->draw_type_name = data->draw_type_name;

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
  return object;
}
bool Loader::is_format_supported(string format){
  //---------------------------

  for(int i=0; i<supported_format.size(); i++){
    if(format == supported_format[i]){
      return true;
    }
  }

  //---------------------------
  return false;
}


}
