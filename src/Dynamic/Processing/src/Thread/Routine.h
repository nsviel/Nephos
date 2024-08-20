#pragma once

#include <Utility/Namespace.h>

namespace dat::base{class Sensor;}


namespace dyn::prc::thread{

class Routine : public sys::thread::Routine
{
public:
  Routine(){}
  virtual ~Routine(){}

public:
  //Main function
  void start_task(dat::base::Sensor* sensor){
    //---------------------------

    this->sensor = sensor;
    this->run_task();

    //---------------------------
  }

protected:
  dat::base::Sensor* sensor = nullptr;
};

}
