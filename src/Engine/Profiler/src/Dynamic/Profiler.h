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

  //Tasker function
  prf::dynamic::Tasker* fetch_tasker(std::string name);

  inline std::list<prf::dynamic::Tasker*> get_list_tasker(){return list_tasker;}

public:
  std::string name = "";

private:
  std::list<prf::dynamic::Tasker*> list_tasker;
};

}
