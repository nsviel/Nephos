#pragma once

#include <Utility/Component/Thread/Task/Job.h>

namespace dyn::base{class Sensor;}


namespace dyn::thread{

class Job : public sys::thread::Job
{
public:
  Job(){}
  virtual ~Job(){}

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
