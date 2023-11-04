#include "DR_scene.h"

#include <VK_command/VK_submit.h>
#include <VK_engine.h>
#include <VK_struct/struct_vulkan.h>
#include <VK_command/VK_command.h>
#include <VK_presentation/VK_canvas.h>
#include <VK_binding/VK_descriptor.h>
#include <VK_camera/VK_camera.h>
#include <VK_camera/VK_viewport.h>
#include <VK_binding/VK_uniform.h>
#include <VK_data/VK_data.h>
#include <VK_pipeline/VK_pipeline.h>
#include <VK_drawing/VK_drawing.h>


//Constructor / Destructor
DR_scene::DR_scene(VK_engine* vk_engine){
  //---------------------------

  this->vk_engine = vk_engine;
  this->struct_vulkan = vk_engine->get_struct_vulkan();
  this->vk_command = vk_engine->get_vk_command();
  this->vk_descriptor = vk_engine->get_vk_descriptor();
  this->vk_submit = vk_engine->get_vk_submit();
  this->vk_uniform = vk_engine->get_vk_uniform();
  this->vk_camera = new VK_camera(vk_engine);
  this->vk_data = vk_engine->get_vk_data();
  this->vk_viewport = vk_engine->get_vk_viewport();
  this->vk_pipeline = vk_engine->get_vk_pipeline();
  this->vk_drawing = vk_engine->get_vk_drawing();

  //---------------------------
}
DR_scene::~DR_scene(){}

//Draw frame parts
void DR_scene::draw_scene(Struct_renderpass* renderpass){
  timer_time t1 = timer.start_t();
  //---------------------------

  this->record_command(renderpass);
  this->submit_command(renderpass);

  //---------------------------
  struct_vulkan->time.renderpass_scene.push_back(timer.stop_ms(t1));
}

//Subfunction
void DR_scene::record_command(Struct_renderpass* renderpass){
  Frame* frame = renderpass->get_rendering_frame();
  //---------------------------

  vk_command->start_render_pass(renderpass, frame, false);
  vk_viewport->cmd_viewport(renderpass);
  this->cmd_draw_scene(renderpass);
  this->cmd_draw_glyph(renderpass);
  vk_command->stop_render_pass(renderpass);

  //---------------------------
}
void DR_scene::submit_command(Struct_renderpass* renderpass){
  //---------------------------

  Frame* frame_swap = struct_vulkan->swapchain.get_frame_inflight();
  renderpass->semaphore_to_wait = frame_swap->semaphore_image_ready;
  renderpass->semaphore_to_run = frame_swap->semaphore_scene_ready;
  renderpass->fence = VK_NULL_HANDLE;
  vk_submit->submit_graphics_command(renderpass);

  //---------------------------
}

//Command function
void DR_scene::cmd_draw_scene(Struct_renderpass* renderpass){
  list<Struct_data*> list_data_scene = vk_data->get_list_data_scene();
  //---------------------------

  vk_pipeline->cmd_bind_pipeline(renderpass, "point");

  //Bind and draw vertex buffers
  for(int i=0; i<list_data_scene.size(); i++){
    Struct_data* data =  *next(list_data_scene.begin(),i);

    if(data->object->draw_type_name == "point" && data->object->is_visible){
      vk_camera->compute_mvp(data->object);
      vk_uniform->update_uniform_mat4("mvp", &data->binding, data->object->mvp);
      vk_uniform->update_uniform_int("point_size", &data->binding, data->object->draw_point_size);

      vk_descriptor->cmd_bind_descriptor(renderpass, "point", data->binding.descriptor.set);
      vk_drawing->cmd_draw_data(renderpass, data);
    }
  }

  //---------------------------
}
void DR_scene::cmd_draw_glyph(Struct_renderpass* renderpass){
  list<Struct_data*> list_data_glyph = vk_data->get_list_data_glyph();
  //---------------------------

  vk_pipeline->cmd_bind_pipeline(renderpass, "line");

  //Bind and draw vertex buffers
  for(int i=0; i<list_data_glyph.size(); i++){
    Struct_data* data =  *next(list_data_glyph.begin(),i);

    if(data->object->draw_type_name == "line" && data->object->is_visible){
      vk_camera->compute_mvp(data->object);
      vk_uniform->update_uniform_mat4("mvp", &data->binding, data->object->mvp);

      vk_descriptor->cmd_bind_descriptor(renderpass, "line", data->binding.descriptor.set);
      vk_drawing->cmd_line_with(renderpass, data);
      vk_drawing->cmd_draw_data(renderpass, data);
    }
  }

  //---------------------------
}
