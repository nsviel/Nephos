#pragma once

#include <Utility/GUI/Navigator/Navigator.h>
#include <imgui/core/imgui.h>
#include <string>
#include <vector>

namespace ldr{class Node;}
namespace ldr{class Structure;}
namespace ldr::io{class Exporter;}
namespace utl::gui::navigator{class Item;}
namespace dat::graph{class Selection;}
namespace dat::base{class Entity;}
namespace utl::base{class Element;}


namespace ldr::gui::exporter{

class Exporter
{
public:
  //Constructor / Destructor
  Exporter(ldr::Node* node_loader);
  ~Exporter();

public:
  //Main function
  void draw_header(utl::base::Element* element);

  //Header function
  void display_action();
  void display_path(utl::base::Element* element);
  void display_format();
  void display_encording();
  void display_option();

  //Subfunction
  void item_filtering(std::vector<std::string>& vec_path);
  void item_update(utl::base::Element* element);
  void item_operation(dat::base::Entity* entity);

private:
  ldr::Structure* ldr_struct;
  ldr::io::Exporter* ldr_exporter;
  dat::graph::Selection* dat_selection;
};

}
