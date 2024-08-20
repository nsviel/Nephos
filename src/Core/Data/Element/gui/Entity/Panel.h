#pragma once

#include <string>

namespace dat::elm{class Node;}
namespace dat::elm{class Set;}
namespace dat::base{class Entity;}
namespace dat::entity::gui{class Topology;}
namespace dat::entity::gui{class Data;}
namespace eng::trf{class Operation;}
namespace utl::base{class Data;}


namespace dat::entity::gui{

class Panel
{
public:
  //Constructor / Destructor
  Panel(dat::elm::Node* node_element);
  ~Panel();

  //Main function
  void run_panel();
  void design_panel();
  void close_panel();

  //Subfunction
  void entity_title(dat::base::Entity* entity);
  void entity_button(dat::base::Entity* entity);
  void entity_parameter(dat::base::Entity* entity);

  inline void set_entity(dat::base::Entity* entity){this->entity = entity;}
  inline void show_panel(bool value){this->panel_show = value;}

private:
  eng::trf::Operation* trf_operation;
  dat::elm::Set* dat_set;
  dat::entity::gui::Topology* gui_topology;
  dat::entity::gui::Data* gui_data;

  dat::base::Entity* entity;
  std::string panel_name;
  bool panel_show;;
  int item_width;
};

}
