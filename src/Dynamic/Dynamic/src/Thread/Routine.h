#pragma once

#include <System/Namespace.h>

namespace dyn::base{class Sensor;}


namespace dyn::thread{

class Routine : public sys::thread::Routine
{
public:
  Routine(){}
  virtual ~Routine(){}

public:
  //Main function
  void start_task(dyn::base::Sensor* sensor){
    //---------------------------

    this->sensor = sensor;
    this->run_task();

    //---------------------------
  }

protected:
  dyn::base::Sensor* sensor = nullptr;
};

}
