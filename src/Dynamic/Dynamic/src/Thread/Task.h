#pragma once

#include <Thread/Namespace.h>

namespace dyn::base{class Sensor;}


namespace dyn::thread{

class Task : public sys::thread::Task
{
public:
  Task(){}
  virtual ~Task(){}

public:
  //Main function
  void start_thread(dyn::base::Sensor* sensor){
    //---------------------------

    this->sensor = sensor;
    this->run_thread();

    //---------------------------
  }

protected:
  dyn::base::Sensor* sensor = nullptr;
};

}
