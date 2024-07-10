#pragma once

#include <Utility/Element/Thread/Task.h>

namespace dyn::base{class Sensor;}


namespace dyn::thread{

class Task : public utl::thread::Task
{
public:
  Task();
  virtual ~Task();

public:
  //Main function
  void start_task(dyn::base::Sensor* sensor);

protected:
  dyn::base::Sensor* sensor = nullptr;
};

}
