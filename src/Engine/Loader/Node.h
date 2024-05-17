#pragma once

#include <Utility/Base/Type/Node.h>

namespace vk{class Node;}
namespace dat{class Node;}
namespace eng{class Node;}
namespace ldr{class Loader;}
namespace ldr{class Exporter;}
namespace ldr{class Format;}
namespace ldr{class Bookmark;}
namespace ldr::gui{class Loader;}


namespace ldr{

class Node : public utl::base::Node
{
public:
  //Constructor / Destructor
  Node(eng::Node* node_engine);
  ~Node();

public:
  void init();
  void loop();
  void clean();
  void gui();
  void reset();

  inline eng::Node* get_node_engine(){return node_engine;}
  inline vk::Node* get_node_vulkan(){return node_vulkan;}
  inline dat::Node* get_node_data(){return node_data;}

  inline ldr::Format* get_ldr_format(){return ldr_format;}
  inline ldr::Loader* get_ldr_loader(){return ldr_loader;}
  inline ldr::Exporter* get_ldr_exporter(){return ldr_exporter;}
  inline ldr::Bookmark* get_ldr_bookmark(){return ldr_bookmark;}

private:
  //Dependancy
  eng::Node* node_engine;
  vk::Node* node_vulkan;
  dat::Node* node_data;

  //Child
  ldr::Loader* ldr_loader;
  ldr::Exporter* ldr_exporter;
  ldr::Format* ldr_format;
  ldr::Bookmark* ldr_bookmark;
  ldr::gui::Loader* gui_loader;

  bool show_scene = true;
  bool show_loader = true;
};

}
