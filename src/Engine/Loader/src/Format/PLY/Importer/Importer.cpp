#include "Importer.h"

#include <Data/Namespace.h>
#include <Loader/Namespace.h>


namespace format::ply{

//Constructor / Destructor
Importer::Importer(){
  //---------------------------

  this->ply_ascii = new format::ply::importer::Ascii();
  this->ply_binary = new format::ply::importer::Binary();

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
  this->parse_header(path.build());

  //Parsing
  switch(header.format){
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
void Importer::parse_header(std::string path){
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
      header.nb_vertex = std::stoi(h3);
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
}
void Importer::parse_header_format(std::string format){
  //---------------------------

  if(format == "ascii") header.format = format::ply::ASCII;
  else if(format == "binary_little_endian") header.format = format::ply::BINARY_LITTLE_ENDIAN;
  else if(format == "binary_big_endian") header.format = format::ply::BINARY_BIG_ENDIAN;
  else{
    cout<<"[warning] Unknown format: "<<format<<endl;
  }

  //---------------------------
}
void Importer::parse_header_property(std::string type, std::string field){
  format::ply::Property property;
  //---------------------------

  //Property type
  if(type == "float" || type == "float32") property.type = format::ply::FLOAT32;
  else if(type == "float64" || type == "double") property.type = format::ply::FLOAT64;
  else if(type == "uint" || type == "uint8") property.type = format::ply::UINT8;
  else if(type == "uint16") property.type = format::ply::UINT16;
  else if(type == "int" || type == "int32") property.type = format::ply::UINT32;
  else if(type == "uchar") property.type = format::ply::UCHAR;
  else if(type == "ushort") property.type = format::ply::USHORT;
  else{
    cout<<"[warning] Unknown property type: "<<type<<endl;
    return;
  }

  //Property field
  if(field == "x") property.field = format::ply::X;
  else if(field == "y") property.field = format::ply::Y;
  else if(field == "z") property.field = format::ply::Z;
  else if(field == "timestamp") property.field = format::ply::TS;
  else if(field == "nx") property.field = format::ply::NX;
  else if(field == "ny") property.field = format::ply::NY;
  else if(field == "nz") property.field = format::ply::NZ;
  else if(field == "red") property.field = format::ply::R;
  else if(field == "green") property.field = format::ply::G;
  else if(field == "blue") property.field = format::ply::B;
  else if(field == "scalar_field" || field == "scalar_Scalar_field" || field == "intensity") property.field = format::ply::I;
  else{
    //cout<<"[warning] Unknown property field: "<<field<<endl;
    property.field = format::ply::VOID;
  }

  //Store property
  header.vec_property.push_back(property);

  //---------------------------
}

}
