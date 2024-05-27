#pragma once

#include <Loader/gui/Navigator/Navigator.h>
#include <imgui/core/imgui.h>
#include <string>
#include <vector>

namespace ldr{class Node;}
namespace dat{class Graph;}
namespace ldr::io{class Importer;}
namespace ldr::gui{class File;}
namespace ldr::bookmark{class Manager;}
namespace dat{class Set;}
namespace ope{class Transformation;}
namespace ope{class Operation;}
namespace dat::base{class Entity;}


namespace ldr::gui{

class Loader : public ldr::gui::Navigator
{
public:
  //Constructor / Destructor
  Loader(ldr::Node* node_loader, bool* show_window);
  ~Loader();

public:
  //Main function
  void run_panel();
  void design_panel();

  //Subfunction
  void draw_header();
  void draw_bookmark_tab();

  //Operation function
  void item_selection();
  void operation_bookmark(std::string path);
  void operation_entity(dat::base::Entity* entity);

private:
  dat::Graph* dat_graph;
  ldr::io::Importer* ldr_importer;
  ldr::bookmark::Manager* ldr_bookmark;
  dat::Set* dat_set;
  ope::Transformation* ope_transform;
  ope::Operation* ope_operation;

  float param_scaling = 1;
  bool param_remove_old = true;
  bool param_centered = true;
  bool goto_file_tab = false;

  std::string name;
  bool* show_window;
};

}
