#include "Graph.h"

#include <GUI/Utils/TimeSerie/Namespace.h>


namespace utl::gui::serie{

//Constructor
Graph::Graph(){
  //---------------------------

  this->bar_max_nb = 300;
  this->bar_width = 2;
  this->bar_gap = 1;
  this->bar_max_nb_task = 100;
  this->vec_bar.resize(bar_max_nb);
  this->legend_width = 200;
  this->border_color = vec4(255, 255, 255, 0);

  for(utl::gui::serie::Bar& bar : vec_bar){
    bar.vec_task.reserve(bar_max_nb_task);
  }

  //---------------------------
}

//Main function
void Graph::load_frame_data(const std::vector<utl::gui::serie::Graph_task>& vec_task){
  //update the graph with new task data
  //---------------------------

  size_t count = vec_task.size();
  utl::gui::serie::Bar& current_frame = vec_bar[current_frame_idx];
  current_frame.vec_task.resize(0);
  for(size_t task_index = 0; task_index < count; task_index++){
    if(task_index == 0)
      current_frame.vec_task.push_back(vec_task[task_index]);
    else{
      if(vec_task[task_index - 1].color != vec_task[task_index].color || vec_task[task_index - 1].name != vec_task[task_index].name){
        current_frame.vec_task.push_back(vec_task[task_index]);
      }
      else{
        current_frame.vec_task.back().end_time = vec_task[task_index].end_time;
      }
    }
  }
  current_frame.task_stat_index.resize(current_frame.vec_task.size());

  for(size_t task_index = 0; task_index < current_frame.vec_task.size(); task_index++){
    auto &task = current_frame.vec_task[task_index];
    auto it = task_name_to_stat_index.find(task.name);
    if(it == task_name_to_stat_index.end()){
      task_name_to_stat_index[task.name] = vec_task_stat.size();
      Task_stats task_stats;
      task_stats.max_time = -1.0;
      vec_task_stat.push_back(task_stats);
    }
    current_frame.task_stat_index[task_index] = task_name_to_stat_index[task.name];
  }
  current_frame_idx = (current_frame_idx + 1) % vec_bar.size();

  this->rebuild_task_stats(current_frame_idx);

  //---------------------------
}
void Graph::rebuild_task_stats(size_t frame_end){
  //---------------------------

  //Reset task
  for(auto &task_stat : vec_task_stat){
    task_stat.max_time = -1.0f;
    task_stat.priority_order = size_t(-1);
    task_stat.on_screen_index = size_t(-1);
  }

  for(size_t frame_number=0; frame_number<bar_max_nb; frame_number++){
    size_t frame_idx = (frame_end - 1 - frame_number + vec_bar.size()) % vec_bar.size();
    utl::gui::serie::Bar& frame = vec_bar[frame_idx];

    for(size_t task_index=0; task_index<frame.vec_task.size(); task_index++){
      auto &task = frame.vec_task[task_index];
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
  for(int i=0; i<vec_bar.size(); i++){
    //Get frame index compared to the current frame
    size_t frame_idx = (current_frame_idx - 1 - i + 2 * vec_bar.size()) % vec_bar.size();

    // Calculate the position of the frame
    float x_offset = graph_dim.x - 1 - bar_width - (bar_width + bar_gap) * i;
    float y_offset = graph_dim.y - 1;
    glm::vec2 offset(x_offset, y_offset);
    glm::vec2 frame_pose = graph_pose + offset;
    if(frame_pose.x < graph_pose.x + 1){
      break;
    }

    // Iterate through each task in the ith frame
    utl::gui::serie::Bar& frame = vec_bar[frame_idx];
    for(const auto& task : frame.vec_task){
      // Calculate the heights based on task start and end times
      float task_start_height = (float(task.start_time) / max_frame_time) * graph_dim.y;
      float task_end_height = (float(task.end_time) / max_frame_time) * graph_dim.y;

      if(abs(task_end_height - task_start_height) > height_threshold){
        glm::vec2 rect_start = frame_pose + glm::vec2(0.0f, -task_start_height);
        glm::vec2 rect_end = frame_pose + glm::vec2(bar_width, -task_end_height);
        this->draw_rect(draw_list, rect_start, rect_end, task.color, true);
      }
    }
  }

  //---------------------------
}
void Graph::render_legend(ImDrawList *draw_list){
  //---------------------------

  float max_frame_time = 1.0f / 30.0f;
  float markerMidWidth = 30.0f;
  float markerLeftRectMargin = 3.0f;
  float markerLeftRectWidth = 5.0f;
  float markerRightRectWidth = 10.0f;
  float markerRigthRectMargin = 3.0f;
  float markerRightRectHeight = 10.0f;
  float markerRightRectSpacing = 4.0f;

  //Initialization
  utl::gui::serie::Bar& current_frame = vec_bar[(current_frame_idx - 1 + 2 * vec_bar.size()) % vec_bar.size()];
  for(auto &task_stat : vec_task_stat){
    task_stat.on_screen_index = size_t(-1);
  }

  //Find number of displayed vec_task
  size_t max_task = size_t(graph_dim.y / (markerRightRectHeight + markerRightRectSpacing));
  size_t nb_task = std::min<size_t>(vec_task_stat.size(), max_task);

  // Iterate through vec_task in the current frame
  size_t cpt_task = 0;
  for(size_t task_index = 0; task_index < current_frame.vec_task.size(); task_index++){
    utl::gui::serie::Graph_task& task = current_frame.vec_task[task_index];
    auto &stat = vec_task_stat[current_frame.task_stat_index[task_index]];

    // Skip vec_task beyond the maximum number to show
    if(stat.priority_order >= nb_task){
      continue;
    }

    // Check if the task is already shown
    if(stat.on_screen_index == size_t(-1)){
      stat.on_screen_index = cpt_task++;
    }
    else{
      continue;
    }

    // Calculate heights for task rendering
    float task_start_height = (float(task.start_time) / max_frame_time) * graph_dim.y;
    float task_end_height = (float(task.end_time) / max_frame_time) * graph_dim.y;

    // Calculate positions for left and right markers
    glm::vec2 markerLeftRectMin = legend_pose + glm::vec2(markerLeftRectMargin, graph_dim.y);
    glm::vec2 markerLeftRectMax = markerLeftRectMin + glm::vec2(markerLeftRectWidth, 0.0f);
    markerLeftRectMin.y -= task_start_height;
    markerLeftRectMax.y -= task_end_height;
    glm::vec2 markerRightRectMin = legend_pose + glm::vec2(markerLeftRectMargin + markerLeftRectWidth + markerMidWidth, graph_dim.y - markerRigthRectMargin - (markerRightRectHeight + markerRightRectSpacing) * stat.on_screen_index);
    glm::vec2 markerRightRectMax = markerRightRectMin + glm::vec2(markerRightRectWidth, -markerRightRectHeight);

    // Render the task marker and legend text
    this->render_legend_marker(draw_list, markerLeftRectMin, markerLeftRectMax, markerRightRectMin, markerRightRectMax, task.color);
    this->render_legend_text(draw_list, markerRightRectMax, task.color, task);
  }

  //---------------------------
}
void Graph::render_legend_marker(ImDrawList *draw_list, glm::vec2 leftMinPoint, glm::vec2 leftMaxPoint, glm::vec2 rightMinPoint, glm::vec2 rightMaxPoint, vec4 color){
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

  glm::vec2 text_margin = glm::vec2(5.0f, -3.0f);
  float name_offset = 40.0f;
  vec4 text_color = task.color;

  float taskTimeMs = float(task.end_time - task.start_time);
  std::ostringstream timeText;
  timeText.precision(2);
  timeText << std::fixed << std::string("[") << (taskTimeMs * 1000.0f);

  this->draw_text(draw_list, rightMaxPoint + text_margin, text_color, timeText.str().c_str());
  this->draw_text(draw_list, rightMaxPoint + text_margin + glm::vec2(name_offset, 0.0f), text_color, (std::string("ms] ") + task.name).c_str());

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
