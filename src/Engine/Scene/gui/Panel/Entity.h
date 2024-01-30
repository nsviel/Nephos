#pragma once

#include <Utility/Specific/common.h>

namespace eng::scene{class Node;}
namespace eng::scene{class Scene;}
namespace eng::ope{class Attribut;}
namespace eng::ope{class Operation;}


namespace eng::scene::gui{

class Entity
{
public:
  //Constructor / Destructor
  Entity(eng::scene::Node* sce_node, bool* show_window);
  ~Entity();

  //Main function
  void run_panel();
  void design_panel();
  void close_panel();

  //Sub functions
  void entity_title(utl::type::Entity* entity);
  void entity_button(utl::type::Entity* entity);
  void entity_parameter(utl::type::Entity* entity);

  //Parameter
  void general_info(utl::type::Entity* entity);
  void data_line(utl::type::Data* data);
  void data_point(utl::type::Data* data);

  inline void set_entity(utl::type::Entity* entity){this->entity = entity;}

private:
  eng::ope::Attribut* ope_attribut;
  eng::ope::Operation* ope_operation;
  eng::scene::Scene* sce_scene;

  utl::type::Entity* entity;
  string panel_name;
  bool* panel_show;;
  int item_width;
};

}
