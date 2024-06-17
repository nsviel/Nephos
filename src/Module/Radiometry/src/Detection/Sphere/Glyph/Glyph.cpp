#include "Glyph.h"

#include <Radiometry/Namespace.h>
#include <Dynamic/Namespace.h>
#include <Data/Namespace.h>


namespace rad::detection::sphere{

//Constructor / Destructor
Glyph::Glyph(rad::detection::Node* node_detection){
  //---------------------------

  rad::Node* node_radio = node_detection->get_node_radio();
  dat::Node* node_data = node_radio->get_node_data();

  this->dat_glyph = node_data->get_dat_glyph();
  this->dat_entity = node_data->get_dat_entity();
  this->node_engine = node_radio->get_node_engine();
  this->rad_struct = node_detection->get_rad_struct();

  //---------------------------
}
Glyph::~Glyph(){}

//Main function
void Glyph::create_sphere_glyph(){
  //---------------------------

  //Detection spheres
  for(int i=0; i<20; i++){
    rad::detection::glyph::Sphere* sphere = new rad::detection::glyph::Sphere(node_engine);
    vec4 color = math::random(i);
    sphere->set_color(color);
    dat_glyph->create_glyph(sphere);

    rad_struct->sphere.hough.vec_glyph.push_back(sphere);
  }

  //Calibration sphere
  rad::detection::glyph::Sphere* sphere = new rad::detection::glyph::Sphere(node_engine);
  rad_struct->sphere.ransac.glyph = sphere;
  sphere->set_color(vec4(0, 1, 0, 1));
  dat_glyph->create_glyph(sphere);

  //---------------------------
}
void Glyph::update_sphere_glyph(){
  //---------------------------

  //Detection spheres
  std::vector<rad::detection::glyph::Sphere*>& vec_glyph = rad_struct->sphere.hough.vec_glyph;
  for(int i=0; i<vec_glyph.size(); i++){
    rad::detection::glyph::Sphere* sphere = vec_glyph[i];
    dat_entity->update_pose(sphere);
  }

  //Calibration sphere
  rad::detection::glyph::Sphere* sphere = rad_struct->sphere.ransac.glyph;
  dat_entity->update_pose(sphere);

  //---------------------------
}

//Subfunction
void Glyph::draw_calibration_sphere(dyn::base::Sensor* sensor){
  rad::detection::glyph::Sphere* sphere = rad_struct->sphere.ransac.glyph;
  //---------------------------

  //Reset and move sphere
  sphere->reset_glyph();
  sphere->move_sphere(rad_struct->sphere.ransac.current_pose, rad_struct->sphere.ransac.sphere_diameter);
  sphere->update_pose(sensor);

  //---------------------------
}
void Glyph::draw_detection_sphere(dyn::base::Sensor* sensor){
  std::vector<rad::detection::structure::Circle>& vec_circle = rad_struct->sphere.hough.vec_circle;
  //---------------------------

  //Reset
  this->reset_detection_sphere();

  //Draw
  switch(rad_struct->sphere.hough.draw){
    case rad::hough::ALL:{
      this->draw_sphere_glyph(sensor, vec_circle);
      break;
    }
    case rad::hough::BEST:{
      std::vector<rad::detection::structure::Circle> best_circle;
      if(vec_circle.size() > 0) best_circle.push_back(vec_circle[0]);
      this->draw_sphere_glyph(sensor, best_circle);
      break;
    }
  }

  //---------------------------
}
void Glyph::draw_sphere_glyph(dyn::base::Sensor* sensor, vector<rad::detection::structure::Circle>& vec_circle){
  vector<rad::detection::glyph::Sphere*>& vec_sphere = rad_struct->sphere.hough.vec_glyph;
  //---------------------------

  int size = std::min(vec_sphere.size(), vec_circle.size());

  for(int i=0; i<size; i++){
    rad::detection::structure::Circle& circle = vec_circle[i];
    rad::detection::glyph::Sphere* sphere = vec_sphere[i];

    //Add sphere radius to the detected circle center
    vec3 pose = sensor->convert_depth_2d_to_3d(circle.center);say(pose);
    vec3 dir = glm::normalize(pose);
    pose = pose + dir * (rad_struct->sphere.ransac.sphere_diameter / 2);

    //Position sphere
    sphere->move_sphere(pose, rad_struct->sphere.ransac.sphere_diameter);
    sphere->update_pose(sensor);
  }

  //---------------------------
}

//Reset function
void Glyph::reset_all_sphere(){
  //---------------------------

  rad_struct->sphere.ransac.glyph->reset_glyph();
  this->reset_detection_sphere();

  //---------------------------
}
void Glyph::reset_detection_sphere(){
  vector<rad::detection::glyph::Sphere*>& vec_sphere = rad_struct->sphere.hough.vec_glyph;
  //---------------------------

  for(int i=0; i<vec_sphere.size(); i++){
    rad::detection::glyph::Sphere* sphere = vec_sphere[i];
    sphere->reset_glyph();
  }

  //---------------------------
}

}
