#include "Detection.h"

#include <Utility/Namespace.h>
#include <Radiometry/Namespace.h>
#include <Dynamic/Namespace.h>


namespace rad::detection::cloud{

//Constructor / Destructor
Detection::Detection(rad::Node* node_radio){
  //---------------------------

  eng::Node* node_engine = node_radio->get_node_engine();

  this->thread_pool = node_engine->get_thread_pool();
  this->rad_struct = node_radio->get_rad_struct();
  this->rad_glyph = new rad::detection::glyph::Manager(node_radio);
  this->rad_ransac = new rad::detection::cloud::Ransac(node_radio);

  this->ope_fitting = new ope::fitting::Sphere();
  this->ope_ransac = new ope::fitting::Ransac();

  //---------------------------
}
Detection::~Detection(){}

//Main function
void Detection::start_thread(dyn::base::Sensor* sensor){
  //---------------------------

  this->thread_idle = false;
  auto task_function = [this, sensor](){
    this->run_thread(sensor);
  };
  thread_pool->add_task(task_function);

  //---------------------------
}
void Detection::run_thread(dyn::base::Sensor* sensor){
  //---------------------------

  if(rad_struct->model.sphere.state_step == rad::detection::PROCESSING){
    rad_ransac->ransac_sphere(sensor);
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
  if(rad_struct->detection.nb_detection == 0){
    rad_struct->detection.ransac.current_pose = glm::vec3(0, 0, 0);
    return;
  }

  //Retrieve the 3D pose of the bounding box
  ivec2 point_2d = rad_struct->detection.vec_circle[0].center;
  vec3 pose_xyz = sensor->convert_depth_2d_to_3d(point_2d);
  vec4 pose_xyzw = vec4(pose_xyz.x, pose_xyz.y, pose_xyz.z, 1);
  rad_struct->detection.ransac.current_pose = pose->model * pose_xyzw;
  rad_struct->model.sphere.state_step = rad::detection::PROCESSING;

  //---------------------------
}

}