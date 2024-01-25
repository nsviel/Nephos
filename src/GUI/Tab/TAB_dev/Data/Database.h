#pragma once

#include <Utility/Base/GUI/Panel.h>
#include <Utility/Specific/common.h>
#include <Utility/Element/src/Namespace.h>

namespace gui{class Node;}


namespace gui::dev::data{

class Database : public utl::base::Panel
{
public:
  //Constructor / Destructor
  Database(gui::Node* gui, bool* show_window, string name);
  ~Database();

public:
  //Main functions
  void design_panel();

  //Subfunction
  void display_option();
  void combo_table();
  void display_table();

private:
  utl::element::Database* database;

  string path_db;
};

}
