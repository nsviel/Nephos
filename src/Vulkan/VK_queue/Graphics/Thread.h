#pragma once

#include <Utility/Element/Thread/Worker.h>
#include <vulkan/vulkan.h>
#include <vector>
#include <queue>

namespace vk{class Structure;}
namespace vk::structure{class Command;}
namespace vk::queue::graphics{class Submission;}


namespace vk::queue::graphics{

class Thread : public utl::thread::Worker
{
public:
  //Constructor / Destructor
  Thread(vk::Structure* vk_struct);
  ~Thread();

public:
  //Main function
  void thread_init();
  void thread_loop();
  void thread_pause(bool value);

  //Subfunction
  void add_command(vk::structure::Command* command);
  void add_command(std::vector<vk::structure::Command*> vec_command);
  void add_presentation(std::vector<vk::structure::Command*> vec_command);

private:
  vk::Structure* vk_struct;
  vk::queue::graphics::Submission* vk_submission;

  std::queue<std::vector<vk::structure::Command*>> queue;
  bool with_presentation = false;
  bool pause = false;
};

}
