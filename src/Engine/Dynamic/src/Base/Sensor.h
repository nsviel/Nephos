#pragma once

#include <Data/src/Base/Object.h>
#include <Profiler/src/Profiler/Graph/Profiler.h>


namespace dyn::base{

struct Sensor : public dat::base::Object{
  //---------------------------

  //Main function
  void init();
  void clean();

  //Thread function
  void start_thread();
  void run_thread();
  void stop_thread();
  void wait_thread();

  virtual void thread_init(){}
  virtual void thread_loop(){}
  virtual void thread_end(){}
  virtual void manage_reset(){}

  virtual glm::vec3 convert_depth_2d_to_3d(glm::ivec2 point){return glm::vec3(0);}
  virtual void manage_ts_query(float ts_querry){}
  virtual void manage_configuration(){}

  inline bool is_thread_running(){return thread_running;}
  inline bool is_thread_paused(){return thread_paused;}

  prf::graph::Profiler profiler;
  std::vector<uint16_t> buffer_depth;
  std::vector<uint16_t> buffer_ir;
  std::thread thread;
  bool thread_running = false;
  bool thread_paused = false;
  float ts_beg = -1;
  float ts_end = -1;

  //---------------------------
};

}
