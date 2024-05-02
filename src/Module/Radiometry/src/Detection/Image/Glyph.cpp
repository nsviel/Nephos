#include "Glyph.h"

#include <Kinect/Namespace.h>
#include <Radiometry/Namespace.h>


namespace rad::detection{

//Constructor / Destructor
Glyph::Glyph(rad::Node* node_radio){
  //---------------------------

  dat::Node* node_data = node_radio->get_node_data();

  this->radio_struct = node_radio->get_radio_struct();
  this->dat_glyph = node_data->get_glyph();
  this->k4n_transfo = new k4n::utils::Transformation();

  //---------------------------
}
Glyph::~Glyph(){}

//Main function
void Glyph::draw_all_sphere_glyph(dat::base::Sensor* sensor){
  vector<rad::structure::Circle>& vec_circle = radio_struct->detection.vec_circle;
  //---------------------------

  this->reset_all_sphere(sensor);
  this->draw_sphere_from_circle(sensor, vec_circle);

  //---------------------------
}
void Glyph::draw_best_sphere_glyph(dat::base::Sensor* sensor){
  vector<rad::structure::Circle>& vec_circle = radio_struct->detection.vec_circle;
  //---------------------------

  vector<rad::structure::Circle> best_circle;
  if(radio_struct->detection.vec_circle.size() > 0){
    best_circle.push_back(radio_struct->detection.vec_circle[0]);
  }

  this->reset_all_sphere(sensor);
  this->draw_sphere_from_circle(sensor, best_circle);

  //---------------------------
}

//Subfunction
void Glyph::reset_all_sphere(dat::base::Sensor* sensor){
  vector<dat::glyph::object::Sphere*>& vec_glyph_sphere = radio_struct->detection.vec_glyph_sphere;
  //---------------------------

  for(int i=0; i<vec_glyph_sphere.size(); i++){
    dat::glyph::object::Sphere* sphere = vec_glyph_sphere[i];
    sphere->reset_glyph();
  }

  //---------------------------
}
void Glyph::draw_sphere_from_circle(dat::base::Sensor* sensor, vector<rad::structure::Circle>& vec_circle){
/*  vector<dat::glyph::object::Sphere*>& vec_glyph_sphere = radio_struct->detection.vec_glyph_sphere;
  //---------------------------

  for(int i=0; i<vec_circle.size(); i++){
    if(i >= vec_glyph_sphere.size()) return;
    rad::structure::Circle& circle = vec_circle[i];

    //Add sphere radius to the detected circle center
    vec3 pose = k4n_transfo->convert_depth_2d_to_3d(sensor, circle.center);
    vec3 dir = glm::normalize(pose);
    pose = pose + dir * (radio_struct->detection.sphere_diameter / 2);

    //Position sphere
    vec_glyph_sphere[i]->move_sphere(pose, radio_struct->detection.sphere_diameter);
  }
*/
  //---------------------------
}


}
