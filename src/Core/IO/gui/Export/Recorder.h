#pragma once

#include <Utility/GUI/Navigator/Navigator.h>
#include <imgui/core/imgui.h>
#include <string>
#include <vector>

namespace io{class Node;}
namespace io{class Structure;}
namespace utl::gui::navigator{class Item;}
namespace utl::base{class Element;}
namespace dyn{class Structure;}
namespace dyn::base{class Sensor;}
namespace dyn::player{class Player;}
namespace dat::graph{class Selection;}
namespace dat::base{class Entity;}


namespace io::gui::exporter{

class Recorder
{
public:
  //Constructor / Destructor
  Recorder(io::Node* node_io);
  ~Recorder();

public:
  //Main function
  void draw_header(utl::base::Element* element);

  //Header function
  void display_action(dyn::base::Sensor* sensor);
  void display_path();
  void display_format();

  //Subfunction
  void item_filtering(std::vector<std::string>& vec_path);
  void item_update(dyn::base::Sensor* sensor);
  void item_operation(dat::base::Entity* entity);

private:
  dyn::player::Player* dyn_player;
  dyn::Structure* dyn_struct;
  io::Structure* io_struct;
  dat::graph::Selection* dat_selection;

  std::vector<std::string> vec_format;
};

}
