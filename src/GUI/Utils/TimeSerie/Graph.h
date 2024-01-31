#pragma once

#include <GUI/Utils/TimeSerie/Namespace.h>
#include <Utility/Specific/common.h>

namespace utl::gui::serie{class Graph_task;}


namespace utl::gui::serie{

class Graph
{
public:
  //Constructor
  Graph();

public:
  //Main function
  void load_graph_data(const std::vector<utl::gui::serie::Graph_task>& vec_task);
  void rebuild_task_stats(size_t endFrame);

  //Rendering
  void render_graph(ImVec2 size);
  void render_serie(ImDrawList *draw_list);
  void render_legend(ImDrawList *draw_list);
  void render_legend_marker(ImDrawList *draw_list, glm::vec2 leftMinPoint, glm::vec2 leftMaxPoint, glm::vec2 rightMinPoint, glm::vec2 rightMaxPoint, vec4 col);
  void render_legend_text(ImDrawList *draw_list, glm::vec2 rightMaxPoint, vec4 col, utl::gui::serie::Graph_task task);

private:
  //Primitives
  void draw_line(ImDrawList *draw_list, float width, float height, vec4 color);
  void draw_rect(ImDrawList *draw_list, glm::vec2 minPoint, glm::vec2 maxPoint, vec4 color, bool filled);
  void draw_text(ImDrawList *draw_list, glm::vec2 point, vec4 col, const char *text);
  void draw_triangle(ImDrawList *draw_list, std::array<glm::vec2, 3> points, vec4 color, bool filled);

private:
  std::vector<Task_stats> vec_task_stat;
  std::map<std::string, size_t> task_name_to_stat_index;
  std::vector<utl::gui::serie::Bar> vec_bar;
  size_t current_frame_idx = 0;
  vec4 border_color;
  vec2 graph_dim;
  vec2 graph_pose;
  vec2 legend_dim;
  vec2 legend_pose;
  int bar_max_nb;
  int bar_max_nb_task;
  int bar_width;
  int bar_gap;
  float max_frame_time = 1.0f / 30.0f;
  int legend_width;
};

}
