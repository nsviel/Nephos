#include "Shader.h"

#include <Engine/Renderer/Namespace.h>
#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace rnd::gui{

//Constructor / Destructor
Shader::Shader(rnd::Node* node_renderer, bool* show_window){
  //---------------------------

  vk::Node* node_vulkan = node_renderer->get_node_vulkan();
  vk::Structure* vk_struct = node_vulkan->get_vk_struct();

  this->vk_reload = new vk::shader::Reloader(vk_struct);
//  this->vk_render = node_vulkan->get_vk_render();
  this->node_core = node_core;
  this->editor_vs = new utl::gui::editor::Text();
  this->editor_fs = new utl::gui::editor::Text();
  this->gui_console = new utl::gui::widget::Console();
  this->itf_shader = node_renderer->get_rnd_shader();

  this->item_width = 100;
  this->ID_class = 0;
  this->ID_subclass = 0;
  this->has_been_reloaded = true;
  this->read_only = false;
  this->read_only_forced = false;
  this->show_window = show_window;
  this->name = "Shader";

  editor_vs->set_language("glsl");
  editor_fs->set_language("glsl");

  //---------------------------
}
Shader::~Shader(){}

//Main function
void Shader::run_panel(){
  //---------------------------

  if(*show_window){
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1, 0.1, 0.1, 1));
    ImGui::SetNextWindowSizeConstraints(ImVec2(300, 300), ImVec2(FLT_MAX, 500));
    if(ImGui::Begin(name.c_str(), show_window, ImGuiWindowFlags_AlwaysAutoResize) == 1){

      this->design_panel();

      ImGui::End();
    }
    ImGui::PopStyleColor();
  }

  //---------------------------
}
void Shader::design_panel(){
  //---------------------------
/*
  this->check_read_only();
  this->check_reload();
  itf_shader->shader_combo_class();
  itf_shader->shader_combo_subclass();
  itf_shader->shader_command();
  itf_shader->shader_tabs();
  itf_shader->shader_control();
*/
  //---------------------------
}
void Shader::check_read_only(){
  //---------------------------
/*
  bool window_hovered = ImGui::IsWindowHovered(ImGuiHoveredFlags_ChildWindows|ImGuiHoveredFlags_AllowWhenBlockedByActiveItem);
  if(window_hovered == false || read_only_forced){
    this->read_only = true;
  }
  else if(window_hovered && read_only_forced == false){
    this->read_only = false;
  }
  else if(window_hovered && read_only_forced){
    this->read_only = true;
  }

  editor_vs->set_read_only(read_only);
  editor_fs->set_read_only(read_only);
*/
  //---------------------------
}
void Shader::check_reload(){
  //---------------------------
/*
  bool has_vs_changed = editor_vs->is_text_changed();
  bool has_fs_changed = editor_fs->is_text_changed();
  if(has_vs_changed || has_fs_changed){
    has_been_reloaded = false;
  }
*/
  //---------------------------
}


//Design fnunction
void Shader::shader_combo_class(){
  //---------------------------
/*
  if(ImGui::BeginCombo("##shader_combo_class", vec_shader_class[ID_class].c_str())){
    for(int i=0; i<vec_shader_class.size(); ++i){
      const bool is_selected = (ID_class == i);
      if(ImGui::Selectable(vec_shader_class[i].c_str(), is_selected)){
        this->ID_class = i;
        this->ID_subclass = 0;
        this->current_class = vec_shader_class[i];
        this->retrieve_shader_subclasses();
        this->shader_file_selection();
      }

      if(is_selected){
        ImGui::SetItemDefaultFocus();
      }
    }
    ImGui::EndCombo();
  }
*/
  //---------------------------
}
void Shader::shader_combo_subclass(){
  //---------------------------
/*
  if(vec_shader_subclass.size() > 1){
    if(ImGui::BeginCombo("##shader_combo_subclass", vec_shader_subclass[ID_subclass].c_str())){
      for(int i=0; i<vec_shader_subclass.size(); ++i){
        const bool is_selected = (ID_subclass == i);
        if(ImGui::Selectable(vec_shader_subclass[i].c_str(), is_selected)){
          this->ID_subclass = i;
          this->current_subclass = vec_shader_subclass[i];
          this->shader_file_selection();
        }

        if(is_selected){
          ImGui::SetItemDefaultFocus();
        }
      }
      ImGui::EndCombo();
    }
  }else{
    this->ID_subclass = 0;
  }
*/
  //---------------------------
}
void Shader::shader_command(){
  //---------------------------
/*
  //Button commands
  if(ImGui::Button("Reload", ImVec2(item_width, 0))){
    this->reload_vulkan_shader();
  }
  ImGui::SameLine();
  if(ImGui::Button("Save to file", ImVec2(item_width, 0))){
    std::string path_vs = get_path_vs_from_selection();
    std::string path_fs = get_path_fs_from_selection();
    editor_vs->save_to_file(path_vs);
    editor_fs->save_to_file(path_fs);
    this->reload_vulkan_shader();
  }
  ImGui::SameLine();
  if(ImGui::Checkbox("Read only##111", &read_only)){
    this->read_only_forced = read_only;
  }

  //Display status
  this->display_reload();
  ImGui::SameLine();
  this->display_status();
*/
  //---------------------------
}
void Shader::shader_tabs(){
  //---------------------------
/*
  if(ImGui::BeginTabBar("shader_editor")){
    if(ImGui::BeginTabItem("Vertex")){
        editor_vs->run_editor();
        this->active_editor = "Vertex";
        ImGui::EndTabItem();
    }
    if(ImGui::BeginTabItem("Fragment")){
        editor_fs->run_editor();
        this->active_editor = "Fragment";
        ImGui::EndTabItem();
    }
    if(ImGui::BeginTabItem("Parameter")){
        this->show_parameter();
        ImGui::EndTabItem();
    }
    ImGui::EndTabBar();
  }
*/
  //---------------------------
}

//File selection
void Shader::shader_file_selection(){
  //---------------------------
/*
  std::string path_vs = get_path_vs_from_selection();
  std::string path_fs = get_path_fs_from_selection();

  //Load shader into editors
  if(path_vs != "" && path_fs != ""){
    editor_vs->load_from_file(path_vs);
    editor_fs->load_from_file(path_fs);
  }
*/
  //---------------------------
}

//Parameter
void Shader::show_parameter(){
  //---------------------------

  if(current_class == "EDL"){
    this->parameter_EDL();
  }

  //---------------------------
}
void Shader::parameter_EDL(){/*
  vk::gfx::render::edl::Shader* shader_edl = vk_render->get_shader_edl();
  vk::gfx::render::structure::EDL* edl_param = shader_edl->get_edl_struct();
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
  }
*/
  //---------------------------
}

//Shader specific

void Shader::display_reload(){
  //---------------------------
/*
  std::string status;
  ImVec4 color;
  if(has_been_reloaded){
    color = ImVec4(0.4f, 1.0f, 0.4f, 1.0f);
    status = "OK";
  }
  else if(has_been_reloaded == false){
    color = ImVec4(1.0f,0.4f,0.4f,1.0f);
    status = "Not";
  }

  ImGui::TextColored(ImVec4(0.4f,0.4f,0.4f,1.0f), "Reload: ");
  ImGui::SameLine();
  ImGui::TextColored(color, "%s", status.c_str());
*/
  //---------------------------
}
void Shader::display_status(){
  //---------------------------

  if(active_editor == "Vertex"){
    this->current_status = editor_vs->get_status();
    editor_vs->display_status();
  }
  else if(active_editor == "Fragment"){
    this->current_status = editor_fs->get_status();
    editor_fs->display_status();
  }

  //---------------------------
}
void Shader::shader_control(){
  ImGuiIO io = ImGui::GetIO();
  //----------------------------
/*
  //CTRL + S - save to file
  if(io.KeysDown[527] && ImGui::IsKeyPressed(ImGuiKey_S)){
    this->reload_vulkan_shader();
  }
*/
  //----------------------------
}


}
