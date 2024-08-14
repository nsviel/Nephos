#pragma once

#include <string>
#include <list>

namespace prf::dynamic{class Tasker;}
namespace prf::dynamic{class Profiler;}


namespace prf::dynamic{

class Profiler
{
public:
  //Constructor / Destructor
  Profiler();
  ~Profiler();

public:
  //Main function
  void reset();
  void clean();

  //Subfunction
  prf::dynamic::Tasker* fetch_tasker(std::string name);
  std::list<prf::dynamic::Tasker*> get_list_tasker();

public:
  std::string name = "";
  bool pause = false;

private:
  std::list<prf::dynamic::Tasker*> list_tasker;
};

}
