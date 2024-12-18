#pragma once

namespace vk::device{class Physical;}
namespace vk{class Structure;}
namespace vk::device::queue{class Manager;}


namespace vk::device{

class Logical
{
public:
  //Constructor / Destructor
  Logical(vk::Structure* vk_struct);
  ~Logical();

public:
  //Main function
  void init();
  void clean();

  //Subfunction
  void create_logical_device();
  void create_device_queue();

private:
  vk::Structure* vk_struct;
  vk::device::Physical* vk_dev_physical;
  vk::device::queue::Manager* vk_queue;
};

}
