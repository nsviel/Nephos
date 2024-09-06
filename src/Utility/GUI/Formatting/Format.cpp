#include "Format.h"

#include <imgui.h>
#include <sstream>


namespace utl::gui{

std::string format_title(const std::string& name, int totalWidth) {
  //---------------------------

  // Calculate the width of the name using ImGui
  ImGuiIO& io = ImGui::GetIO();
  float nameWidth = ImGui::CalcTextSize(name.c_str()).x;

  // Determine the number of dashes needed to fit the total width
  float availableWidth = totalWidth - nameWidth;
  if (availableWidth < 0) {
      // If totalWidth is smaller than the name width, return the name itself
      return name;
  }

  int dashLength = static_cast<int>(availableWidth / 2);

  std::ostringstream ss;
  ss << std::string(dashLength, '-') << " " << name << " " << std::string(dashLength, '-');

  // Adjust length to ensure it fits the totalWidth, accounting for spaces and dashes
  float currentLength = ImGui::CalcTextSize(ss.str().c_str()).x;
  if (currentLength < totalWidth) {
      ss << std::string(static_cast<int>(totalWidth - currentLength), '-');
  }

  //---------------------------
  return ss.str();
}

}
