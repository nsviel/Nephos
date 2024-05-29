#pragma once

#include <imgui/core/imgui.h>
#include <imgui/core/imgui_impl_glfw.h>
#include <imgui/core/imgui_internal.h>


namespace ImGui{

bool buffering_bar(const char* label, float value,  const ImVec2& size_arg, const ImU32& bg_col, const ImU32& fg_col);
void loading_indicator(const char* label, const float indicator_radius, const ImVec4& main_color, const ImVec4& backdrop_color, const int circle_count, const float speed);
bool spinner(const char* label, float radius, int thickness, const ImU32& color);
void spinner_simple();

}
