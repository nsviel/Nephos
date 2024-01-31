#include "Graph.h"

#include <GUI/Utils/TimeSerie/Namespace.h>


namespace utl::gui::serie{

//Constructor
Graph::Graph(){
  //---------------------------

  this->frame_size = 300;
  this->frame_max_task = 100;
  this->vec_frame.resize(frame_size);
  for(auto &frame : vec_frame){
    frame.tasks.reserve(frame_max_task);
  }
  this->legend_width = 200;
  this->frame_width = 1;
  this->frame_spacing = 1;
  this->border_color = vec4(255, 255, 255, 0);

  //---------------------------
}

//Main function
void Graph::load_frame_data(const std::vector<utl::gui::serie::Graph_task>& tasks){
  //---------------------------

  size_t count = tasks.size();
  auto &current_frame = vec_frame[current_frame_idx];
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
  current_frame_idx = (current_frame_idx + 1) % vec_frame.size();

  this->rebuild_task_stats(current_frame_idx, frame_size);

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
    size_t frame_idx = (frame_end - 1 - frame_number + vec_frame.size()) % vec_frame.size();
    auto &frame = vec_frame[frame_idx];

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
void Graph::render_graph(ImVec2 size){
  const glm::vec2 widget_pose = glm::vec2(ImGui::GetCursorScreenPos().x, ImGui::GetCursorScreenPos().y);
  //---------------------------

  this->graph_dim.x = int(size.x) - legend_width;
  this->graph_dim.y = int(size.y);
  this->graph_pose = widget_pose;

  this->legend_dim = glm::vec2(legend_width, graph_dim.y);
  this->legend_pose = widget_pose + glm::vec2(graph_dim.x, 0.0f);

  ImDrawList* draw_list = ImGui::GetWindowDrawList();
  this->render_serie(draw_list);
  this->render_legend(draw_list);

  //---------------------------
}
void Graph::render_serie(ImDrawList *draw_list){
  //---------------------------

  //Serie outline
  this->draw_rect(draw_list, graph_pose, graph_pose + graph_dim, border_color, false);

  //Line to see objective
  this->draw_line(draw_list, graph_dim.x, 0.5, vec4(255, 255, 255, 255));

  float height_threshold = 1.0f;
  for(int i=0; i<vec_frame.size(); i++){
    //Get frame index compared to the current frame
    size_t frame_idx = (current_frame_idx - 1 - i + 2 * vec_frame.size()) % vec_frame.size();

    // Calculate the position of the frame
    float x_offset = graph_dim.x - 1 - frame_width - (frame_width + frame_spacing) * i;
    float y_offset = graph_dim.y - 1;
    glm::vec2 offset(x_offset, y_offset);
    glm::vec2 frame_pose = graph_pose + offset;
    if(frame_pose.x < graph_pose.x + 1){
      break;
    }

    // Iterate through each task in the ith frame
    Frame_data& frame = vec_frame[frame_idx];
    for(const auto& task : frame.tasks){
      // Calculate the heights based on task start and end times
      float task_start_height = (float(task.start_time) / max_frame_time) * graph_dim.y;
      float task_end_height = (float(task.end_time) / max_frame_time) * graph_dim.y;

      if(abs(task_end_height - task_start_height) > height_threshold){
        glm::vec2 rect_start = frame_pose + glm::vec2(0.0f, -task_start_height);
        glm::vec2 rect_end = frame_pose + glm::vec2(frame_width, -task_end_height);
        this->draw_rect(draw_list, rect_start, rect_end, task.color, true);
      }
    }
  }

  //---------------------------
}
void Graph::render_legend(ImDrawList *draw_list){
  //---------------------------

  float markerLeftRectMargin = 3.0f;
  float markerLeftRectWidth = 5.0f;
  float max_frame_time = 1.0f / 30.0f;
  float markerMidWidth = 30.0f;
  float markerRightRectWidth = 10.0f;
  float markerRigthRectMargin = 3.0f;
  float markerRightRectHeight = 10.0f;
  float markerRightRectSpacing = 4.0f;

  auto &current_frame = vec_frame[(current_frame_idx - 1 + 2 * vec_frame.size()) % vec_frame.size()];
  size_t maxTasksCount = size_t(graph_dim.y / (markerRightRectHeight + markerRightRectSpacing));

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

    float task_start_height = (float(task.start_time) / max_frame_time) * graph_dim.y;
    float task_end_height = (float(task.end_time) / max_frame_time) * graph_dim.y;
    glm::vec2 markerLeftRectMin = legend_pose + glm::vec2(markerLeftRectMargin, graph_dim.y);
    glm::vec2 markerLeftRectMax = markerLeftRectMin + glm::vec2(markerLeftRectWidth, 0.0f);
    markerLeftRectMin.y -= task_start_height;
    markerLeftRectMax.y -= task_end_height;
    glm::vec2 markerRightRectMin = legend_pose + glm::vec2(markerLeftRectMargin + markerLeftRectWidth + markerMidWidth, graph_dim.y - markerRigthRectMargin - (markerRightRectHeight + markerRightRectSpacing) * stat.on_screen_index);
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

//Primitives
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
