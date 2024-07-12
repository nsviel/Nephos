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
void Header::write_header(std::ofstream& file, std::string format, utl::base::Data* data){
  //---------------------------

  this->vec_property.clear();


  this->write_info(file, format, data);
  this->write_property_xyz(file);
  this->write_property_attribut(file, data);
  file << "end_header" <<std::endl;

  //---------------------------
}

//Subfunction
void Header::write_info(std::ofstream& file, std::string& format, utl::base::Data* data){
  //---------------------------

  file << "ply" << std::endl;
  file << "format " + format + " 1.0" << std::endl;
  int nb_vertex = (data->size > 0) ? data->size : data->xyz.size();
  file << "element vertex " << nb_vertex << std::endl;

  //---------------------------
}
void Header::write_property_xyz(std::ofstream& file){
  //---------------------------

  file << "property float32 x" << std::endl;
  file << "property float32 y" << std::endl;
  file << "property float32 z" << std::endl;
  vec_property.push_back(fmt::ply::XYZ);
  this->property_number = 3;

  //---------------------------
}
void Header::write_property_attribut(std::ofstream& file, utl::base::Data* data){
  //---------------------------

  if(data->rgb.size() != 0){
    file << "property uchar red" << std::endl;
    file << "property uchar green" << std::endl;
    file << "property uchar blue" << std::endl;

    vec_property.push_back(fmt::ply::RGB);
    this->property_number += 3;
  }
  if(data->Nxyz.size() != 0){
    file << "property float32 nx" << std::endl;
    file << "property float32 ny" << std::endl;
    file << "property float32 nz" << std::endl;

    vec_property.push_back(fmt::ply::NXYZ);
    this->property_number += 3;
  }
  if(data->Is.size() != 0){
    file << "property float32 intensity" << std::endl;

    vec_property.push_back(fmt::ply::I);
    property_number++;
  }
  if(data->ts.size() != 0){
    file << "property float32 timestamp" << std::endl;

    vec_property.push_back(fmt::ply::TS);
    property_number++;
  }

  //---------------------------
}

}
