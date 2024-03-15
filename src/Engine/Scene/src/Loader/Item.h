#pragma once

#include <Utility/Specific/common.h>


namespace eng::loader{

enum ColumnID{
  NAME,
  WEIGHT,
  FORMAT
};

enum type{
  FOLDER = 0,
  FILE = 1,
};

struct Item{
  //---------------------------

  //Item stuff
  string path;
  string name;
  string type;
  string format;
  string size;
  string icon;
  ImVec4 color_icon;
  ImVec4 color_text;
  bool is_supressible = true;
  float weight;
  int ID;

  //Sorting stuff
  static const ImGuiTableSortSpecs* current_sort_specs;
  static bool compare_with_specs(const Item& a, const Item& b);
  static void sort_item_by_specs(ImGuiTableSortSpecs* sort_specs, std::vector<Item>& vec_item);

  //---------------------------
};

}
