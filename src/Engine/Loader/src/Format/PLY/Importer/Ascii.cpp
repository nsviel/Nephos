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
  //---------------------------
/*
  //Open file
  std::ifstream file(path.data);

  //Read header
  this->parse_header(file);

  //Read data
  if(face_number == 0){
    ply_ascii->parse_data(file, entity);
  }else{
    ply_ascii->parse_data_withface(file, entity);
  }

  file.close();
*/
  //---------------------------
}

//Subfunction
void Ascii::parse_data(std::ifstream& file, utl::base::Data* data){/*
  std::vector<glm::vec3> vertex;
  std::vector<glm::vec3> normal;
  std::vector<float> intensity;
  //---------------------------

  //Retrieve vertex data
  std::string line;
  int cpt = 0;
  while (std::getline(file, line)){
    //Check vertex number
    if(cpt == point_number){
      break;
    }
    cpt++;

    //Stocke all line values
    std::istringstream iss(line);
    std::vector<float> data;
    for(int i=0; i<vec_property.size(); i++){
      float d;
      iss >> d;
      data.push_back(d);
    }

    //Location
    int id_x = get_property_id(format::ply::X);
    if(id_x != -1){
      vertex.push_back(glm::vec3(data[id_x], data[id_x+1], data[id_x+2]));
    }

    //Normal
    int id_nx = get_property_id(format::ply::NX);
    if(id_nx != -1){
      normal.push_back(glm::vec3(data[id_nx], data[id_nx+1], data[id_nx+2]));
    }

    //Intensity
    int id_i = get_property_id(format::ply::I);
    if(id_i != -1){
      intensity.push_back(data[id_i]);
    }
  }

  entity->xyz = vertex;
  entity->Nxyz = normal;
  entity->Is = intensity;

  //---------------------------
  entity->nb_element = entity->xyz.size();*/
}
void Ascii::parse_data_withface(std::ifstream& file, utl::base::Data* data){/*
  std::vector<glm::vec3> vertex;
  std::vector<glm::vec3> normal;
  std::vector<float> intensity;
  //---------------------------

  //Retrieve vertex data
  std::string line;
  for(int i=0; i<point_number; i++){
    //Get line
    std::getline(file, line);
    std::istringstream iss(line);

    //Stocke all line values
    std::vector<float> data;
    float d;
    for(int i=0; i<vec_property.size(); i++){
      iss >> d;
      data.push_back(d);
    }

    //Location
    int id_x = get_property_id(format::ply::X);
    if(id_x != -1){
      vertex.push_back(glm::vec3(data[id_x], data[id_x+1], data[id_x+2]));
    }

    //Normal
    int id_nx = get_property_id(format::ply::NX);
    if(id_nx != -1){
      normal.push_back(glm::vec3(data[id_nx], data[id_nx+1], data[id_nx+2]));
    }

    //Intensity
    int id_i = get_property_id(format::ply::I);
    if(id_i != -1){
      intensity.push_back(data[id_i]);
    }
  }

  //Retrieve face data
  while (std::getline(file, line)){
    std::istringstream iss(line);
    float nb_vertice;
    iss >> nb_vertice;

    //Stocke all line index
    std::vector<int> idx;
    float d;
    for(int i=0; i<nb_vertice; i++){
      iss >> d;
      idx.push_back(d);
    }

    //Retrieve face data
    for(int i=0; i<nb_vertice; i++){
      entity->xyz.push_back(vertex[idx[i]]);
      if(get_property_id(format::ply::NX) != -1){
        entity->Nxyz.push_back(normal[idx[i]]);
      }
      if(get_property_id(format::ply::I) != -1){
        entity->Is.push_back(intensity[idx[i]]);
      }
    }

    //Deduce drawing type
    if(nb_vertice == 3){
      entity->draw_type = utl::topology::TRIANGLE;
    }
    else if(nb_vertice == 4){
      entity->draw_type = utl::topology::QUAD;
    }
  }

  //---------------------------
  entity->nb_element = entity->xyz.size();*/
}
int Ascii::get_property_id(format::ply::Field field){
  //---------------------------

  for(int i=0; i<vec_property.size(); i++){
    format::ply::Property* property = &vec_property[i];

    if(property->field == field){
      return i;
    }
  }

  //---------------------------
  return -1;
}
}
