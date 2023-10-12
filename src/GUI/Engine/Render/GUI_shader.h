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
  void shader_EDL_file();
  void shader_Scene_file();
  void shader_Canvas_file();

  //Subfunction
  void retrieve_shader_subclasses();
  void shader_file_selection();

private:
  VK_reload* vk_reload;
  Shader* shaderManager;
  GUI_editor_text* editor_vs;
  GUI_editor_text* editor_fs;

  vector<string> vec_shader_class;
  vector<string> vec_shader_subclass;
  bool with_parameter;
  int item_width;
  int ID_class;
  int ID_subclass;
};

#endif
