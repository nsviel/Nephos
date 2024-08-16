#include "Misc.h"


namespace ImGui{

void Check_on(){
  bool value = true;
  //---------------------------

  ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0, 0, 0, 0)); // Transparent background
  ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4(0, 0, 0, 0)); // Transparent background on hover
  ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImVec4(0, 0, 0, 0)); // Transparent background when active
  ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0, 0, 0, 0)); // Transparent border
  ImGui::PushStyleColor(ImGuiCol_BorderShadow, ImVec4(0, 0, 0, 0)); // Transparent border shadow
  ImGui::PushStyleColor(ImGuiCol_CheckMark, ImVec4(0, 1, 0, 1)); // Green check mark
  ImGui::Checkbox("##Check_on", &value);
  ImGui::PopStyleColor(6);

  //---------------------------
}
void Cross(ImVec4 color){
  //---------------------------

  ImGuiWindow* window = ImGui::GetCurrentWindow();
  if(window->SkipItems) return;

  ImGuiContext& g = *GImGui;
  const ImGuiStyle& style = g.Style;
  const ImGuiID id = window->GetID("##CrossRed"); // Use a constant ID for the red cross
  const ImVec2 label_size = ImGui::CalcTextSize("OK", NULL, true);

  ImVec2 pos = window->DC.CursorPos;
  ImVec2 size = ImVec2(label_size.y + style.FramePadding.y * 2, label_size.y + style.FramePadding.y * 2);
  const ImRect check_bb(pos, ImVec2(pos.x + size.x, pos.y + size.y));

  ImGui::ItemSize(check_bb, style.FramePadding.y);
  if(!ImGui::ItemAdd(check_bb, id)) return;

  // Draw the red cross mark
  ImU32 col = ImGui::ColorConvertFloat4ToU32(color);
  ImDrawList* draw_list = ImGui::GetWindowDrawList();
  ImVec2 cross_size(size.x * 0.5f, size.y * 0.5f); // Adjust size as needed
  ImVec2 cross_pos(pos.x + size.x * 0.25f, pos.y + size.y * 0.25f); // Center the cross
  draw_list->AddLine(cross_pos, ImVec2(cross_pos.x + cross_size.x, cross_pos.y + cross_size.y), col, 2.0f);
  draw_list->AddLine(ImVec2(cross_pos.x, cross_pos.y + cross_size.y), ImVec2(cross_pos.x + cross_size.x, cross_pos.y), col, 2.0f);

  //---------------------------
}
void Colorbar(ImVec2 range){
  //---------------------------

  // Adjust position and size according to your layout
  ImVec2 position = ImGui::GetCursorScreenPos();
  ImVec2 size(200, 20); // Example size of the colorbar

  ImGuiWindow* window = ImGui::GetCurrentWindow();
  ImDrawList* draw_list = ImGui::GetWindowDrawList();

  const int num_colors = 256; // Number of color segments
  float segment_width = size.x / num_colors;

  for (int i = 0; i < num_colors; ++i){
    ImVec2 rect_min = ImVec2(position.x + i * segment_width, position.y);
    ImVec2 rect_max = ImVec2(position.x + (i + 1) * segment_width, position.y + size.y);

    // Example: Create a gradient from blue to red
    ImVec4 color = ImVec4(static_cast<float>(i) / num_colors, 0.0f, 1.0f - static_cast<float>(i) / num_colors, 1.0f);

    draw_list->AddRectFilled(rect_min, rect_max, ImGui::ColorConvertFloat4ToU32(color));
  }
  ImGui::SetCursorPosY(ImGui::GetCursorPosY() + size.y + 20);

  //---------------------------
}





}
