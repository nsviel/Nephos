#include "Exporter.h"


namespace format::ply{

//Constructor / Destructor
Exporter::Exporter(){}
Exporter::~Exporter(){}

//Main exporter functions
bool Exporter::export_cloud(utl::entity::Object* object, std::string path_dir, std::string ply_format){
  std::string filePath = path_dir + object->name + ".tmp";
  std::string filePath_end = path_dir + object->name + ".ply";
  //---------------------------


  //---------------------------
  return true;
}

}
