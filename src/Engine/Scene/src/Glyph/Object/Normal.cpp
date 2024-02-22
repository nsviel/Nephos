#include "Normal.h"

#include <Utility/Function/Math/Math.h>


namespace glyph::object{

//Constructor / destructor
Normal::Normal(eng::Node* engine) : Glyph(engine){
  //---------------------------

  this->width = 2;
  this->size = 1;
  this->is_visible = true;
  this->color = vec4(0.11f, 0.35f, 0.69f, 1.0f);
  this->need_update = true;

  //---------------------------
}
Normal::~Normal(){}

//Main function
void Normal::create(){
  if(vec_data.size() != 0) return;
  //---------------------------

  //Create glyph
  utl::type::Data* data = new utl::type::Data();
  data->line.width = width;
  data->is_visible = is_visible;
  data->nb_data_max = 1000000;
  data->draw_type = utl::topology::LINE;
  data->unicolor = vec4(0, 0.7, 0.7, 1);
  this->vec_data.push_back(data);

  //---------------------------
}
void Normal::update_glyph(utl::type::Entity* entity){
  //---------------------------

  utl::type::Pose* entity_pose = entity->get_pose();
  pose->model = entity_pose->model;

  this->construct(entity);

  //---------------------------
}

//Subfunction
void Normal::construct(utl::type::Entity* entity){
  //---------------------------

  //Data glyph
  utl::type::Data* data_glyph = vec_data[0];
  vector<vec3>& xyz_g = data_glyph->line.xyz;
  vector<vec4>& rgb_g = data_glyph->line.rgb;

  //Data entity
  utl::type::Data* data_entity = entity->get_data();
  vector<vec3>& xyz_e = data_entity->point.xyz;
  vector<vec3>& Nxyz_e = data_entity->point.Nxyz;

  //Check vector length
  if(xyz_e.size() == 0 || Nxyz_e.size() == 0 || Nxyz_e.size() != xyz_e.size()) return;

  //Clear old glyph values
  xyz_g.clear();
  rgb_g.clear();

  //Construct glyph
  float lgt = 0.05 * size;
  for(int i=0; i<xyz_e.size(); i++){
    vec3& xyz = xyz_e[i];
    vec3& nxyz = Nxyz_e[i];

    if(nxyz == vec3(0, 0, 0)) sayHello();//continue;

    vec3 xyz_n = vec3(xyz.x + nxyz.x * lgt, xyz.y + nxyz.y * lgt, xyz.z + nxyz.z * lgt);

    xyz_g.push_back(xyz);
    xyz_g.push_back(xyz_n);

    rgb_g.push_back(data_glyph->unicolor);
    rgb_g.push_back(data_glyph->unicolor);
  }

  //---------------------------
}
glm::vec4 Normal::generate_random_color(){
  //---------------------------

  float Red = float(rand()%101)/100;
  float Green = float(rand()%101)/100;
  float Blue = float(rand()%101)/100;
  glm::vec4 color = glm::vec4(Red, Green, Blue, 1.0f);

  //---------------------------
  return color;
}

}
