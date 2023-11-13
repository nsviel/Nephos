#include "RND_engine.h"
#include "RND_control.h"

#include <GUI.h>
#include <image/IconsFontAwesome5.h>
#include <RES_gpu/GUI_image.h>

#include <Engine.h>
#include <Vulkan.h>
#include <VK_main/VK_imgui.h>

//Constructor / Destructor
RND_engine::RND_engine(GUI* gui){
  //---------------------------

  this->gui_control = new RND_control(gui);
  this->gui_image = new GUI_image(gui);

  Engine* engine = gui->get_engine();
  Vulkan* eng_vulkan = engine->get_eng_vulkan();
  this->vk_imgui = eng_vulkan->get_vk_imgui();

  //---------------------------
}
RND_engine::~RND_engine(){}

//Main function
void RND_engine::design_panel(){
  //---------------------------

  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
  ImGui::SetNextWindowSizeConstraints(ImVec2(100, 100), ImVec2(500, 500));
  if(ImGui::Begin("Engine_panel", NULL)){
    this->engine_window();
    this->engine_control();
    ImGui::End();
  }
  ImGui::PopStyleVar();

  //---------------------------
}

//Subfunction
void RND_engine::engine_window(){
  //---------------------------
  //IL faut faire passer un staging buffer entre les contextes
//say("----");
  //truct_image image;



gui_image->draw_image("output.png");  Struct_image* image_engine = vk_imgui->engine_texture();
//  gui_image->draw_image("../media/vulkano.jpg");


/*
  image.format = VK_FORMAT_R8G8B8A8_SRGB;
image.tiling = VK_IMAGE_TILING_OPTIMAL;
image.aspect = VK_IMAGE_ASPECT_COLOR_BIT;
image.usage = TYP_IMAGE_USAGE_TRANSFERT | TYP_IMAGE_USAGE_SAMPLER;
image.properties = TYP_MEMORY_GPU;
image.width = image_engine->width;
image.height = image_engine->height;
vk_image->create_image(&image);
vk_color->create_color_attachment(&image);
  //image.image = image_engine->image;







  say(image.image);
  Struct_renderpass* renderpass = struct_vulkan->render.get_renderpass_byName("gui");
  Struct_subpass* subpass = renderpass->vec_subpass[0];


  //vk_command->image_layout_transition_single(image_engine, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL);
  vk_command->image_layout_transition_single(&image, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);

  // Record VkCmdCopyImage from source image to destination image or staging buffer
  VkImageCopy copyRegion = {
      .srcSubresource = {VK_IMAGE_ASPECT_COLOR_BIT, 0, 0, 1},
      .srcOffset = {0, 0, 0},
      .dstSubresource = {VK_IMAGE_ASPECT_COLOR_BIT, 0, 0, 1},
      .dstOffset = {0, 0, 0},
      .extent = {image_engine->width, image_engine->height, 1}
  };
  vkCmdCopyImage(subpass->command_buffer, image_engine->image, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, image.image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &copyRegion);

  //vk_command->image_layout_transition_single(image_engine, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, VK_IMAGE_LAYOUT_GENERAL);
  vk_command->image_layout_transition_single(&image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_GENERAL);




/*
//Create stagging buffer
VkBuffer staging_buffer;
VkDeviceMemory staging_mem;
VkDeviceSize tex_size = image_engine->width * image_engine->height * 4;
vk_buffer->create_gpu_buffer(tex_size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, staging_buffer);
vk_buffer->bind_buffer_memory(TYP_MEMORY_SHARED_CPU_GPU, staging_buffer, staging_mem);

// Create a command buffer for the copy operation
Struct_renderpass* renderpass = struct_vulkan->render.get_renderpass_byName("gui");
Struct_subpass* subpass = renderpass->vec_subpass[0];





// Begin the command buffer recording
VkCommandBufferBeginInfo beginInfo = {};
beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

//vkResetCommandBuffer(subpass->command_buffer, 0);
vkBeginCommandBuffer(subpass->command_buffer, &beginInfo);

VkImageMemoryBarrier imageMemoryBarrier = {};
imageMemoryBarrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
imageMemoryBarrier.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
imageMemoryBarrier.newLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
imageMemoryBarrier.srcAccessMask = 0;
imageMemoryBarrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
imageMemoryBarrier.image = image.image;
imageMemoryBarrier.subresourceRange = {VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1};

vkCmdPipelineBarrier(
    subpass->command_buffer,
    VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
    VK_PIPELINE_STAGE_TRANSFER_BIT,
    0,
    0, nullptr,
    0, nullptr,
    1, &imageMemoryBarrier
);



// Specify the copy region
VkBufferImageCopy copyRegion = {};
copyRegion.bufferOffset = 0;
copyRegion.bufferRowLength = 0;
copyRegion.bufferImageHeight = 0;
copyRegion.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
copyRegion.imageSubresource.mipLevel = 0;
copyRegion.imageSubresource.baseArrayLayer = 0;
copyRegion.imageSubresource.layerCount = 1;
copyRegion.imageOffset = {0, 0, 0};
copyRegion.imageExtent = {image_engine->width, image_engine->height, 1}; // Adjust width and height based on your image size

// Perform the buffer-to-image copy
vkCmdCopyBufferToImage(subpass->command_buffer, staging_buffer, image.image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &copyRegion);


// Transition the image layout to VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL
VkImageMemoryBarrier postCopyBarrier = {};
postCopyBarrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
postCopyBarrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
postCopyBarrier.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
postCopyBarrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
postCopyBarrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
postCopyBarrier.image = image.image;
postCopyBarrier.subresourceRange = {VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1};

vkCmdPipelineBarrier(
    subpass->command_buffer,
    VK_PIPELINE_STAGE_TRANSFER_BIT,
    VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
    0,
    0, nullptr,
    0, nullptr,
    1, &postCopyBarrier
);


// End the command buffer recording
vkEndCommandBuffer(subpass->command_buffer);

// Submit the command buffer for execution
VkSubmitInfo submitInfo = {};
submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
submitInfo.commandBufferCount = 1;
submitInfo.pCommandBuffers = &subpass->command_buffer;

vkQueueSubmit(struct_vulkan->device.queue_graphics, 1, &submitInfo, VK_NULL_HANDLE);
vkQueueWaitIdle(struct_vulkan->device.queue_graphics); // Wait for the copy operation to complete



VkDescriptorSet descriptor = ImGui_ImplVulkan_AddTexture(image.sampler, image.view, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
ImTextureID texture = reinterpret_cast<ImTextureID>(descriptor);
if(texture == 0) return;
ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
ImGui::Image(texture, ImVec2{viewportPanelSize.x, viewportPanelSize.y});



/*
  Struct_renderpass* renderpass = struct_vulkan->render.get_renderpass_byName("gui");
  Struct_subpass* subpass = renderpass->vec_subpass[0];
  vk_command->start_command_buffer_once(subpass->command_buffer);

  VkImageMemoryBarrier barrier = {};
  barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
  barrier.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;                    // Initial layout
  barrier.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;    // Target layout
  barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
  barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
  barrier.image = image.image;
  barrier.subresourceRange = {VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1};
  barrier.srcAccessMask = 0; // Memory access flags for the source layout
  barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT; // Memory access flags for the target layout

  vkCmdPipelineBarrier(subpass->command_buffer,
                       VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,    // Source pipeline stage
                       VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT, // Target pipeline stage
                       0,                                    // Dependency flags
                       0, nullptr, 0, nullptr, 1, &barrier);


  vk_command->stop_command_buffer(subpass->command_buffer);


  VkDescriptorSet descriptor = ImGui_ImplVulkan_AddTexture(image.sampler, image.view, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
  ImTextureID texture = reinterpret_cast<ImTextureID>(descriptor);
  if(texture == 0) return;
  ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
  ImGui::Image(texture, ImVec2{viewportPanelSize.x, viewportPanelSize.y});
*/

  //---------------------------
}

void RND_engine::engine_control(){
  //---------------------------

  if(ImGui::IsItemHovered()){
    ImVec2 windowPos = ImGui::GetWindowPos();
    ImVec2 windowSize = ImGui::GetWindowSize();
    ImVec2 center = ImVec2(windowPos.x + windowSize.x * 0.5f, windowPos.y + windowSize.y * 0.5f);

    gui_control->run_control(center);
  }

  //---------------------------
}
