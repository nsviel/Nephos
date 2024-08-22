#pragma once

#include <string>

namespace dat::gph{class Node;}
namespace dat::gph{class Selection;}
namespace dat::gph::gui{class Button;}
namespace dat::entity::gui{class Panel;}
namespace dat::base{class Set;}
namespace dat::base{class Entity;}


namespace dat::gph::gui{

class Entity
{
public:
  //Constructor / Destructor
  Entity(dat::gph::Node* node_graph, bool* show_window);
  ~Entity();

public:
  //Main function
  void tree_entity(dat::base::Set* set, dat::base::Entity* entity, int& nb_row);

  //Subfunction
  void draw_leaf(dat::base::Set* set, dat::base::Entity* entity);
  void draw_click(dat::base::Entity* entity);
  void draw_button(dat::base::Set* set, dat::base::Entity* entity);

private:
  dat::gph::Selection* gph_selection;
  dat::gph::gui::Button* gui_button;
  dat::entity::gui::Panel* gui_entity;
};

}
