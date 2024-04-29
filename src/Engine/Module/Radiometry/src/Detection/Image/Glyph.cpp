#include "Glyph.h"

#include <Kinect/Namespace.h>
#include <Graph/Namespace.h>
#include <Radiometry/Namespace.h>


namespace radio::detection{

//Constructor / Destructor
Glyph::Glyph(radio::Structure* radio_struct){
  //---------------------------

  this->sce_glyph = radio_struct->node_scene->get_scene_glyph();
  this->k4n_transfo = new k4n::utils::Transformation();

  //---------------------------
}
Glyph::~Glyph(){}

//Main function
void Glyph::draw_all_sphere_glyph(k4n::dev::Sensor* sensor){
  vector<radio::structure::Circle>& vec_circle = sensor->detection.vec_circle;
  //---------------------------

  this->reset_all_sphere(sensor);
  this->draw_sphere_from_circle(sensor, vec_circle);

  //---------------------------
}
void Glyph::draw_best_sphere_glyph(k4n::dev::Sensor* sensor){
  vector<radio::structure::Circle>& vec_circle = sensor->detection.vec_circle;
  //---------------------------

  vector<radio::structure::Circle> best_circle;
  if(sensor->detection.vec_circle.size() > 0){
    best_circle.push_back(sensor->detection.vec_circle[0]);
  }

  this->reset_all_sphere(sensor);
  this->draw_sphere_from_circle(sensor, best_circle);

  //---------------------------
}

//Subfunction
void Glyph::reset_all_sphere(k4n::dev::Sensor* sensor){
  vector<glyph::object::Sphere*>& vec_glyph_sphere = sensor->detection.vec_glyph_sphere;
  //---------------------------

  for(int i=0; i<vec_glyph_sphere.size(); i++){
    glyph::object::Sphere* sphere = vec_glyph_sphere[i];
    sphere->reset_glyph();
  }

  //---------------------------
}
void Glyph::draw_sphere_from_circle(k4n::dev::Sensor* sensor, vector<radio::structure::Circle>& vec_circle){
  vector<glyph::object::Sphere*>& vec_glyph_sphere = sensor->detection.vec_glyph_sphere;
  //---------------------------

  for(int i=0; i<vec_circle.size(); i++){
    if(i >= vec_glyph_sphere.size()) return;
    radio::structure::Circle& circle = vec_circle[i];

    //Add sphere radius to the detected circle center
    vec3 pose = k4n_transfo->convert_depth_2d_to_3d(sensor, circle.center);
    vec3 dir = glm::normalize(pose);
    pose = pose + dir * (sensor->detection.sphere_diameter / 2);

    //Position sphere
    vec_glyph_sphere[i]->move_sphere(pose, sensor->detection.sphere_diameter);
  }

  //---------------------------
}


}
