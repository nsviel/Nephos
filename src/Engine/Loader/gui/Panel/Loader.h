#pragma once

#include <Loader/gui/Navigator/Navigator.h>
#include <imgui/core/imgui.h>
#include <string>
#include <vector>

namespace ldr{class Node;}
namespace ldr{class Structure;}
namespace ldr::io{class Importer;}
namespace ldr::gui{class File;}
namespace ldr::bookmark{class Manager;}
namespace dat{class Graph;}
namespace dat{class Set;}
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
  void item_operation();
  bool item_format(std::string format);
  void item_bookmark(std::string path);

private:
  ldr::Structure* ldr_struct;
  ldr::io::Importer* ldr_importer;
  ldr::bookmark::Manager* ldr_bookmark;
  dat::Set* dat_set;
  dat::Graph* dat_graph;

  std::string name;
  bool goto_file_tab = false;
  bool* show_window;
};

}
