#include "Ransac.h"

#include <Utility/Namespace.h>
#include <Radiometry/Namespace.h>


namespace rad::detection{

//Constructor / Destructor
Ransac::Ransac(rad::Node* node_radio){
  //---------------------------

  eng::Node* node_engine = node_radio->get_node_engine();

  this->rad_struct = node_radio->get_rad_struct();
  this->thread_pool = node_engine->get_thread_pool();
  this->rad_glyph = new rad::detection::cloud::Glyph(node_radio);
  this->ope_fitting = new ope::fitting::Sphere();
  this->ope_ransac = new ope::fitting::Ransac();
  this->ope_normal = new ope::attribut::Normal();

  //---------------------------
}
Ransac::~Ransac(){}

//Main function
void Ransac::start_thread(dat::base::Sensor* sensor){
  //---------------------------

  this->idle = false;
  auto task_function = [this, sensor](){
    this->run_thread(sensor);
  };
  thread_pool->add_task(task_function);

  //---------------------------
}
void Ransac::run_thread(dat::base::Sensor* sensor){
  //---------------------------

  this->ransac_sphere(sensor);

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
void Ransac::ransac_sphere(dat::base::Sensor* sensor){
  //if(step != rad::detection::PROCESSING) return;
  //---------------------------

  utl::type::Data* data = sensor->get_data();
  vector<vec3>& vec_xyz = data->xyz;
  vector<float>& vec_i = data->Is;

  //Search for point inside a global sphere around current center point
  vector<vec3> sphere_xyz;
  vector<float> sphere_i;
  for(int i=0; i<vec_xyz.size(); i++){
    vec3& xyz = vec_xyz[i];
    float distance = math::distance(xyz, current_pose);

    if(distance <= rad_struct->detection.sphere_diameter * rad_struct->detection.ransac.search_diameter_x){
      sphere_xyz.push_back(xyz);
      sphere_i.push_back(vec_i[i]);
    }
  }

  //Apply least square fitting
  ope_ransac->set_num_iteration(rad_struct->detection.ransac.nb_iter);
  ope_ransac->set_threshold_sphere(rad_struct->detection.ransac.thres_sphere);
  ope_ransac->set_threshold_pose(rad_struct->detection.ransac.thres_pose);
  ope_ransac->set_threshold_radius(rad_struct->detection.ransac.thres_radius);
  ope_ransac->ransac_sphere_in_cloud(sphere_xyz, current_pose, radius, rad_struct->detection.sphere_diameter/2);

  //Apply post-processing stuff
  rad_glyph->draw_sphere_glyph(sensor, current_pose, radius);
  /*this->data_IfR(sphere_xyz, sphere_i);
  this->data_IfIt(sphere_xyz, sphere_i);
  this->data_model(sphere_xyz, sphere_i);*/

  //---------------------------
}

}
