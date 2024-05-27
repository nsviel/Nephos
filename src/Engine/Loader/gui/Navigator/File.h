#pragma once

#include <Loader/src/Bookmark/Item.h>
#include <imgui/core/imgui.h>
#include <vector>
#include <string>

namespace ldr::bookmark{class Item;}


namespace ldr::gui{

struct File{
  //---------------------------

  ldr::bookmark::Item item;

  //Sorting stuff
  static const ImGuiTableSortSpecs* current_sort_specs;
  static bool compare_with_specs(const ldr::gui::File& a, const ldr::gui::File& b);
  static void sort_file_by_specs(ImGuiTableSortSpecs* sort_specs, std::vector<ldr::gui::File>& vec_file);

  //---------------------------
};

}
