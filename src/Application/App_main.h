#pragma once

class Config;
namespace prf{class Node;}
namespace eng{class Node;}
namespace utl{class Node;}
namespace gui{class Node;}
namespace utl::fps{class Control;}


class App_main
{
public:
  //Constructor / Destructor
  App_main();
  ~App_main();

public:
  //Main functions
  void run();

  //Subfunction
  void init();
  void loop();
  void end();

private:
  Config* config;
  utl::fps::Control* fps_control;
  prf::Node* node_profiler;
  eng::Node* node_engine;
  utl::Node* node_utility;
  gui::Node* node_gui;
};
