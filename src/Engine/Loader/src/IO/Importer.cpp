#include "Importer.h"

#include <Data/Namespace.h>
#include <Loader/Namespace.h>
#include <Utility/Namespace.h>


namespace ldr::io{

//Constructor / Destructor
Importer::Importer(ldr::Node* node_loader){
  //---------------------------

  this->ldr_operation = new ldr::processing::Operation(node_loader);

  this->insert_importer(new format::ply::Importer());
  this->insert_importer(new format::obj::Importer());
  this->insert_importer(new format::csv::Importer());
  this->insert_importer(new format::pts::Importer());
  this->insert_importer(new format::ptx::Importer());
  this->insert_importer(new format::xyz::Importer());

  //---------------------------
}
Importer::~Importer(){}

//Main functions
utl::base::Data* Importer::load_data(std::string path){
  if(!check_path(path)) return nullptr;
  //---------------------------

  //Init
  utl::media::Path utl_path;
  utl_path.data = path;

  //Load data from path
  utl::base::Element* element = this->import_from_path(utl_path);
  if(element == nullptr) return nullptr;

  //Convert into data
  utl::base::Data* data = nullptr;
  if(element->type == utl::element::DATA){
    data = dynamic_cast<utl::base::Data*>(element);
  }else if(element->type == utl::element::ENTITY){
    dat::base::Entity* entity = dynamic_cast<dat::base::Entity*>(element);
    data = &entity->data;
  }

  //---------------------------
  return data;
}
dat::base::Set* Importer::load_set(utl::media::Path path){
  if(!check_path(path.data)) return nullptr;
  //---------------------------

  //Load
  utl::base::Element* element = this->import_from_path(path);
  if(element == nullptr) return nullptr;

  //Convert
  dat::base::Set* set = nullptr;
  if(element->type == utl::element::SET){
    set = dynamic_cast<dat::base::Set*>(element);
  }

  //Insert
  ldr_operation->insert_set(set);

  //---------------------------
  return set;
}
dat::base::Object* Importer::load_object(utl::media::Path path){
  if(!check_path(path.data)) return nullptr;
  //---------------------------

  //Load
  utl::base::Element* element = this->import_from_path(path);
  if(element == nullptr) return nullptr;

  //Convert
  dat::base::Object* object = nullptr;
  if(element->type == utl::element::ENTITY){
    object = dynamic_cast<dat::base::Object*>(element);
  }

  //Insert
  ldr_operation->insert_object(object);

  //---------------------------
  return object;
}

//Subfunction
void Importer::insert_importer(ldr::base::Importer* importer){
  //---------------------------

  this->vec_importer.push_back(importer);

  //---------------------------
}
bool Importer::check_path(std::string path){
  //---------------------------

  //Check file existence
  if(utl::file::is_exist(path) == false){
    cout<<"[error] File doesn't exists at "<<path<<endl;
    return false;
  }

  //Check file format
  std::string format = utl::path::get_format_from_path(path);
  if(!this->is_format_supported(format)){
    cout<<"[error] '"<<format<<"' file format not supported"<<endl;
    cout<<"Supported file formats:"<<endl;
    for(int i=0; i<vec_importer.size(); i++){
      ldr::base::Importer* importer = vec_importer[i];
      cout<<"o "<<importer->format<<endl;
    }
    return false;
  }

  //---------------------------
  return true;
}
bool Importer::is_format_supported(std::string format){
  //---------------------------

  for(int i=0; i<vec_importer.size(); i++){
    ldr::base::Importer* importer = vec_importer[i];

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
    ldr::base::Importer* importer = vec_importer[i];
    vec_format.push_back(importer->format);
  }

  //---------------------------
  return vec_format;
}
utl::base::Element* Importer::import_from_path(utl::media::Path path){
  utl::base::Element* element = nullptr;
  //---------------------------

  std::string format = utl::path::get_format_from_path(path.data);

  for(int i=0; i<vec_importer.size(); i++){
    ldr::base::Importer* importer = vec_importer[i];

    if(importer->format == format){
      //Check for discrete gpu requirement
      /*if(importer->require_discrete_gpu && vk_interface->is_gpu_discrete() == false){
        cout<<"[error] no discrete GPU - could not load " + importer->format + " file"<<endl;
        continue;
      }*/

      element = importer->import(path);
    }
  }

  //---------------------------
  return element;
}

}
