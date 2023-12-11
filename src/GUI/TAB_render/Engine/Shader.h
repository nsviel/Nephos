#pragma once

#include <Utility/Specific/common.h>
#include <Engine/Render/ENG_shader/Base/BASE_shader.h>
#include <Engine/Render/Namespace.h>
#include <GUI/GUI_utility/Base/Namespace.h>
#include <GUI/GUI_utility/Editor/Namespace.h>
#include <GUI/GUI_utility/Widget/Namespace.h>

class GUI;
class Text;
class VK_engine;


namespace gui::engine{

class Shader : public gui::base::Panel
{
public:
  //Constructor / Destructor
  Shader(GUI* gui, bool* show_window, string name);
  ~Shader();

public:
  //Main function
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
  string get_path_vs_from_selection();
  string get_path_fs_from_selection();

private:
  VK_engine* vk_engine;
  eng::shader::ENG_shader* eng_shader;
  gui::editor::Text* editor_vs;
  gui::editor::Text* editor_fs;
  gui::widget::Console* gui_console;

  vector<string> vec_shader_class;
  vector<string> vec_shader_subclass;
  string active_editor;
  string reload;
  string current_status;
  string current_class;
  string current_subclass;
  bool has_been_reloaded;
  bool read_only;
  bool read_only_forced;
  int item_width;
  int ID_class;
  int ID_subclass;
};

}
