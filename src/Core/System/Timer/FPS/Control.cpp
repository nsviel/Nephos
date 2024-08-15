#include "Control.h"


namespace sys::timer::fps{

// Constructor / Destructor
Control::Control(int fps_max){
  //---------------------------

  this->fps_max = fps_max;

  //---------------------------
}

Control::~Control(){}

// Main function
void Control::start_loop(){
  //---------------------------

  this->start_time = std::chrono::steady_clock::now();

  //---------------------------
}
void Control::stop_loop(){
  //---------------------------

  auto now = std::chrono::steady_clock::now();
  auto elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(now - start_time).count();

  int sleep_time = 1000000.0f / (float)fps_max - elapsed_time;
  if(sleep_time > 0){
    std::this_thread::sleep_for(std::chrono::microseconds(sleep_time));
  }

  //---------------------------
}

}
