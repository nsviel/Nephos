#include "FPS_counter.h"

// Constructor / Destructor
FPS_counter::FPS_counter(){
  //---------------------------

  this->last_time = std::chrono::steady_clock::now();

  //---------------------------
}

FPS_counter::~FPS_counter(){}

// Main function
float FPS_counter::update(){
  //---------------------------

  auto now = std::chrono::steady_clock::now();
  auto elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(now - last_time).count();
  this->last_time = now;
  this->fps = 1000000.0f / elapsed_time;

  //---------------------------
  return fps
}
