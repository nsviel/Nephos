#pragma once

namespace vk{class Structure;}


namespace vk::main{

class Profiler
{
public:
  //Constructor / Destructor
  Profiler(vk::Structure* vk_struct);
  ~Profiler();

public:
  //Main function
  void clear();

private:
  vk::Structure* vk_struct;
};

}
