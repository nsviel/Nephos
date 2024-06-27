#pragma once

#include <glm/glm.hpp>

namespace vk{class Structure;}


namespace vk::window{

class GLFW
{
public:
  //Constructor / Destructor
  GLFW(vk::Structure* vk_struct);
  ~GLFW();

public:
  //Main function
  void init();
  void loop();
  void clean();

  //Window function
  void create_window();
  void window_closing();
  void destroy_window();
  void create_surface();

  //Sizing function
  bool is_window_resized();
  void update_window_dim();
  void set_window_constraint_min(glm::vec2 constraint);
  void set_window_constraint_max(glm::vec2 constraint);

  //Input function
  void wait_event();
  void window_poll_event();
  void set_mouse_pose(glm::vec2 pos);
  glm::vec2 get_mouse_pose();
  glm::vec2 get_dimension();

private:
  vk::Structure* vk_struct;
};

}
