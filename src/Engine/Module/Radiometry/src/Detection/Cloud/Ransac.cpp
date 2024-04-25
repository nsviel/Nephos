#include "Ransac.h"

#include <K4N/Namespace.h>
#include <Utility/Namespace.h>
#include <Radiometry/Namespace.h>

namespace radio::detection{

//Constructor / Destructor
Ransac::Ransac(k4n::Node* node_k4n){
  //---------------------------

  radio::Node* node_radio = node_k4n->get_node_radio();

  this->radio_glyph = new radio::detection::cloud::Glyph(node_k4n);
  this->k4n_struct = node_k4n->get_k4n_struct();
  this->k4n_pool = node_k4n->get_k4n_pool();
  this->radio_detection = node_radio->get_radio_detection();
  this->ope_fitting = new ope::fitting::Sphere();
  this->ope_ransac = new ope::fitting::Ransac();
  this->ope_normal = new ope::attribut::Normal();

  //---------------------------
}
Ransac::~Ransac(){}

//Main function
void Ransac::start_thread(k4n::dev::Sensor* sensor){
  //---------------------------

  this->idle = false;
  auto task_function = [this, sensor](){
    this->run_thread(sensor);
  };
  k4n_pool->add_task(task_function);

  //---------------------------
}
void Ransac::run_thread(k4n::dev::Sensor* sensor){
  prf::graph::Tasker* tasker = sensor->profiler->get_or_create_tasker("calibration");
  //---------------------------

  tasker->loop_begin();

  tasker->task_begin("calibration");
  this->ransac_sphere(sensor);
  tasker->task_end("calibration");

  tasker->loop_end();

  //---------------------------
  this->idle = true;
}
void Ransac::wait_thread(){
  //For external thread to wait this queue thread idle
  //---------------------------

  while(idle == false){
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

  //---------------------------
}

//Subfunction
void Ransac::ransac_sphere(k4n::dev::Sensor* sensor){
  //if(step != radio::detection::PROCESSING) return;
  //---------------------------

  vector<vec3>& vec_xyz = sensor->object.data.xyz;
  vector<float>& vec_i = sensor->object.data.Is;

  //Search for point inside a global sphere around current center point
  vector<vec3> sphere_xyz;
  vector<float> sphere_i;
  for(int i=0; i<vec_xyz.size(); i++){
    vec3& xyz = vec_xyz[i];
    float distance = math::distance(xyz, current_pose);

    if(distance <= sensor->detection.sphere_diameter * k4n_struct->radio.detection.ransac.search_diameter_x){
      sphere_xyz.push_back(xyz);
      sphere_i.push_back(vec_i[i]);
    }
  }

  //Apply least square fitting
  ope_ransac->set_num_iteration(k4n_struct->radio.detection.ransac.nb_iter);
  ope_ransac->set_threshold_sphere(k4n_struct->radio.detection.ransac.thres_sphere);
  ope_ransac->set_threshold_pose(k4n_struct->radio.detection.ransac.thres_pose);
  ope_ransac->set_threshold_radius(k4n_struct->radio.detection.ransac.thres_radius);
  ope_ransac->ransac_sphere_in_cloud(sphere_xyz, current_pose, radius, sensor->detection.sphere_diameter/2);

  //Apply post-processing stuff
  radio_glyph->draw_sphere_glyph(sensor, current_pose, radius);
  /*this->data_IfR(sphere_xyz, sphere_i);
  this->data_IfIt(sphere_xyz, sphere_i);
  this->data_model(sphere_xyz, sphere_i);*/

  //---------------------------
}

}
