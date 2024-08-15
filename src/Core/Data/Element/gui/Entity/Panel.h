#pragma once

#include <string>

namespace dat::elm{class Node;}
namespace dat::elm{class Set;}
namespace dat::base{class Entity;}
namespace dat::gui::entity{class Topology;}
namespace dat::gui::entity{class Data;}
namespace dat::atr{class Location;}
namespace eng::trf{class Operation;}
namespace utl::base{class Data;}


namespace dat::gui::entity{

class Panel
{
public:
  //Constructor / Destructor
  Panel(dat::elm::Node* node_element, bool* show_window);
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

private:
  dat::atr::Location* ope_location;
  eng::trf::Operation* trf_operation;
  dat::elm::Set* dat_set;
  dat::gui::entity::Topology* gui_topology;
  dat::gui::entity::Data* gui_data;

  dat::base::Entity* entity;
  std::string panel_name;
  bool* panel_show;;
  int item_width;
};

}
