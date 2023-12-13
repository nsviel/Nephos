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

  static void Rect(ImDrawList *drawList, glm::vec2 minPoint, glm::vec2 maxPoint, uint32_t col, bool filled = true){
    if(filled)
      drawList->AddRectFilled(ImVec2(minPoint.x, minPoint.y), ImVec2(maxPoint.x, maxPoint.y), col);
    else
      drawList->AddRect(ImVec2(minPoint.x, minPoint.y), ImVec2(maxPoint.x, maxPoint.y), col);
  }
  static void Text(ImDrawList *drawList, glm::vec2 point, uint32_t col, const char *text){
    drawList->AddText(ImVec2(point.x, point.y), col, text);
  }
  static void Triangle(ImDrawList *drawList, std::array<glm::vec2, 3> points, uint32_t col, bool filled = true){
    if (filled)
      drawList->AddTriangleFilled(ImVec2(points[0].x, points[0].y), ImVec2(points[1].x, points[1].y), ImVec2(points[2].x, points[2].y), col);
    else
      drawList->AddTriangle(ImVec2(points[0].x, points[0].y), ImVec2(points[1].x, points[1].y), ImVec2(points[2].x, points[2].y), col);
  }
  static void RenderTaskMarker(ImDrawList *drawList, glm::vec2 leftMinPoint, glm::vec2 leftMaxPoint, glm::vec2 rightMinPoint, glm::vec2 rightMaxPoint, uint32_t col){
    Rect(drawList, leftMinPoint, leftMaxPoint, col, true);
    Rect(drawList, rightMinPoint, rightMaxPoint, col, true);
    std::array<ImVec2, 4> points = {
      ImVec2(leftMaxPoint.x, leftMinPoint.y),
      ImVec2(leftMaxPoint.x, leftMaxPoint.y),
      ImVec2(rightMinPoint.x, rightMaxPoint.y),
      ImVec2(rightMinPoint.x, rightMinPoint.y)
    };
    drawList->AddConvexPolyFilled(points.data(), int(points.size()), col);
  }

  struct FrameData{
    /*void BuildPriorityTasks(size_t maxPriorityTasksCount)
    {
      priorityTaskIndices.clear();
      std::set<std::string> usedTaskNames;

      for (size_t priorityIndex = 0; priorityIndex < maxPriorityTasksCount; priorityIndex++)
      {
        size_t bestTaskIndex = size_t(-1);
        for (size_t taskIndex = 0; taskIndex < tasks.size(); taskIndex++)
        {
          auto &task = tasks[taskIndex];
          auto it = usedTaskNames.find(tasks[taskIndex].name);
          if (it == usedTaskNames.end() && (bestTaskIndex == size_t(-1) || tasks[bestTaskIndex].GetLength() < task.GetLength()))
          {
            bestTaskIndex = taskIndex;
          }
        }
        if (bestTaskIndex == size_t(-1))
          break;
        priorityTaskIndices.push_back(bestTaskIndex);
        usedTaskNames.insert(tasks[bestTaskIndex].name);
      }
    }*/
    std::vector<ImProfil::Graph_task> tasks;
    std::vector<size_t> taskStatsIndex;
    //std::vector<size_t> priorityTaskIndices;
  };
  struct TaskStats{
    double maxTime;
    size_t priorityOrder;
    size_t onScreenIndex;
  };

  std::vector<TaskStats> taskStats;
  std::map<std::string, size_t> taskNameToStatsIndex;
  std::vector<FrameData> frames;
  size_t currFrameIndex = 0;
};

}
