#include "Graph.h"

#include <GUI/Utils/TimeSerie/Namespace.h>


namespace utl::gui::serie{

//Constructor
Graph::Graph(size_t frame_size){
  //---------------------------

  this->frame_max_task = 100;
  this->frames.resize(frame_size);
  for(auto &frame : frames){
    frame.tasks.reserve(frame_max_task);
  }

  this->frame_size = frame_size;
  this->frame_width = 1;
  this->frame_spacing = 1;
  this->use_colored_legend_text = true;
  this->border_color = 0x00ffffff;

  //---------------------------
}

//Main function
void Graph::load_frame_data(const std::vector<utl::gui::serie::Graph_task>& tasks){
  //---------------------------

  size_t count = tasks.size();
  auto &current_frame = frames[current_frameIndex];
  current_frame.tasks.resize(0);
  for (size_t taskIndex = 0; taskIndex < count; taskIndex++){
    if(taskIndex == 0)
      current_frame.tasks.push_back(tasks[taskIndex]);
    else{
      if(tasks[taskIndex - 1].color != tasks[taskIndex].color || tasks[taskIndex - 1].name != tasks[taskIndex].name){
        current_frame.tasks.push_back(tasks[taskIndex]);
      }
      else{
        current_frame.tasks.back().endTime = tasks[taskIndex].endTime;
      }
    }
  }
  current_frame.taskStatsIndex.resize(current_frame.tasks.size());

  for (size_t taskIndex = 0; taskIndex < current_frame.tasks.size(); taskIndex++){
    auto &task = current_frame.tasks[taskIndex];
    auto it = taskNameToStatsIndex.find(task.name);
    if(it == taskNameToStatsIndex.end()){
      taskNameToStatsIndex[task.name] = taskStats.size();
      Task_stats taskStat;
      taskStat.maxTime = -1.0;
      taskStats.push_back(taskStat);
    }
    current_frame.taskStatsIndex[taskIndex] = taskNameToStatsIndex[task.name];
  }
  current_frameIndex = (current_frameIndex + 1) % frames.size();

  this->rebuild_task_stats(current_frameIndex, frame_size);

  //---------------------------
}
void Graph::rebuild_task_stats(size_t endFrame, size_t framesCount){
  //---------------------------

  for (auto &taskStat : taskStats){
    taskStat.maxTime = -1.0f;
    taskStat.priorityOrder = size_t(-1);
    taskStat.onScreenIndex = size_t(-1);
  }

  for (size_t frameNumber = 0; frameNumber < framesCount; frameNumber++){
    size_t frameIndex = (endFrame - 1 - frameNumber + frames.size()) % frames.size();
    auto &frame = frames[frameIndex];
    for (size_t taskIndex = 0; taskIndex < frame.tasks.size(); taskIndex++)
    {
      auto &task = frame.tasks[taskIndex];
      auto &stats = taskStats[frame.taskStatsIndex[taskIndex]];
      stats.maxTime = std::max(stats.maxTime, task.endTime - task.startTime);
    }
  }
  std::vector<size_t> statPriorities;
  statPriorities.resize(taskStats.size());
  for(size_t statIndex = 0; statIndex < taskStats.size(); statIndex++){
    statPriorities[statIndex] = statIndex;
  }

  std::sort(statPriorities.begin(), statPriorities.end(), [this](size_t left, size_t right) {return taskStats[left].maxTime > taskStats[right].maxTime; });
  for (size_t statNumber = 0; statNumber < taskStats.size(); statNumber++){
    size_t statIndex = statPriorities[statNumber];
    taskStats[statIndex].priorityOrder = statNumber;
  }

  //---------------------------
}

//Rendering
void Graph::render_timings(int graphWidth, int legendWidth, int height){
  //---------------------------

  ImDrawList* draw_list = ImGui::GetWindowDrawList();
  const glm::vec2 widgetPos = glm::vec2(ImGui::GetCursorScreenPos().x, ImGui::GetCursorScreenPos().y);
  this->render_graph(draw_list, widgetPos, glm::vec2(graphWidth, height));
  this->render_legend(draw_list, widgetPos + glm::vec2(graphWidth, 0.0f), glm::vec2(legendWidth, height));
  ImGui::Dummy(ImVec2(float(graphWidth + legendWidth), float(height)));

  //---------------------------
}
void Graph::render_graph(ImDrawList *draw_list, glm::vec2 graph_pose, glm::vec2 graph_size){
  //---------------------------

  this->draw_rect(draw_list, graph_pose, graph_pose + graph_size, border_color, false);
  this->draw_line(draw_list, graph_size.x, 0.5, 0xffffffff);
  float heightThreshold = 1.0f;

  for (size_t frameNumber = 0; frameNumber < frames.size(); frameNumber++){
    size_t frameIndex = (current_frameIndex - 1 - frameNumber + 2 * frames.size()) % frames.size();

    glm::vec2 framePos = graph_pose + glm::vec2(graph_size.x - 1 - frame_width - (frame_width + frame_spacing) * frameNumber, graph_size.y - 1);
    if(framePos.x < graph_pose.x + 1){
      break;
    }

    glm::vec2 taskPos = framePos + glm::vec2(0.0f, 0.0f);
    auto &frame = frames[frameIndex];
    for (const auto& task : frame.tasks){
      float taskStartHeight = (float(task.startTime) / maxFrameTime) * graph_size.y;
      float taskEndHeight = (float(task.endTime) / maxFrameTime) * graph_size.y;
      //taskMaxCosts[task.name] = std::max(taskMaxCosts[task.name], task.endTime - task.startTime);
      if(abs(taskEndHeight - taskStartHeight) > heightThreshold){
        this->draw_rect(draw_list, taskPos + glm::vec2(0.0f, -taskStartHeight), taskPos + glm::vec2(frame_width, -taskEndHeight), task.color, true);
      }
    }
  }

  //---------------------------
}
void Graph::render_legend(ImDrawList *draw_list, glm::vec2 legendPos, glm::vec2 legendSize){
  //---------------------------

  float markerLeftRectMargin = 3.0f;
  float markerLeftRectWidth = 5.0f;
  float maxFrameTime = 1.0f / 30.0f;
  float markerMidWidth = 30.0f;
  float markerRightRectWidth = 10.0f;
  float markerRigthRectMargin = 3.0f;
  float markerRightRectHeight = 10.0f;
  float markerRightRectSpacing = 4.0f;

  auto &current_frame = frames[(current_frameIndex - 1 + 2 * frames.size()) % frames.size()];
  size_t maxTasksCount = size_t(legendSize.y / (markerRightRectHeight + markerRightRectSpacing));

  for (auto &taskStat : taskStats){
    taskStat.onScreenIndex = size_t(-1);
  }

  size_t tasksToShow = std::min<size_t>(taskStats.size(), maxTasksCount);
  size_t tasksShownCount = 0;
  for(size_t taskIndex = 0; taskIndex < current_frame.tasks.size(); taskIndex++){
    utl::gui::serie::Graph_task& task = current_frame.tasks[taskIndex];
    auto &stat = taskStats[current_frame.taskStatsIndex[taskIndex]];

    if(stat.priorityOrder >= tasksToShow){
      continue;
    }

    if(stat.onScreenIndex == size_t(-1)){
      stat.onScreenIndex = tasksShownCount++;
    }
    else{
      continue;
    }

    float taskStartHeight = (float(task.startTime) / maxFrameTime) * legendSize.y;
    float taskEndHeight = (float(task.endTime) / maxFrameTime) * legendSize.y;
    glm::vec2 markerLeftRectMin = legendPos + glm::vec2(markerLeftRectMargin, legendSize.y);
    glm::vec2 markerLeftRectMax = markerLeftRectMin + glm::vec2(markerLeftRectWidth, 0.0f);
    markerLeftRectMin.y -= taskStartHeight;
    markerLeftRectMax.y -= taskEndHeight;
    glm::vec2 markerRightRectMin = legendPos + glm::vec2(markerLeftRectMargin + markerLeftRectWidth + markerMidWidth, legendSize.y - markerRigthRectMargin - (markerRightRectHeight + markerRightRectSpacing) * stat.onScreenIndex);
    glm::vec2 markerRightRectMax = markerRightRectMin + glm::vec2(markerRightRectWidth, -markerRightRectHeight);

    this->render_task_marker(draw_list, markerLeftRectMin, markerLeftRectMax, markerRightRectMin, markerRightRectMax, task.color);
    this->render_legend_text(draw_list, markerRightRectMax, task.color, task);
  }

  //---------------------------
}
void Graph::render_task_marker(ImDrawList *draw_list, glm::vec2 leftMinPoint, glm::vec2 leftMaxPoint, glm::vec2 rightMinPoint, glm::vec2 rightMaxPoint, uint32_t col){
  //---------------------------

  this->draw_rect(draw_list, leftMinPoint, leftMaxPoint, col, true);
  this->draw_rect(draw_list, rightMinPoint, rightMaxPoint, col, true);
  std::array<ImVec2, 4> points = {
    ImVec2(leftMaxPoint.x, leftMinPoint.y),
    ImVec2(leftMaxPoint.x, leftMaxPoint.y),
    ImVec2(rightMinPoint.x, rightMaxPoint.y),
    ImVec2(rightMinPoint.x, rightMinPoint.y)
  };
  draw_list->AddConvexPolyFilled(points.data(), int(points.size()), col);

  //---------------------------
}
void Graph::render_legend_text(ImDrawList *draw_list, glm::vec2 rightMaxPoint, uint32_t col, utl::gui::serie::Graph_task task){
  //---------------------------

  glm::vec2 textMargin = glm::vec2(5.0f, -3.0f);
  float nameOffset = 40.0f;

  uint32_t textColor = use_colored_legend_text ? task.color : utl::gui::serie::color::imguiText;

  float taskTimeMs = float(task.endTime - task.startTime);
  std::ostringstream timeText;
  timeText.precision(2);
  timeText << std::fixed << std::string("[") << (taskTimeMs * 1000.0f);

  this->draw_text(draw_list, rightMaxPoint + textMargin, textColor, timeText.str().c_str());
  this->draw_text(draw_list, rightMaxPoint + textMargin + glm::vec2(nameOffset, 0.0f), textColor, (std::string("ms] ") + task.name).c_str());

  //---------------------------
}

//Element
void Graph::draw_line(ImDrawList *draw_list, float width, float height, uint32_t color){
  //---------------------------

  draw_list->AddRectFilled(ImVec2(0, height), ImVec2(width, height + 1), color);

  //---------------------------
}
void Graph::draw_rect(ImDrawList *draw_list, glm::vec2 minPoint, glm::vec2 maxPoint, uint32_t color, bool filled = true){
  //---------------------------

  if(filled)
    draw_list->AddRectFilled(ImVec2(minPoint.x, minPoint.y), ImVec2(maxPoint.x, maxPoint.y), color);
  else
    draw_list->AddRect(ImVec2(minPoint.x, minPoint.y), ImVec2(maxPoint.x, maxPoint.y), color);

  //---------------------------
}
void Graph::draw_text(ImDrawList *draw_list, glm::vec2 point, uint32_t col, const char *text){
  //---------------------------

  draw_list->AddText(ImVec2(point.x, point.y), col, text);

  //---------------------------
}
void Graph::draw_triangle(ImDrawList *draw_list, std::array<glm::vec2, 3> points, uint32_t col, bool filled = true){
  //---------------------------

  if(filled)
    draw_list->AddTriangleFilled(ImVec2(points[0].x, points[0].y), ImVec2(points[1].x, points[1].y), ImVec2(points[2].x, points[2].y), col);
  else
    draw_list->AddTriangle(ImVec2(points[0].x, points[0].y), ImVec2(points[1].x, points[1].y), ImVec2(points[2].x, points[2].y), col);

  //---------------------------
}

}
