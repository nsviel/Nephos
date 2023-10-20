#ifndef GUI_SHADER_H
#define GUI_SHADER_H

#include <Specific/common.h>
#include <Panel/BASE_panel.h>

class GUI;
class GUI_editor_text;
class Shader;
class VK_reload;


class GUI_shader : public BASE_panel
{
public:
  //Constructor / Destructor
  GUI_shader(GUI* gui, bool* show_window, string name);
  ~GUI_shader();

public:
  //Main function
  void init_panel();
  void design_panel();

  //Design function
  void shader_combo_class();
  void shader_combo_subclass();
  void shader_command();
  void shader_tabs();

  //Shader specific
  void shader_EDL_parameter();
  void check_reload();
  void display_reload();
  void shader_control();
  void reload_vulkan_shader();

  //Subfunction
  void retrieve_shader_subclasses();
  void shader_file_selection();
  string get_path_vs_from_selection();
  string get_path_fs_from_selection();

private:
  VK_reload* vk_reload;
  Shader* shaderManager;
  GUI_editor_text* editor_vs;
  GUI_editor_text* editor_fs;

  vector<string> vec_shader_class;
  vector<string> vec_shader_subclass;
  string active_editor;
  string reload;
  string current_status;
  bool with_parameter;
  bool has_been_reloaded;
  int item_width;
  int ID_class;
  int ID_subclass;
};

#endif
