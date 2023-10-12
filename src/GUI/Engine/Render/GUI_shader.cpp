#include "GUI_shader.h"

#include <GUI.h>
#include <Engine.h>
#include <Vulkan/Shader/VK_reload.h>
#include <Vulkan/VK_engine.h>
#include <Shader/Shader.h>
#include <Shader/EDL/EDL_shader.h>
#include <Shader/Canvas/CAN_shader.h>
#include <Shader/Scene/SCE_shader.h>
#include <Element/Editor/GUI_editor_text.h>


//Constructor / Destructor
GUI_shader::GUI_shader(GUI* gui, bool* show_window, string name) : BASE_panel(show_window, name){
  //---------------------------

  Engine* engine = gui->get_engine();
  VK_engine* vk_engine = engine->get_vk_engine();
  this->vk_reload = vk_engine->get_vk_reload();
  this->shaderManager = engine->get_shaderManager();
  this->editor_vs = new GUI_editor_text();
  this->editor_fs = new GUI_editor_text();

  this->with_parameter = false;
  this->item_width = 100;
  this->ID_class = 0;
  this->ID_subclass = 0;

  //---------------------------
  this->init_panel();
}
GUI_shader::~GUI_shader(){}

//Main function
void GUI_shader::init_panel(){
  //---------------------------

  vec_shader_class.push_back("Scene");
  vec_shader_class.push_back("EDL");
  vec_shader_class.push_back("Canvas");

  this->retrieve_shader_subclasses();
  this->shader_file_selection();

  //---------------------------
}
void GUI_shader::design_panel(){
  //---------------------------

  this->shader_combo_class();
  this->shader_combo_subclass();
  this->shader_command();
  this->shader_tabs();

  //---------------------------
}

//Design fnunction
void GUI_shader::shader_combo_class(){
  //---------------------------

  //Table list combo
  if(ImGui::BeginCombo("##shader_combo_class", vec_shader_class[ID_class].c_str())){
    for(int i=0; i<vec_shader_class.size(); ++i){
      const bool is_selected = (ID_class == i);
      if(ImGui::Selectable(vec_shader_class[i].c_str(), is_selected)){
        this->ID_class = i;
        this->ID_subclass = 0;
        this->retrieve_shader_subclasses();
        this->shader_file_selection();
      }

      if(is_selected){
        ImGui::SetItemDefaultFocus();
      }
    }
    ImGui::EndCombo();
  }

  //---------------------------
}
void GUI_shader::shader_combo_subclass(){
  //---------------------------

  if(vec_shader_subclass.size() != 1){
    if(ImGui::BeginCombo("##shader_combo_subclass", vec_shader_subclass[ID_subclass].c_str())){
      for(int i=0; i<vec_shader_subclass.size(); ++i){
        const bool is_selected = (ID_subclass == i);
        if(ImGui::Selectable(vec_shader_subclass[i].c_str(), is_selected)){
          this->ID_subclass = i;
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

  //---------------------------
}
void GUI_shader::shader_command(){
  //---------------------------

  if(ImGui::Button("Reload")){
    string shader_1 = vec_shader_class[ID_class];
    string shader_2 = vec_shader_subclass[ID_subclass];
    vk_reload->hot_shader_reload(shader_1, shader_2);
  }
  ImGui::SameLine();

  if(ImGui::Button("Save to file")){
    EDL_shader* edl_shader = shaderManager->get_edl_shader();
    vector<Shader_info*> vec_shader_info = edl_shader->get_vec_shader_info();
    string title   = vec_shader_info[ID_subclass]->title;
    string file_vs = vec_shader_info[ID_subclass]->path_vs;
    string file_fs = vec_shader_info[ID_subclass]->path_fs;
    string path_vs = "../src/Engine/Shader/EDL/glsl/" + file_vs + ".vert";
    string path_fs = "../src/Engine/Shader/EDL/glsl/" + file_fs + ".frag";
    editor_vs->save_to_file(path_vs);
    editor_fs->save_to_file(path_fs);
  }
  ImGui::SameLine();

  if(ImGui::Button("Save to save")){

  }

  //---------------------------
}
void GUI_shader::shader_tabs(){
  //---------------------------

  if (ImGui::BeginTabBar("shader_editor")){
    if (ImGui::BeginTabItem("Vertex")){
        editor_vs->run_editor();
        ImGui::EndTabItem();
    }
    if (ImGui::BeginTabItem("Fragment")){
        editor_fs->run_editor();
        ImGui::EndTabItem();
    }
    if (with_parameter && ImGui::BeginTabItem("Parameter")){
        this->shader_EDL_parameter();
        ImGui::EndTabItem();
    }
    ImGui::EndTabBar();
  }

  //---------------------------
}

//Shader specific
void GUI_shader::shader_EDL_parameter(){
  EDL_shader* edl_shader = shaderManager->get_edl_shader();
  EDL_param* edl_param = edl_shader->get_edl_param();
  //---------------------------

  //if(ImGui::CollapsingHeader("Parameter")){
    ImGui::SetNextItemWidth(item_width);
    if(ImGui::Checkbox("Activated", &edl_param->activated)){
      edl_shader->update_shader();
    }

    ImGui::SetNextItemWidth(item_width);
    if(ImGui::SliderFloat("Radius", &edl_param->radius, 1.0f, 5.0f)){
      edl_shader->update_shader();
    }

    ImGui::SetNextItemWidth(item_width);
    if(ImGui::SliderFloat("Strength", &edl_param->strength, 1.0f, 100.0f)){
      edl_shader->update_shader();
    }
  //}

  //---------------------------
}
void GUI_shader::shader_EDL_file(){
  EDL_shader* edl_shader = shaderManager->get_edl_shader();
  //---------------------------

  string path_vs = edl_shader->get_glsl_path_vs(ID_subclass);
  string path_fs = edl_shader->get_glsl_path_fs(ID_subclass);
  editor_vs->load_from_file(path_vs);
  editor_fs->load_from_file(path_fs);

  //---------------------------
}
void GUI_shader::shader_Scene_file(){
  SCE_shader* sce_shader = shaderManager->get_sce_shader();
  //---------------------------

  string path_vs = sce_shader->get_glsl_path_vs(ID_subclass);
  string path_fs = sce_shader->get_glsl_path_fs(ID_subclass);
  editor_vs->load_from_file(path_vs);
  editor_fs->load_from_file(path_fs);

  //---------------------------
}
void GUI_shader::shader_Canvas_file(){
  CAN_shader* can_shader = shaderManager->get_can_shader();
  //---------------------------

  string path_vs = can_shader->get_glsl_path_vs(ID_subclass);
  string path_fs = can_shader->get_glsl_path_fs(ID_subclass);
  editor_vs->load_from_file(path_vs);
  editor_fs->load_from_file(path_fs);

  //---------------------------
}

//Subfunction
void GUI_shader::retrieve_shader_subclasses(){
  //---------------------------

  string selection = vec_shader_class[ID_class];

  vector<Shader_info*> vec_shader_info;
  if(selection == "EDL"){
    EDL_shader* edl_shader = shaderManager->get_edl_shader();
    vec_shader_info = edl_shader->get_vec_shader_info();
  }
  else if(selection == "Scene"){
    SCE_shader* sce_shader = shaderManager->get_sce_shader();
    vec_shader_info = sce_shader->get_vec_shader_info();
  }
  else if(selection == "Canvas"){
    CAN_shader* sce_shader = shaderManager->get_can_shader();
    vec_shader_info = sce_shader->get_vec_shader_info();
  }

  this->vec_shader_subclass.clear();
  for(int i=0; i<vec_shader_info.size(); i++){
    string title = vec_shader_info[i]->title;
    this->vec_shader_subclass.push_back(title);
  }

  //---------------------------
}
void GUI_shader::shader_file_selection(){
  //---------------------------

  string selection = vec_shader_class[ID_class];

  if(selection == "EDL"){
    this->shader_EDL_file();
    this->with_parameter = true;
  }
  else if(selection == "Scene"){
    this->shader_Scene_file();
    this->with_parameter = false;
  }
  else if(selection == "Canvas"){
    this->shader_Canvas_file();
    this->with_parameter = false;
  }

  //---------------------------
}
