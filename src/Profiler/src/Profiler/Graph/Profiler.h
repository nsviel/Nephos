#pragma once

#include <Utility/Specific/common.h>
#include <Profiler/src/Profiler/Struct_profiler.h>

namespace prf::graph{class Tasker;}
namespace prf::type{class Profiler;}


namespace prf::graph{

class Profiler : public prf::type::Profiler
{
public:
  //Constructor / Destructor
  Profiler(string name, string type);
  ~Profiler();

public:
  //Main function
  void clear();

  //Tasker function
  prf::graph::Tasker* new_tasker(string name);
  prf::graph::Tasker* get_or_create_tasker(string name);
  void new_tasker(prf::graph::Tasker* tasker);
  void remove_tasker(prf::graph::Tasker* tasker);

  inline std::vector<prf::graph::Tasker*> get_vec_tasker(){return vec_tasker;}

private:
  std::vector<prf::graph::Tasker*> vec_tasker;
};

}
