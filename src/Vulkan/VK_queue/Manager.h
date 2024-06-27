#pragma once

namespace vk{class Structure;}


namespace vk::queue{

enum Type{
  GRAPHICS = 0,
  PRESENTATION = 1,
  TRANSFER = 2,
};

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
