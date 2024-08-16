#include "Operation.h"

#include <Utility/Namespace.h>
#include <Processing/Namespace.h>
#include <Core/Namespace.h>
#include <Radiometry/Namespace.h>


namespace dyn::prc::image{

//Constructor / Destructor
Operation::Operation(dyn::prc::Node* node_dynamic){
  //---------------------------

  core::Node* node_core = node_dynamic->get_node_core();

  this->dyn_struct = node_dynamic->get_dyn_struct();
  this->thread_pool = node_core->get_thread_pool();

  //---------------------------
}
Operation::~Operation(){}

//Main function
void Operation::start_thread(dyn::prc::base::Sensor* sensor){
  //---------------------------

  this->wait_thread();
  this->thread_idle = false;
  auto task_function = [this, sensor](){
    this->run_thread(sensor);
  };
  thread_pool->add_task(task_function);

  //---------------------------
}
void Operation::run_thread(dyn::prc::base::Sensor* sensor){
  //---------------------------


  //---------------------------
  this->thread_idle = true;
}
void Operation::wait_thread(){
  //For external thread to wait this queue thread idle
  //---------------------------

  while(thread_idle == false){
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

  //---------------------------
}

//Subfunction
void Operation::make_normal_from_depth_image(dyn::prc::base::Sensor* sensor){
  /*uint8_t* depth = sensor->depth.data.buffer;
  //---------------------------

  utl::base::Data* data = &sensor->data;

  int width = sensor->depth.data.width;
  int height = sensor->depth.data.height;
  std::vector<glm::vec3> Nxyz;

 //BUT OBTENIR UNE NORMAL IMAGE FROM DEPTH IMAGE

  for(int i=0; i<height; i++){
    for(int j=0; j<width; j++){

      int id_1 = i * width + j + 1;
      int id_2 = i * width + j - 1;
      uint16_t value_1 = depth[id_1 * 2] | (depth[id_1 * 2 + 1] << 8);
      uint16_t value_2 = depth[id_2 * 2] | (depth[id_2 * 2 + 1] << 8);
      float dzdx = (value_1 - value_2) / 2.0;

      id_1 = (i + 1) * width + j;
      id_2 = (i - 1) * width + j;
      value_1 = depth[id_1 * 2] | (depth[id_1 * 2 + 1] << 8);
      value_2 = depth[id_2 * 2] | (depth[id_2 * 2 + 1] << 8);
      float dzdy = (value_1 - value_2) / 2.0;

      glm::vec3 d(-dzdx, -dzdy, 1.0f);
      glm::vec3 n = glm::normalize(d);

      Nxyz.push_back(n);
    }
  }

  data->Nxyz = Nxyz;*/

  //---------------------------
}
void Operation::convert_normal_into_color(dyn::prc::base::Sensor* sensor, std::vector<glm::vec3>& vec_Nxyz){
  //---------------------------
/*
  std::vector<uint8_t> output = std::vector<uint8_t>(vec_Nxyz.size() * 4, 0);

  // Convert the float value to uint8_t
  for(int i=0; i<vec_Nxyz.size(); i++){
    glm::vec3 normal = vec_Nxyz[i];

    size_t j = i * 4;
    output[j] = normal.x * 255.0f;
    output[j + 1] = normal.y * 255.0f;
    output[j + 2] = normal.z * 255.0f;
    output[j + 3] = 255;
  }

  //sensor->normal.image.data = output;
*/
  //---------------------------
}

}
