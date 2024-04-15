#pragma once

#include <Utility/Specific/Common.h>

namespace vk::structure{class Vulkan;}


namespace vk::window{

class GLFW
{
public:
  //Constructor / Destructor
  GLFW(vk::structure::Vulkan* vk_struct);
  ~GLFW();

public:
  //Main functions
  void init();
  void loop();
  void clean();

  //Window function
  void create_window();
  void close_window();
  void destroy_window();
  bool window_should_close();

  //Sizing function
  vec2 compute_window_dim();
  bool check_for_resizing();
  void set_window_constraint_min(int width, int height);
  void set_window_constraint_max(int width, int height);

  //Input function
  void manage_input();
  glm::vec2 get_mouse_pose();
  glm::vec2 get_dimension();
  glm::vec2 get_center();
  void set_center(vec2 value);
  void set_mouse_pose(glm::vec2 pos);

private:
  vk::structure::Vulkan* vk_struct;
};

}
