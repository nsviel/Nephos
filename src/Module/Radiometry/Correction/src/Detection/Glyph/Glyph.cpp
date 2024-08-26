#include "Glyph.h"

#include <Radiometry/Correction/Namespace.h>
#include <Data/Namespace.h>


namespace rad::cor{

//Constructor / Destructor
Glyph::Glyph(rad::cor::Node* node_correction){
  //---------------------------

  dat::Node* node_data = node_correction->get_node_data();
  dat::elm::Node* node_element = node_data->get_node_element();

  this->dat_glyph = node_element->get_dat_glyph();
  this->dat_entity = node_element->get_dat_entity();
  this->node_core = node_correction->get_node_core();
  this->rad_struct = node_correction->get_rad_struct();

  //---------------------------
}
Glyph::~Glyph(){}

//Main function
void Glyph::create_sphere_glyph(){
  //---------------------------

  //Detection spheres
  for(int i=0; i<20; i++){
    std::shared_ptr<rad::cor::glyph::Sphere> sphere = std::make_shared<rad::cor::glyph::Sphere>(node_core);
    glm::vec4 color = math::random(i);
    sphere->set_color(color);
    dat_glyph->create_glyph(sphere);

    rad_struct->hough.vec_glyph.push_back(sphere);
  }

  //Calibration sphere
  std::shared_ptr<rad::cor::glyph::Sphere> sphere =  std::make_shared<rad::cor::glyph::Sphere>(node_core);
  rad_struct->ransac.glyph = sphere;
  sphere->set_color(glm::vec4(0, 1, 0, 1));
  dat_glyph->create_glyph(sphere);

  //---------------------------
}
void Glyph::update_sphere_glyph(){
  //---------------------------

  //Detection spheres
  std::vector< std::shared_ptr<rad::cor::glyph::Sphere> >& vec_glyph = rad_struct->hough.vec_glyph;
  for(int i=0; i<vec_glyph.size(); i++){
    std::shared_ptr<rad::cor::glyph::Sphere> sphere = vec_glyph[i];
    //dat_entity->update_pose(sphere);
  }

  //Calibration sphere
  std::shared_ptr<rad::cor::glyph::Sphere> sphere = rad_struct->ransac.glyph;
  //dat_entity->update_pose(sphere);

  //---------------------------
}

//Subfunction
void Glyph::draw_calibration_sphere(const std::shared_ptr<dat::base::Sensor> sensor){
  std::shared_ptr<rad::cor::glyph::Sphere> sphere = rad_struct->ransac.glyph;
  //---------------------------

  //Reset and move sphere
  sphere->reset_glyph();
  sphere->move_sphere(rad_struct->ransac.current_pose, rad_struct->ransac.sphere_diameter);
  sphere->update_pose(sensor);

  //---------------------------
}
void Glyph::draw_detection_sphere(std::shared_ptr<dat::base::Sensor> sensor){
  std::vector<rad::cor::structure::Circle>& vec_circle = rad_struct->hough.vec_circle;
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
      std::vector<rad::cor::structure::Circle> best_circle;
      if(vec_circle.size() > 0) best_circle.push_back(vec_circle[0]);
      this->draw_sphere_glyph(sensor, best_circle);
      break;
    }
  }

  //---------------------------
}
void Glyph::draw_sphere_glyph(std::shared_ptr<dat::base::Sensor> sensor, std::vector<rad::cor::structure::Circle>& vec_circle){
  std::vector< std::shared_ptr<rad::cor::glyph::Sphere> >& vec_sphere = rad_struct->hough.vec_glyph;
  //---------------------------

  int size = std::min(vec_sphere.size(), vec_circle.size());

  for(int i=0; i<size; i++){
    rad::cor::structure::Circle& circle = vec_circle[i];
    std::shared_ptr<rad::cor::glyph::Sphere> sphere = vec_sphere[i];

    //Add sphere radius to the detected circle center
    glm::vec3 pose = sensor->convert_depth_2d_to_3d(circle.center);
    glm::vec3 dir = glm::normalize(pose);
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

  std::shared_ptr<rad::cor::glyph::Sphere> sphere = rad_struct->ransac.glyph;
  sphere->reset_glyph();

  //---------------------------
}
void Glyph::reset_detection_sphere(){
  std::vector< std::shared_ptr<rad::cor::glyph::Sphere> >& vec_sphere = rad_struct->hough.vec_glyph;
  //---------------------------

  for(int i=0; i<vec_sphere.size(); i++){
    std::shared_ptr<rad::cor::glyph::Sphere> sphere = vec_sphere[i];
    sphere->reset_glyph();
  }

  //---------------------------
}

}
