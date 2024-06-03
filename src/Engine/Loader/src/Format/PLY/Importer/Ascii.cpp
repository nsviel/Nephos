#include "Ascii.h"

#include <Data/Namespace.h>


namespace format::ply::importer{

//Constructor / Destructor
Ascii::Ascii(){
  //---------------------------


  //---------------------------
}
Ascii::~Ascii(){}

//Main function
void Ascii::parse_ascii(dat::base::Object* object, format::ply::Header* header){
  this->header = header;
  //---------------------------

  //Open file
  std::ifstream file(header->path);
  this->pass_header(file);

  //Read data
  this->parse_vertice(file);
  this->parse_face(file);

  //Store result
  object->data.xyz = xyz;
  object->data.Nxyz = Nxyz;
  object->data.Is = Is;
  object->data.size = xyz.size();

  file.close();

  //---------------------------
}

//Parser
void Ascii::parse_vertice(std::ifstream& file){
  xyz.clear();
  Nxyz.clear();
  Is.clear();
  //---------------------------

  //Retrieve vertex data
  std::string line;
  for(int i=0; i<header->nb_vertex; i++){
    //Data
    std::getline(file, line);
    std::istringstream iss(line);
    std::vector<float> data;
    for(int i=0; i<header->vec_property.size(); i++){
      float d;
      iss >> d;
      data.push_back(d);
    }

    //Location
    int id_x = get_property_id(format::ply::X);
    if(id_x != -1){
      xyz.push_back(glm::vec3(data[id_x], data[id_x+1], data[id_x+2]));
    }

    //Normal
    int id_nx = get_property_id(format::ply::NX);
    if(id_nx != -1){
      Nxyz.push_back(glm::vec3(data[id_nx], data[id_nx+1], data[id_nx+2]));
    }

    //Intensity
    int id_i = get_property_id(format::ply::I);
    if(id_i != -1){
      Is.push_back(data[id_i]);
    }
  }

  //---------------------------
}
void Ascii::parse_face(std::ifstream& file){
  if(header->nb_face == 0) return;
  //---------------------------

  //Init
  std::vector<glm::vec3> vertex = xyz; xyz.clear();
  std::vector<glm::vec3> normal = Nxyz; Nxyz.clear();
  std::vector<float> intensity = Is; Is.clear();

  //Retrieve face data
  std::string line;
  while(std::getline(file, line)){
    //Data
    std::istringstream iss(line);
    float nb_vertice;
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
      xyz.push_back(vertex[idx[i]]);

      //Normal
      if(get_property_id(format::ply::NX) != -1){
        Nxyz.push_back(normal[idx[i]]);
      }

      //Intensity
      if(get_property_id(format::ply::I) != -1){
        Is.push_back(intensity[idx[i]]);
      }
    }

    //Deduce drawing type
    if(nb_vertice == 3){
      header->topology = utl::topology::TRIANGLE;
    }
    else if(nb_vertice == 4){
      header->topology = utl::topology::QUAD;
    }
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
int Ascii::get_property_id(format::ply::Field field){
  //---------------------------

  for(int i=0; i<header->vec_property.size(); i++){
    format::ply::Property* property = &header->vec_property[i];

    if(property->field == field){
      return i;
    }
  }

  //---------------------------
  return -1;
}

}
