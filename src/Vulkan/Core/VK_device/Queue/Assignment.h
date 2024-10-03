#pragma once

#include <vulkan/vulkan.h>
#include <vector>

namespace vk{class Structure;}
namespace vk::structure{class Physical;}
namespace vk::queue::structure{class Queue;}


namespace vk::device::queue{

class Assignment
{
public:
  //Constructor / Destructor
  Assignment(vk::Structure* vk_struct);
  ~Assignment();

public:
  //Main function
  void assign_queue();

  //Subfunction
  void assign_graphics_queue();
  void assign_presentation_queue();
  void assign_transfer_queue();
  void check_proper_assigment();

private:
  vk::Structure* vk_struct;
};

}
