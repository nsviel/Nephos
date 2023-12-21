#include "FPS_counter.h"

// Constructor / Destructor
FPS_counter::FPS_counter(int fps_max){
  //---------------------------

  this->last_time = std::chrono::steady_clock::now();
  this->fps_max = fps_max;

  //---------------------------
}

FPS_counter::~FPS_counter(){}

// Main function
void FPS_counter::update(){
  //---------------------------

  auto now = std::chrono::steady_clock::now();
  auto elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(now - last_time).count();
  this->last_time = now;

  this->fps = 1000000.0f / elapsed_time;

  int sleep_time = 1000000.0f / fps_max - elapsed_time;
  if (sleep_time > 0) {
    std::this_thread::sleep_for(std::chrono::microseconds(sleep_time));
  }

  //---------------------------
}
