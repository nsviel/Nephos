#pragma once

class Configuration;
namespace prf{class Node;}
namespace eng{class Node;}
namespace utl{class Node;}
namespace gui{class Node;}


namespace app{

class Node
{
public:
  //Constructor / Destructor
  Node();
  ~Node();

public:
  //Main functions
  void run();

  //Subfunction
  void init();
  void loop();
  void end();

  inline Configuration* get_configuration(){return config;}
  inline utl::Node* get_node_utility(){return node_utility;}
  inline eng::Node* get_node_engine(){return node_engine;}
  inline prf::Node* get_node_profiler(){return node_profiler;}

private:
  Configuration* config;
  prf::Node* node_profiler;
  eng::Node* node_engine;
  utl::Node* node_utility;
  gui::Node* node_gui;

  bool running;
};

}
