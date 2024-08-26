#pragma once

#include <memory>
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
  Entity(dat::gph::Node* node_graph);
  ~Entity();

public:
  //Main function
  void tree_entity(std::shared_ptr<dat::base::Set> set, std::shared_ptr<dat::base::Entity> entity, int& nb_row);

  //Subfunction
  void draw_leaf(std::shared_ptr<dat::base::Set> set, std::shared_ptr<dat::base::Entity> entity);
  void draw_click(std::shared_ptr<dat::base::Entity> entity);
  void draw_button(std::shared_ptr<dat::base::Set> set, std::shared_ptr<dat::base::Entity> entity);

private:
  dat::gph::Selection* gph_selection;
  dat::gph::gui::Button* gui_button;
  dat::entity::gui::Panel* gui_entity;
};

}
