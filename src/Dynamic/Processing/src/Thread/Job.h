#pragma once

#include <Utility/Namespace.h>

namespace dat::base{class Sensor;}


namespace dyn::prc::thread{

class Job : public sys::thread::Job
{
public:
  Job(){}
  virtual ~Job(){}

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
