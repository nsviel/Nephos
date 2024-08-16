#pragma once

#include "Bar.h"
#include "Stat.h"
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <map>


namespace utl::improfil{

struct Configuration{
  //---------------------------

  std::map<std::string, std::size_t> map_idx;
  std::vector<utl::improfil::Stat> vec_stat;
  std::vector<utl::improfil::Bar> vec_bar;
  std::size_t current_idx = 0;

  glm::vec2 graph_dim;
  glm::vec2 graph_pose;
  glm::vec2 legend_dim;
  glm::vec2 legend_pose;

  float max_time_s = 50.0f / 1000.0f;
  int legend_width = 200;
  int bar_max_nb = 400;
  int bar_max_nb_task = 100;
  int bar_width = 4;
  int bar_gap = 0;

  //---------------------------
};

}
