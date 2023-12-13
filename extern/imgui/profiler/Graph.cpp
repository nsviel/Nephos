#include "Graph.h"


namespace ImProfil{

Graph::Graph(size_t framesCount){
  frames.resize(framesCount);
  for(auto &frame : frames){
    frame.tasks.reserve(100);
  }

  frame_width = 3;
  frame_spacing = 1;
  use_colored_legend_text = false;
}
void Graph::LoadFrameData(const std::vector<ImProfil::Graph_task>& tasks){
   size_t count = tasks.size();
  auto &currFrame = frames[currFrameIndex];
  currFrame.tasks.resize(0);
  for (size_t taskIndex = 0; taskIndex < count; taskIndex++){
    if (taskIndex == 0)
      currFrame.tasks.push_back(tasks[taskIndex]);
    else
    {
      if (tasks[taskIndex - 1].color != tasks[taskIndex].color || tasks[taskIndex - 1].name != tasks[taskIndex].name)
      {
        currFrame.tasks.push_back(tasks[taskIndex]);
      }
      else
      {
        currFrame.tasks.back().endTime = tasks[taskIndex].endTime;
      }
    }
  }
  currFrame.taskStatsIndex.resize(currFrame.tasks.size());

  for (size_t taskIndex = 0; taskIndex < currFrame.tasks.size(); taskIndex++){
    auto &task = currFrame.tasks[taskIndex];
    auto it = taskNameToStatsIndex.find(task.name);
    if (it == taskNameToStatsIndex.end())
    {
      taskNameToStatsIndex[task.name] = taskStats.size();
      TaskStats taskStat;
      taskStat.maxTime = -1.0;
      taskStats.push_back(taskStat);
    }
    currFrame.taskStatsIndex[taskIndex] = taskNameToStatsIndex[task.name];
  }
  currFrameIndex = (currFrameIndex + 1) % frames.size();

  this->RebuildTaskStats(currFrameIndex, 300/*frames.size()*/);
}
void Graph::RenderTimings(int graphWidth, int legendWidth, int height, int frameIndexOffset){
  ImDrawList* drawList = ImGui::GetWindowDrawList();
  const glm::vec2 widgetPos = Vec2(ImGui::GetCursorScreenPos());
  this->RenderGraph(drawList, widgetPos, glm::vec2(graphWidth, height), frameIndexOffset);
  this->RenderLegend(drawList, widgetPos + glm::vec2(graphWidth, 0.0f), glm::vec2(legendWidth, height), frameIndexOffset);
  ImGui::Dummy(ImVec2(float(graphWidth + legendWidth), float(height)));
}
void Graph::RebuildTaskStats(size_t endFrame, size_t framesCount){
  for (auto &taskStat : taskStats)
  {
    taskStat.maxTime = -1.0f;
    taskStat.priorityOrder = size_t(-1);
    taskStat.onScreenIndex = size_t(-1);
  }

  for (size_t frameNumber = 0; frameNumber < framesCount; frameNumber++)
  {
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
  for(size_t statIndex = 0; statIndex < taskStats.size(); statIndex++)
    statPriorities[statIndex] = statIndex;

  std::sort(statPriorities.begin(), statPriorities.end(), [this](size_t left, size_t right) {return taskStats[left].maxTime > taskStats[right].maxTime; });
  for (size_t statNumber = 0; statNumber < taskStats.size(); statNumber++)
  {
    size_t statIndex = statPriorities[statNumber];
    taskStats[statIndex].priorityOrder = statNumber;
  }
}
void Graph::RenderGraph(ImDrawList *drawList, glm::vec2 graphPos, glm::vec2 graphSize, size_t frameIndexOffset){
  Rect(drawList, graphPos, graphPos + graphSize, 0xffffffff, false);
  float heightThreshold = 1.0f;

  for (size_t frameNumber = 0; frameNumber < frames.size(); frameNumber++)
  {
    size_t frameIndex = (currFrameIndex - frameIndexOffset - 1 - frameNumber + 2 * frames.size()) % frames.size();

    glm::vec2 framePos = graphPos + glm::vec2(graphSize.x - 1 - frame_width - (frame_width + frame_spacing) * frameNumber, graphSize.y - 1);
    if (framePos.x < graphPos.x + 1)
      break;
    glm::vec2 taskPos = framePos + glm::vec2(0.0f, 0.0f);
    auto &frame = frames[frameIndex];
    for (const auto& task : frame.tasks)
    {
      float taskStartHeight = (float(task.startTime) / maxFrameTime) * graphSize.y;
      float taskEndHeight = (float(task.endTime) / maxFrameTime) * graphSize.y;
      //taskMaxCosts[task.name] = std::max(taskMaxCosts[task.name], task.endTime - task.startTime);
      if (abs(taskEndHeight - taskStartHeight) > heightThreshold)
        Rect(drawList, taskPos + glm::vec2(0.0f, -taskStartHeight), taskPos + glm::vec2(frame_width, -taskEndHeight), task.color, true);
    }
  }
}
void Graph::RenderLegend(ImDrawList *drawList, glm::vec2 legendPos, glm::vec2 legendSize, size_t frameIndexOffset){
    float markerLeftRectMargin = 3.0f;
    float markerLeftRectWidth = 5.0f;
    float maxFrameTime = 1.0f / 30.0f;
    float markerMidWidth = 30.0f;
    float markerRightRectWidth = 10.0f;
    float markerRigthRectMargin = 3.0f;
    float markerRightRectHeight = 10.0f;
    float markerRightRectSpacing = 4.0f;
    float nameOffset = 30.0f;
    glm::vec2 textMargin = glm::vec2(5.0f, -3.0f);

    auto &currFrame = frames[(currFrameIndex - frameIndexOffset - 1 + 2 * frames.size()) % frames.size()];
    size_t maxTasksCount = size_t(legendSize.y / (markerRightRectHeight + markerRightRectSpacing));

    for (auto &taskStat : taskStats)
    {
      taskStat.onScreenIndex = size_t(-1);
    }

    size_t tasksToShow = std::min<size_t>(taskStats.size(), maxTasksCount);
    size_t tasksShownCount = 0;
    for (size_t taskIndex = 0; taskIndex < currFrame.tasks.size(); taskIndex++)
    {
      auto &task = currFrame.tasks[taskIndex];
      auto &stat = taskStats[currFrame.taskStatsIndex[taskIndex]];

      if (stat.priorityOrder >= tasksToShow)
        continue;

      if (stat.onScreenIndex == size_t(-1))
      {
        stat.onScreenIndex = tasksShownCount++;
      }
      else
        continue;
      float taskStartHeight = (float(task.startTime) / maxFrameTime) * legendSize.y;
      float taskEndHeight = (float(task.endTime) / maxFrameTime) * legendSize.y;

      glm::vec2 markerLeftRectMin = legendPos + glm::vec2(markerLeftRectMargin, legendSize.y);
      glm::vec2 markerLeftRectMax = markerLeftRectMin + glm::vec2(markerLeftRectWidth, 0.0f);
      markerLeftRectMin.y -= taskStartHeight;
      markerLeftRectMax.y -= taskEndHeight;

      glm::vec2 markerRightRectMin = legendPos + glm::vec2(markerLeftRectMargin + markerLeftRectWidth + markerMidWidth, legendSize.y - markerRigthRectMargin - (markerRightRectHeight + markerRightRectSpacing) * stat.onScreenIndex);
      glm::vec2 markerRightRectMax = markerRightRectMin + glm::vec2(markerRightRectWidth, -markerRightRectHeight);
      RenderTaskMarker(drawList, markerLeftRectMin, markerLeftRectMax, markerRightRectMin, markerRightRectMax, task.color);

      uint32_t textColor = use_colored_legend_text ? task.color : ImProfil::color::imguiText;// task.color;

      float taskTimeMs = float(task.endTime - task.startTime);
      std::ostringstream timeText;
      timeText.precision(2);
      timeText << std::fixed << std::string("[") << (taskTimeMs * 1000.0f);

      Text(drawList, markerRightRectMax + textMargin, textColor, timeText.str().c_str());
      Text(drawList, markerRightRectMax + textMargin + glm::vec2(nameOffset, 0.0f), textColor, (std::string("ms] ") + task.name).c_str());
    }

    /*
    struct PriorityEntry
    {
      bool isUsed;
      ImProfil::Graph_task task;
    };
    std::map<std::string, PriorityEntry> priorityEntries;
    for (auto priorityTask : priorityTasks)
    {
      PriorityEntry entry;
      entry.task = frames[priorityTask.frameIndex].tasks[priorityTask.taskIndex];
      entry.isUsed = false;
      priorityEntries[entry.task.name] = entry;
    }
    size_t shownTasksCount = 0;
    for (size_t taskIndex = 0; taskIndex < currFrame.tasks.size(); taskIndex++)
    {
      auto &task = currFrame.tasks[taskIndex];
      auto it = priorityEntries.find(task.name);
      if (it != priorityEntries.end() && !it->second.isUsed)
      {
        it->second.isUsed = true;

        float taskStartHeight = (float(task.startTime) / maxFrameTime) * legendSize.y;
        float taskEndHeight = (float(task.endTime) / maxFrameTime) * legendSize.y;


        glm::vec2 markerLeftRectMin = legendPos + glm::vec2(markerLeftRectMargin, legendSize.y);
        glm::vec2 markerLeftRectMax = markerLeftRectMin + glm::vec2(markerLeftRectWidth, 0.0f);
        markerLeftRectMin.y -= taskStartHeight;
        markerLeftRectMax.y -= taskEndHeight;

        glm::vec2 markerRightRectMin = legendPos + glm::vec2(markerLeftRectMargin + markerLeftRectWidth + markerMidWidth, legendSize.y - markerRigthRectMargin - (markerRightRectHeight + markerRightRectSpacing) * shownTasksCount);
        glm::vec2 markerRightRectMax = markerRightRectMin + glm::vec2(markerRightRectWidth, -markerRightRectHeight);
        RenderTaskMarker(drawList, markerLeftRectMin, markerLeftRectMax, markerRightRectMin, markerRightRectMax, task.color);

        uint32_t textColor = ImProfil::color::imguiText;// task.color;

        float taskTimeMs = float(task.endTime - task.startTime);
        std::ostringstream timeText;
        timeText.precision(2);
        timeText << std::fixed << std::string("[") << (taskTimeMs * 1000.0f);

        Text(drawList, markerRightRectMax + textMargin, textColor, timeText.str().c_str());
        Text(drawList, markerRightRectMax + textMargin + glm::vec2(nameOffset, 0.0f), textColor, (std::string("ms] ") + task.name).c_str());
        shownTasksCount++;
      }
    }*/

    /*for (size_t priorityTaskIndex = 0; priorityTaskIndex < priorityTasks.size(); priorityTaskIndex++)
    {
      auto &priorityTask = priorityTasks[priorityTaskIndex];
      auto &globalTask = frames[priorityTask.frameIndex].tasks[priorityTask.taskIndex];

      size_t lastFrameTaskIndex = currFrame.FindTask(globalTask.name);

      glm::vec2 taskPos = legendPos + marginSpacing + glm::vec2(0.0f, markerHeight) + glm::vec2(0.0f, (markerHeight + itemSpacing) * priorityTaskIndex);
      Rect(drawList, taskPos, taskPos + glm::vec2(markerHeight, -markerHeight), task.color, true);
      Text(drawList, taskPos + textOffset, 0xffffffff, task.name.c_str());
    }*/
  }

}
