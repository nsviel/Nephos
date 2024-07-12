#include "Importer.h"

#include <Data/Namespace.h>
#include <Loader/Namespace.h>


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
  if(!parse_header(path.build())) return nullptr;

  //Parsing
  switch(header.encoding){
    case ASCII:{
      ply_ascii->parse_ascii(object, &header);
      break;
    }
    case BINARY_LITTLE_ENDIAN:
    case BINARY_BIG_ENDIAN:{
      ply_binary->parse_binary(object, &header);
      break;
    }
  }

  object->data.topology.type = header.topology;

  //---------------------------
  return object;
}

//Header
bool Importer::parse_header(std::string path){
  //---------------------------

  //Init
  this->header = {};
  this->header.path = path;
  std::ifstream file(path);

  // Separate the header
  std::string line, h1, h2, h3, h4;
  bool vertex_ended = false;
  do{
    getline(file, line);
    std::istringstream iss(line);
    iss >> h1 >> h2 >> h3 >> h4;

    //Retrieve format
    if(h1 == "format"){
      this->parse_header_format(h2);
    }
    //Retrieve number of point
    else if(h1 + h2 == "elementvertex"){
      if(!parse_header_size(h3)) return false;
    }
    //Retrieve property
    else if(h1 == "property" && vertex_ended == false){
      this->parse_header_property(h2, h3);
    }
    //Retrieve property
    else if(h1 + h2 == "elementface"){
      vertex_ended = true;
      header.nb_face = std::stoi(h3);
    }

  }while(line.find("end_header") != 0);

  //---------------------------
  return true;
}
void Importer::parse_header_format(std::string format){
  //---------------------------

  if(format == "ascii") header.encoding = fmt::ply::ASCII;
  else if(format == "binary_little_endian") header.encoding = fmt::ply::BINARY_LITTLE_ENDIAN;
  else if(format == "binary_big_endian") header.encoding = fmt::ply::BINARY_BIG_ENDIAN;
  else{
    std::cout<<"[warning] Unknown format: "<<format<<std::endl;
  }

  //---------------------------
}
void Importer::parse_header_property(std::string type, std::string field){
  fmt::ply::Property property;
  //---------------------------

  //Property type
  if(type == "float" || type == "float32") property.type = fmt::ply::FLOAT32;
  else if(type == "float64" || type == "double") property.type = fmt::ply::FLOAT64;
  else if(type == "uint" || type == "uint8") property.type = fmt::ply::UINT8;
  else if(type == "uint16") property.type = fmt::ply::UINT16;
  else if(type == "int" || type == "int32") property.type = fmt::ply::UINT32;
  else if(type == "uchar") property.type = fmt::ply::UCHAR;
  else if(type == "ushort") property.type = fmt::ply::USHORT;
  else{
    std::cout<<"[warning] Unknown property type: "<<type<<std::endl;
    return;
  }

  //Property field
  if(field == "x") property.field = fmt::ply::X;
  else if(field == "y") property.field = fmt::ply::Y;
  else if(field == "z") property.field = fmt::ply::Z;
  else if(field == "timestamp") property.field = fmt::ply::TS;
  else if(field == "nx") property.field = fmt::ply::NX;
  else if(field == "ny") property.field = fmt::ply::NY;
  else if(field == "nz") property.field = fmt::ply::NZ;
  else if(field == "red") property.field = fmt::ply::R;
  else if(field == "green") property.field = fmt::ply::G;
  else if(field == "blue") property.field = fmt::ply::B;
  else if(field == "scalar_field" || field == "scalar_Scalar_field" || field == "intensity") property.field = fmt::ply::I;
  else{
    //cout<<"[warning] Unknown property field: "<<field<<std::endl;
    property.field = fmt::ply::VOID;
  }

  //Store property
  header.vec_property.push_back(property);

  //---------------------------
}
bool Importer::parse_header_size(std::string value){
  //---------------------------

  int nb_vertex = std::stoi(value);
  if(nb_vertex < 0){
    std::cout<<"[error] ply file number vertex wrong"<<std::endl;
    return false;
  }
  header.nb_vertex = nb_vertex;

  //---------------------------
  return true;
}

}
