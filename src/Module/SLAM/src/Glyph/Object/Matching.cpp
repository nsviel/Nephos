#include "Matching.h"


namespace slam::glyph{

//Constructor / destructor
Matching::Matching(){
  //---------------------------

  this->name = "matching";
  this->color = glm::vec4(0.11f, 0.35f, 0.69f, 1.0f);

  //---------------------------
  this->create_glyph();
}
Matching::~Matching(){}

void Matching::create_glyph(){
  this->matching = new Glyph();
  //---------------------------

  matching->name = "matching";
  matching->draw_line_width = 100;
  matching->draw_type = utl::topology::LINE;
  matching->unicolor = color;
  matching->is_visible = true;
  matching->is_permanent = true;

  //---------------------------
}
void Matching::update_matching(std::vector<glm::vec3>& xyz){
  std::vector<glm::vec4>& rgb = matching->rgb;
  matching->xyz = xyz;
  //---------------------------

  rgb.clear();
  for(int i=0; i<xyz.size(); i++){
    rgb.push_back(matching->unicolor);
  }

  //---------------------------
}
void Matching::reset(){
  //---------------------------

  matching->is_visible = false;

  //---------------------------
}

}
