#pragma once

#include <string>

namespace dat::gph{class Node;}
namespace dat::gph{class Selection;}
namespace dat::gph::gui{class Button;}
namespace dat::set::gui{class Panel;}
namespace dat::base{class Set;}


namespace dat::gph::gui{

class Set
{
public:
  //Constructor / Destructor
  Set(dat::gph::Node* node_graph, bool* show_window);
  ~Set();

public:
  //Main function
  int tree_set(dat::base::Set* set);
  void tree_set_open(dat::base::Set* set, int& nb_row);

private:
  dat::gph::Selection* gph_selection;
  dat::gph::gui::Button* gui_button;
  dat::set::gui::Panel* gui_set;
};

}
