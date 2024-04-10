#include "Pool.h"

#include <Utility/Namespace.h>
#include <Profiler/Namespace.h>
#include <Engine/Namespace.h>


namespace eng::thread{

//Constructor / Destructor
Pool::Pool(eng::Node* node_engine){
  //---------------------------

  this->size = 100;
  this->running = true;

  //---------------------------
  this->init();
}
Pool::~Pool(){}

//Main function
void Pool::init(){
  //---------------------------
/*
  this->vec_thread = std::vector<eng::thread::Thread>(size);

  for(int i=0; i<vec_thread.size(); i++){
    eng::thread::Thread& thread = vec_thread[i];
    thread.start();
  }
*/
  //---------------------------
}
void Pool::clean(){
  //---------------------------

  for(int i=0; i<vec_thread.size(); i++){
    eng::thread::Thread& thread = vec_thread[i];
    thread.stop();
  }

  //---------------------------
}

}
