#pragma once

#include <memory>
#include <string>

namespace dat::gph{class Node;}
namespace dat::gph{class Selection;}
namespace dat::gph::gui{class Button;}
namespace dat::gph::gui{class Entity;}
namespace dat::set::gui{class Panel;}
namespace dat::base{class Set;}


namespace dat::gph::gui{

class Set
{
public:
  //Constructor / Destructor
  Set(dat::gph::Node* node_graph);
  ~Set();

public:
  //Main function
  int tree_set(std::shared_ptr<dat::base::Set> set);

  //Subfunction
  void draw_node(std::shared_ptr<dat::base::Set> set, bool& node_open);
  void draw_click(std::shared_ptr<dat::base::Set> set);
  void draw_button(std::shared_ptr<dat::base::Set> set);
  void draw_open(std::shared_ptr<dat::base::Set> set, bool& node_open, int& nb_row);

private:
  dat::gph::Selection* gph_selection;
  dat::gph::gui::Button* gui_button;
  dat::set::gui::Panel* gui_set;
  dat::gph::gui::Entity* gui_entity;
};

}
