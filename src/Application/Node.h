#pragma once

namespace eng{class Node;}
namespace gui{class Node;}
namespace sce{class Node;}


namespace app{

class Node
{
public:
  //Constructor / Destructor
  Node();
  ~Node();

public:
  //Main function
  void run();

  //Subfunction
  void init();
  void loop();
  void end();

  inline sce::Node* get_node_scene(){return node_scene;}
  inline eng::Node* get_node_engine(){return node_engine;}
  inline bool* get_app_running(){return &running;}

private:
  eng::Node* node_engine;
  gui::Node* node_gui;
  sce::Node* node_scene;

  bool running = true;
};

}
