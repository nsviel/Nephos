#include "Ascii.h"

#include <Data/Namespace.h>


namespace fmt::ply::importer{

//Constructor / Destructor
Ascii::Ascii(){
  //---------------------------


  //---------------------------
}
Ascii::~Ascii(){}

//Main function
void Ascii::parse_ascii(dat::base::Object* object, fmt::ply::Header* header){
  this->header = header;
  //---------------------------

  //Open file
  std::ifstream file(header->path);
  this->pass_header(file);

  //Read data
  this->parse_vertex(file);
  this->parse_face(file);

  //Store result
  object->data.xyz = buffer.xyz;
  object->data.Nxyz = buffer.Nxyz;
  object->data.Is = buffer.Is;
  object->data.size = buffer.xyz.size();

  //Close file
  file.close();

  //---------------------------
}

//Parser
void Ascii::parse_vertex(std::ifstream& file){
  this->buffer = {};
  //---------------------------

  //Retrieve vertex data
  std::string line;
  for(int i=0; i<header->nb_vertex; i++){
    //Data
    std::getline(file, line);
    std::istringstream iss(line);
    std::vector<float> row;
    for(int i=0; i<header->vec_property.size(); i++){
      float d;
      iss >> d;
      row.push_back(d);
    }

    //Location
    int id_x = get_property_id(fmt::ply::XYZ);
    if(id_x != -1){
      buffer.xyz.push_back(glm::vec3(row[id_x], row[id_x+1], row[id_x+2]));
    }

    //Normal
    int id_nx = get_property_id(fmt::ply::NXYZ);
    if(id_nx != -1){
      buffer.Nxyz.push_back(glm::vec3(row[id_nx], row[id_nx+1], row[id_nx+2]));
    }

    //Intensity
    int id_i = get_property_id(fmt::ply::I);
    if(id_i != -1){
      buffer.Is.push_back(row[id_i]);
    }
  }

  //---------------------------
}
void Ascii::parse_face(std::ifstream& file){
  if(header->nb_face == 0) return;
  //---------------------------

  //Init
  fmt::ply::Buffer buffer_tmp = buffer;
  this->buffer = {};

  //Retrieve face data
  std::string line;
  float nb_vertice;
  while(std::getline(file, line)){
    //Data
    std::istringstream iss(line);
    iss >> nb_vertice;
    std::vector<int> idx;
    float d;
    for(int i=0; i<nb_vertice; i++){
      iss >> d;
      idx.push_back(d);
    }

    //Retrieve face data
    for(int i=0; i<nb_vertice; i++){
      //Location
      buffer.xyz.push_back(buffer_tmp.xyz[idx[i]]);

      //Normal
      if(get_property_id(fmt::ply::NXYZ) != -1){
        buffer.Nxyz.push_back(buffer_tmp.Nxyz[idx[i]]);
      }

      //Intensity
      if(get_property_id(fmt::ply::I) != -1){
        buffer.Is.push_back(buffer_tmp.Is[idx[i]]);
      }
    }
  }

  //Deduce drawing type
  if(nb_vertice == 3){
    header->topology = utl::topology::TRIANGLE;
  }
  else if(nb_vertice == 4){
    header->topology = utl::topology::QUAD;
  }

  //---------------------------
}

//Subfunction
void Ascii::pass_header(std::ifstream& file){
  std::string line;
  //---------------------------

  while(std::getline(file, line)){
    if(line == "end_header"){
      break;
    }
  }

  //---------------------------
}
int Ascii::get_property_id(fmt::ply::Field field){
  //---------------------------

  for(int i=0; i<header->vec_property.size(); i++){
    fmt::ply::Property* property = &header->vec_property[i];

    if(property->field == field){
      return i;
    }
  }

  //---------------------------
  return -1;
}

}
