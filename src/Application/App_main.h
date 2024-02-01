#pragma once

class Config;
namespace utl::element{class Profiler;}
namespace eng{class Node;}
namespace utl{class Node;}
namespace gui{class Node;}


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
  utl::element::Profiler* cpu_profiler;
  eng::Node* node_engine;
  utl::Node* node_utility;
  gui::Node* node_gui;
};
