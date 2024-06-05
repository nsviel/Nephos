#include "Sensor.h"


namespace dyn::base{

//Main function
void Sensor::init(){
  //---------------------------

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
}
void Sensor::clean(){
  //---------------------------

  this->stop_thread();

  //---------------------------
}

//Thread function
void Sensor::start_thread(){
  //---------------------------

  if(!thread_running){
    this->thread_running = true;
    this->thread = std::thread(&Sensor::run_thread, this);
  }

  //---------------------------
}
void Sensor::run_thread(){
  //---------------------------

  this->thread_init();

  //Sensor thread
  while(thread_running){
    this->thread_loop();
  }

  this->thread_end();

  //---------------------------
}
void Sensor::stop_thread(){
  //---------------------------

  this->thread_running = false;
  if(thread.joinable()){
    thread.join();
  }

  //---------------------------
}
void Sensor::wait_thread(){
  //For external thread to wait this queue thread idle
  //---------------------------

  while(thread_paused == false){
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

  //---------------------------
}

}
