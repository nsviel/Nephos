#pragma once

namespace vk::structure{class Vulkan;}


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
  Manager(vk::structure::Vulkan* vk_struct);
  ~Manager();

public:
  //Main function
  void init();
  void clean();

private:
  vk::structure::Vulkan* vk_struct;
};

}
