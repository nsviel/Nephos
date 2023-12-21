#include "FPS_control.h"

// Constructor / Destructor
FPS_control::FPS_control(int fps_max){
  //---------------------------

  this->last_time = std::chrono::steady_clock::now();
  this->fps_max = fps_max;

  //---------------------------
}

FPS_control::~FPS_control(){}

// Main function
void FPS_control::start(){
  //---------------------------

  this->start_time = std::chrono::steady_clock::now();

  //---------------------------
}
void FPS_control::start(){
  //---------------------------

  auto now = std::chrono::steady_clock::now();
  auto elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(now - start_time).count();

  int sleep_time = 1000000.0f / (float)fps_max - elapsed_time;
  if (sleep_time > 0) {
    std::this_thread::sleep_for(std::chrono::microseconds(sleep_time));
  }

  //---------------------------
}
