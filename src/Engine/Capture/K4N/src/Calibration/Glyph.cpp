#include "Glyph.h"

#include <K4N/Namespace.h>
#include <Scene/Namespace.h>


namespace k4n::calibration{

//Constructor / Destructor
Glyph::Glyph(k4n::Node* node_k4n){
  //---------------------------

  eng::scene::Node* node_scene = node_k4n->get_node_scene();

  this->sce_glyph = node_scene->get_scene_glyph();

  //---------------------------
}
Glyph::~Glyph(){}

//Main function
void Glyph::draw_glyph(k4n::dev::Sensor* sensor){
  //---------------------------

  this->reset_all_sphere(sensor);
  this->draw_all_sphere(sensor);

  //---------------------------
}

//Subfunction
void Glyph::reset_all_sphere(k4n::dev::Sensor* sensor){
  vector<glyph::scene::Sphere*>& vec_sphere_glyph = sensor->sphere.vec_sphere_glyph;
  //---------------------------

  for(int i=0; i<vec_sphere_glyph.size(); i++){
    glyph::scene::Sphere* sphere = vec_sphere_glyph[i];
    sphere->reset_glyph();
  }

  //---------------------------
}
void Glyph::draw_all_sphere(k4n::dev::Sensor* sensor){
  vector<glyph::scene::Sphere*>& vec_sphere_glyph = sensor->sphere.vec_sphere_glyph;
  vector<vec3>& vec_circle = sensor->sphere.vec_circle;
  //---------------------------

  uint16_t* buffer = reinterpret_cast<uint16_t*>(sensor->depth.data.buffer);
  int width = sensor->depth.data.width;

  for(int i=0; i<vec_circle.size(); i++){
    if(i >= vec_sphere_glyph.size()) return;
    
    vec3& circle = vec_circle[i];

    //Retrieve image coordinates
    int x = circle[0];
    int y = circle[1];
    k4a_float2_t source_xy = { static_cast<float>(x), static_cast<float>(y) };
    float source_z = static_cast<float>(buffer[y * width + x]);

    //Convert it into 3D coordinate
    k4a_float3_t target_xyz;
    bool success = sensor->param.calibration.convert_2d_to_3d(source_xy, source_z, K4A_CALIBRATION_TYPE_DEPTH, K4A_CALIBRATION_TYPE_DEPTH, &target_xyz);
    vec4 xyzw = vec4(target_xyz.xyz.x, target_xyz.xyz.y, target_xyz.xyz.z, 1);

    //Apply transformation
    float inv_scale = 1.0f / 1000.0f;
    xyzw.x = -xyzw.x * inv_scale;
    xyzw.y = -xyzw.y * inv_scale;
    xyzw.z = xyzw.z * inv_scale;
    xyzw = vec4(xyzw.z, xyzw.x, xyzw.y, 1);
    xyzw = xyzw * sensor->object.get_pose()->model;
    vec3 pose = vec3(xyzw.x, xyzw.y, xyzw.z);

    //Add sphere radius to the detected circle center
    vec3 dir = glm::normalize(pose);
    pose = pose + dir * sensor->sphere.sphere_diameter;

    //Position sphere
    vec_sphere_glyph[i]->move_sphere(pose);
  }

  //---------------------------
}

}
