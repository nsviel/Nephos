#include "Header.h"

#include <Utility/Namespace.h>


namespace fmt::ply::exporter{

//Constructor / Destructor
Header::Header(){
  //---------------------------

  //---------------------------
}
Header::~Header(){}

//Main exporter functions
void Header::write_header(io::exporter::Configuration& config, std::ofstream& file){
  //---------------------------

  this->write_info(config, file);
  this->write_property(config, file);
  this->write_end(file);

  //---------------------------
}

//Subfunction
void Header::write_info(io::exporter::Configuration& config, std::ofstream& file){
  //---------------------------

  file << "ply" << std::endl;
  file << "format " + config.format + " 1.0" << std::endl;
  file << "element vertex " << config.nb_vertex << std::endl;

  //---------------------------
}
void Header::write_property(io::exporter::Configuration& config, std::ofstream& file){
  //---------------------------

  for(int i=0; i<config.vec_property.size(); i++){
    io::exporter::Field& field = config.vec_property[i];

    switch(field){
      case io::exporter::XYZ:{
        file << "property float32 x" << std::endl;
        file << "property float32 y" << std::endl;
        file << "property float32 z" << std::endl;
        break;
      }
      case io::exporter::RGB:{
        file << "property uchar red" << std::endl;
        file << "property uchar green" << std::endl;
        file << "property uchar blue" << std::endl;
        break;
      }
      case io::exporter::NXYZ:{
        file << "property float32 nx" << std::endl;
        file << "property float32 ny" << std::endl;
        file << "property float32 nz" << std::endl;
        break;
      }
      case io::exporter::I:{
        file << "property float32 intensity" << std::endl;
        break;
      }
      case io::exporter::TS:{
        file << "property float32 timestamp" << std::endl;
        break;
      }
    }
  }

  //---------------------------
}
void Header::write_end(std::ofstream& file){
  //---------------------------

  file << "end_header" <<std::endl;

  //---------------------------
}

}