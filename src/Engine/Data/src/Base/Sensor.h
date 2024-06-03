#pragma once

#include <Data/src/Base/Object.h>


namespace dat::base{

struct Sensor : public dat::base::Object{
  //---------------------------

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

  int state_UID = 0;
  bool thread_running = false;
  bool thread_paused = false;
  std::thread thread;
  std::vector<uint16_t> buffer_depth;
  std::vector<uint16_t> buffer_ir;




/*
  //Sensor glyph
  for(int i=0; i<20; i++){
    dat::glyph::object::Sphere* sphere = new dat::glyph::object::Sphere(node_engine);
    dat_glyph->create_glyph(&object, sphere);
    vec4 color = math::random(i);
    sphere->construct(color);

    this->detection.vec_glyph_sphere.push_back(sphere);
  }
  dat::glyph::object::Sphere* sphere = new dat::glyph::object::Sphere(node_engine);
  this->detection.glyph_calibration = sphere;
  dat_glyph->create_glyph(&object, sphere);
  sphere->construct(vec4(0, 1, 0, 1));
*/

  //---------------------------
};

}
