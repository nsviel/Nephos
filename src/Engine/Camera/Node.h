#pragma once

#include <Utility/Base/Type/Node.h>

namespace vk{class Node;}
namespace dat{class Node;}
namespace eng{class Node;}
namespace sce{class Node;}
namespace cam{class Control;}
namespace cam{class Manager;}
namespace cam{class Pather;}
namespace cam{class Structure;}
namespace cam::gui{class Panel;}


namespace cam{

class Node : public utl::base::Node
{
public:
  Node(eng::Node* node_engine);
  ~Node();

public:
  //Main function
  void init();
  void loop();
  void gui();
  void reset();

  inline vk::Node* get_node_vulkan(){return node_vulkan;}
  inline dat::Node* get_node_data(){return node_data;}
  inline eng::Node* get_node_engine(){return node_engine;}

  inline cam::Control* get_cam_control(){return cam_control;}
  inline cam::Manager* get_cam_manager(){return cam_manager;}
  inline cam::Structure* get_cam_struct(){return cam_struct;}

private:
  //Dependancy
  vk::Node* node_vulkan;
  dat::Node* node_data;
  eng::Node* node_engine;

  //Child
  cam::Structure* cam_struct;
  cam::Control* cam_control;
  cam::Manager* cam_manager;
  cam::Pather* cam_pather;
  cam::gui::Panel* gui_panel;
};

}
