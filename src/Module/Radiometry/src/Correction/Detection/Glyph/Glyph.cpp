#include "Glyph.h"

#include <Radiometry/Namespace.h>
#include <Dynamic/Namespace.h>
#include <Data/Namespace.h>


namespace rad::correction{

//Constructor / Destructor
Glyph::Glyph(rad::correction::Node* node_correction){
  //---------------------------

  rad::Node* node_radio = node_correction->get_node_radio();
  dat::Node* node_data = node_radio->get_node_data();

  this->dat_glyph = node_data->get_dat_glyph();
  this->dat_entity = node_data->get_dat_entity();
  this->node_engine = node_radio->get_node_engine();
  this->rad_struct = node_correction->get_rad_struct();

  //---------------------------
}
Glyph::~Glyph(){}

//Main function
void Glyph::create_sphere_glyph(){
  //---------------------------

  //Detection spheres
  for(int i=0; i<20; i++){
    rad::correction::glyph::Sphere* sphere = new rad::correction::glyph::Sphere(node_engine);
    vec4 color = math::random(i);
    sphere->set_color(color);
    dat_glyph->create_glyph(sphere);

    rad_struct->hough.vec_glyph.push_back(sphere);
  }

  //Calibration sphere
  rad::correction::glyph::Sphere* sphere = new rad::correction::glyph::Sphere(node_engine);
  rad_struct->ransac.glyph = sphere;
  sphere->set_color(vec4(0, 1, 0, 1));
  dat_glyph->create_glyph(sphere);

  //---------------------------
}
void Glyph::update_sphere_glyph(){
  //---------------------------

  //Detection spheres
  std::vector<rad::correction::glyph::Sphere*>& vec_glyph = rad_struct->hough.vec_glyph;
  for(int i=0; i<vec_glyph.size(); i++){
    rad::correction::glyph::Sphere* sphere = vec_glyph[i];
    dat_entity->update_pose(sphere);
  }

  //Calibration sphere
  rad::correction::glyph::Sphere* sphere = rad_struct->ransac.glyph;
  dat_entity->update_pose(sphere);

  //---------------------------
}

//Subfunction
void Glyph::draw_calibration_sphere(dyn::base::Sensor* sensor){
  rad::correction::glyph::Sphere* sphere = rad_struct->ransac.glyph;
  //---------------------------

  //Reset and move sphere
  sphere->reset_glyph();
  sphere->move_sphere(rad_struct->ransac.current_pose, rad_struct->ransac.sphere_diameter);
  sphere->update_pose(sensor);

  //---------------------------
}
void Glyph::draw_detection_sphere(dyn::base::Sensor* sensor){
  std::vector<rad::correction::structure::Circle>& vec_circle = rad_struct->hough.vec_circle;
  //---------------------------

  //Reset
  this->reset_detection_sphere();

  //Draw
  switch(rad_struct->hough.draw){
    case rad::hough::ALL:{
      this->draw_sphere_glyph(sensor, vec_circle);
      break;
    }
    case rad::hough::BEST:{
      std::vector<rad::correction::structure::Circle> best_circle;
      if(vec_circle.size() > 0) best_circle.push_back(vec_circle[0]);
      this->draw_sphere_glyph(sensor, best_circle);
      break;
    }
  }

  //---------------------------
}
void Glyph::draw_sphere_glyph(dyn::base::Sensor* sensor, vector<rad::correction::structure::Circle>& vec_circle){
  std::vector<rad::correction::glyph::Sphere*>& vec_sphere = rad_struct->hough.vec_glyph;
  //---------------------------

  int size = std::min(vec_sphere.size(), vec_circle.size());

  for(int i=0; i<size; i++){
    rad::correction::structure::Circle& circle = vec_circle[i];
    rad::correction::glyph::Sphere* sphere = vec_sphere[i];

    //Add sphere radius to the detected circle center
    vec3 pose = sensor->convert_depth_2d_to_3d(circle.center);
    vec3 dir = glm::normalize(pose);
    pose = pose + dir * (rad_struct->ransac.sphere_diameter / 2);

    //Position sphere
    sphere->move_sphere(pose, rad_struct->ransac.sphere_diameter);
    sphere->update_pose(sensor);
  }

  //---------------------------
}

//Reset function
void Glyph::reset_calibration_sphere(){
  //---------------------------

  rad::correction::glyph::Sphere* sphere = rad_struct->ransac.glyph;
  sphere->reset_glyph();

  //---------------------------
}
void Glyph::reset_detection_sphere(){
  std::vector<rad::correction::glyph::Sphere*>& vec_sphere = rad_struct->hough.vec_glyph;
  //---------------------------

  for(int i=0; i<vec_sphere.size(); i++){
    rad::correction::glyph::Sphere* sphere = vec_sphere[i];
    sphere->reset_glyph();
  }

  //---------------------------
}

}
