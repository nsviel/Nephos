#ifndef GUI_SHADER_H
#define GUI_SHADER_H

#include <Specific/common.h>
#include <Shader/Base/BASE_shader.h>
#include <RES_base/BASE_panel.h>

class GUI;
class GUI_editor_text;
class GUI_console;
class Shader;
class VK_reload;


class RND_shader : public BASE_panel
{
public:
  //Constructor / Destructor
  RND_shader(GUI* gui, bool* show_window, string name);
  ~RND_shader();

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
  VK_reload* vk_reload;
  Shader* shaderManager;
  GUI_editor_text* editor_vs;
  GUI_editor_text* editor_fs;
  GUI_console* gui_console;

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

#endif
