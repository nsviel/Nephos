#pragma once

#include <Utility/Specific/common.h>

namespace prf{class Tasker;}


namespace prf{

class Profiler
{
public:
  //Constructor / Destructor
  Profiler(string name);
  ~Profiler();

public:
  //Main function


  inline std::vector<prf::Tasker*> get_vec_tasker(){return vec_tasker;}

private:
  std::vector<prf::Tasker*> vec_tasker;
  string name;
};

}
