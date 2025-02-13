#pragma once

#include <string>
#include <vector>

namespace rnd{class Node;}
namespace vk::shader{class Reloader;}
namespace vk::gfx::render{class Render;}
namespace core{class Node;}
namespace utl::gui::terminal{class Terminal;}
namespace utl::gui::editor{class Text;}


namespace rnd{

class Shader
{
public:
  //Constructor / Destructor
  Shader(rnd::Node* node_renderer);
  ~Shader();

public:
  //Main function
  void init();
  void design_panel();

  //Design function
  void shader_combo_class();
  void shader_combo_subclass();
  void shader_command();
  void shader_tabs();

  //Parameter
  void show_parameter();
  void parameter_EDL();

  //Shader specific
  void check_reload();
  void display_reload();
  void display_status();
  void shader_control();
  void reload_vulkan_shader();
  void check_read_only();

  //Subfunction
  void retrieve_shader_subclasses();
  void shader_file_selection();
  std::string get_path_vs_from_selection();
  std::string get_path_fs_from_selection();

private:
  vk::shader::Reloader* vk_reload;
  vk::gfx::render::Render* vk_render;
  core::Node* node_core;
  utl::gui::editor::Text* editor_vs;
  utl::gui::editor::Text* editor_fs;
  utl::gui::terminal::Terminal* gui_console;

  std::vector<std::string> vec_shader_class;
  std::vector<std::string> vec_shader_subclass;
  std::string active_editor;
  std::string reload;
  std::string current_status;
  std::string current_class;
  std::string current_subclass;
  bool has_been_reloaded;
  bool read_only;
  bool read_only_forced;
  int item_width;
  int ID_class;
  int ID_subclass;

  std::string name;
  bool* show_window;
};

}
