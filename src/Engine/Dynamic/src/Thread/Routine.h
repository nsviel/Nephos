#pragma once

#include <Utility/Element/Thread/Routine.h>

namespace dyn::base{class Sensor;}


namespace dyn::thread{

class Routine : public utl::thread::Routine
{
public:
  Routine();
  virtual ~Routine();

public:
  //Main function
  void start_task(dyn::base::Sensor* sensor);

protected:
  dyn::base::Sensor* sensor = nullptr;
};

}
