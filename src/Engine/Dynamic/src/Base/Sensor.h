#pragma once

#include <Data/src/Base/Object.h>
#include <Profiler/src/Profiler/Graph/Profiler.h>
#include <Dynamic/src/Base/Timestamp.h>
#include <Dynamic/src/Base/State.h>


namespace dyn::base{

struct Sensor : public dat::base::Object, public utl::base::Thread{
  //---------------------------

  //Main function
  void init();
  void clean();

  virtual glm::vec3 convert_depth_2d_to_3d(glm::ivec2 point){return glm::vec3(0);}
  virtual void manage_query(float ts_querry){}
  virtual void manage_configuration(){}
  virtual void manage_reset(){}

  dyn::base::Timestamp timestamp;
  dyn::base::State state;
  prf::graph::Profiler profiler;
  std::vector<uint16_t> buffer_depth;
  std::vector<uint16_t> buffer_ir;

  //---------------------------
};

}
