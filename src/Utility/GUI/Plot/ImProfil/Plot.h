#pragma once

#include <Utility/GUI/Plot/Namespace.h>
#include <imgui/core/imgui.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>

namespace utl::improfil{class Renderer;}


namespace utl::improfil{

class Plot{
public:
  //Constructor / Destructor
  Plot();
  Plot(std::string name);
  ~Plot();

public:
  //Main function
  void render(std::string name, ImVec2 size);
  void update();
  void reset();

  //Task function
  void add_task(float ts_begin, float ts_end, std::string name, glm::vec4 color = {});
  void add_vec_task(std::vector<utl::improfil::Task> vec_task);

  //Subfunction
  glm::vec4 get_next_color();
  void set_time_max(int value);


private:
  utl::improfil::Renderer* renderer;
  std::vector<utl::improfil::Task> vec_task;
  std::vector<glm::vec4> vec_color;
  std::string name = "";
  int idx_color;
  int max_nb_data;
};

}
