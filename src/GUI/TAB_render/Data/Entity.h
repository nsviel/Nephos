#pragma once

#include <Engine/Scene/Namespace.h>
#include <Utility/Base/Namespace.h>
#include <Utility/Specific/common.h>
#include <Engine/Operation/Namespace.h>

class GUI;
class Panel;


namespace gui::rnd::data{

class Entity
{
public:
  //Constructor / Destructor
  Entity(GUI* gui, bool* show_window);
  ~Entity();

  //Main function
  void run_panel();
  void design_panel();
  void close_panel();

  //Sub functions
  void entity_title(entity::Entity* entity);
  void entity_button(entity::Entity* entity);
  void entity_parameter(entity::Entity* entity);

  //Primitive size
  void entity_line(entity::Object* object);
  void entity_point(entity::Object* object);

  inline void set_entity(entity::Entity* entity){this->entity = entity;}

private:
  Panel* gui_render_panel;
  eng::ope::Attribut* ope_attribut;
  eng::ope::Operation* ope_operation;
  eng::scene::Scene* sce_scene;

  entity::Entity* entity;
  string panel_name;
  bool* panel_show;;
  int item_width;
};

}
