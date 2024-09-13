#pragma once

#include <Utility/Base/Class/Node.h>

namespace vk{class Node;}
namespace prf{class Node;}
namespace dat{class Node;}

namespace dat::elm{class Entity;}
namespace dat::elm{class Set;}
namespace dat::elm{class Glyph;}
namespace dat::elm{class UID;}
namespace dat::elm{class Sensor;}
namespace dat::elm{class Structure;}
namespace dat::entity::gui{class Panel;}
namespace dat::set::gui{class Panel;}


namespace dat::elm{

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
  inline prf::Node* get_node_profiler(){return node_profiler;}

  inline dat::elm::Entity* get_dat_entity(){return dat_entity;}
  inline dat::elm::Set* get_dat_set(){return dat_set;}
  inline dat::elm::Glyph* get_dat_glyph(){return dat_glyph;}
  inline dat::elm::Structure* get_dat_struct(){return dat_struct;}
  inline dat::elm::UID* get_dat_uid(){return dat_uid;}
  inline dat::elm::Sensor* get_dat_sensor(){return dat_sensor;}
  inline dat::entity::gui::Panel* get_gui_entity(){return gui_entity;}
  inline dat::set::gui::Panel* get_gui_set(){return gui_set;}

private:
  //Dependancy
  vk::Node* node_vulkan;
  prf::Node* node_profiler;

  //Child
  dat::elm::Structure* dat_struct;
  dat::elm::Entity* dat_entity;
  dat::elm::Set* dat_set;
  dat::elm::Glyph* dat_glyph;
  dat::elm::UID* dat_uid;
  dat::elm::Sensor* dat_sensor;
  dat::entity::gui::Panel* gui_entity;
  dat::set::gui::Panel* gui_set;
};

}
