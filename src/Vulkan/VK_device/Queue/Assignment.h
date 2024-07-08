#pragma once

#include <vulkan/vulkan.h>
#include <vector>

namespace vk{class Structure;}
namespace vk::device::structure{class Physical;}
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
  void find_queue_family_assigment();

  //Subfunction
  void find_graphics_queue();
  void find_presentation_queue();
  void find_transfer_queue();
  void check_proper_assigment();

private:
  vk::Structure* vk_struct;
};

}
