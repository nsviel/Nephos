#pragma once

#include <Utility/GUI/Navigator/Navigator.h>
#include <imgui/core/imgui.h>
#include <memory>
#include <string>
#include <vector>

namespace io::exp{class Node;}
namespace io::exp{class Structure;}
namespace io::exp{class Exporter;}
namespace utl::gui::navigator{class Item;}
namespace dat::gph{class Selection;}
namespace dat::base{class Entity;}
namespace utl::base{class Element;}


namespace io::exp::gui{

class Exporter
{
public:
  //Constructor / Destructor
  Exporter(io::exp::Node* node_exporter);
  ~Exporter();

public:
  //Main function
  void draw_header(std::shared_ptr<utl::base::Element> element);

  //Header function
  void display_action();
  void display_path(std::shared_ptr<utl::base::Element> element);
  void display_format();
  void display_encording();
  void display_option();

  //Subfunction
  void item_filtering(std::vector<std::string>& vec_path);
  void item_update(std::shared_ptr<utl::base::Element> element);
  void item_operation(std::shared_ptr<dat::base::Entity> entity);

private:
  io::exp::Structure* io_struct;
  io::exp::Exporter* io_exporter;
  dat::gph::Selection* gph_selection;
};

}
