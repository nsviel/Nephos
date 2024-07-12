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
void Header::write_header(fmt::ply::exporter::Structure& exporter, std::ofstream& file){
  //---------------------------

  this->write_info(exporter, file);
  this->write_property(exporter, file);
  this->write_end(file);

  //---------------------------
}

//Subfunction
void Header::write_info(fmt::ply::exporter::Structure& exporter, std::ofstream& file){
  //---------------------------

  file << "ply" << std::endl;
  file << "format " + exporter.encoding + " 1.0" << std::endl;
  file << "element vertex " << exporter.nb_vertex << std::endl;

  //---------------------------
}
void Header::write_property(fmt::ply::exporter::Structure& exporter, std::ofstream& file){
  //---------------------------

  for(int i=0; i<exporter.vec_property.size(); i++){
    fmt::ply::Field& field = exporter.vec_property[i];

    switch(field){
      case fmt::ply::XYZ:{
        file << "property float32 x" << std::endl;
        file << "property float32 y" << std::endl;
        file << "property float32 z" << std::endl;
        break;
      }
      case fmt::ply::RGB:{
        file << "property uchar red" << std::endl;
        file << "property uchar green" << std::endl;
        file << "property uchar blue" << std::endl;
        break;
      }
      case fmt::ply::NXYZ:{
        file << "property float32 nx" << std::endl;
        file << "property float32 ny" << std::endl;
        file << "property float32 nz" << std::endl;
        break;
      }
      case fmt::ply::I:{
        file << "property float32 intensity" << std::endl;
        break;
      }
      case fmt::ply::TS:{
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
