#pragma once

#include <imgui/core/imgui.h>
#include <imgui/core/imgui_impl_glfw.h>
#include <imgui/core/imgui_internal.h>
#include <imgui/widget/imspinner.h>


namespace ImGui{

bool Spinner_variable(const char* label, const ImU32& color);
void Spinner_cicle(const char* label, ImVec4 color_vec4);
void Spinner_simple();

}
