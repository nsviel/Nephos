#pragma once

namespace app{class Configuration;}
namespace vk{class Node;}
namespace prf{class Node;}
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
  //Main functions
  void run();

  //Subfunction
  void init();
  void loop();
  void end();

  inline app::Configuration* get_app_config(){return app_config;}
  inline vk::Node* get_node_vulkan(){return node_vulkan;}
  inline eng::Node* get_node_engine(){return node_engine;}
  inline prf::Node* get_node_profiler(){return node_profiler;}

private:
  app::Configuration* app_config;
  vk::Node* node_vulkan;
  prf::Node* node_profiler;
  eng::Node* node_engine;
  gui::Node* node_gui;
  sce::Node* node_scene;
};

}
