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
  void reset();
  void clean();

  //Tasker function
  prf::graph::Tasker* new_tasker(string name);
  prf::graph::Tasker* get_or_create_tasker(string name);
  void new_tasker(prf::graph::Tasker* tasker);
  void remove_tasker(prf::graph::Tasker* tasker);

  inline std::list<prf::graph::Tasker*> get_list_tasker(){return list_tasker;}

private:
  std::list<prf::graph::Tasker*> list_tasker;
};

}
