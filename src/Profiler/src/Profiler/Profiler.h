#pragma once

#include <Utility/Specific/common.h>

namespace prf{class Tasker;}
namespace prf::vulkan{class Manager;}


namespace prf{

class Profiler
{
public:
  //Constructor / Destructor
  Profiler(string name, string type);
  ~Profiler();

public:
  //Main function
  void clear();

  //Tasker function
  prf::Tasker* new_tasker(string name);
  prf::Tasker* get_tasker(string name);
  prf::vulkan::Manager* get_tasker_vulkan();
  void new_tasker(prf::Tasker* tasker);
  void remove_tasker(prf::Tasker* tasker);

  inline std::vector<prf::Tasker*> get_vec_tasker(){return vec_tasker;}
  inline std::string get_name(){return name;}
  inline std::string get_type(){return type;}

private:
  std::vector<prf::Tasker*> vec_tasker;
  string name;
  string type;
};

}