#pragma once

#include "Task.h"
#include "Color.h"
#include "../core/imgui.h"

#include <glm/glm.hpp>
#include <array>
#include <map>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>


namespace ImProfil{

struct FrameData{
  std::vector<ImProfil::Graph_task> tasks;
  std::vector<size_t> taskStatsIndex;
};
struct TaskStats{
  double maxTime;
  size_t priorityOrder;
  size_t onScreenIndex;
};
inline glm::vec2 Vec2(ImVec2 vec){return glm::vec2(vec.x, vec.y);}

class Graph
{
public:
  Graph(size_t framesCount);
  void LoadFrameData(const std::vector<ImProfil::Graph_task>& tasks);
  void RenderTimings(int graphWidth, int legendWidth, int height, int frameIndexOffset);

  int frame_width;
  int frame_spacing;
  bool use_colored_legend_text;
  float maxFrameTime = 1.0f / 30.0f;

private:
  void RebuildTaskStats(size_t endFrame, size_t framesCount);
  void RenderGraph(ImDrawList *drawList, glm::vec2 graphPos, glm::vec2 graphSize, size_t frameIndexOffset);
  void RenderLegend(ImDrawList *drawList, glm::vec2 legendPos, glm::vec2 legendSize, size_t frameIndexOffset);

  void Rect(ImDrawList *drawList, glm::vec2 minPoint, glm::vec2 maxPoint, uint32_t col, bool filled);
  void Text(ImDrawList *drawList, glm::vec2 point, uint32_t col, const char *text);
  void Triangle(ImDrawList *drawList, std::array<glm::vec2, 3> points, uint32_t col, bool filled);
  void RenderTaskMarker(ImDrawList *drawList, glm::vec2 leftMinPoint, glm::vec2 leftMaxPoint, glm::vec2 rightMinPoint, glm::vec2 rightMaxPoint, uint32_t col);

  std::vector<TaskStats> taskStats;
  std::map<std::string, size_t> taskNameToStatsIndex;
  std::vector<FrameData> frames;
  size_t currFrameIndex = 0;
};

}
