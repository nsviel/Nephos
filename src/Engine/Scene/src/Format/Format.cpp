#include "Format.h"

#include <Engine/Scene/src/Format/Namespace.h>


namespace eng::scene{

//Constructor / Destructor
Format::Format(){
  //---------------------------

  this->ply_import = new format::ply::Importer();
  this->obj_import = new format::obj::Importer();
  this->csv_import = new format::csv::Importer();
  this->pts_import = new format::pts::Importer();
  this->ptx_import = new format::ptx::Importer();
  this->xyz_import = new format::xyz::Importer();

  this->supported_format.push_back("pts");
  this->supported_format.push_back("obj");
  this->supported_format.push_back("ply");
  this->supported_format.push_back("xyz");
  this->supported_format.push_back("pcap");
  this->supported_format.push_back("ptx");
  this->supported_format.push_back("csv");
  this->supported_format.push_back("las");

  //---------------------------
}
Format::~Format(){
  //---------------------------

  delete ply_import;
  delete obj_import;
  delete csv_import;
  delete pts_import;
  delete ptx_import;
  delete xyz_import;

  //---------------------------
}

//Main functions
MyFile* Format::get_data_from_file(std::string path){
  MyFile* data;
  //---------------------------

  std::string format = utl::fct::info::get_format_from_path(path);
  if     (format == "ply"){
    data = ply_import->Loader(path);
  }
  else if(format == "obj"){
    data = obj_import->Loader(path);
  }
  else if(format == "csv"){
    data = csv_import->Loader(path);
  }
  else if(format == "pcap"){
    //data = pcap_import->Loader(path);
  }
  else if(format == "pts"){
    data = pts_import->Loader(path);
  }
  else if(format == "ptx"){
    data = ptx_import->Loader(path);
  }
  else if(format == "xyz"){
    data = xyz_import->Loader(path);
  }

  //---------------------------
  return data;
}
bool Format::is_format_supported(string format){
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
