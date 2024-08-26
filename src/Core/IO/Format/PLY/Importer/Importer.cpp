#include "Importer.h"
#include "Ascii.h"
#include "Binary.h"

#include <Data/Namespace.h>


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
std::shared_ptr<utl::base::Element> Importer::import(utl::base::Path path){
  //---------------------------

  //Init
  std::shared_ptr<dat::base::Object> object = std::make_shared<dat::base::Object>();
  object->name = path.name;
  object->data.name = path.name;
  object->data.path = path;
  object->data.path.format = format;

  //Header
  io::imp::Configuration config;
  config.path = path.build();
  if(!parse_header(config)) return nullptr;

  //Parsing
  switch(config.encoding){
    case io::imp::ASCII:{
      ply_ascii->parse_ascii(&config, object);
      break;
    }
    case io::imp::BINARY_LITTLE_ENDIAN:
    case io::imp::BINARY_BIG_ENDIAN:{
      ply_binary->parse_binary(&config, object);
      break;
    }
  }

  object->data.topology.type = config.topology;

  //---------------------------
  return object;
}

//Header
bool Importer::parse_header(io::imp::Configuration& config){
  //---------------------------

  //Init
  std::ifstream file(config.path);

  // Separate the header
  std::string line, h1, h2, h3, h4;
  bool vertex_ended = false;
  do{
    getline(file, line);
    std::istringstream iss(line);
    iss >> h1 >> h2 >> h3 >> h4;

    //Retrieve format
    if(h1 == "format"){
      this->parse_header_format(config, h2);
    }
    //Retrieve number of point
    else if(h1 + h2 == "elementvertex"){
      if(!parse_header_size(config, h3)) return false;
    }
    //Retrieve property
    else if(h1 == "property" && vertex_ended == false){
      this->parse_header_property(config, h2, h3);
    }
    //Retrieve property
    else if(h1 + h2 == "elementface"){
      vertex_ended = true;
      config.nb_face = std::stoi(h3);
    }

  }while(line.find("end_header") != 0);

  //---------------------------
  return true;
}
void Importer::parse_header_format(io::imp::Configuration& config, std::string format){
  //---------------------------

  if(format == "ascii") config.encoding = io::imp::ASCII;
  else if(format == "binary_little_endian") config.encoding = io::imp::BINARY_LITTLE_ENDIAN;
  else if(format == "binary_big_endian") config.encoding = io::imp::BINARY_BIG_ENDIAN;
  else std::cout<<"[warning] Unknown format: "<<format<<std::endl;

  //---------------------------
}
bool Importer::parse_header_size(io::imp::Configuration& config, std::string value){
  //---------------------------

  int nb_vertex = std::stoi(value);
  if(nb_vertex < 0){
    std::cout<<"[error] ply file number vertex wrong"<<std::endl;
    return false;
  }
  config.nb_vertex = nb_vertex;

  //---------------------------
  return true;
}
void Importer::parse_header_property(io::imp::Configuration& config, std::string type, std::string field){
  io::imp::Property property;
  //---------------------------

  //Property type
  if(type == "float" || type == "float32") property.type = io::imp::FLOAT32;
  else if(type == "float64" || type == "double") property.type = io::imp::FLOAT64;
  else if(type == "uint" || type == "uint8") property.type = io::imp::UINT8;
  else if(type == "uint16") property.type = io::imp::UINT16;
  else if(type == "int" || type == "int32") property.type = io::imp::UINT32;
  else if(type == "uchar") property.type = io::imp::UCHAR;
  else if(type == "ushort") property.type = io::imp::USHORT;
  else{
    std::cout<<"[warning] Unknown property type: "<<type<<std::endl;
    return;
  }

  //Property field
  if(field == "x") property.field = io::imp::XYZ;
  else if(field == "timestamp") property.field = io::imp::TS;
  else if(field == "nx") property.field = io::imp::NXYZ;
  else if(field == "red") property.field = io::imp::RGB;
  else if(field == "scalar_field" || field == "scalar_Scalar_field" || field == "intensity") property.field = io::imp::I;
  else{
    property.field = io::imp::VOID;
  }

  //Store property
  config.vec_property.push_back(property);

  //---------------------------
}


}
