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
  void load_frame_data(const std::vector<utl::gui::serie::Graph_task>& tasks);
  void rebuild_task_stats(size_t endFrame, size_t framesCount);

  //Rendering
  void render_timings(int graphWidth, int legendWidth, int height);
  void render_graph(ImDrawList *draw_list, glm::vec2 graphPos, glm::vec2 graphSize);
  void render_legend(ImDrawList *draw_list, glm::vec2 legendPos, glm::vec2 legendSize);
  void render_task_marker(ImDrawList *draw_list, glm::vec2 leftMinPoint, glm::vec2 leftMaxPoint, glm::vec2 rightMinPoint, glm::vec2 rightMaxPoint, uint32_t col);
  void render_legend_text(ImDrawList *draw_list, glm::vec2 rightMaxPoint, uint32_t col, utl::gui::serie::Graph_task task);

private:
  void draw_line(ImDrawList *draw_list, float width, float height, uint32_t color);
  void draw_rect(ImDrawList *draw_list, glm::vec2 minPoint, glm::vec2 maxPoint, uint32_t col, bool filled);
  void draw_text(ImDrawList *draw_list, glm::vec2 point, uint32_t col, const char *text);
  void draw_triangle(ImDrawList *draw_list, std::array<glm::vec2, 3> points, uint32_t col, bool filled);

private:
  std::vector<Task_stats> task_stats;
  std::map<std::string, size_t> taskNameToStatsIndex;
  std::vector<Frame_data> frames;
  size_t current_frameIndex = 0;
  int border_color;
  int frame_size;
  int frame_max_task;
  int frame_width;
  int frame_spacing;
  float maxFrameTime = 1.0f / 30.0f;
};

}
