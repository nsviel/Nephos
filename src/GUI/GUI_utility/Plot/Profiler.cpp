#include "Profiler.h"


namespace gui::plot{

//Constructor / Destructor
Profiler::Profiler(){
  //---------------------------

  this->win = ImGuiUtils::ProfilersWindow();

  //---------------------------
}
Profiler::~Profiler(){}

//Main function
void Profiler::design_profiling(){
  //---------------------------

/*
  struct ProfilerTask{
    double startTime;
    double endTime;
    std::string name;
    uint32_t color;
    double GetLength(){
      return endTime - startTime;
    }
  };*/

  legit::ProfilerTask task;
  vector<legit::ProfilerTask> vec_task;

  task = {0, 0.003, "hello", legit::Colors::turqoise};
  vec_task.push_back(task);

  task = {0.004, 0.010, "yup", legit::Colors::nephritis};
  vec_task.push_back(task);

  win.gpuGraph.LoadFrameData(vec_task);

  win.Render();

  //---------------------------
}
