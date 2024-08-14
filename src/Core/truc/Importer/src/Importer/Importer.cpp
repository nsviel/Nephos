#include "Importer.h"

#include <Element/Namespace.h>
#include <Importer/Namespace.h>
#include <IO/Namespace.h>
#include <Format/Namespace.h>
#include <Utility/Namespace.h>


namespace io::imp{

//Constructor / Destructor
Importer::Importer(io::imp::Node* node_importer){
  //---------------------------

  this->io_struct = node_importer->get_io_struct();
  this->io_operation = node_importer->get_io_operation();

  this->insert_importer(new fmt::ply::Importer());
  this->insert_importer(new fmt::obj::Importer());
  this->insert_importer(new fmt::csv::Importer());
  this->insert_importer(new fmt::pts::Importer());
  this->insert_importer(new fmt::ptx::Importer());
  this->insert_importer(new fmt::xyz::Importer());
  this->insert_importer(new fmt::hdf5::Importer());

  //---------------------------
}
Importer::~Importer(){}

//Main function
utl::base::Data* Importer::load_data(std::string path){
  if(!check_path(path)) return nullptr;
  //---------------------------

  //Init
  utl::base::Path utl_path(path);

  //Load data from path
  utl::base::Element* element = this->import_from_path(utl_path);
  if(element == nullptr) return nullptr;

  //Convert into data
  utl::base::Data* data = nullptr;
  if(dat::base::Entity* entity = dynamic_cast<dat::base::Entity*>(element)){
    data = &entity->data;
  }

  //---------------------------
  return data;
}
void Importer::load_set(utl::base::Path path){
  if(!check_path(path.build())) return;
  //---------------------------

  //Load
  utl::base::Element* element = this->import_from_path(path);
  if(element == nullptr) return;

  //Convert
  dat::base::Set* set = nullptr;
  if(element->type == utl::element::SET){
    set = dynamic_cast<dat::base::Set*>(element);
  }

  //Insert
  io_operation->insert_set(set);

  //---------------------------
}
void Importer::load_directory(utl::base::Path path){
  //---------------------------

  //Get vector of all directory files
  std::vector<std::string> vec_file = utl::path::list_all_file(path.directory);

  //Load object one by one
  for(int i=0; i<vec_file.size(); i++){
    utl::base::Path utl_path(vec_file[i]);
    utl_path.directory = path.directory;
    this->load_object(utl_path);
  }

  //---------------------------
}
void Importer::load_object(utl::base::Path path){
  if(!check_path(path.build())) return;
  //---------------------------

  //Load
  utl::base::Element* element = this->import_from_path(path);
  if(element == nullptr) return;

  //Convert
  dat::base::Object* object = nullptr;
  if(element->type == utl::element::ENTITY){
    object = dynamic_cast<dat::base::Object*>(element);
  }

  //Insert
  io_operation->insert_object(object);

  //---------------------------
}
void Importer::load_object(utl::base::Path path, utl::base::Path path_transfo){
  if(!check_path(path.build())) return;
  //---------------------------

  //Load
  utl::base::Element* element = this->import_from_path(path);
  if(element == nullptr) return;

  //Convert
  dat::base::Object* object = nullptr;
  if(element->type == utl::element::ENTITY){
    object = dynamic_cast<dat::base::Object*>(element);
    object->pose.path = path_transfo;
  }

  //Insert
  io_operation->insert_object(object);

  //---------------------------
}

//Subfunction
void Importer::init_path(){
  //---------------------------

  io_struct->path.directory = utl::path::get_current_directory_path();
  io_struct->path.format = ".ply";

  //---------------------------
}
void Importer::insert_importer(io::imp::Base* importer){
  //---------------------------

  this->vec_importer.push_back(importer);

  //---------------------------
}
bool Importer::check_path(std::string path){
  //---------------------------

  //Check file existence
  if(utl::file::is_exist(path) == false){
    std::cout<<"[error] File doesn't exists at "<<path<<std::endl;
    return false;
  }

  //Check file format
  std::string format = utl::path::get_format_from_path(path);
  if(!this->is_format_supported(format)){
    std::cout<<"[error] '"<<format<<"' file format not supported"<<std::endl;
    std::cout<<"Supported file formats:"<<std::endl;
    for(int i=0; i<vec_importer.size(); i++){
      io::imp::Base* importer = vec_importer[i];
      std::cout<<"o "<<importer->format<<std::endl;
    }
    return false;
  }

  //---------------------------
  return true;
}
bool Importer::is_format_supported(std::string format){
  if(format == "-") return false;
  //---------------------------

  for(int i=0; i<vec_importer.size(); i++){
    io::imp::Base* importer = vec_importer[i];

    if(format == importer->format){
      return true;
    }
  }

  //---------------------------
  return false;
}
std::vector<std::string> Importer::get_supported_format(){
  std::vector<std::string> vec_format;
  //---------------------------

  for(int i=0; i<vec_importer.size(); i++){
    io::imp::Base* importer = vec_importer[i];
    vec_format.push_back(importer->format);
  }

  //---------------------------
  return vec_format;
}
utl::base::Element* Importer::import_from_path(utl::base::Path path){
  utl::base::Element* element = nullptr;
  //---------------------------

  for(int i=0; i<vec_importer.size(); i++){
    io::imp::Base* importer = vec_importer[i];

    if(importer->format == path.format){
      element = importer->import(path);
    }
  }

  //---------------------------
  return element;
}

}
