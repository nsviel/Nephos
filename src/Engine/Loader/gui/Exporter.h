#pragma once

#include <Loader/gui/Navigator.h>
#include <imgui/core/imgui.h>
#include <string>
#include <vector>

namespace ldr{class Node;}
namespace ldr::gui{class Bookmark;}


namespace ldr::gui{

class Exporter : public ldr::gui::Navigator
{
public:
  //Constructor / Destructor
  Exporter(ldr::Node* node_loader, bool* show_window);
  ~Exporter();

public:
  //Main function
  void run_panel();
  void design_panel();

  //Subfunction
  void draw_header();

private:
  std::vector<ldr::gui::Bookmark> vec_bookmark_folder;
  std::vector<ldr::gui::Bookmark> vec_bookmark_file;
  std::string default_dir = "";
  std::string current_dir = "";
  std::string current_path = "";
  std::string name = "";
  bool* show_window;
  int selection;
};

}
