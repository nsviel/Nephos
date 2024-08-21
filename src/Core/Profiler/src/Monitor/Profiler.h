#pragma once

#include <string>
#include <list>

namespace prf::monitor{class Tasker;}
namespace prf::monitor{class Profiler;}


namespace prf::monitor{

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
  prf::monitor::Tasker* fetch_tasker(std::string name);
  std::list<prf::monitor::Tasker*> get_list_tasker();

public:
  std::string name = "";
  bool pause = false;

private:
  std::list<prf::monitor::Tasker*> list_tasker;
};

}
