#include "Format.h"

#include <Scene/Namespace.h>
#include <Data/Namespace.h>
#include <Loader/Namespace.h>
#include <Vulkan/Namespace.h>
#include <Engine/Namespace.h>


namespace ldr{

//Constructor / Destructor
Format::Format(ldr::Node* node_scene){
  //---------------------------

  eng::Node* node_engine = node_scene->get_node_engine();
  vk::Node* node_vulkan = node_engine->get_node_vulkan();
  this->vk_interface = node_vulkan->get_vk_interface();

  this->insert_importer(new format::ply::Importer());
  this->insert_importer(new format::obj::Importer());
  this->insert_importer(new format::csv::Importer());
  this->insert_importer(new format::pts::Importer());
  this->insert_importer(new format::ptx::Importer());
  this->insert_importer(new format::xyz::Importer());

  this->insert_exporter(new format::ply::Exporter());

  //---------------------------
}
Format::~Format(){
  //---------------------------

  for(int i=0; i<vec_importer.size(); i++){
    delete vec_importer[i];
  }

  //---------------------------
}

//Main functions
utl::File* Format::import_from_path(utl::Path path){
  utl::File* file = nullptr;
  //---------------------------

  std::string format = utl::path::get_format_from_path(path.data);

  for(int i=0; i<vec_importer.size(); i++){
    utl::type::Importer* importer = vec_importer[i];

    if(importer->format == format){
      //Check for discrete gpu requirement
      if(importer->require_discrete_gpu && vk_interface->is_gpu_discrete() == false){
        cout<<"[error] no discrete GPU - could not load " + importer->format + " file"<<endl;
        continue;
      }

      file = importer->import(path);
    }
  }

  //---------------------------
  return file;
}
void Format::insert_from_path(utl::Path path, utl::type::Set* set){
  //---------------------------

  std::string format = utl::path::get_format_from_path(path.data);

  for(int i=0; i<vec_importer.size(); i++){
    utl::type::Importer* importer = vec_importer[i];

    if(importer->format == format){
      importer->insert(set);
    }
  }

  //---------------------------
}

//Subfunction
void Format::insert_importer(utl::type::Importer* importer){
  //---------------------------

  this->vec_importer.push_back(importer);

  //---------------------------
}
void Format::insert_exporter(utl::type::Exporter* exporter){
  //---------------------------

  this->vec_exporter.push_back(exporter);

  //---------------------------
}
bool Format::is_format_supported(string format){
  //---------------------------

  for(int i=0; i<vec_importer.size(); i++){
    utl::type::Importer* importer = vec_importer[i];

    if(format == importer->format){
      return true;
    }
  }

  //---------------------------
  return false;
}
void Format::display_supported_format(){
  //---------------------------

  cout<<"Supported file formats:"<<endl;
  for(int i=0; i<vec_importer.size(); i++){
    utl::type::Importer* importer = vec_importer[i];
    cout<<"o "<<importer->format<<endl;
  }

  //---------------------------
}

}
