#pragma once

#include <glm/glm.hpp>

namespace vk{class Structure;}


namespace vk::window{

class Window
{
public:
  //Constructor / Destructor
  Window(vk::Structure* vk_struct);
  ~Window();

public:
  //Main function
  void create_window();
  void destroy_window();
  void create_surface();

  //Subfunction
  bool is_window_resized();
  void update_window_dim();
  void set_window_constraint_min(glm::vec2 constraint);
  void set_window_constraint_max(glm::vec2 constraint);
  void set_mouse_pose(glm::vec2 pos);
  glm::vec2 get_mouse_pose();
  glm::vec2 get_dimension();

private:
  vk::Structure* vk_struct;
};

}
