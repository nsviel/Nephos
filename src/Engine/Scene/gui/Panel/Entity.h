#pragma once

#include <Utility/Specific/common.h>

namespace eng::scene{class Node;}
namespace eng::scene{class Scene;}
namespace ope{class Attribut;}
namespace ope{class Operation;}


namespace eng::scene::gui{

class Entity
{
public:
  //Constructor / Destructor
  Entity(eng::scene::Node* node_scene, bool* show_window);
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
  void entity_info(utl::type::Entity* entity);
  void data_info(utl::type::Entity* entity);
  void pose_info(utl::type::Entity* entity);

  //Primitive
  void primitive_line(utl::type::Data* data);
  void primitive_point(utl::type::Data* data);

  inline void set_entity(utl::type::Entity* entity){this->entity = entity;}

private:
  ope::Attribut* ope_attribut;
  ope::Operation* ope_operation;
  eng::scene::Scene* sce_scene;

  utl::type::Entity* entity;
  string panel_name;
  bool* panel_show;;
  int item_width;
};

}
