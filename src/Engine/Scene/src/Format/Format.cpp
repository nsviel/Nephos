#include "Format.h"

#include <Scene/Namespace.h>


namespace eng::scene{

//Constructor / Destructor
Format::Format(){
  //---------------------------

  this->insert_importer(new format::ply::Importer());
  this->insert_importer(new format::obj::Importer());
  this->insert_importer(new format::csv::Importer());
  this->insert_importer(new format::pts::Importer());
  this->insert_importer(new format::ptx::Importer());
  this->insert_importer(new format::xyz::Importer());

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
utl::file::Data* Format::import_from_path(utl::file::Path path){
  utl::file::Data* data = nullptr;
  //---------------------------

  std::string format = utl::fct::info::get_format_from_path(path.data);
  for(int i=0; i<vec_importer.size(); i++){
    utl::type::Importer* importer = vec_importer[i];

    if(format == importer->format){
      data = importer->import(path);
    }
  }

  //---------------------------
  return data;
}

//Subfunction
void Format::insert_importer(utl::type::Importer* importer){
  //---------------------------

  this->vec_importer.push_back(importer);

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
