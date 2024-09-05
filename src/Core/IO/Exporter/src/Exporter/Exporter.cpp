#include "Exporter.h"

#include <IO/Exporter/Namespace.h>
#include <IO/Format/Namespace.h>
#include <Data/Namespace.h>


namespace io::exp{

//Constructor / Destructor
Exporter::Exporter(io::exp::Node* node_exporter){
  //---------------------------

  this->io_struct = node_exporter->get_io_struct();

  //---------------------------
}
Exporter::~Exporter(){}

//Main function
void Exporter::export_entity(std::shared_ptr<dat::base::Entity> entity, std::string path){
  //---------------------------

  for(int i=0; i<vec_exporter.size(); i++){
    io::base::Exporter* exporter = vec_exporter[i];

    if(entity->data->path.format == exporter->reference.format){
      this->export_with_config(exporter, entity, path);
    }
  }

  //---------------------------
}

//Subfunction
void Exporter::export_with_config(io::base::Exporter* exporter, std::shared_ptr<dat::base::Entity> entity, std::string path){
  utl::base::Data& data = *entity->data;
  utl::base::Pose& pose = *entity->pose;
  //---------------------------

  //Make export configuration
  io::exp::Configuration config;
  config.mat_model = (io_struct->with_transformation) ? pose.model : glm::mat4(1);
  config.mat_rotation = glm::mat3(config.mat_model);
  config.with_colorization = io_struct->with_colorization;
  config.encoding = io_struct->encoding;
  config.path = path;

  //Export data
  exporter->export_data(config, data);

  //---------------------------
}
void Exporter::insert_exporter(io::base::Exporter* exporter){
  //---------------------------

  this->vec_exporter.push_back(exporter);

  //---------------------------
}
void Exporter::update_current_path(std::shared_ptr<utl::base::Element> element){
  //---------------------------
/*
  std::shared_ptr<dat::base::Entity> entity = std::dynamic_pointer_cast<dat::base::Entity>(element);
  if(!entity) return;

  static dat::base::Entity* old_entity = nullptr;

  //If entity different from previous one, change curent path
  if(!old_entity || entity->UID != old_entity->UID){
    io_struct->path.insert(*entity->data->path);
    if(!is_format_supported(*entity->data->path.format)) io_struct->path.format = "ply";
    old_entity = entity;
  }
*/
  //---------------------------
}
bool Exporter::is_format_supported(std::string format){
  //---------------------------

  for(int i=0; i<vec_exporter.size(); i++){
    io::base::Exporter* exporter = vec_exporter[i];

    if(format == exporter->reference.format){
      return true;
    }
  }

  //---------------------------
  return false;
}
bool Exporter::is_current_config(std::shared_ptr<dat::base::Entity> entity){
  //---------------------------

  if(entity->data->path.build() == io_struct->path.build()){
    return true;
  }

  //---------------------------
  return false;
}
bool Exporter::is_recording(std::shared_ptr<utl::base::Element> element){
  //---------------------------

  std::shared_ptr<dat::base::Sensor> sensor = std::dynamic_pointer_cast<dat::base::Sensor>(element);
  if(sensor && sensor->info.vec_recorder.size() != 0){
    return true;
  }

  //---------------------------
  return false;
}
std::vector<std::string> Exporter::get_supported_format(){
  std::vector<std::string> vec_format;
  //---------------------------

  for(int i=0; i<vec_exporter.size(); i++){
    io::base::Exporter* exporter = vec_exporter[i];
    vec_format.push_back(exporter->reference.format);
  }

  //---------------------------
  return vec_format;
}
std::vector<io::exp::Encoding> Exporter::get_supported_encoding(std::string format){
  std::vector<io::exp::Encoding> vec_encoding;
  //---------------------------

  for(int i=0; i<vec_exporter.size(); i++){
    io::base::Exporter* exporter = vec_exporter[i];

    if(format == exporter->reference.format){
      vec_encoding = exporter->vec_encoding;
      break;
    }
  }

  //---------------------------
  return vec_encoding;
}

}
