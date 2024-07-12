#pragma once

#include <Utility/Base/Data/Attribut.h>
#include <Utility/Base/Data/Element.h>
#include <Utility/Base/Data/Topology.h>
#include <Utility/Base/Data/Path.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <iostream>


namespace utl::base{

struct Data : public utl::base::Element{
  //---------------------------

  Data(){
    this->type = utl::element::DATA;
  }
  std::vector<float>& get_attribut_data(std::string name){
    for(int i=0; i<vec_attribut.size(); i++){
      utl::base::data::Attribut& attribut = vec_attribut[i];
      if(attribut.name == name) return attribut.data;
    }
    std::cout<<"[error] attribut name doesn't exists"<<std::endl;
    static std::vector<float> empty_vector;
    return empty_vector;
  }
  utl::base::data::Attribut* get_attribut(std::string name){
    for(int i=0; i<vec_attribut.size(); i++){
      utl::base::data::Attribut& attribut = vec_attribut[i];
      if(attribut.name == name) return &attribut;
    }
    std::cout<<"[error] attribut name doesn't exists"<<std::endl;
    return nullptr;
  }

  //State
  bool is_visible = true;
  int nb_data_max = -1;
  int width = -1;
  int height = -1;
  int size = -1;

  //Infos
  utl::base::Topology topology;
  utl::base::Path path;
  glm::vec4 unicolor = glm::vec4(1, 1, 1, 1);
  glm::vec3 centroid = glm::vec3(0.0f, 0.0f, 0.0f);

  //Data
  std::vector<glm::vec3> xyz; //XYZ location
  std::vector<glm::vec3> rgb; //RGB color
  std::vector<glm::vec4> rgba; //Displayed color data
  std::vector<glm::vec3> Nxyz; //Normal
  std::vector<glm::vec2> uv;  //UV coordinate
  std::vector<utl::base::data::Attribut> vec_attribut;

  std::vector<float> ts; //Timestamp
  std::vector<float> Is; //Intensity
  std::vector<float> Is_cor; //Corrected intensity
  std::vector<float> Is_cal; //Calibrated intensity
  std::vector<float> It; //Incidence angle
  std::vector<float> R; //Range
  std::vector<float> A; //Azimuth
  std::vector<int> idx; //Index

  //---------------------------
};

}
