#pragma once

#include <Utility/Specific/Common.h>
#include <Profiler/src/Profiler/Base/Profiler.h>

namespace prf::graph{class Tasker;}
namespace prf::base{class Profiler;}


namespace prf::graph{

class Profiler : public prf::base::Profiler
{
public:
  //Constructor / Destructor
  Profiler();
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
