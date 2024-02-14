#include "Format.h"

#include <Engine/Scene/src/Format/Namespace.h>
#include "PLY/PLY_importer.h"
#include "PTS/PTS_importer.h"
#include "PTX/PTX_importer.h"
#include "XYZ/XYZ_importer.h"


namespace eng::scene{

//Constructor / Destructor
Format::Format(){
  //---------------------------

  this->ply_import = new PLY_importer();
  this->obj_import = new format::obj::Importer();
  this->csv_import = new format::csv::Importer();
  this->pcap_import = new format::pcap::Importer();
  this->pts_import = new PTS_importer();
  this->ptx_import = new PTX_importer();
  this->xyz_import = new XYZ_importer();

  //---------------------------
}
Format::~Format(){
  //---------------------------

  delete ply_import;
  delete obj_import;
  delete csv_import;
  delete pcap_import;
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
    data = pcap_import->Loader(path);
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

}
