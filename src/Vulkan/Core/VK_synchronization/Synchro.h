#pragma once

namespace vk{class Structure;}


namespace vk::synchro{

class Synchro
{
public:
  //Constructor / Destructor
  Synchro(vk::Structure* vk_struct);
  ~Synchro();

public:
  //Main function
  void wait_idle();
  void end_idle();

private:
  vk::Structure* vk_struct;
};

}
