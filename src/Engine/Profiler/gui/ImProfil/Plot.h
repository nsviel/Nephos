#pragma once

#include <Utility/GUI/Plot/Namespace.h>
#include <Utility/Specific/Common.h>

namespace prf::improfil{class Renderer;}
namespace prf::graph::structure{class Task;}


namespace prf::improfil{

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
  void add_task(float ts_begin, float ts_end, string name, glm::vec4 color = {});
  void add_vec_task(std::vector<prf::graph::structure::Task> vec_task);

  //Subfunction
  vec4 get_next_color();
  void set_time_max(int value);


private:
  prf::improfil::Renderer* renderer;
  vector<prf::graph::structure::Task> vec_task;
  vector<vec4> vec_color;
  string name = "";
  int idx_color;
  int max_nb_data;
};

}
