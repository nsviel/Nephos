#include "Exporter.h"

#include <Loader/Namespace.h>


namespace ldr::io{

//Constructor / Destructor
Exporter::Exporter(ldr::Node* node_loader){
  //---------------------------

  this->ldr_struct = node_loader->get_ldr_struct();

  this->insert_exporter(new format::ply::Exporter());
  this->insert_exporter(new format::pts::Exporter());

  //---------------------------
}
Exporter::~Exporter(){}

//Main functions
void Exporter::export_entity(dat::base::Entity* entity, std::string path){
  utl::base::Data* data = &entity->data;
  utl::base::Pose* pose = &entity->pose;;
  //---------------------------

  for(int i=0; i<vec_exporter.size(); i++){
    ldr::base::Exporter* exporter = vec_exporter[i];

    if(data->format == exporter->format){

      switch(ldr_struct->export_encoding){
        case ldr::io::ASCII:{
          exporter->export_ascii(data, pose, path);
          break;
        }
        case ldr::io::BINARY:{
          exporter->export_binary(data, pose, path);
          break;
        }
      }

    }
  }

  //---------------------------
}

//Exporter function
void Exporter::insert_exporter(ldr::base::Exporter* exporter){
  //---------------------------

  this->vec_exporter.push_back(exporter);

  //---------------------------
}
void Exporter::insert_recorder(ldr::base::Recorder* recorder){
  //---------------------------

  //this->vec_exporter.push_back(exporter);

  //---------------------------
}
bool Exporter::is_format_supported(std::string format){
  //---------------------------

  for(int i=0; i<vec_exporter.size(); i++){
    ldr::base::Exporter* exporter = vec_exporter[i];

    if(format == exporter->format){
      return true;
    }
  }

  //---------------------------
  return false;
}

//Subfunction
std::vector<std::string> Exporter::get_supported_format(){
  std::vector<std::string> vec_format;
  //---------------------------

  for(int i=0; i<vec_exporter.size(); i++){
    ldr::base::Exporter* exporter = vec_exporter[i];
    vec_format.push_back(exporter->format);
  }

  //---------------------------
  return vec_format;
}
std::vector<int> Exporter::get_supported_encoding(std::string format){
  std::vector<int> vec_encoding;
  //---------------------------

  for(int i=0; i<vec_exporter.size(); i++){
    ldr::base::Exporter* exporter = vec_exporter[i];

    if(format == exporter->format){
      vec_encoding = exporter->vec_encoding;
      break;
    }
  }

  //---------------------------
  return vec_encoding;
}

}
