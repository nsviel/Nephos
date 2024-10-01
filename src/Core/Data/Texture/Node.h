#pragma once

#include <Utility/Base/Class/Node.h>

namespace vk{class Node;}
namespace dat{class Node;}
namespace dat::elm{class Node;}
namespace dat::gph{class Node;}

namespace dat::img{class Image;}
namespace dat::img{class Storage;}
namespace dat::img::gui{class Panel;}


namespace dat::img{

class Node : public utl::base::Node
{
public:
  //Constructor / Destructor
  Node(dat::Node* node_data);
  ~Node();

public:
  //Main function
  void gui();

  inline vk::Node* get_node_vulkan(){return node_vulkan;}
  inline dat::gph::Node* get_node_graph(){return node_graph;}
  inline dat::elm::Node* get_node_element(){return node_element;}

  inline dat::img::Image* get_dat_image(){return dat_image;}
  inline dat::img::Storage* get_dat_storage(){return dat_storage;}

private:
  vk::Node* node_vulkan;
  dat::gph::Node* node_graph;
  dat::elm::Node* node_element;

  dat::img::Image* dat_image;
  dat::img::Storage* dat_storage;
  dat::img::gui::Panel* gui_stream;
};

}
