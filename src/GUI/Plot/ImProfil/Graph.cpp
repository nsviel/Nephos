#include "Graph.h"

#include <GUI/Plot/Namespace.h>


namespace utl::improfil{

//Constructor
Graph::Graph(){
  //---------------------------

  this->bar_max_nb = 200;
  this->bar_width = 4;
  this->bar_gap = 0;
  this->bar_max_nb_task = 100;
  this->vec_bar.resize(bar_max_nb);
  this->legend_width = 200;
  this->border_color = vec4(255, 255, 255, 25);
  this->max_time_s = 50.0f / 1000.0f;

  for(utl::improfil::Bar& bar : vec_bar){
    bar.vec_task.reserve(bar_max_nb_task);
  }

  //---------------------------
}
Graph::~Graph(){}

//Main function
void Graph::load_graph_data(const std::vector<utl::type::Task>& vec_task){
  //update the graph with new task data
  //---------------------------

  // Get the current bar that needs to be updated and clear it
  utl::improfil::Bar& current_bar = vec_bar[current_bar_idx];
  current_bar.vec_task.resize(0);

  // Iterate through each task in the input data
  for(size_t task_index=0; task_index<vec_task.size(); task_index++){
    // If it's the first task or the current and previous tasks have different color or name,
    // add a new task to the current bar
    if(task_index == 0)
      current_bar.vec_task.push_back(vec_task[task_index]);
    else{
      if(vec_task[task_index - 1].color != vec_task[task_index].color || vec_task[task_index - 1].name != vec_task[task_index].name){
        current_bar.vec_task.push_back(vec_task[task_index]);
      }
      else{
        // If the current and previous tasks have the same color and name,
        // update the end time of the last task in the current bar
        current_bar.vec_task.back().time_end = vec_task[task_index].time_end;
      }
    }
  }

  // Resize the index array for task statistics in the current bar
  current_bar.task_stat_index.resize(current_bar.vec_task.size());

  // Iterate through each task in the current bar
  for(size_t task_index = 0; task_index < current_bar.vec_task.size(); task_index++){
    auto &task = current_bar.vec_task[task_index];

    // Check if the task name exists in the map
    auto it = map_task_to_stat_idx.find(task.name);

    // If the task name is not found, add it to the map and create a new task_stats entry
    if(it == map_task_to_stat_idx.end()){
      map_task_to_stat_idx[task.name] = vec_stat.size();
      utl::improfil::Stat task_stats;
      task_stats.max_time = -1.0;
      vec_stat.push_back(task_stats);
    }

    // Set the task_stat_index for the current task in the current bar
    current_bar.task_stat_index[task_index] = map_task_to_stat_idx[task.name];
  }

  // Move to the next bar in the circular buffer
  current_bar_idx = (current_bar_idx + 1) % vec_bar.size();

  // Rebuild task statistics based on the updated bars
  this->rebuild_task_stats(current_bar_idx);

  //---------------------------
}
void Graph::rebuild_task_stats(size_t bar_end){
  //---------------------------

  //Reset task
  for(auto &task_stat : vec_stat){
    task_stat.max_time = -1.0f;
    task_stat.priority_order = size_t(-1);
    task_stat.on_screen_index = size_t(-1);
  }

  for(size_t bar_number=0; bar_number<bar_max_nb; bar_number++){
    size_t bar_idx = (bar_end - 1 - bar_number + vec_bar.size()) % vec_bar.size();
    utl::improfil::Bar& bar = vec_bar[bar_idx];

    for(size_t task_index=0; task_index<bar.vec_task.size(); task_index++){
      auto &task = bar.vec_task[task_index];
      auto &stats = vec_stat[bar.task_stat_index[task_index]];
      stats.max_time = std::max(stats.max_time, task.time_end - task.time_beg);
    }
  }

  //Reorder task according to their priority
  std::vector<size_t> stat_priority;
  stat_priority.resize(vec_stat.size());
  for(size_t stat_index = 0; stat_index < vec_stat.size(); stat_index++){
    stat_priority[stat_index] = stat_index;
  }

  std::sort(stat_priority.begin(), stat_priority.end(), [this](size_t left, size_t right) {return vec_stat[left].max_time > vec_stat[right].max_time; });
  for(size_t stat_number = 0; stat_number < vec_stat.size(); stat_number++){
    size_t stat_index = stat_priority[stat_number];
    vec_stat[stat_index].priority_order = stat_number;
  }

  //---------------------------
}

//Rendering
void Graph::render_graph(ImVec2 dimension){
  const glm::vec2 widget_pose = glm::vec2(ImGui::GetCursorScreenPos().x, ImGui::GetCursorScreenPos().y);
  //---------------------------

  this->graph_pose = widget_pose;
  this->graph_dim.x = int(dimension.x) - legend_width;
  this->graph_dim.y = int(dimension.y);

  this->legend_dim = glm::vec2(legend_width, graph_dim.y);
  this->legend_pose = widget_pose + glm::vec2(graph_dim.x, 0.0f);

  ImDrawList* draw_list = ImGui::GetWindowDrawList();
  this->render_serie(draw_list);
  this->render_legend(draw_list);

  //---------------------------
}
void Graph::render_serie(ImDrawList *draw_list){
  //---------------------------

  //Objectif outline zone
  this->draw_zone(draw_list, 0, 16.7f, vec4(44, 150, 44, 30));

  for(int i=0; i<vec_bar.size(); i++){
    // Get bar index compared to the current bar
    size_t bar_idx = (current_bar_idx - 1 - i + 2 * vec_bar.size()) % vec_bar.size();

    // Calculate the position of the bar
    float x_offset = graph_dim.x - 1 - bar_width - (bar_width + bar_gap) * i;
    float y_offset = graph_dim.y - 1;
    glm::vec2 offset(x_offset, y_offset);
    glm::vec2 bar_pose = graph_pose + offset;
    if (bar_pose.x < graph_pose.x + 1){
      break;
    }

    // Iterate through each task in the ith bar
    utl::improfil::Bar& bar = vec_bar[bar_idx];
    for(utl::type::Task& task : bar.vec_task){
      this->render_serie_task_rect(draw_list, task, bar_pose);
    }
  }

  //Background tics
  this->render_background_tics(draw_list);

  //Objectif outline line
  this->draw_line_at_time(draw_list, 16.7f, 1, vec4(44, 150, 44, 255));
  this->draw_line_at_time(draw_list, 33.3f, 1, vec4(150, 150, 44, 255));

  //---------------------------
}
void Graph::render_legend(ImDrawList *draw_list){
  //---------------------------

  float markerMidWidth = 30.0f;
  float markerLeftRectMargin = 3.0f;
  float markerLeftRectWidth = 5.0f;
  float markerRightRectWidth = 10.0f;
  float markerRigthRectMargin = 3.0f;
  float markerRightRectHeight = 10.0f;
  float markerRightRectSpacing = 4.0f;

  //Initialization
  utl::improfil::Bar& current_bar = vec_bar[(current_bar_idx - 1 + 2 * vec_bar.size()) % vec_bar.size()];
  for(auto &task_stat : vec_stat){
    task_stat.on_screen_index = size_t(-1);
  }

  //Find number of displayed vec_task
  size_t max_task = size_t(graph_dim.y / (markerRightRectHeight + markerRightRectSpacing));
  size_t nb_task = std::min<size_t>(vec_stat.size(), max_task);

  // Iterate through vec_task in the current bar
  size_t cpt_task = 0;
  for(size_t task_index = 0; task_index < current_bar.vec_task.size(); task_index++){
    utl::type::Task& task = current_bar.vec_task[task_index];
    auto &stat = vec_stat[current_bar.task_stat_index[task_index]];

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
    float scaling_factor = graph_dim.y / max_time_s;
    float task_start_height = float(task.time_beg) * scaling_factor;
    float task_end_height = float(task.time_end) * scaling_factor;

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

//Subfunction
void Graph::render_background_tics(ImDrawList *draw_list){
  //---------------------------

  for(float time = 0.0f; time <= max_time_s*1000.0f; time += 5.0f) {
    int lineWidth = (int)(time / 5.0f) % 2 == 0 ? 1 : 2;
    vec4 color(255, 255, 255, 20);
    this->draw_line_at_time(draw_list, time, lineWidth, color);
  }

  //---------------------------
}
void Graph::render_serie_task_rect(ImDrawList *draw_list, utl::type::Task& task, glm::vec2 bar_pose){
  float height_threshold = 1.0f;
  //---------------------------

  // Calculate the heights based on task start and end times
  float scaling_factor = graph_dim.y / max_time_s;
  float task_start_height = float(task.time_beg) * scaling_factor;
  float task_end_height = float(task.time_end) * scaling_factor;

  if (abs(task_end_height - task_start_height) > height_threshold){
    glm::vec2 rect_start = bar_pose + glm::vec2(0.0f, -task_start_height);
    glm::vec2 rect_end = bar_pose + glm::vec2(bar_width, -task_end_height);
    this->draw_rect(draw_list, rect_start, rect_end, task.color, true);
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
void Graph::render_legend_text(ImDrawList *draw_list, glm::vec2 rightMaxPoint, vec4 col, utl::type::Task task){
  //---------------------------

  glm::vec2 text_margin = glm::vec2(5.0f, -3.0f);
  float name_offset = 40.0f;
  vec4 text_color = task.color;

  float taskTimeMs = float(task.time_end - task.time_beg);
  std::ostringstream timeText;
  timeText.precision(2);
  timeText << std::fixed << std::string("[") << (taskTimeMs * 1000.0f);

  this->draw_text(draw_list, rightMaxPoint + text_margin, text_color, timeText.str().c_str());
  this->draw_text(draw_list, rightMaxPoint + text_margin + glm::vec2(name_offset, 0.0f), text_color, (std::string("ms] ") + task.name).c_str());

  //---------------------------
}

//Primitives
void Graph::draw_line_at_time(ImDrawList *draw_list, float time_ms, float thickness, vec4 color){
  //---------------------------

  float scaling_factor = graph_dim.y / max_time_s;

  float line_time = time_ms / 1000.0f * scaling_factor;
  glm::vec2 line_beg;
  line_beg.x = graph_pose.x;
  line_beg.y = graph_pose.y + graph_dim.y - line_time - thickness;
  glm::vec2 line_end = graph_pose + glm::vec2(graph_dim.x, graph_dim.y - line_time);
  this->draw_rect(draw_list, line_beg, line_end, color, true);

  //---------------------------
}
void Graph::draw_zone(ImDrawList *draw_list, float time_beg_ms, float time_end_ms, vec4 color){
  //---------------------------

  float scaling_factor = graph_dim.y / max_time_s;

  float line_time_beg = time_beg_ms / 1000.0f * scaling_factor;
  float line_time_end = time_end_ms / 1000.0f * scaling_factor;
  glm::vec2 line_beg;
  line_beg.x = graph_pose.x;
  line_beg.y = graph_pose.y + graph_dim.y - line_time_beg;
  glm::vec2 line_end;
  line_end.x = graph_pose.x + graph_dim.x;
  line_end.y = graph_pose.y + graph_dim.y - line_time_end;

  this->draw_rect(draw_list, line_beg, line_end, color, true);

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
