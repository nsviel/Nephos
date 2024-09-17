#include "Shader.h"

#include <Engine/Renderer/Namespace.h>
#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace rnd{

//Constructor / Destructor
Shader::Shader(rnd::Node* node_renderer){
  //---------------------------

  vk::Node* node_vulkan = node_renderer->get_node_vulkan();
  vk::Structure* vk_struct = node_vulkan->get_vk_struct();

  this->vk_reload = new vk::shader::Reloader(vk_struct);
  //this->vk_render = node_vulkan->get_vk_render();
  this->node_core = node_core;
  this->gui_console = new utl::gui::widget::Console();

  this->item_width = 100;
  this->ID_class = 0;
  this->ID_subclass = 0;
  this->has_been_reloaded = true;
  this->read_only = false;
  this->read_only_forced = false;

  //---------------------------
}
Shader::~Shader(){}

//Main function
void Shader::init(){
  //---------------------------
/*
  vec_shader_class.push_back("Scene");
  vec_shader_class.push_back("EDL");
  vec_shader_class.push_back("Canvas");

  this->retrieve_shader_subclasses();
  this->shader_file_selection();
*/
  //---------------------------
}
void Shader::design_panel(){
  //---------------------------
/*
  this->check_read_only();
  this->check_reload();
  this->shader_combo_class();
  this->shader_combo_subclass();
  this->shader_command();
  this->shader_tabs();
  this->shader_control();

  /*
  std::string message = LOG_shader::get_instance().get_shader_printf();
  gui_console->add_log(message);
  gui_console->add_file("error", "output.txt");
  gui_console->draw_console("truc");
  */

  //---------------------------
}

//File selection
void Shader::retrieve_shader_subclasses(){
  //---------------------------

  std::string selection = vec_shader_class[ID_class];

  std::vector<vk::shader::structure::Info*> vec_shader_info;
  if(selection == "EDL"){
    //vk::render::edl::Shader* shader_edl = vk_render->get_shader_edl();
    //vec_shader_info = shader_edl->get_vec_shader_info();
  }
  else if(selection == "Scene"){
    //vk::render::geometry::Shader* shader_scene = vk_render->get_shader_scene();
    //vec_shader_info = shader_scene->get_vec_shader_info();
  }

  this->vec_shader_subclass.clear();
  for(int i=0; i<vec_shader_info.size(); i++){
    std::string& name = vec_shader_info[i]->name;
    this->vec_shader_subclass.push_back(name);
  }

  //---------------------------
}
std::string Shader::get_path_vs_from_selection(){
  //---------------------------

  std::string selection = vec_shader_class[ID_class];
  std::string path_vs = "";

  if(selection == "EDL"){
    //vk::render::edl::Shader* shader_edl = vk_render->get_shader_edl();
    //path_vs = shader_edl->get_glsl_path_vs(ID_subclass);
  }
  else if(selection == "Scene"){
    //vk::render::geometry::Shader* shader_scene = vk_render->get_shader_scene();
    //path_vs = shader_scene->get_glsl_path_vs(ID_subclass);
  }

  //---------------------------
  return path_vs;
}
std::string Shader::get_path_fs_from_selection(){
  //---------------------------

  std::string selection = vec_shader_class[ID_class];
  std::string path_fs = "";

  if(selection == "EDL"){
    //vk::render::edl::Shader* shader_edl = vk_render->get_shader_edl();
    //path_fs = shader_edl->get_glsl_path_fs(ID_subclass);
  }
  else if(selection == "Scene"){
    //vk::render::geometry::Shader* shader_scene = vk_render->get_shader_scene();
    //path_fs = shader_scene->get_glsl_path_fs(ID_subclass);
  }

  //---------------------------
  return path_fs;
}

//Parameter
void Shader::show_parameter(){
  //---------------------------

  if(current_class == "EDL"){
    this->parameter_EDL();
  }

  //---------------------------
}
void Shader::parameter_EDL(){
  /*vk::render::edl::Shader* shader_edl = vk_render->get_shader_edl();
  vk::render::structure::EDL* edl_param = shader_edl->get_edl_struct();
  //---------------------------

  ImGui::SetNextItemWidth(item_width);
  if(ImGui::Checkbox("Activated", &edl_param->activated)){
    shader_edl->update_shader();
  }

  ImGui::SetNextItemWidth(item_width);
  if(ImGui::SliderFloat("Radius", &edl_param->radius, 1.0f, 5.0f)){
    shader_edl->update_shader();
  }

  ImGui::SetNextItemWidth(item_width);
  if(ImGui::SliderFloat("Strength", &edl_param->strength, 1.0f, 100.0f)){
    shader_edl->update_shader();
  }*/

  //---------------------------
}

//Shader specific
void Shader::check_reload(){
  //---------------------------

  bool has_vs_changed = editor_vs->is_text_changed();
  bool has_fs_changed = editor_fs->is_text_changed();
  if(has_vs_changed || has_fs_changed){
    has_been_reloaded = false;
  }

  //---------------------------
}
void Shader::reload_vulkan_shader(){
  //---------------------------

  gui_console->clear_log();
  std::string shader_class = vec_shader_class[ID_class];
  std::string shader_subclass = vec_shader_subclass[ID_subclass];
  vk_reload->hot_shader_reload(shader_class, shader_subclass);
  this->has_been_reloaded = true;

  //---------------------------
}


}
