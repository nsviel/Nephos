#pragma once

#include <Utility/Namespace.h>

namespace dat::base{class Sensor;}


namespace dyn::prc::thread{

class Task : public sys::thread::Task
{
public:
  Task(){}
  virtual ~Task(){}

public:
  //Main function
  void start_thread(dat::base::Sensor* sensor){
    //---------------------------

    this->sensor = sensor;
    this->run_thread();

    //---------------------------
  }

protected:
  dat::base::Sensor* sensor = nullptr;
};

}
