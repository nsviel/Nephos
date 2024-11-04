#pragma once

#include <Utility/Base/Class/Node.h>

namespace dat{class Node;}
namespace dat::elm{class Node;}
namespace dat::gph{class Graph;}
namespace dat::gph{class Selection;}
namespace dat::gph{class Structure;}
namespace dat::gph{class Element;}
namespace dat::gph{class Publisher;}
namespace dat::gph::gui{class Panel;}
namespace vk{class Node;}


namespace dat::gph{

class Node : public utl::base::Node
{
public:
  //Constructor / Destructor
  Node(dat::Node* node_data);
  ~Node();

public:
  void init();
  void loop();
  void gui();
  void reset();

  inline vk::Node* get_node_vulkan(){return node_vulkan;}
  inline dat::elm::Node* get_node_element(){return node_element;}

  inline dat::gph::Graph* get_gph_graph(){return gph_graph;}
  inline dat::gph::Selection* get_gph_selection(){return gph_selection;}
  inline dat::gph::Structure* get_gph_struct(){return gph_struct;}
  inline dat::gph::Element* get_gph_element(){return gph_element;}
  inline dat::gph::Publisher* get_gph_publisher(){return gph_publisher;}

private:
  //Dependancy
  vk::Node* node_vulkan;
  dat::elm::Node* node_element;

  //Child
  dat::gph::Structure* gph_struct;
  dat::gph::Graph* gph_graph;
  dat::gph::Selection* gph_selection;
  dat::gph::Element* gph_element;
  dat::gph::Publisher* gph_publisher;
  dat::gph::gui::Panel* gui_graph;
};

}
