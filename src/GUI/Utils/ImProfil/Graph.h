#pragma once

#include <GUI/Utils/ImProfil/Namespace.h>
#include <Utility/Specific/common.h>

namespace utl::improfil{class Task;}


namespace utl::improfil{

class Graph
{
public:
  //Constructor
  Graph();

public:
  //Main function
  void load_graph_data(const std::vector<utl::improfil::Task>& vec_task);
  void rebuild_task_stats(size_t endFrame);

  //Rendering
  void render_graph(ImVec2 size);
  void render_serie(ImDrawList *draw_list);
  void render_legend(ImDrawList *draw_list);

  //Subfunction
  void render_legend_marker(ImDrawList *draw_list, glm::vec2 leftMinPoint, glm::vec2 leftMaxPoint, glm::vec2 rightMinPoint, glm::vec2 rightMaxPoint, vec4 col);
  void render_legend_text(ImDrawList *draw_list, glm::vec2 rightMaxPoint, vec4 col, utl::improfil::Task task);

private:
  //Primitives
  void draw_line_at_time(ImDrawList *draw_list, float time_ms, vec4 color);
  void draw_rect(ImDrawList *draw_list, glm::vec2 minPoint, glm::vec2 maxPoint, vec4 color, bool filled);
  void draw_text(ImDrawList *draw_list, glm::vec2 point, vec4 col, const char *text);
  void draw_triangle(ImDrawList *draw_list, std::array<glm::vec2, 3> points, vec4 color, bool filled);

private:
  std::vector<Stat> vec_stat;
  std::map<std::string, size_t> map_task_to_stat_idx;
  std::vector<utl::improfil::Bar> vec_bar;
  size_t current_bar_idx = 0;
  vec4 border_color;
  vec2 graph_dim;
  vec2 graph_pose;
  vec2 legend_dim;
  vec2 legend_pose;
  float max_time_s;
  int legend_width;
  int bar_max_nb;
  int bar_max_nb_task;
  int bar_width;
  int bar_gap;
};

}
