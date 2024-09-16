#pragma once

#include <glm/glm.hpp>

namespace vk{class Structure;}


namespace vk::window{

class Event
{
public:
  //Constructor / Destructor
  Event(vk::Structure* vk_struct);
  ~Event();

public:
  //Main function
  void wait_event();
  void window_close_event();
  void window_poll_event();

private:
  vk::Structure* vk_struct;
};

}
