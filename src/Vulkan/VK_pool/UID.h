#pragma once

namespace vk::structure{class Vulkan;}


namespace vk::instance{

class UID
{
public:
  //Constructor / Destructor
  UID(vk::structure::Vulkan* vk_struct);
  ~UID();

public:
  //Main function
  int query_free_UID();

private:
  vk::structure::Vulkan* vk_struct;
};

}
