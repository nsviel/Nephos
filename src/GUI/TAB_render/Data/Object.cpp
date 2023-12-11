#include "Object.h"

#include <Node/GUI.h>
#include <Engine/Node/Engine.h>
#include <Engine/ENG_data/ENG_scene/ENG_scene.h>
#include <image/IconsFontAwesome5.h>


namespace gui::rnd::panel{

//Constructor / Destructor
Object::Object(GUI* gui, bool* panel_show){
  //---------------------------

  Engine* engine = gui->get_engine();
  eng::data::ENG_data* eng_data = engine->get_eng_data();
  this->eng_scene = eng_data->get_eng_scene();

  this->panel_show = panel_show;
  this->panel_name = "Object";
  this->item_width = 150;

  //---------------------------
}
Object::~Object(){}

//Main function
void Object::run_panel(){
  //---------------------------

  if(*panel_show){
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1, 0.1, 0.1, 1));
    if(ImGui::Begin(panel_name.c_str(), panel_show, ImGuiWindowFlags_AlwaysAutoResize) == 1){

      this->design_panel();

      ImGui::End();
    }
    ImGui::PopStyleColor();
  }

  //---------------------------
}
void Object::design_panel(){
  //---------------------------

  this->object_info(object_selected);
  this->object_parameter(object_selected);

  //---------------------------
}

//Subfunction
void Object::object_info(eng::structure::Object* object){
  //---------------------------

  this->panel_name = "Object " + object->name;

  //---------------------------
}
void Object::object_parameter(eng::structure::Object* object){
  ImGui::Columns(2);
  //---------------------------

  //Visibility
  ImGui::Text("Visibility");
  ImGui::NextColumn();
  ImGui::Checkbox("##4555", &object->is_visible);
  if(object->is_suppressible){
    ImGui::SameLine();
    if(ImGui::Button(ICON_FA_TRASH "##4567")){
      eng_scene->delete_scene_object(object);
      this->object_selected = nullptr;
    }
  }
  ImGui::NextColumn();

  //Name
  ImGui::SetColumnWidth(-1,75);
  ImGui::Text("Name");
  ImGui::NextColumn();
  static char str_n[256];
  strcpy(str_n, object->name.c_str());
  if(ImGui::InputText("##name", str_n, IM_ARRAYSIZE(str_n), ImGuiInputTextFlags_EnterReturnsTrue)){
    object->name = str_n;
  }
  ImGui::NextColumn();

  //Format
  ImGui::Text("Format ");
  ImGui::NextColumn();
  static char str_f[256];
  strcpy(str_f, object->file_format.c_str());
  if(ImGui::InputText("##format", str_f, IM_ARRAYSIZE(str_f), ImGuiInputTextFlags_EnterReturnsTrue)){
    object->file_format = str_f;
  }
  ImGui::NextColumn();

  //Uniform collection color
  ImGui::Text("Uniform color");
  ImGui::NextColumn();
  ImGuiColorEditFlags flags = ImGuiColorEditFlags_NoInputs;
  flags |= ImGuiColorEditFlags_AlphaBar;
  if(ImGui::ColorEdit4("Color", (float*)&object->unicolor, flags)){
    //colorManager->set_color_new(object, object->unicolor);
  }
  ImGui::NextColumn();

  //Root pos
  vec3& root = object->root;
  ImGui::Text("Root ");
  ImGui::NextColumn();
  ImGui::Text("%.2f  %.2f  %.2f", root.x, root.y, root.z);
  ImGui::SameLine();
  if(ImGui::Button("R", ImVec2(15,0))){
    root = vec3(0,0,0);
  }
  ImGui::NextColumn();

  //Primitive size
  if(object->draw_type_name == "point"){
    //Number of points
    ImGui::Text("Nb point");
    ImGui::NextColumn();
    string nb_point = math::thousand_separator(object->nb_point);
    ImGui::Text("%s", nb_point.c_str());
    ImGui::NextColumn();

    this->size_point(object);
  }
  else if(object->draw_type_name == "line"){
    this->width_line(object);
  }

  //---------------------------
  ImGui::Columns(1);
  //ImGui::Separator();
}

//Primitive size
void Object::width_line(eng::structure::Object* object){
  ImGuiStyle& style = ImGui::GetStyle();
  //---------------------------

  //Column 1
  ImGui::SetNextItemWidth(item_width);
  ImGui::AlignTextToFramePadding();
  ImGui::Text("Line width ");
  ImGui::NextColumn();

  //Column 2
  ImGui::PushButtonRepeat(true);
  if(ImGui::ArrowButton("##left", ImGuiDir_Left)){
    object->draw_line_width--;

    if(object->draw_line_width <= 1){
      object->draw_line_width = 1;
    }
  }
  ImGui::SameLine(0.0f, style.ItemInnerSpacing.x);
  if(ImGui::ArrowButton("##right", ImGuiDir_Right)){
    object->draw_line_width++;
  }
  ImGui::PopButtonRepeat();
  ImGui::SameLine();
  ImGui::Text("%d", object->draw_line_width);

  //---------------------------
}
void Object::size_point(eng::structure::Object* object){
  ImGuiStyle& style = ImGui::GetStyle();
  //---------------------------

  //Column 1
  ImGui::SetNextItemWidth(item_width);
  ImGui::AlignTextToFramePadding();
  ImGui::Text("Point size ");
  ImGui::NextColumn();

  //Column 2
  ImGui::PushButtonRepeat(true);
  if(ImGui::ArrowButton("##left", ImGuiDir_Left)){
    object->draw_point_size--;

    if(object->draw_point_size <= 1){
      object->draw_point_size = 1;
    }
  }
  ImGui::SameLine(0.0f, style.ItemInnerSpacing.x);
  if(ImGui::ArrowButton("##right", ImGuiDir_Right)){
    object->draw_point_size++;
  }
  ImGui::PopButtonRepeat();
  ImGui::SameLine();
  ImGui::Text("%d", object->draw_point_size);

  //---------------------------
}

}
