#pragma once

#include <Thread/Namespace.h>

namespace dyn::prc::base{class Sensor;}


namespace dyn::prc::thread{

class Job : public sys::thread::Job
{
public:
  Job(){}
  virtual ~Job(){}

public:
  //Main function
  void start_thread(dyn::prc::base::Sensor* sensor){
    //---------------------------

    this->sensor = sensor;
    this->run_thread();

    //---------------------------
  }

protected:
  dyn::prc::base::Sensor* sensor = nullptr;
};

}
