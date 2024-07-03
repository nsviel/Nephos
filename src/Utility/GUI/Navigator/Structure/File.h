#pragma once

#include <Utility/GUI/Navigator/Structure/Item.h>
#include <imgui/core/imgui.h>
#include <vector>
#include <string>

namespace utl::gui::navigator{class Item;}


namespace utl::gui::navigator{

struct File{
  //---------------------------

  utl::gui::navigator::Item item;

  //Sorting stuff
  static const ImGuiTableSortSpecs* current_sort_specs;
  static bool compare_with_specs(const utl::gui::navigator::File& a, const utl::gui::navigator::File& b);
  static void sort_file_by_specs(ImGuiTableSortSpecs* sort_specs, std::vector<utl::gui::navigator::File>& vec_file);

  //---------------------------
};

}
