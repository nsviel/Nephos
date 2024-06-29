#pragma once

#include <string>
#include <vector>

namespace itf{class Node;}
namespace vk::shader{class Reloader;}
namespace vk::render{class Render;}
namespace eng{class Node;}
namespace utl::gui::widget{class Console;}
namespace utl::gui::editor{class Text;}


namespace itf::render{

class Shader
{
public:
  //Constructor / Destructor
  Shader(itf::Node* node_interface, bool* show_window);
  ~Shader();

public:
  //Main function
  void run_panel();
  void init_panel();
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
  vk::render::Render* vk_render;
  eng::Node* node_engine;
  utl::gui::editor::Text* editor_vs;
  utl::gui::editor::Text* editor_fs;
  utl::gui::widget::Console* gui_console;

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
