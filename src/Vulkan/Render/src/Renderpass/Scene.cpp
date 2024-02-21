#include "Scene.h"

#include <Vulkan/Namespace.h>


namespace vk::renderpass{

//Constructor / Destructor
Scene::Scene(vk::Node* node_vulkan){
  //---------------------------

  vk::render::Node* node_render = node_vulkan->get_node_render();
  vk::structure::Vulkan* struct_vulkan = node_vulkan->get_struct_vulkan();

  this->shader_scene = node_render->get_shader_scene();
  this->vk_graphical = node_vulkan->get_vk_graphical();
  this->vk_pipeline = new vk::renderpass::Pipeline(struct_vulkan);
  this->vk_viewport = new vk::draw::Viewport(struct_vulkan);
  this->vk_descriptor = new vk::binding::Descriptor(struct_vulkan);
  this->vk_uniform = new vk::binding::Uniform(struct_vulkan);
  this->vk_drawing = new vk::draw::Graphical(struct_vulkan);

  //---------------------------
}
Scene::~Scene(){}

//Init function
void Scene::init_renderpass(){
  //---------------------------

  //Renderpass
  vk::structure::Renderpass* renderpass = new vk::structure::Renderpass();
  renderpass->name = "scene";
  renderpass->target = "graphics";

  //Pipeline
  this->create_subpass(renderpass);

  //---------------------------
  vk_graphical->add_renderpass_description(renderpass);
}
void Scene::create_subpass(vk::structure::Renderpass* renderpass){
  //---------------------------

  vk::structure::Subpass* subpass = new vk::structure::Subpass();
  subpass->target = "shader";
  subpass->draw_task = [this](vk::structure::Subpass* subpass){Scene::draw_scene(subpass);};

  //Line pipeline
  vk::structure::Pipeline* pipeline;
  pipeline = new vk::structure::Pipeline();
  pipeline->definition.name = "line";
  pipeline->definition.topology = "line";
  pipeline->definition.purpose = "graphics";
  pipeline->definition.shader = shader_scene->get_shader_info("Line");
  pipeline->definition.vec_data_name.push_back("location");
  pipeline->definition.vec_data_name.push_back("color");
  pipeline->binding.vec_required_binding.push_back(std::make_tuple("mvp", sizeof(mat4), 0, TYP_UNIFORM, TYP_SHADER_VS));
  subpass->vec_pipeline.push_back(pipeline);

  //Point pipeline
  pipeline = new vk::structure::Pipeline();
  pipeline->definition.name = "point";
  pipeline->definition.topology = "point";
  pipeline->definition.purpose = "graphics";
  pipeline->definition.shader = shader_scene->get_shader_info("Point");
  pipeline->definition.vec_data_name.push_back("location");
  pipeline->definition.vec_data_name.push_back("color");
  pipeline->binding.vec_required_binding.push_back(std::make_tuple("mvp", sizeof(mat4), 0, TYP_UNIFORM, TYP_SHADER_VS));
  pipeline->binding.vec_required_binding.push_back(std::make_tuple("point_size", sizeof(int), 1, TYP_UNIFORM, TYP_SHADER_VS));
  subpass->vec_pipeline.push_back(pipeline);

  //Triangle pipeline
  pipeline = new vk::structure::Pipeline();
  pipeline->definition.name = "triangle";
  pipeline->definition.topology = "triangle";
  pipeline->definition.purpose = "graphics";
  pipeline->definition.shader = shader_scene->get_shader_info("Triangle");
  pipeline->definition.vec_data_name.push_back("location");
  pipeline->definition.vec_data_name.push_back("color");
  pipeline->binding.vec_required_binding.push_back(std::make_tuple("mvp", sizeof(mat4), 0, TYP_UNIFORM, TYP_SHADER_VS));
  subpass->vec_pipeline.push_back(pipeline);

  //---------------------------
  renderpass->vec_subpass.push_back(subpass);
}

//Draw function
void Scene::draw_scene(vk::structure::Subpass* subpass){
  //---------------------------

  vk_viewport->cmd_viewport(subpass->command_buffer->command);
  this->cmd_draw_point(subpass);
  this->cmd_draw_line(subpass);
  this->cmd_draw_triangle(subpass);

  //---------------------------
}
void Scene::cmd_draw_point(vk::structure::Subpass* subpass){
  list<vk::structure::Object*> list_data = vk_graphical->get_list_data();
  //---------------------------

  vk::structure::Pipeline* pipeline = subpass->get_pipeline_byName("point");
  vk_pipeline->cmd_bind_pipeline(subpass->command_buffer->command, pipeline);

  //Bind and draw vertex buffers
  for(int i=0; i<list_data.size(); i++){
    vk::structure::Object* vk_object =  *next(list_data.begin(), i);
    bool is_visible = vk_object->data->is_visible;
    bool has_topology = vk_object->data->draw_type_name == "point";
    bool has_xyz = vk_object->data->point.xyz.size() != 0;
    bool has_rgb = vk_object->data->point.rgb.size() != 0;
    bool same_length = vk_object->data->point.rgb.size() == vk_object->data->point.xyz.size();

    if(is_visible && has_topology && has_xyz && has_rgb){
      vk_uniform->update_uniform("mvp", &vk_object->binding, vk_object->pose->mvp);
      vk_uniform->update_uniform("point_size", &vk_object->binding, vk_object->data->point.width);

      vk_descriptor->cmd_bind_descriptor(subpass->command_buffer->command, pipeline, vk_object->binding.descriptor.set);
      vk_drawing->cmd_draw_data(subpass->command_buffer->command, vk_object);
    }
  }

  //---------------------------
}
void Scene::cmd_draw_line(vk::structure::Subpass* subpass){
  list<vk::structure::Object*> list_data = vk_graphical->get_list_data();
  //---------------------------

  vk::structure::Pipeline* pipeline = subpass->get_pipeline_byName("line");
  vk_pipeline->cmd_bind_pipeline(subpass->command_buffer->command, pipeline);

  //Bind and draw vertex buffers
  for(int i=0; i<list_data.size(); i++){
    vk::structure::Object* vk_object =  *next(list_data.begin(), i);
    bool& is_visible = vk_object->data->is_visible;
    bool has_topology = vk_object->data->draw_type_name == "line";
    bool has_xyz = vk_object->data->point.xyz.size() != 0;
    bool has_rgb = vk_object->data->point.rgb.size() != 0;
    bool same_length = vk_object->data->point.rgb.size() == vk_object->data->point.xyz.size();

    if(is_visible && has_topology && has_xyz && has_rgb && same_length){
      vk_uniform->update_uniform("mvp", &vk_object->binding, vk_object->pose->mvp);

      vk_descriptor->cmd_bind_descriptor(subpass->command_buffer->command, pipeline, vk_object->binding.descriptor.set);
      vk_drawing->cmd_line_with(subpass->command_buffer->command, vk_object);
      vk_drawing->cmd_draw_data(subpass->command_buffer->command, vk_object);
    }
  }

  //---------------------------
}
void Scene::cmd_draw_triangle(vk::structure::Subpass* subpass){
  list<vk::structure::Object*> list_data = vk_graphical->get_list_data();
  //---------------------------

  vk::structure::Pipeline* pipeline = subpass->get_pipeline_byName("triangle");
  vk_pipeline->cmd_bind_pipeline(subpass->command_buffer->command, pipeline);

  //Bind and draw vertex buffers
  for(int i=0; i<list_data.size(); i++){
    vk::structure::Object* vk_object =  *next(list_data.begin(), i);
    bool& is_visible = vk_object->data->is_visible;
    bool has_topology = vk_object->data->draw_type_name == "triangle";
    bool has_xyz = vk_object->data->point.xyz.size() != 0;
    bool has_rgb = vk_object->data->point.rgb.size() != 0;
    bool same_length = vk_object->data->point.rgb.size() == vk_object->data->point.xyz.size();

    if(is_visible && has_topology && has_xyz && has_rgb && same_length){
      vk_uniform->update_uniform("mvp", &vk_object->binding, vk_object->pose->mvp);

      vk_descriptor->cmd_bind_descriptor(subpass->command_buffer->command, pipeline, vk_object->binding.descriptor.set);
      vk_drawing->cmd_line_with(subpass->command_buffer->command, vk_object);
      vk_drawing->cmd_draw_data(subpass->command_buffer->command, vk_object);
    }
  }

  //---------------------------
}

}
