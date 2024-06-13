#pragma once

#include <Utility/Specific/Common.h>

namespace vld{class Node;}
namespace vk::image{class Screenshot;}


namespace vld::thread{

class Screenshot
{
public:
  //Constructor / Destructor
  Screenshot(vld::Node* node_vld);
  ~Screenshot();

public:
  //Main function
  void start_thread();
  void run_thread();
  void stop_thread();

private:
  vk::image::Screenshot* vk_screenshot;

  std::thread thread;
  bool thread_running = false;
  bool thread_idle = true;
};

}
