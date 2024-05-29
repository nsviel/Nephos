#pragma once

#include <imgui/core/imgui.h>
#include <imgui/core/imgui_impl_glfw.h>
#include <imgui/core/imgui_internal.h>
#include <imgui/widget/imspinner.h>
#include <Utility/GUI/Widget/Spinner.h>
#include <string>


namespace ImGui{

void Validation_state(std::string label, bool state);
void Check_on();
void Cross_red();

}
