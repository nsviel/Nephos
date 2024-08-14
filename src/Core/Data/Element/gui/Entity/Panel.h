#pragma once

#include <string>

namespace dat{class Node;}
namespace dat::graph{class Selection;}
namespace dat::element{class Set;}
namespace dat::base{class Entity;}
namespace dat::gui::entity{class Topology;}
namespace dat::gui::entity{class Data;}
namespace ope::attribut{class Location;}
namespace ope{class Operation;}
namespace utl::base{class Data;}


namespace dat::gui::entity{

class Panel
{
public:
  //Constructor / Destructor
  Panel(dat::Node* node_data, bool* show_window);
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
  ope::attribut::Location* ope_location;
  ope::Operation* ope_operation;
  dat::graph::Selection* dat_selection;
  dat::element::Set* dat_set;
  dat::gui::entity::Topology* gui_topology;
  dat::gui::entity::Data* gui_data;

  dat::base::Entity* entity;
  std::string panel_name;
  bool* panel_show;;
  int item_width;
};

}