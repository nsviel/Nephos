#include "Exporter.h"

#include <IO/Namespace.h>
#include <Dynamic/Namespace.h>


namespace io{

//Constructor / Destructor
Exporter::Exporter(io::Node* node_io){
  //---------------------------

  this->io_struct = node_io->get_io_struct();

  this->insert_exporter(new fmt::ply::Exporter());
  this->insert_exporter(new fmt::pts::Exporter());
  this->insert_exporter(new fmt::hdf5::Exporter());

  //---------------------------
}
Exporter::~Exporter(){}

//Main function
void Exporter::export_entity(dat::base::Entity* entity, std::string path){
  //---------------------------

  for(int i=0; i<vec_exporter.size(); i++){
    io::exporter::Base* exporter = vec_exporter[i];

    if(entity->data.path.format == exporter->format){
      this->export_with_encoding(exporter, entity, path);
    }
  }

  //---------------------------
}

//Subfunction
void Exporter::init_path(){
  //---------------------------

  io_struct->exporter.path.directory = utl::path::get_current_directory_path();
  io_struct->exporter.path.format = "ply";

  //---------------------------
}
void Exporter::export_with_encoding(io::exporter::Base* exporter, dat::base::Entity* entity, std::string path){
  utl::base::Data* data = &entity->data;
  utl::base::Pose* pose = &entity->pose;
  //---------------------------

  glm::mat4 mat = (io_struct->exporter.with_transformation) ? pose->model : glm::mat4(1);
  exporter->use_rgba = io_struct->exporter.with_colorization;

  switch(io_struct->exporter.encoding){
    case io::exporter::ASCII:{
      exporter->export_ascii(data, mat, path);
      break;
    }
    case io::exporter::BINARY:{
      exporter->export_binary(data, mat, path);
      break;
    }
  }

  //---------------------------
}
void Exporter::insert_exporter(io::exporter::Base* exporter){
  //---------------------------

  this->vec_exporter.push_back(exporter);

  //---------------------------
}
void Exporter::update_current_path(utl::base::Element* element){
  //---------------------------

  dat::base::Entity* entity = dynamic_cast<dat::base::Entity*>(element);
  if(!entity) return;

  static dat::base::Entity* old_entity = nullptr;

  //If entity different from previous one, change curent path
  if(!old_entity || entity->UID != old_entity->UID){
    io_struct->exporter.path.insert(entity->data.path);
    if(!is_format_supported(entity->data.path.format)) io_struct->exporter.path.format = "ply";
    old_entity = entity;
  }

  //---------------------------
}
bool Exporter::is_format_supported(std::string format){
  //---------------------------

  for(int i=0; i<vec_exporter.size(); i++){
    io::exporter::Base* exporter = vec_exporter[i];

    if(format == exporter->format){
      return true;
    }
  }

  //---------------------------
  return false;
}
bool Exporter::is_current_config(dat::base::Entity* entity){
  //---------------------------

  if(entity->data.path.build() == io_struct->exporter.path.build()){
    return true;
  }

  //---------------------------
  return false;
}
bool Exporter::is_recording(utl::base::Element* element){
  //---------------------------

  dyn::base::Sensor* sensor = dynamic_cast<dyn::base::Sensor*>(element);
  if(sensor && sensor->vec_recorder.size() != 0){
    return true;
  }

  //---------------------------
  return false;
}
std::vector<std::string> Exporter::get_supported_format(){
  std::vector<std::string> vec_format;
  //---------------------------

  for(int i=0; i<vec_exporter.size(); i++){
    io::exporter::Base* exporter = vec_exporter[i];
    vec_format.push_back(exporter->format);
  }

  //---------------------------
  return vec_format;
}
std::vector<io::exporter::Encoding> Exporter::get_supported_encoding(std::string format){
  std::vector<io::exporter::Encoding> vec_encoding;
  //---------------------------

  for(int i=0; i<vec_exporter.size(); i++){
    io::exporter::Base* exporter = vec_exporter[i];

    if(format == exporter->format){
      vec_encoding = exporter->vec_encoding;
      break;
    }
  }

  //---------------------------
  return vec_encoding;
}

}