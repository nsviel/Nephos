#pragma once

#include <Utility/Namespace.h>

namespace dyn::prc::base{class Sensor;}


namespace dyn::prc::thread{

class Routine : public sys::thread::Routine
{
public:
  Routine(){}
  virtual ~Routine(){}

public:
  //Main function
  void start_task(dyn::prc::base::Sensor* sensor){
    //---------------------------

    this->sensor = sensor;
    this->run_task();

    //---------------------------
  }

protected:
  dyn::prc::base::Sensor* sensor = nullptr;
};

}
