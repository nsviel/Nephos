#include "Glyph.h"

#include <Engine/Engine.h>
#include <Vulkan/Namespace.h>
#include <Engine/Render/Namespace.h>


namespace eng::renderpass{

//Constructor / Destructor
Glyph::Glyph(eng::render::Node* node_render){
  //---------------------------

  Engine* engine = node_render->get_engine();
  Vulkan* eng_vulkan = engine->get_eng_vulkan();
  vk::structure::Vulkan* struct_vulkan = eng_vulkan->get_struct_vulkan();

  this->node_render = engine->get_node_render();
  this->vk_engine = eng_vulkan->get_vk_engine();
  this->vk_pipeline = new VK_pipeline(struct_vulkan);
  this->vk_viewport = new VK_viewport(struct_vulkan);
  this->vk_descriptor = new VK_descriptor(struct_vulkan);
  this->vk_uniform = new VK_uniform(struct_vulkan);
  this->vk_drawing = new VK_drawing(struct_vulkan);

  //---------------------------
}
Glyph::~Glyph(){}

//Init function
void Glyph::init_renderpass(){
  //---------------------------

  //Renderpass
  vk::structure::Renderpass* renderpass = new vk::structure::Renderpass();
  renderpass->name = "scene";
  renderpass->target = "graphics";

  //Pipeline
  this->create_subpass(renderpass);

  //---------------------------
  vk_engine->add_renderpass_description(renderpass);
}
void Glyph::create_subpass(vk::structure::Renderpass* renderpass){
  eng::shader::SCE* sce_shader = node_render->get_sce_shader();
  //---------------------------

  vk::structure::Subpass* subpass = new vk::structure::Subpass();
  subpass->target = "shader";
  subpass->draw_task = [this](vk::structure::Subpass* subpass){Glyph::draw_scene(subpass);};

  vk::structure::Pipeline* pipeline;
  pipeline = new vk::structure::Pipeline();
  pipeline->definition.name = "line";
  pipeline->definition.topology = "line";
  pipeline->definition.purpose = "graphics";
  pipeline->definition.shader = sce_shader->get_shader_info("Line");
  pipeline->definition.vec_data_name.push_back("location");
  pipeline->definition.vec_data_name.push_back("color");
  pipeline->binding.vec_required_binding.push_back(std::make_tuple("mvp", sizeof(mat4), 0, TYP_UNIFORM, TYP_SHADER_VS));
  subpass->vec_pipeline.push_back(pipeline);

  pipeline = new vk::structure::Pipeline();
  pipeline->definition.name = "point";
  pipeline->definition.topology = "point";
  pipeline->definition.purpose = "graphics";
  pipeline->definition.shader = sce_shader->get_shader_info("Point");
  pipeline->definition.vec_data_name.push_back("location");
  pipeline->definition.vec_data_name.push_back("color");
  pipeline->binding.vec_required_binding.push_back(std::make_tuple("mvp", sizeof(mat4), 0, TYP_UNIFORM, TYP_SHADER_VS));
  pipeline->binding.vec_required_binding.push_back(std::make_tuple("point_size", sizeof(int), 1, TYP_UNIFORM, TYP_SHADER_VS));
  subpass->vec_pipeline.push_back(pipeline);

  //---------------------------
  renderpass->vec_subpass.push_back(subpass);
}

//Draw function
void Glyph::draw_scene(vk::structure::Subpass* subpass){
  timer_time t1 = timer.start_t();
  //---------------------------

  vk_viewport->cmd_viewport(subpass->command_buffer);
  this->cmd_draw_point(subpass);
  this->cmd_draw_line(subpass);

  //---------------------------
  this->time_renderpass = timer.stop_ms(t1);
}
void Glyph::cmd_draw_point(vk::structure::Subpass* subpass){
  list<vk::structure::Object*> list_data = vk_engine->get_list_data();
  //---------------------------

  vk::structure::Pipeline* pipeline = subpass->get_pipeline_byName("point");
  vk_pipeline->cmd_bind_pipeline(subpass->command_buffer, pipeline);

  //Bind and draw vertex buffers
  for(int i=0; i<list_data.size(); i++){
    vk::structure::Object* vk_object =  *next(list_data.begin(), i);
    bool& is_visible = vk_object->data->is_visible;
    bool is_point = vk_object->data->draw_type_name == "point";
    bool has_xyz = vk_object->data->xyz.size() != 0;
    bool has_rgb = vk_object->data->rgb.size() != 0;
    bool same_length = vk_object->data->rgb.size() == vk_object->data->xyz.size();

    if(is_visible && is_point && has_xyz && has_rgb){
      vk_uniform->update_uniform("mvp", &vk_object->binding, vk_object->pose->mvp);
      vk_uniform->update_uniform("point_size", &vk_object->binding, vk_object->data->draw_point_size);

      vk_descriptor->cmd_bind_descriptor(subpass->command_buffer, pipeline, vk_object->binding.descriptor.set);
      vk_drawing->cmd_draw_data(subpass->command_buffer, vk_object);
    }
  }

  //---------------------------
}
void Glyph::cmd_draw_line(vk::structure::Subpass* subpass){
  list<vk::structure::Object*> list_data = vk_engine->get_list_data();
  //---------------------------

  vk::structure::Pipeline* pipeline = subpass->get_pipeline_byName("line");
  vk_pipeline->cmd_bind_pipeline(subpass->command_buffer, pipeline);

  //Bind and draw vertex buffers
  for(int i=0; i<list_data.size(); i++){
    vk::structure::Object* vk_object =  *next(list_data.begin(), i);
    bool& is_visible = vk_object->data->is_visible;
    bool is_point = vk_object->data->draw_type_name == "line";
    bool has_xyz = vk_object->data->xyz.size() != 0;
    bool has_rgb = vk_object->data->rgb.size() != 0;
    bool same_length = vk_object->data->rgb.size() == vk_object->data->xyz.size();

    if(is_visible && is_point && has_xyz && has_rgb && same_length){
      vk_uniform->update_uniform("mvp", &vk_object->binding, vk_object->pose->mvp);

      vk_descriptor->cmd_bind_descriptor(subpass->command_buffer, pipeline, vk_object->binding.descriptor.set);
      vk_drawing->cmd_line_with(subpass->command_buffer, vk_object);
      vk_drawing->cmd_draw_data(subpass->command_buffer, vk_object);
    }
  }

  //---------------------------
}

}
