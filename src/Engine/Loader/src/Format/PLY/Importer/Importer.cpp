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
  fmt::ply::importer::Structure ply_struct;
  ply_struct.path = path.build();
  if(!parse_header(ply_struct)) return nullptr;

  //Parsing
  switch(ply_struct.encoding){
    case ASCII:{
      ply_ascii->parse_ascii(&ply_struct, object);
      break;
    }
    case BINARY_LITTLE_ENDIAN:
    case BINARY_BIG_ENDIAN:{
      ply_binary->parse_binary(&ply_struct, object);
      break;
    }
  }

  object->data.topology.type = ply_struct.topology;

  //---------------------------
  return object;
}

//Header
bool Importer::parse_header(fmt::ply::importer::Structure& ply_struct){
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
void Importer::parse_header_format(fmt::ply::importer::Structure& ply_struct, std::string format){
  //---------------------------

  if(format == "ascii") ply_struct.encoding = fmt::ply::ASCII;
  else if(format == "binary_little_endian") ply_struct.encoding = fmt::ply::BINARY_LITTLE_ENDIAN;
  else if(format == "binary_big_endian") ply_struct.encoding = fmt::ply::BINARY_BIG_ENDIAN;
  else{
    std::cout<<"[warning] Unknown format: "<<format<<std::endl;
  }

  //---------------------------
}
bool Importer::parse_header_size(fmt::ply::importer::Structure& ply_struct, std::string value){
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
void Importer::parse_header_property(fmt::ply::importer::Structure& ply_struct, std::string type, std::string field){
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
  if(field == "x") property.field = fmt::ply::XYZ;
  else if(field == "timestamp") property.field = fmt::ply::TS;
  else if(field == "nx") property.field = fmt::ply::NXYZ;
  else if(field == "red") property.field = fmt::ply::RGB;
  else if(field == "scalar_field" || field == "scalar_Scalar_field" || field == "intensity") property.field = fmt::ply::I;
  else{
    property.field = fmt::ply::VOID;
  }

  //Store property
  ply_struct.vec_property.push_back(property);

  //---------------------------
}


}
