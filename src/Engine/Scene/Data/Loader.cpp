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
eng::data::Object* Loader::load_object(std::string path){
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
    //Create new object
    object = new eng::data::Object();
    object->path_file = path;
    object->has_texture = true;

    //Retrieve data and insert into engine
    eng::data::File* data = eng_format->get_data_from_file(path);
    this->transfert_data(object, data);
  }

  //---------------------------
  return object;
}

//Subfunctions
void Loader::transfert_data(eng::data::Object* object, eng::data::File* file_data){
  //---------------------------

  object->name = file_data->name;
  object->nb_point = file_data->xyz.size();
  object->draw_type_name = file_data->draw_type_name;

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
