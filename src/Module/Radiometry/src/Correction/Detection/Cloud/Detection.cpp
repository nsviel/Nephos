#include "Detection.h"

#include <Utility/Namespace.h>
#include <Radiometry/Namespace.h>
#include <Dynamic/Namespace.h>
#include <Engine/Namespace.h>


namespace rad::correction::cloud{

//Constructor / Destructor
Detection::Detection(rad::correction::Node* node_correction){
  //---------------------------

  rad::Node* node_radio = node_correction->get_node_radio();
  eng::Node* node_engine = node_radio->get_node_engine();

  this->thread_pool = node_engine->get_thread_pool();
  this->rad_struct = node_correction->get_rad_struct();
  this->rad_glyph = new rad::correction::Glyph(node_correction);
  this->rad_ransac = new rad::correction::cloud::Ransac(node_correction);

  this->ope_fitting = new ope::fitting::Sphere();
  this->ope_ransac = new ope::fitting::Ransac();

  //---------------------------
}
Detection::~Detection(){}

//Main function
void Detection::start_thread(dyn::base::Sensor* sensor){
  //---------------------------

  if(thread.joinable()){
    this->thread.join();
  }
  this->thread = std::thread(&Detection::run_thread, this, sensor);

  //---------------------------
}
void Detection::run_thread(dyn::base::Sensor* sensor){
  //---------------------------

  if(sensor != nullptr && rad_struct->state_step == rad::correction::cloud::PROCESSING){
    rad_ransac->ransac_sphere(sensor);
    rad_glyph->reset_detection_sphere();
  }else{
    rad_glyph->reset_calibration_sphere();
  }

  //---------------------------
  this->thread_idle = true;
}
void Detection::wait_thread(){
  //For external thread to wait this queue thread idle
  //---------------------------

  while(thread_idle == false){
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

  //---------------------------
}

//Subfunction
void Detection::validate_bbox(dyn::base::Sensor* sensor){
  utl::base::Pose* pose = &sensor->pose;
  //---------------------------

  //Stop if no detection
  if(rad_struct->hough.nb_detection == 0){
    rad_struct->ransac.current_pose = glm::vec3(0, 0, 0);
    return;
  }

  //Retrieve the 3D pose of the bounding box
  ivec2 point_2d = rad_struct->hough.vec_circle[0].center;
  vec3 pose_xyz = sensor->convert_depth_2d_to_3d(point_2d);
  vec4 pose_xyzw = vec4(pose_xyz.x, pose_xyz.y, pose_xyz.z, 1);
  rad_struct->ransac.current_pose = pose->model * pose_xyzw;
  rad_ransac->ransac_sphere(sensor);

  //Up step and display glyph
  rad_struct->state_step = rad::correction::cloud::PROCESSING;

  //---------------------------
}

}
