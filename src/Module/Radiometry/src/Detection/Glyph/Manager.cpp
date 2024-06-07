#include "Manager.h"

#include <Radiometry/Namespace.h>


namespace rad::detection::glyph{

//Constructor / Destructor
Manager::Manager(rad::Node* node_radio){
  //---------------------------

  dat::Node* node_data = node_radio->get_node_data();

  this->dat_glyph = node_data->get_dat_glyph();
  this->node_engine = node_radio->get_node_engine();
  this->rad_struct = node_radio->get_rad_struct();

  //---------------------------
}
Manager::~Manager(){}

//Main function
void Manager::create_sphere_glyph(){
  //---------------------------

  //Detection spheres
  for(int i=0; i<20; i++){
    rad::detection::glyph::Sphere* sphere = new rad::detection::glyph::Sphere(node_engine);
    dat_glyph->create_glyph(sphere);
    vec4 color = math::random(i);
    sphere->construct(color);

    rad_struct->detection.vec_glyph_sphere.push_back(sphere);
  }

  //Calibration sphere
  rad::detection::glyph::Sphere* sphere = new rad::detection::glyph::Sphere(node_engine);
  rad_struct->detection.glyph_calibration = sphere;
  dat_glyph->create_glyph(sphere);
  sphere->construct(vec4(0, 1, 0, 1));

  //---------------------------
}
void Manager::draw_calibration_sphere(vec3 pose, float radius){
  rad::detection::glyph::Sphere* sphere = rad_struct->detection.glyph_calibration;
  //---------------------------

  sphere->reset_glyph();
  sphere->move_sphere(pose, radius * 2);

  //---------------------------
}

void Manager::draw_detected_sphere(dyn::base::Sensor* sensor){
  //---------------------------

  switch(rad_struct->detection.hough.drawing_mode){
    case rad::hough::ALL:{
      this->draw_all_sphere_glyph(sensor);
      break;
    }
    case rad::hough::BEST:{
      this->draw_best_sphere_glyph(sensor);
      break;
    }
  }

  //---------------------------
}
void Manager::draw_all_sphere_glyph(dyn::base::Sensor* sensor){
  vector<rad::detection::structure::Circle>& vec_circle = rad_struct->detection.vec_circle;
  //---------------------------

  this->reset_all_sphere();
  this->draw_sphere_from_circle(sensor, vec_circle);

  //---------------------------
}
void Manager::draw_best_sphere_glyph(dyn::base::Sensor* sensor){
  vector<rad::detection::structure::Circle>& vec_circle = rad_struct->detection.vec_circle;
  //---------------------------

  vector<rad::detection::structure::Circle> best_circle;
  if(rad_struct->detection.vec_circle.size() > 0){
    best_circle.push_back(rad_struct->detection.vec_circle[0]);
  }

  this->reset_all_sphere();
  this->draw_sphere_from_circle(sensor, best_circle);

  //---------------------------
}

//Subfunction
void Manager::reset_all_sphere(){
  vector<rad::detection::glyph::Sphere*>& vec_glyph_sphere = rad_struct->detection.vec_glyph_sphere;
  //---------------------------

  for(int i=0; i<vec_glyph_sphere.size(); i++){
    rad::detection::glyph::Sphere* sphere = vec_glyph_sphere[i];
    sphere->reset_glyph();
  }

  //---------------------------
}
void Manager::draw_sphere_from_circle(dyn::base::Sensor* sensor, vector<rad::detection::structure::Circle>& vec_circle){
/*  vector<rad::detection::glyph::Sphere*>& vec_glyph_sphere = rad_struct->detection.vec_glyph_sphere;
  //---------------------------

  for(int i=0; i<vec_circle.size(); i++){
    if(i >= vec_glyph_sphere.size()) return;
    rad::detection::structure::Circle& circle = vec_circle[i];

    //Add sphere radius to the detected circle center
    vec3 pose = sensor->convert_depth_2d_to_3d(circle.center);
    vec3 dir = glm::normalize(pose);
    pose = pose + dir * (rad_struct->detection.sphere_diameter / 2);

    //Position sphere
    vec_glyph_sphere[i]->move_sphere(pose, rad_struct->detection.sphere_diameter);
  }
*/
  //---------------------------
}

}
