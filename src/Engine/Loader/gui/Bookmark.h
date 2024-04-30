#pragma once

#include <Loader/src/Loader/Item.h>
#include <imgui/core/imgui.h>
#include <vector>
#include <string>

namespace ldr{class Item;}


namespace ldr::gui{

struct Bookmark{
  //---------------------------

  ldr::Item item;

  //Sorting stuff
  static const ImGuiTableSortSpecs* current_sort_specs;
  static bool compare_with_specs(const ldr::gui::Bookmark& a, const ldr::gui::Bookmark& b);
  static void sort_item_by_specs(ImGuiTableSortSpecs* sort_specs, std::vector<ldr::gui::Bookmark>& vec_item);

  //---------------------------
};

}
