#include "Manager.h"

#include <Radiometry/Namespace.h>
#include <Dynamic/Namespace.h>


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

//Subfunction
void Manager::draw_calibration_sphere(vec3 pose, float radius){
  rad::detection::glyph::Sphere* sphere = rad_struct->detection.glyph_calibration;
  //---------------------------

  sphere->reset_glyph();
  sphere->move_sphere(pose, radius * 2);

  //---------------------------
}
void Manager::draw_detection_sphere(dyn::base::Sensor* sensor){
  vector<rad::detection::structure::Circle>& vec_circle = rad_struct->detection.vec_circle;
  //---------------------------

  //Reset
  this->reset_detection_sphere();

  //Draw
  switch(rad_struct->detection.hough.drawing_mode){
    case rad::hough::ALL:{
      this->draw_detection_sphere(sensor, vec_circle);
      break;
    }
    case rad::hough::BEST:{
      vector<rad::detection::structure::Circle> best_circle;
      if(vec_circle.size() > 0) best_circle.push_back(vec_circle[0]);
      this->draw_detection_sphere(sensor, best_circle);
      break;
    }
  }

  //---------------------------
}
void Manager::reset_detection_sphere(){
  vector<rad::detection::glyph::Sphere*>& vec_sphere = rad_struct->detection.vec_glyph_sphere;
  //---------------------------

  for(int i=0; i<vec_sphere.size(); i++){
    rad::detection::glyph::Sphere* sphere = vec_sphere[i];
    sphere->reset_glyph();
  }

  //---------------------------
}
void Manager::draw_detection_sphere(dyn::base::Sensor* sensor, vector<rad::detection::structure::Circle>& vec_circle){
  vector<rad::detection::glyph::Sphere*>& vec_sphere = rad_struct->detection.vec_glyph_sphere;
  //---------------------------

  int size = std::min(vec_sphere.size(), vec_circle.size());

  for(int i=0; i<size; i++){
    rad::detection::structure::Circle& circle = vec_circle[i];
    rad::detection::glyph::Sphere* sphere = vec_sphere[i];

    //Add sphere radius to the detected circle center
    vec3 pose = sensor->convert_depth_2d_to_3d(circle.center);
    vec3 dir = glm::normalize(pose);
    pose = pose + dir * (rad_struct->detection.sphere_diameter / 2);

    //Position sphere
    sphere->move_sphere(pose, rad_struct->detection.sphere_diameter);
    sphere->update_pose(sensor);
  }

  //---------------------------
}

}
