#pragma once

#include <Profiler/src/Dynamic/Structure/Profiler.h>
#include <string>
#include <list>

namespace prf::graph{class Tasker;}
namespace prf::dynamic{class Profiler;}


namespace prf::graph{

class Profiler : public prf::dynamic::Profiler
{
public:
  //Constructor / Destructor
  Profiler();
  Profiler(std::string name);
  ~Profiler();

public:
  //Main function
  void reset();
  void clean();

  //Tasker function
  prf::graph::Tasker* fetch_tasker(std::string name);
  void remove_tasker(prf::graph::Tasker* tasker);

  inline std::list<prf::graph::Tasker*> get_list_tasker(){return list_tasker;}

private:
  std::list<prf::graph::Tasker*> list_tasker;
};

}
