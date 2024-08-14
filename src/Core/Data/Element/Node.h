#pragma once

#include <Utility/Base/Class/Node.h>

namespace vk{class Node;}
namespace core{class Node;}
namespace dat{class Node;}
namespace dat::elm{class Entity;}
namespace dat::elm{class Set;}
namespace dat::elm{class Image;}
namespace dat::elm{class Glyph;}
namespace dat::elm{class Structure;}
namespace dat::elm{class UID;}


namespace dat::elm{

class Node : public utl::base::Node
{
public:
  //Constructor / Destructor
  Node(dat::Node* node_data);
  ~Node();

public:
  void init();
  void loop();
  void clean();
  void gui();
  void reset();

  inline core::Node* get_node_core(){return node_core;}
  inline vk::Node* get_node_vulkan(){return node_vulkan;}

  inline dat::elm::Entity* get_dat_entity(){return dat_entity;}
  inline dat::elm::Set* get_dat_set(){return dat_set;}
  inline dat::elm::Image* get_dat_image(){return dat_image;}
  inline dat::elm::Glyph* get_dat_glyph(){return dat_glyph;}
  inline dat::elm::Structure* get_dat_struct(){return dat_struct;}
  inline dat::elm::UID* get_dat_uid(){return dat_uid;}

private:
  //Dependancy
  core::Node* node_core;
  vk::Node* node_vulkan;

  //Child
  dat::elm::Structure* dat_struct;
  dat::elm::Entity* dat_entity;
  dat::elm::Set* dat_set;
  dat::elm::Glyph* dat_glyph;
  dat::elm::UID* dat_uid;
  dat::elm::Image* dat_image;
};

}
