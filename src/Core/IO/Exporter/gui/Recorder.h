#pragma once

#include <Utility/GUI/Navigator/Navigator.h>
#include <imgui/core/imgui.h>
#include <memory>
#include <string>
#include <vector>

namespace io::exp{class Node;}
namespace io::exp{class Structure;}
namespace dat::base{class Sensor;}
namespace dat::ply{class Button;}
namespace dat::gph{class Selection;}
namespace dat::base{class Entity;}
namespace utl::gui::navigator{class Item;}
namespace utl::base{class Element;}


namespace io::exp::gui{

class Recorder
{
public:
  //Constructor / Destructor
  Recorder(io::exp::Node* node_exporter);
  ~Recorder();

public:
  //Main function
  void draw_header(std::shared_ptr<utl::base::Element> element);

  //Header function
  void display_action(std::shared_ptr<dat::base::Sensor> sensor);
  void display_path();
  void display_format();

  //Subfunction
  void item_filtering(std::vector<std::string>& vec_path);
  void item_update(std::shared_ptr<dat::base::Sensor> sensor);
  void item_operation(std::shared_ptr<dat::base::Entity> entity);

private:
  io::exp::Structure* io_struct;
  dat::ply::Button* ply_button;
  dat::gph::Selection* gph_selection;

  std::vector<std::string> vec_format;
};

}
