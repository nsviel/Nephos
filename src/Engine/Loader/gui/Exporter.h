#pragma once

#include <imgui/core/imgui.h>
#include <string>
#include <vector>

namespace ldr{class Node;}


namespace ldr::gui{

class Exporter
{
public:
  //Constructor / Destructor
  Exporter(ldr::Node* node_loader, bool* show_window);
  ~Exporter();

public:
  //Main function
  void run_panel();
  void design_panel();

  //File stuff
  void draw_file();
  void draw_file_header();
  void draw_file_content();

private:
  std::string default_dir;
  std::string current_dir;

  std::string name;
  bool* show_window;
};

}
