#pragma once

namespace vk{class Structure;}


namespace vk::command{

class Manager
{
public:
  //Constructor / Destructor
  Manager(vk::Structure* vk_struct);
  ~Manager();

public:
  //Main function
  void init();
  void clean();

private:
  vk::Structure* vk_struct;
};

}
