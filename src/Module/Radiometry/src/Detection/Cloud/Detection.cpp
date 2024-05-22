#include "Detection.h"

#include <Utility/Namespace.h>
#include <Radiometry/Namespace.h>


namespace rad::detection::cloud{

//Constructor / Destructor
Detection::Detection(rad::Node* node_radio){
  //---------------------------

  eng::Node* node_engine = node_radio->get_node_engine();

  this->thread_pool = node_engine->get_thread_pool();
  this->rad_struct = node_radio->get_rad_struct();
  this->rad_glyph = new rad::detection::cloud::Glyph(node_radio);
  this->rad_ransac = new rad::detection::cloud::Ransac(node_radio);

  this->ope_fitting = new ope::fitting::Sphere();
  this->ope_ransac = new ope::fitting::Ransac();
  this->ope_normal = new ope::normal::KNN();
  this->map_step[rad::detection::cloud::WAIT_VALIDATION] = "Wait validation";
  this->map_step[rad::detection::cloud::PROCESSING] = "Detectioning";
  this->step = rad::detection::cloud::WAIT_VALIDATION;

  //---------------------------
}
Detection::~Detection(){}

//Main function
void Detection::start_thread(dat::base::Sensor* sensor){
  //---------------------------

  this->idle = false;
  auto task_function = [this, sensor](){
    this->run_thread(sensor);
  };
  thread_pool->add_task(task_function);

  //---------------------------
}
void Detection::run_thread(dat::base::Sensor* sensor){
  //---------------------------

  rad_ransac->ransac_sphere(sensor);

  //---------------------------
  this->idle = true;
}
void Detection::wait_thread(){
  //For external thread to wait this queue thread idle
  //---------------------------

  while(idle == false){
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

  //---------------------------
}

//Subfunction
void Detection::next_step(dat::base::Sensor* sensor){
  //---------------------------

  switch(step){
    case rad::detection::cloud::WAIT_VALIDATION:{
      this->validate_bbox(sensor);
      break;
    }
    case rad::detection::cloud::PROCESSING:{
      this->step = rad::detection::cloud::WAIT_VALIDATION;
      break;
    }
  }

  //---------------------------
}
void Detection::validate_bbox(dat::base::Sensor* sensor){
  if(rad_struct->detection.nb_detection == 0) return;
  //---------------------------

  utl::base::Pose* pose = sensor->get_pose();

  this->step++;
  ivec2 point_2d = rad_struct->detection.vec_circle[0].center;
  vec3 truc = sensor->convert_depth_2d_to_3d(point_2d);
  vec4 machin = vec4(truc.x, truc.y, truc.z, 1);
  truc = pose->model * machin;
  rad_struct->detection.ransac.current_pose = vec3(truc.x, truc.y, truc.z);

  //---------------------------
}

}
