#include "Graph.h"

#include <GUI/Utils/TimeSerie/Namespace.h>


namespace utl::gui::serie{

//Constructor
Graph::Graph(){
  //---------------------------

  this->frame_size = 300;
  this->frame_max_task = 100;
  this->frames.resize(frame_size);
  for(auto &frame : frames){
    frame.tasks.reserve(frame_max_task);
  }

  this->frame_width = 1;
  this->frame_spacing = 1;
  this->border_color = vec4(255, 255, 255, 255);

  //---------------------------
}

//Main function
void Graph::load_frame_data(const std::vector<utl::gui::serie::Graph_task>& tasks){
  //---------------------------

  size_t count = tasks.size();
  auto &current_frame = frames[current_frame_index];
  current_frame.tasks.resize(0);
  for(size_t task_index = 0; task_index < count; task_index++){
    if(task_index == 0)
      current_frame.tasks.push_back(tasks[task_index]);
    else{
      if(tasks[task_index - 1].color != tasks[task_index].color || tasks[task_index - 1].name != tasks[task_index].name){
        current_frame.tasks.push_back(tasks[task_index]);
      }
      else{
        current_frame.tasks.back().end_time = tasks[task_index].end_time;
      }
    }
  }
  current_frame.task_stat_index.resize(current_frame.tasks.size());

  for(size_t task_index = 0; task_index < current_frame.tasks.size(); task_index++){
    auto &task = current_frame.tasks[task_index];
    auto it = task_name_to_stat_index.find(task.name);
    if(it == task_name_to_stat_index.end()){
      task_name_to_stat_index[task.name] = vec_task_stat.size();
      Task_stats task_stats;
      task_stats.max_time = -1.0;
      vec_task_stat.push_back(task_stats);
    }
    current_frame.task_stat_index[task_index] = task_name_to_stat_index[task.name];
  }
  current_frame_index = (current_frame_index + 1) % frames.size();

  this->rebuild_task_stats(current_frame_index, frame_size);

  //---------------------------
}
void Graph::rebuild_task_stats(size_t frame_end, size_t framesCount){
  //---------------------------

  //Reset task
  for(auto &task_stat : vec_task_stat){
    task_stat.max_time = -1.0f;
    task_stat.priority_order = size_t(-1);
    task_stat.on_screen_index = size_t(-1);
  }

  for(size_t frame_number=0; frame_number<framesCount; frame_number++){
    size_t frame_index = (frame_end - 1 - frame_number + frames.size()) % frames.size();
    auto &frame = frames[frame_index];

    for(size_t task_index=0; task_index<frame.tasks.size(); task_index++){
      auto &task = frame.tasks[task_index];
      auto &stats = vec_task_stat[frame.task_stat_index[task_index]];
      stats.max_time = std::max(stats.max_time, task.end_time - task.start_time);
    }
  }

  //Reorder task according to their priority
  std::vector<size_t> stat_priority;
  stat_priority.resize(vec_task_stat.size());
  for(size_t stat_index = 0; stat_index < vec_task_stat.size(); stat_index++){
    stat_priority[stat_index] = stat_index;
  }

  std::sort(stat_priority.begin(), stat_priority.end(), [this](size_t left, size_t right) {return vec_task_stat[left].max_time > vec_task_stat[right].max_time; });
  for(size_t stat_number = 0; stat_number < vec_task_stat.size(); stat_number++){
    size_t stat_index = stat_priority[stat_number];
    vec_task_stat[stat_index].priority_order = stat_number;
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
  this->draw_line(draw_list, graph_size.x, 0.5, vec4(255, 255, 255, 255));
  float heightThreshold = 1.0f;

  for(size_t frame_number = 0; frame_number < frames.size(); frame_number++){
    size_t frame_index = (current_frame_index - 1 - frame_number + 2 * frames.size()) % frames.size();

    glm::vec2 framePos = graph_pose + glm::vec2(graph_size.x - 1 - frame_width - (frame_width + frame_spacing) * frame_number, graph_size.y - 1);
    if(framePos.x < graph_pose.x + 1){
      break;
    }

    glm::vec2 taskPos = framePos + glm::vec2(0.0f, 0.0f);
    auto &frame = frames[frame_index];
    for(const auto& task : frame.tasks){
      float taskStartHeight = (float(task.start_time) / max_frame_time) * graph_size.y;
      float taskEndHeight = (float(task.end_time) / max_frame_time) * graph_size.y;
      //taskMaxCosts[task.name] = std::max(taskMaxCosts[task.name], task.end_time - task.start_time);
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
  float max_frame_time = 1.0f / 30.0f;
  float markerMidWidth = 30.0f;
  float markerRightRectWidth = 10.0f;
  float markerRigthRectMargin = 3.0f;
  float markerRightRectHeight = 10.0f;
  float markerRightRectSpacing = 4.0f;

  auto &current_frame = frames[(current_frame_index - 1 + 2 * frames.size()) % frames.size()];
  size_t maxTasksCount = size_t(legendSize.y / (markerRightRectHeight + markerRightRectSpacing));

  for(auto &task_stat : vec_task_stat){
    task_stat.on_screen_index = size_t(-1);
  }

  size_t tasksToShow = std::min<size_t>(vec_task_stat.size(), maxTasksCount);
  size_t tasksShownCount = 0;
  for(size_t task_index = 0; task_index < current_frame.tasks.size(); task_index++){
    utl::gui::serie::Graph_task& task = current_frame.tasks[task_index];
    auto &stat = vec_task_stat[current_frame.task_stat_index[task_index]];

    if(stat.priority_order >= tasksToShow){
      continue;
    }

    if(stat.on_screen_index == size_t(-1)){
      stat.on_screen_index = tasksShownCount++;
    }
    else{
      continue;
    }

    float taskStartHeight = (float(task.start_time) / max_frame_time) * legendSize.y;
    float taskEndHeight = (float(task.end_time) / max_frame_time) * legendSize.y;
    glm::vec2 markerLeftRectMin = legendPos + glm::vec2(markerLeftRectMargin, legendSize.y);
    glm::vec2 markerLeftRectMax = markerLeftRectMin + glm::vec2(markerLeftRectWidth, 0.0f);
    markerLeftRectMin.y -= taskStartHeight;
    markerLeftRectMax.y -= taskEndHeight;
    glm::vec2 markerRightRectMin = legendPos + glm::vec2(markerLeftRectMargin + markerLeftRectWidth + markerMidWidth, legendSize.y - markerRigthRectMargin - (markerRightRectHeight + markerRightRectSpacing) * stat.on_screen_index);
    glm::vec2 markerRightRectMax = markerRightRectMin + glm::vec2(markerRightRectWidth, -markerRightRectHeight);

    this->render_task_marker(draw_list, markerLeftRectMin, markerLeftRectMax, markerRightRectMin, markerRightRectMax, task.color);
    this->render_legend_text(draw_list, markerRightRectMax, task.color, task);
  }

  //---------------------------
}
void Graph::render_task_marker(ImDrawList *draw_list, glm::vec2 leftMinPoint, glm::vec2 leftMaxPoint, glm::vec2 rightMinPoint, glm::vec2 rightMaxPoint, vec4 color){
  //---------------------------

  this->draw_rect(draw_list, leftMinPoint, leftMaxPoint, color, true);
  this->draw_rect(draw_list, rightMinPoint, rightMaxPoint, color, true);
  std::array<ImVec2, 4> points = {
    ImVec2(leftMaxPoint.x, leftMinPoint.y),
    ImVec2(leftMaxPoint.x, leftMaxPoint.y),
    ImVec2(rightMinPoint.x, rightMaxPoint.y),
    ImVec2(rightMinPoint.x, rightMinPoint.y)
  };
  draw_list->AddConvexPolyFilled(points.data(), int(points.size()), IM_COL32(color.x, color.y, color.z, color.w));

  //---------------------------
}
void Graph::render_legend_text(ImDrawList *draw_list, glm::vec2 rightMaxPoint, vec4 col, utl::gui::serie::Graph_task task){
  //---------------------------

  glm::vec2 textMargin = glm::vec2(5.0f, -3.0f);
  float nameOffset = 40.0f;

  vec4 textColor = task.color;

  float taskTimeMs = float(task.end_time - task.start_time);
  std::ostringstream timeText;
  timeText.precision(2);
  timeText << std::fixed << std::string("[") << (taskTimeMs * 1000.0f);

  this->draw_text(draw_list, rightMaxPoint + textMargin, textColor, timeText.str().c_str());
  this->draw_text(draw_list, rightMaxPoint + textMargin + glm::vec2(nameOffset, 0.0f), textColor, (std::string("ms] ") + task.name).c_str());

  //---------------------------
}

//Element
void Graph::draw_line(ImDrawList *draw_list, float width, float height, vec4 color){
  //---------------------------

  draw_list->AddRectFilled(ImVec2(0, height), ImVec2(width, height + 1), IM_COL32(color.x, color.y, color.z, color.w));

  //---------------------------
}
void Graph::draw_rect(ImDrawList *draw_list, glm::vec2 minPoint, glm::vec2 maxPoint, vec4 color, bool filled = true){
  //---------------------------

  if(filled)
    draw_list->AddRectFilled(ImVec2(minPoint.x, minPoint.y), ImVec2(maxPoint.x, maxPoint.y), IM_COL32(color.x, color.y, color.z, color.w));
  else
    draw_list->AddRect(ImVec2(minPoint.x, minPoint.y), ImVec2(maxPoint.x, maxPoint.y), IM_COL32(color.x, color.y, color.z, color.w));

  //---------------------------
}
void Graph::draw_text(ImDrawList *draw_list, glm::vec2 point, vec4 color, const char *text){
  //---------------------------

  draw_list->AddText(ImVec2(point.x, point.y), IM_COL32(color.x, color.y, color.z, color.w), text);

  //---------------------------
}
void Graph::draw_triangle(ImDrawList *draw_list, std::array<glm::vec2, 3> points, vec4 color, bool filled = true){
  //---------------------------

  if(filled)
    draw_list->AddTriangleFilled(ImVec2(points[0].x, points[0].y), ImVec2(points[1].x, points[1].y), ImVec2(points[2].x, points[2].y), IM_COL32(color.x, color.y, color.z, color.w));
  else
    draw_list->AddTriangle(ImVec2(points[0].x, points[0].y), ImVec2(points[1].x, points[1].y), ImVec2(points[2].x, points[2].y), IM_COL32(color.x, color.y, color.z, color.w));

  //---------------------------
}

}
