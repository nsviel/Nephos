#include "Importer.h"

#include <Data/Namespace.h>
#include <IO/Namespace.h>


namespace fmt::ply{

//Constructor / Destructor
Importer::Importer(){
  //---------------------------

  this->ply_ascii = new fmt::ply::importer::Ascii();
  this->ply_binary = new fmt::ply::importer::Binary();

  this->format = ".ply";

  //---------------------------
}
Importer::~Importer(){}

//Main loader functions
utl::base::Element* Importer::import(utl::base::Path path){
  //---------------------------

  //Init
  dat::base::Object* object = new dat::base::Object();
  object->name = path.name;
  object->data.name = path.name;
  object->data.path = path;
  object->data.path.format = format;

  //Header
  io::importer::Configuration ply_struct;
  ply_struct.path = path.build();
  if(!parse_header(ply_struct)) return nullptr;

  //Parsing
  switch(ply_struct.encoding){
    case io::importer::ASCII:{
      ply_ascii->parse_ascii(&ply_struct, object);
      break;
    }
    case io::importer::BINARY_LITTLE_ENDIAN:
    case io::importer::BINARY_BIG_ENDIAN:{
      ply_binary->parse_binary(&ply_struct, object);
      break;
    }
  }

  object->data.topology.type = ply_struct.topology;

  //---------------------------
  return object;
}

//Header
bool Importer::parse_header(io::importer::Configuration& ply_struct){
  //---------------------------

  //Init
  std::ifstream file(ply_struct.path);

  // Separate the header
  std::string line, h1, h2, h3, h4;
  bool vertex_ended = false;
  do{
    getline(file, line);
    std::istringstream iss(line);
    iss >> h1 >> h2 >> h3 >> h4;

    //Retrieve format
    if(h1 == "format"){
      this->parse_header_format(ply_struct, h2);
    }
    //Retrieve number of point
    else if(h1 + h2 == "elementvertex"){
      if(!parse_header_size(ply_struct, h3)) return false;
    }
    //Retrieve property
    else if(h1 == "property" && vertex_ended == false){
      this->parse_header_property(ply_struct, h2, h3);
    }
    //Retrieve property
    else if(h1 + h2 == "elementface"){
      vertex_ended = true;
      ply_struct.nb_face = std::stoi(h3);
    }

  }while(line.find("end_header") != 0);

  //---------------------------
  return true;
}
void Importer::parse_header_format(io::importer::Configuration& ply_struct, std::string format){
  //---------------------------

  if(format == "ascii") ply_struct.encoding = io::importer::ASCII;
  else if(format == "binary_little_endian") ply_struct.encoding = io::importer::BINARY_LITTLE_ENDIAN;
  else if(format == "binary_big_endian") ply_struct.encoding = io::importer::BINARY_BIG_ENDIAN;
  else{
    std::cout<<"[warning] Unknown format: "<<format<<std::endl;
  }

  //---------------------------
}
bool Importer::parse_header_size(io::importer::Configuration& ply_struct, std::string value){
  //---------------------------

  int nb_vertex = std::stoi(value);
  if(nb_vertex < 0){
    std::cout<<"[error] ply file number vertex wrong"<<std::endl;
    return false;
  }
  ply_struct.nb_vertex = nb_vertex;

  //---------------------------
  return true;
}
void Importer::parse_header_property(io::importer::Configuration& ply_struct, std::string type, std::string field){
  io::importer::Property property;
  //---------------------------

  //Property type
  if(type == "float" || type == "float32") property.type = io::importer::FLOAT32;
  else if(type == "float64" || type == "double") property.type = io::importer::FLOAT64;
  else if(type == "uint" || type == "uint8") property.type = io::importer::UINT8;
  else if(type == "uint16") property.type = io::importer::UINT16;
  else if(type == "int" || type == "int32") property.type = io::importer::UINT32;
  else if(type == "uchar") property.type = io::importer::UCHAR;
  else if(type == "ushort") property.type = io::importer::USHORT;
  else{
    std::cout<<"[warning] Unknown property type: "<<type<<std::endl;
    return;
  }

  //Property field
  if(field == "x") property.field = io::importer::XYZ;
  else if(field == "timestamp") property.field = io::importer::TS;
  else if(field == "nx") property.field = io::importer::NXYZ;
  else if(field == "red") property.field = io::importer::RGB;
  else if(field == "scalar_field" || field == "scalar_Scalar_field" || field == "intensity") property.field = io::importer::I;
  else{
    property.field = io::importer::VOID;
  }

  //Store property
  ply_struct.vec_property.push_back(property);

  //---------------------------
}


}
