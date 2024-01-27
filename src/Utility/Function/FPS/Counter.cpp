#include "Counter.h"


namespace utl::fps{

// Constructor / Destructor
Counter::Counter(){
  //---------------------------

  this->last_time = std::chrono::steady_clock::now();

  //---------------------------
}

Counter::~Counter(){}

// Main function
float Counter::update(){
  //---------------------------

  auto now = std::chrono::steady_clock::now();
  auto elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(now - last_time).count();
  this->last_time = now;
  this->fps = 1000000.0f / elapsed_time;

  //---------------------------
  return fps;
}

}
