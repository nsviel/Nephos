#pragma once

#include "Structure/Configuration.h"
#include <Utility/GUI/Plot/Namespace.h>
#include <Utility/Specific/Common.h>

namespace utl::improfil{class Bar;}
namespace utl::improfil{class Stat;}
namespace prf::graph::structure{class Task;}


namespace utl::improfil{

class Renderer
{
public:
  //Constructor
  Renderer();
  ~Renderer();

public:
  //Main function
  void load_graph_data(const std::vector<utl::improfil::Task>& vec_task);
  void render_graph(ImVec2 size);
  void rebuild_task_stats(size_t endFrame);

  inline float* get_max_time(){return &config.max_time_s;}

private:
  //Render
  void render_serie(ImDrawList *draw_list);
  void render_legend(ImDrawList *draw_list);

  //Subfunction
  void render_background_tics(ImDrawList *draw_list);
  void render_serie_task_rect(ImDrawList *draw_list, utl::improfil::Task& task, glm::vec2 bar_pose);
  void render_legend_marker(ImDrawList *draw_list, glm::vec2 leftMinPoint, glm::vec2 leftMaxPoint, glm::vec2 rightMinPoint, glm::vec2 rightMaxPoint, vec4 col);
  void render_legend_text(ImDrawList *draw_list, glm::vec2 rightMaxPoint, vec4 col, utl::improfil::Task task);

  //Primitives
  void draw_line_at_time(ImDrawList *draw_list, float time_ms, float thickness, vec4 color);
  void draw_zone(ImDrawList *draw_list, float ts_begin_ms, float ts_end_ms, vec4 color);
  void draw_rect(ImDrawList *draw_list, glm::vec2 minPoint, glm::vec2 maxPoint, vec4 color, bool filled);
  void draw_text(ImDrawList *draw_list, glm::vec2 point, vec4 col, const char *text);
  void draw_triangle(ImDrawList *draw_list, std::array<glm::vec2, 3> points, vec4 color, bool filled);

private:
  utl::improfil::Configuration config;
};

}
