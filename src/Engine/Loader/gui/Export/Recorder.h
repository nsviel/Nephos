#pragma once

#include <Loader/gui/Navigator/Navigator.h>
#include <imgui/core/imgui.h>
#include <string>
#include <vector>

namespace ldr{class Node;}
namespace ldr{class Structure;}
namespace ldr::gui{class File;}
namespace dyn{class Structure;}
namespace dyn::base{class Sensor;}
namespace dyn::player{class Player;}
namespace dat{class Selection;}


namespace ldr::gui::exporter{

class Recorder
{
public:
  //Constructor / Destructor
  Recorder(ldr::Node* node_loader);
  ~Recorder();

public:
  //Main function
  void design_header(dyn::base::Sensor* sensor);

  //Header function
  void display_action(dyn::base::Sensor* sensor);
  void display_path();
  void display_format();

  //Subfunction
  void item_filtering(std::vector<std::string>& vec_path);
  void item_update(dyn::base::Sensor* sensor);
  void item_operation();

private:
  dyn::player::Player* dyn_player;
  dyn::Structure* dyn_struct;
  ldr::Structure* ldr_struct;
  dat::Selection* dat_selection;

  std::vector<std::string> vec_format;
};

}
