#pragma once

#include <memory>
#include <string>

namespace dat::elm{class Node;}
namespace dat::elm{class Set;}
namespace dat::base{class Set;}


namespace dat::set::gui{

class Panel
{
public:
  //Constructor / Destructor
  Panel(dat::elm::Node* node_element);
  ~Panel();

  //Main function
  void run_panel();
  void design_panel();
  void close_panel();

  //Sub functions
  void set_info(std::shared_ptr<dat::base::Set> set);
  void set_parameter(std::shared_ptr<dat::base::Set> set);

  inline void set_selected_set(std::shared_ptr<dat::base::Set> set){this->set = set;}
  inline void show_panel(bool value){this->panel_show = value;}

private:
  dat::elm::Set* dat_set;

  std::weak_ptr<dat::base::Set> set;
  std::string panel_name;
  bool panel_show;;
  int item_width;
};

}
